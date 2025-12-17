import os
import tkinter as tk
import numpy as np
import torch
from PIL import Image, ImageDraw
from TTQ_CNNforMNIST import TTQ_CNN, TTQConv2d, TTQLinear

def load_ternary_state(model, path, device):
    state = torch.load(path, map_location=device, weights_only=False)
    for name, module in model.named_modules():
        if isinstance(module, (TTQConv2d, TTQLinear)):
            w_key = f"{name}.weight_ternary"
            a_key = f"{name}.alpha"
            b_key = f"{name}.bias"
            if w_key in state and a_key in state:
                ternary = state[w_key].to(device).float()
                alpha = state[a_key].to(device).float()
                module.weight.data = alpha * ternary
                module.alpha.data = alpha
            if module.bias is not None and b_key in state:
                module.bias.data = state[b_key].to(device)


# 加载最佳模型
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = TTQ_CNN().to(device)

ternary_path = 'model/best_model_ternary.pth'
if os.path.exists(ternary_path):
    load_ternary_state(model, ternary_path, device)
    print("Loaded ternary model state.")
else:
    model.load_state_dict(torch.load('model/best_model.pth', map_location=device, weights_only=False))
    print("Loaded full precision model state.")

model.eval()

# 创建主窗口
root = tk.Tk()
root.title("Handwritten Digit Recognition")

# 创建画布
canvas_width = 280
canvas_height = 280
canvas = tk.Canvas(root, width=canvas_width, height=canvas_height, bg="white")
canvas.pack()

# 初始化绘图
image = Image.new("L", (canvas_width, canvas_height), 0)
draw = ImageDraw.Draw(image)
last_x, last_y = None, None

# 鼠标按下事件处理函数
def on_mouse_down(event):
    global last_x, last_y
    last_x, last_y = event.x, event.y

# 鼠标移动事件处理函数
def on_mouse_move(event):
    global last_x, last_y
    if last_x and last_y:
        canvas.create_line((last_x, last_y, event.x, event.y), fill="black", width=10)
        draw.line((last_x, last_y, event.x, event.y), fill=255, width=10)
    last_x, last_y = event.x, event.y

# 鼠标释放事件处理函数
def on_mouse_up(event):
    global last_x, last_y
    last_x, last_y = None, None

# 绑定鼠标事件
canvas.bind("<ButtonPress-1>", on_mouse_down)
canvas.bind("<B1-Motion>", on_mouse_move)
canvas.bind("<ButtonRelease-1>", on_mouse_up)

# 识别按钮
def recognize():
    global image
    img = image.resize((28, 28), Image.LANCZOS)
    img_array = np.array(img) / 255.0
    img_tensor = torch.tensor(img_array, dtype=torch.float32).view(1, 1, 28, 28).to(device)

    with torch.no_grad():
        output = model(img_tensor)
        probabilities = torch.softmax(output, dim=1).cpu().numpy()[0]
        predicted = int(np.argmax(probabilities))

    result_label.config(text=f"Result: {predicted}")
    confidence_text = " ".join([f"{i}: {prob:.2f}\n" for i, prob in enumerate(probabilities)])
    print(f"Confidence:\n {confidence_text}")

    return predicted

# 正确按钮
correct_count = 0
total_count = 0

def mark_correct():
    global correct_count, total_count
    total_count += 1
    correct_count += 1
    accuracy = correct_count / total_count * 100
    correct_label.config(text=f"Accuracy: {accuracy:.1f}%")
    clear_canvas()

# 错误按钮
def mark_incorrect():
    global total_count
    total_count += 1
    if total_count > 0:
        accuracy = correct_count / total_count * 100
    else:
        accuracy = 0
    correct_label.config(text=f"Accuracy: {accuracy:.1f}%")
    clear_canvas()

def clear_canvas():
    global last_x, last_y, image, draw
    canvas.delete("all")
    image = Image.new("L", (canvas_width, canvas_height), 0)
    draw = ImageDraw.Draw(image)
    last_x, last_y = None, None
    result_label.config(text="Result: ")
    accuracy = correct_count / total_count * 100
    correct_label.config(text=f"Accuracy: {accuracy:.1f}%")

# 按钮布局
button_frame1 = tk.Frame(root)
button_frame1.pack()
recognize_button = tk.Button(button_frame1, text="Recognize", command=recognize)
recognize_button.pack(side=tk.LEFT, padx=5)
clear_button = tk.Button(button_frame1, text="Clear", command=clear_canvas)
clear_button.pack(side=tk.LEFT, padx=5)

button_frame2 = tk.Frame(root)
button_frame2.pack()
correct_button = tk.Button(button_frame2, text="Correct", command=mark_correct)
correct_button.pack(side=tk.LEFT, padx=5)
incorrect_button = tk.Button(button_frame2, text="Wrong", command=mark_incorrect)
incorrect_button.pack(side=tk.LEFT, padx=5)

# 结果显示
result_label = tk.Label(root, text="Result: ")
result_label.pack()

correct_label = tk.Label(root, text="Accuracy: 0.0%")
correct_label.pack()

# 运行主循环
root.mainloop()