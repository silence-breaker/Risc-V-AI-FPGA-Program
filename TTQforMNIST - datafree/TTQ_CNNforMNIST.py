import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.autograd import Function
from torchvision import datasets, transforms
import matplotlib.pyplot as plt
import numpy as np


device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# 定义超参数 
input_size = 28  #图像的总尺寸28*28
num_classes = 10  #标签的种类数
num_epochs = 5  #量化训练轮次
batch_size = 64  #一个撮（批次）的大小，64张图片
lr = 0.001  #学习率
t = 1.1  #阈值系数

# 训练集
train_dataset = datasets.MNIST(
    root='./data',
    train=True,
    transform=transforms.ToTensor(),
    download=True,
)

# 测试集
test_dataset = datasets.MNIST(
    root='./data',
    train=False,
    transform=transforms.ToTensor(),
)

# 构建batch数据
train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                           batch_size=batch_size,
                                           shuffle=True)
test_loader = torch.utils.data.DataLoader(dataset=test_dataset,
                                          batch_size=batch_size,
                                          shuffle=True)

class Ternarize(Function):
    @staticmethod
    def forward(ctx, w, delta, scale):
        ctx.save_for_backward(w, delta, scale)
        w_out = torch.zeros_like(w)
        w_out = torch.where(w > delta, scale, w_out)
        w_out = torch.where(w < -delta, -scale, w_out)
        return w_out

    @staticmethod
    def backward(ctx, grad_output):
        w, delta, scale = ctx.saved_tensors
        mask = (w.abs() <= delta).float()
        grad_w = grad_output * mask  # STE：仅在阈值附近传梯度
        grad_delta = None
        grad_scale = (grad_output * torch.sign(w) * (w.abs() > delta).float()).sum()
        return grad_w, grad_delta, grad_scale


class TTQConv2d(nn.Conv2d):
    def __init__(self, *args, init_scale=0.7, t=t, **kwargs):
        super().__init__(*args, **kwargs)
        self.t = t  # 阈值系数: delta = t * mean(|w|)
        self.alpha = nn.Parameter(torch.tensor(init_scale))

    def _ternary_weight(self):
        delta = self.t * self.weight.abs().mean()
        return Ternarize.apply(self.weight, delta, self.alpha)

    def forward(self, x):
        w_q = self._ternary_weight()
        return F.conv2d(x, w_q, self.bias, self.stride, self.padding, self.dilation, self.groups)


class TTQLinear(nn.Linear):
    def __init__(self, *args, init_scale=0.7, t=t, **kwargs):
        super().__init__(*args, **kwargs)
        self.t = t
        self.alpha = nn.Parameter(torch.tensor(init_scale))

    def _ternary_weight(self):
        delta = self.t * self.weight.abs().mean()
        return Ternarize.apply(self.weight, delta, self.alpha)

    def forward(self, x):
        w_q = self._ternary_weight()
        return F.linear(x, w_q, self.bias)


class TTQ_CNN(nn.Module):
    def __init__(self):
        super(TTQ_CNN, self).__init__()
        self.conv1 = nn.Sequential(
            TTQConv2d(1, 16, 5, stride=1, padding=2),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2),
        )
        self.conv2 = nn.Sequential(
            TTQConv2d(16, 32, 5, stride=1, padding=2),
            nn.ReLU(),
            nn.MaxPool2d(2),
        )
        self.out = TTQLinear(32 * 7 * 7, 10)

    def forward(self, x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = x.view(x.size(0), -1)
        return self.out(x)
    @staticmethod
    def accuracy(predictions, labels):
        pred = predictions.argmax(dim=1)
        rights = pred.eq(labels).sum().detach().cpu()
        return rights, len(labels)


net = TTQ_CNN().to(device)

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(net.parameters(), lr=lr)


def export_ternary_state(model, path):
    export = {'format': 'int8_ternary_with_alpha'}
    for name, module in model.named_modules():
        if isinstance(module, (TTQConv2d, TTQLinear)):
            weight = module.weight.data
            delta = module.t * weight.abs().mean()
            ternary = torch.zeros_like(weight, dtype=torch.int8)
            ternary[weight > delta] = 1
            ternary[weight < -delta] = -1

            export[f"{name}.weight_ternary"] = ternary.cpu()
            export[f"{name}.alpha"] = module.alpha.data.cpu()
            if module.bias is not None:
                export[f"{name}.bias"] = module.bias.data.cpu()

    torch.save(export, path)

def main():
    best_accuracy = 0

    for epoch in range(num_epochs):
        train_rights = []

        for batch_idx, (data, target) in enumerate(train_loader):
            net.train()
            data, target = data.to(device), target.to(device)

            output = net(data)
            loss = criterion(output, target)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            right = TTQ_CNN.accuracy(output, target)
            train_rights.append(right)

            if batch_idx % 100 == 0:
                net.eval()
                val_rights = []
                with torch.no_grad():
                    for (val_data, val_target) in test_loader:
                        val_data, val_target = val_data.to(device), val_target.to(device)
                        val_output = net(val_data)
                        right = TTQ_CNN.accuracy(val_output, val_target)
                        val_rights.append(right)

                train_correct = sum([tup[0] for tup in train_rights]).item()
                train_total = sum([tup[1] for tup in train_rights])
                val_correct = sum([tup[0] for tup in val_rights]).item()
                val_total = sum([tup[1] for tup in val_rights])

                train_acc = 100.0 * train_correct / train_total
                val_acc = 100.0 * val_correct / val_total

                print('当前epoch: {} [{}/{} ({:.0f}%)]\t损失: {:.6f}\t训练集准确率: {:.2f}%\t测试集正确率: {:.2f}%'.format(
                    epoch, batch_idx * batch_size, len(train_loader.dataset),
                    100. * batch_idx / len(train_loader),
                    loss.item(),
                    train_acc,
                    val_acc))

                if val_acc > best_accuracy:
                    best_accuracy = val_acc
                    torch.save(net.state_dict(), 'model/best_model.pth')
                    export_ternary_state(net, 'model/best_model_ternary.pth')

    print(f'Done! Best accuracy: {best_accuracy:.2f}%')
    torch.save(net.state_dict(), 'model/latest_model.pth')
    export_ternary_state(net, 'model/latest_model_ternary.pth')

if __name__ == '__main__':
    main()