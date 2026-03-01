仅做**无板卡纯软件仿真**时，**无需进行交叉环境编译**（交叉编译仅为生成板载可执行文件所用），全程基于**Win10 上位机的 Icraft v3.33.1**环境即可完成从模型下载、格式转换、全流程编译到 Host 后端（CPU）仿真运行、结果分析的所有操作，步骤完整且无硬件依赖，以下是**可直接落地的纯仿真全流程**，每一步都包含具体操作命令和配置要求：

### 前提环境确认（已完成可跳过）

1. Win10 系统已安装**Icraft v3.33.1**（含`Icraft_Setup_v3.33.1.exe`和`CustomOp_Setup_v3.33.1.exe`，安装路径`C:\Icraft`）；
2. 已配置**Python3.8**环境，且安装了 Icraft python 包（`icraft-3.33.1-cp38-none-win_amd64.whl`）；
3. 已安装**Git**环境（用于克隆示例工程，版本≥2.42.0）；
4. 关闭电脑防火墙 / 杀毒软件（避免 Icraft 编译 / 仿真时文件读写、网络权限受限）；
5. 所有操作均在**管理员权限的 CMD**中执行（Win10 搜索 CMD→右键→以管理员身份运行）。

## 步骤 1：下载 modelzoo_yolov5_psin 示例工程（以 YOLOv5s 为例，官方验证过的仿真工程）

该工程为复旦微官方提供的适配 30TAI 的示例，包含模型文件、编译配置、测试图片，直接克隆即可使用，无需额外配置。

1. 进入 Icraft 目录，创建 modelzoo 文件夹并进入：   
```
    cd C:\Icraft
    mkdir modelzoo && cd modelzoo
```
2. 初始化 Git LFS（因工程包含模型权重文件，需 LFS 支持）：
```
    git lfs install
```
3. 克隆指定 v3.33.1 版本的 YOLOv5 7.0 工程：
    ```
    git clone -bv3.33.1 https://www.modelscope.cn/AIBS/yolov5_7.0.git
    ```
4. 进入工程目录，确认文件完整性：
    ```
    cd yolov5_7.0
    ```
    工程内包含`1_save.py`（模型导出脚本）、`icraft`文件夹（编译配置）、`images`文件夹（测试图片），缺一则克隆失败，需重新执行。
## 步骤 2：将 Pytorch 模型转为 Icraft 支持的 Torchscript 格式（编译输入源）

官方工程提供的是 Pytorch 原生模型，需导出为**Torchscript 格式（.pt）** 才能被 Icraft 解析编译，直接运行工程内的导出脚本即可，无需修改代码。

1. 进入工程根目录（确保当前路径有`1_save.py`）：
```
 cd C:\Icraft\modelzoo\yolov5_7.0
```   
2. 运行导出脚本，生成 Torchscript 模型：
```
    python 1_save.py
```

这个时候命令框出现以下的报错：
```
   command: 'd:\python3.8\python.exe' 'd:\python3.8\lib\site-packages\pip' install --ignore-installed --no-user --prefix 'C:\Users\HUAWEI\AppData\Local\Temp\pip-build-env-dufwefyb\normal' --no-warn-script-location --no-binary :none: --only-binary :none: -i https://pypi.org/simple -- puccinialin
       cwd: None
```

```
  ERROR: Could not find a version that satisfies the requirement puccinialin (from versions: none)
  ERROR: No matching distribution found for puccinialin
  WARNING: You are using pip version 19.2.3, however version 25.0.1 is available.
```

```
ERROR: Command errored out with exit status 1: 'd:\python3.8\python.exe' 'd:\python3.8\lib\site-packages\pip' install --ignore-installed --no-user --prefix 'C:\Users\HUAWEI\AppData\Local\Temp\pip-build-env-dufwefyb\normal' --no-warn-script-location --no-binary :none: --only-binary :none: -i https://pypi.org/simple -- puccinialin Check the logs for full command output.
```

出现问题的原因：
`pucciniolin`是 30TAI 私有依赖，仅随集创赛完整套件分发，Icraft 主安装包不含该文件；如果在没有实体版卡的情况下，可以通过修改模型导出的代码直接跳过。
目前存储在本地的1_save-副本是完整的代码，1_save是修改后的代码。
修改之后没有报错

出现另一个遗留的问题
```
Traceback (most recent call last):
  File "D:\icraft\project\yolov5_7.0\yolov5_7.0_icraft\1_scripts\..\utils\general.py", line 41, in <module>
    import ultralytics
ModuleNotFoundError: No module named 'ultralytics'
```
这里有一个很致命的问题：一般电脑默认的python版本会比这个板卡要求的python版本要高。3.8的版本实在是太低了，在运行1_save的时候一定要强制在python3.8的环境下进行运行
删去默认路径下的ultralytics

3. 验证生成结果：执行后会在`yolov5_7.0`目录下生成`yolov5s_traced.pt`文件（约 14MB），即为 Icraft 可解析的模型文件，无此文件则检查 Python 环境是否为 3.8、Icraft python 包是否安装成功。

## 步骤 3：模型全流程编译（核心，生成仿真用中间层文件）

使用 Icraft 的`compile`命令，基于官方提供的**诸葛 / ZHUGE 架构配置文件**编译模型，编译会依次完成**解析→优化→量化→适配→指令生成**，最终生成`json&raw`中间层文件（仿真运行的核心文件），**30TAI 的 NPU 架构必须指定为 zhuge，否则编译失败**。

1. 进入工程的 icraft 编译配置目录（已内置 zhuge 架构的 int8 量化配置）：
    ```
    cd C:\Icraft\modelzoo\yolov5_7.0\yolov5_7.0_icraft\2_compile\config\ZG
    ```
2. 执行编译命令，使用`yolov5s_int8.toml`配置文件（int8 量化，兼顾仿真速度和精度，官方推荐）：
```
    icraft compile .\yolov5s_int8.toml
```

出现报错
```
led: (std::filesystem::exists(net_param.network)) is false
File "fmodel/yolov5s_640x640.pt" does not exist!

[03/01/26 17:00:36.306] [E] 执行以下命令时捕获到错误码1:
icraft-parse --channel_swap "0,1,2" --frame_version "1.9" --framework "pytorch" --inputs "1,640,640,3" --inputs_dtype "UINT8" --inputs_layout "NHWC" --jr_path "../3_deploy/imodel/ZG/int8/" --net_name "yolov5s" --network "fmodel/yolov5s_640x640.pt" --pre_mean "0,0,0" --pre_method "nop" --pre_scale "255,255,255" --target "zhuge"
```
修改文件路径成绝对路径之后，出现另一个报错
```
[03/01/26 17:06:50.707] [F] Error while parsing key-value pair: expected a comment or whitespace, saw 'D'
[03/01/26 17:10:38.258] [F] Error while parsing string: unknown escape sequence '\i'
```
语法和间隔符的问题

运行到一半
![[Pasted image 20260301171518.png]]
出现新的报错
```
Exception occurs at line 1438 in file C:\Icraft-Build\build\windows-x64-release\_deps\icraft-quantizer-src\source\passes\common\CalibratePass\CalibratePass.cpp
Exception info : File ./qtset/coco.txt does not exist

[03/01/26 17:14:38.099] [F] 21002
[03/01/26 17:14:38.249] [E] 执行以下命令时捕获到错误码21002:
icraft-quantize --forward_dir "./qtset/coco" --forward_list "./qtset/coco.txt" --forward_mode "image" --jr_path "../3_deploy/imodel/ZG/int8/" --json "../3_deploy/imodel/ZG/int8/yolov5s_optimized.json" --per "channel" --qdtype "int8" --raw "../3_deploy/imodel/ZG/int8/yolov5s_optimized.raw" --saturation "kld" --target "zhuge"
```
应该又是路径问题，文件需要有较大的改动

![[Pasted image 20260301172751.png]]

3. 编译过程与日志：
    - 控制台会打印编译进度（loop1/loop2），全程约 10-30 秒，无报错则编译成功；
    - 若出现`nvfuser library failed`警告，**直接忽略**（该警告为 CUDA 相关库缺失，不影响 Host 后端仿真）；
    - 若出现算子不支持 / 配置错误，查看`C:\Icraft\modelzoo\yolov5_7.0\.icraft\logs`下的编译日志，定位具体问题。
4. 验证编译结果：编译成功后，在`2_compile\config\ZG`目录下生成 **`json&raw`文件夹**和**.icraft 文件夹 **：
    - `json&raw`：存放各阶段中间层文件（.json/.raw），是仿真运行的输入；
    - `.icraft`：存放编译日志，仅用于问题排查，仿真无需修改。
## 步骤 4：配置仿真运行文件（基于 Host 后端，无板卡专属）

Icraft 仿真通过`icraft run`命令实现，需配置**toml 仿真配置文件**，核心指定**Host 后端、中间层文件路径、测试图片路径**，无需配置任何板卡相关参数（如 ZG330Backend、板卡 IP），官方工程可直接新建配置文件，无需修改原有文件。

1. 在`json&raw`文件夹同级目录（即`ZG`目录），新建仿真配置文件`sim_config.toml`（右键→新建文本文档→重命名，后缀改为 toml，注意关闭文件扩展名隐藏）；
2. 打开`sim_config.toml`，粘贴以下配置内容（**路径需与实际编译结果一致，直接复制即可**），保存并关闭： ```
```
    # 仿真核心配置，仅指定Host后端，无任何板卡相关配置
    [run]
    # 编译生成的网络结构JSON文件路径
    json = "json&raw/yolov5s_ZG.json"
    # 编译生成的模型权重RAW文件路径
    raw = "json&raw/yolov5s_ZG.raw"
    # 测试图片路径，工程内自带640x640测试图，路径直接复制
    input = "C:/Icraft/modelzoo/yolov5_7.0/images/test/test_640x640.jpg"
    # 仅使用Host后端（CPU）仿真，关键配置，无板卡必须设为Host
    backends = "Host"
    # 导出算子输出结果格式：HQB（硬件排布+定点+二进制），便于后续分析
    dump_format = "HQB"
    # 记录所有算子的输入输出日志，用于仿真结果分析
    log_io = true
    ```
    
    ⚠️ 路径注意：toml 文件中路径分隔符用`/`而非`\`，否则会识别失败；测试图片路径需确认文件存在。

```

## 步骤 5：执行 Host 后端纯软件仿真（最终运行步骤）

通过`icraft run`命令加载上述仿真配置文件，Icraft 会在**CPU 上模拟 30TAI 的 NPU 推理过程**，输出仿真日志、算子执行信息，并保存特征图结果，全程无硬件依赖，执行完成即仿真成功。

1. 保持在`ZG`目录（配置文件所在目录），执行仿真命令：
    
    cmd
    
    ```
    icraft run .\sim_config.toml
    ```
    以后干脆把所有的路径改成绝对路径就好了
1. 仿真运行过程（控制台输出）：
    
    1. 首先打印**设备初始化信息**（Host 后端无实际设备，仅打印版本信息，无报错即可）；
    2. 然后打印**进度条**（Run 100%），表示算子依次执行；
    3. 最后打印**每一层算子的 IO 信息**，包括`opId`（算子 ID）、`opType`（算子类型，如 Conv2d、Resize、HardOp）、`Inputs`（输入维度），表示每个算子仿真执行完成。
    
2. 仿真成功标志：控制台无报错，最后打印`Run 100%[00m:xxs]Done!`，即为仿真运行完成。

## 步骤 6：仿真结果分析与验证（确认模型推理正确性）

仿真完成后，Icraft 会自动保存**算子输出特征图**和**运行日志**，通过官方工具`icraft-show`可可视化网络结构、分析算子执行结果，确认编译和仿真无错误，无需板卡即可验证模型推理逻辑的正确性。

### 6.1 查看仿真结果文件

仿真生成的所有结果均在`.icraft`文件夹中，路径：

plaintext

```
C:\Icraft\modelzoo\yolov5_7.0\yolov5_7.0_icraft\2_compile\config\ZG\.icraft\logs
```

核心文件：

- `ftmpHQB`文件夹：存放**每个算子的输出特征图**（二进制文件），是仿真推理的实际结果；
- `run.log`：仿真运行全日志，记录算子执行顺序、耗时、输入输出维度，可排查仿真错误。

### 6.2 网络结构可视化（icraft-show 工具，直观验证）

Icraft 内置`icraft-show`工具，可可视化编译后的网络结构，查看算子类型、维度、参数，确认无算子丢失 / 错误，是仿真验证的核心步骤。

1. 保持在`ZG`目录，执行可视化命令：

    ```
    icraft-show --json json&raw/yolov5s_ZG.json --raw json&raw/yolov5s_ZG.raw
    ```
    
2. 可视化结果：
    
    - 控制台会以**图形化形式**展示网络结构，每个节点为一个算子，包含`opId`、`opType`、输入输出维度；
    - 例如`Conv2d 34`表示算子 ID34 为卷积算子，后续会打印卷积核维度`W<2x2x16x32>`、偏置维度`B<32>`；
    - 若能完整展示所有算子（从 Input 到 Output），无缺失 / 报错，说明网络编译和仿真无结构错误。

![[Pasted image 20260301181554.png]]
尝试可视化无果，需要修改图形可视化的代码并调整，放弃
![[Pasted image 20260301183211.png]]
### 6.3 逐层误差分析（可选，验证仿真精度）

若需要验证仿真精度，可将**Host 仿真结果**与**Pytorch 原生模型推理结果**（Golden Model）对比，通过`icraft-show`的逐层对比功能，定位量化 / 编译带来的误差，无板卡也可完成。

1. 运行 Pytorch 原生模型`yolov5s_traced.pt`，生成原生推理的中间层特征图（作为 Golden Model）；
2. 执行对比命令，指定 Golden Model 和 Test Model（Host 仿真结果）的 json/raw 文件：
    
    cmd
    
    ```
    icraft-show --golden_json 原生模型.json --golden_raw 原生模型.raw --test_json json&raw/yolov5s_ZG.json --test_raw json&raw/yolov5s_ZG.raw
    ```
    
3. 对比结果：控制台会打印每层特征图的误差值，若误差在可接受范围内（如 int8 量化误差 < 5%），说明仿真精度符合要求。

## 可选步骤：仿真其他模型 / 修改量化配置（按需扩展）

若需要仿真 30TAI 支持的其他模型（如 YOLOv8n、RTMDet-Tiny），或修改量化配置（如 bf16/fp16 量化），仅需修改 2 处：

1. 克隆对应模型的 modelzoo 工程（官方 modelzoo 网址：[https://www.modelscope.cn/collections/icraft_modelzoo-18b52923d4854f](https://www.modelscope.cn/collections/icraft_modelzoo-18b52923d4854f)）；
2. 替换编译配置文件中的`qdtype`参数（`yolov5s_int8.toml`中）：
    
    - `qdtype = "int8"`：int8 量化，速度最快，精度略有损失；
    - `qdtype = "bf16"`：bf16 量化，精度更高，仿真速度稍慢；
    - `qdtype = "fp16"`：fp16 量化，精度接近原生，仿真速度最慢。
        
        其余步骤与 YOLOv5s 完全一致，无板卡仿真流程通用。
    

# 核心注意事项（无板卡纯仿真专属）

1. 全程**无需安装 WSL / 虚拟机 / Docker**，无需交叉编译，所有操作均在 Win10 上位机完成；
2. 仿真仅支持**HostBackend**，切勿在配置文件中添加`ZG330Backend/ZhugeBackend`（该后端仅支持实体板卡 NPU，无板卡配置会直接报错）；
3. 编译时必须指定**target = "zhuge"**（30TAI 的 NPU 架构），否则编译生成的中间层文件无法仿真；
4. 所有命令均需在**管理员权限 CMD**中执行，普通 CMD 会因文件读写权限不足导致编译 / 仿真失败；
5. 仿真耗时为**CPU 模拟耗时**，与实体板卡 NPU 的实际耗时无参考性，仅用于验证模型推理逻辑的正确性。