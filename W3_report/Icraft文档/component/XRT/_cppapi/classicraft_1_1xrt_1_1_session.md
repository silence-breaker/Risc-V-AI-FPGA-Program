# Class Session

**Defined in:** `File session.h`


                  
  

## Inheritance Relationships#

## Base Type#

<code class="docutils literal notranslate">public
 icraft::xir::HandleBase<
 Session,
 Handle,
 SessionNode
 >
</code>

## Class Documentation#

```cpp
class Session : public icraft::xir::HandleBase<Session, Handle, SessionNode>#
```

会话的引用类 

## Public Types

```cpp
using CallBackFunc = std::function<void(const Session &sess, const Operation &op, const Backend &backend, std::vector<Tensor> &output_tensors)>#
```

回调函数类型 

---

```cpp
using ForwardOps = std::vector<std::tuple<Operation, Backend, FForwardOp, std::vector<int64_t>, std::vector<int64_t>>>#
```

前向算子类型 

---

## Public Functions

```cpp
Session() = default#
```

默认构造函数 

---

```cpp
Session sub(int64_t start_index, int64_t end_index) const#
```

从该session创建一个新的session, 共享相同的backends, 但是network_view不同. 

```cpp
参数:
```

<dd class="field-odd">
<strong>start_index</strong> – NetworkView包含的算子在原网络中的开始索引(包含)，支持负数索引 

<strong>end_index</strong> – NetworkView包含的算子在原网络中的结束索引(不包含)，支持负数索引 

---

```cpp
返回:
```

<dd class="field-even">创建的session 

---

---

```cpp
Session sub(int64_t start_index) const#
```

从该session创建一个新的session, 共享相同的backends, 但是network_view不同. 

```cpp
参数:
```

<dd class="field-odd"><strong>start_index</strong> – NetworkView包含的算子在原网络视图中的开始索引(包含)，支持负数索引 

---

```cpp
返回:
```

<dd class="field-even">创建的Session 

---

---

```cpp
void apply()#
```

应用Session的一些选项 

---

```cpp
void enableTimeProfile(bool enable)#
```

使能时间分析功能. 

```cpp
参数:
```

<dd class="field-odd"><strong>enable</strong> – 是否使能 

---

---

```cpp
std::vector<Tensor> stepTo(int64_t op_id, const std::vector<Tensor> &inputs = {})#
```

前向到指定的算子. 

备注

只有在算子的输入来自外部时，才会取输入Tensor列表中的，否则使用生产者算子产生的Tensor 

```cpp
参数:
```

<dd class="field-odd">
<strong>op_id</strong> – 指定算子的Op ID 

<strong>inputs</strong> – 输入的Tensor列表 

---

```cpp
返回:
```

<dd class="field-even">指定算子的前向结果

---

---

```cpp
std::vector<Tensor> forward(const std::vector<Tensor> &inputs)#
```

前向会话中绑定的整个网络视图 

```cpp
参数:
```

<dd class="field-odd"><strong>inputs</strong> – 输入的Tensor列表 

---

```cpp
返回:
```

<dd class="field-even">整个网络视图的前向结果 

---

---

```cpp
void forward(const std::vector<Tensor> &inputs, const std::vector<Tensor> &outputs)#
```

前向会话中绑定的整个网络视图 

```cpp
参数:
```

<dd class="field-odd">
<strong>inputs</strong> – 输入的Tensor列表 

<strong>outputs</strong> – 输出的Tensor列表 

---

---

```cpp
std::unordered_map<int64_t, Backend> backendBindings() const#
```

获取会话中所有算子的后端绑定关系. 

```cpp
返回:
```

<dd class="field-odd">Map表示的算子后端绑定关系，其键为Op ID, 值为该算子绑定的后端 

---

---

```cpp
TimeProfileResults timeProfileResults() const#
```

获取时间分析的结果. 

参见

TimeProfileResults 

---

```cpp
template<typename T>inline double totalTime() const#
```

获取会话总时间. 

```cpp
模板参数:
```

<dd class="field-odd"><strong>T</strong> – 时间单位类型，支持std::chrono::seconds等单位 

---

```cpp
返回:
```

<dd class="field-even">指定单位下的总时间 

---

---

```cpp
void setPreCallBack(CallBackFunc func)#
```

向会话添加回调函数，通过该接口配置的回调函数将在每个算子执行前向之前被调用 

```cpp
参数:
```

<dd class="field-odd"><strong>回调函数</strong> – 

---

---

```cpp
void setPostCallBack(CallBackFunc func)#
```

向会话添加回调函数，通过该接口配置的回调函数将在每个算子执行前向之前被调用 

```cpp
参数:
```

<dd class="field-odd"><strong>回调函数</strong> – 

---

---

```cpp
const ForwardOps &getForwards()#
```

获取会话的前向算子列表 

```cpp
返回:
```

<dd class="field-odd">前向算子列表 

---

---

```cpp
void setLogIO(bool flag)#
```

设置每层前向结束后是否打印IO信息，默认关闭 

```cpp
参数:
```

<dd class="field-odd"><strong>开启标志</strong> – 

---

---

```cpp
void setLogTime(bool flag)#
```

设置每层前向结束后是否打印耗时信息，默认关闭 

```cpp
参数:
```

<dd class="field-odd"><strong>开启标志</strong> – 

---

---

```cpp
void setDumpOutputs(bool flag, const std::string &file_path, const std::string &format)#
```

设置每层前向结束后是否保存输出结果至指定路径下，默认关闭 

备注

支持的格式由三个字母表示： 第一个字母表示排布，H表示硬件，S表示软件 第二个字母表示数值，F表示浮点，Q表示定点 第三个字母表示序列化形式，B表示二进制，T表示文本 若一个Tensor原本的排布时H，那么可以转为S；若原本的数值为Q，那么可以转为F；反之不可 

```cpp
参数:
```

<dd class="field-odd">
<strong>flag</strong> – 开启标志 

<strong>path</strong> – 保存输出结果路径 

<strong>format</strong> – 指定的输出格式

---

---

```cpp
void dumpSnapshot(const std::string &filePath)#
```

对当前session进行序列化得到二进制文件 

```cpp
参数:
```

<dd class="field-odd"><strong>filePath</strong> – 二进制文件保存路径 

---

---

## Public Static Functions

```cpp
template<typename ...BackendType>static inline Session Create(const NetworkView &network, const std::vector<Device> &devices)#
```

创建一个会话，按优先级绑定到指定的后端. 

备注

设备列表中的Device和后端类型列表中的后端是一一对应的 

```cpp
模板参数:
```

<dd class="field-odd"><strong>BackendType</strong> – 会话绑定的后端类型列表 

---

```cpp
参数:
```

<dd class="field-even">
<strong>network</strong> – 网络视图 

<strong>devices</strong> – 设备列表

---

---

```cpp
static Session CreateByOrder(const NetworkView &network, std::vector<Backend> backends, const std::vector<Device> &devices)#
```

创建一个会话，按优先级绑定到指定的后端. 

备注

设备列表中的Device和后端类型列表中的后端是一一对应的 

```cpp
参数:
```

<dd class="field-odd">
<strong>network</strong> – 网络视图 

<strong>backends</strong> – 后端列表 

<strong>devices</strong> – 设备列表

---

---

```cpp
static Session CreateWithBackends(const NetworkView &network, const std::vector<Backend> &backends)#
```

创建一个会话，使用绑定好网络和设备的后端. 

备注

后端列表中的Backend已经完成了网络视图和设备的绑定 

```cpp
参数:
```

<dd class="field-odd">
<strong>network</strong> – 网络视图 

<strong>backends</strong> – 后端列表

---

---

```cpp
static Session CreateWithSnapshot(const std::string &filePath, std::vector<Backend> backends, const std::vector<Device> &devices)#
```

根据二进制文件反序列化得到session 

```cpp
参数:
```

<dd class="field-odd">
<strong>filePath</strong> – 二进制文件保存路径 

<strong>backends</strong> – 后端列表 

<strong>devices</strong> – 设备列表 

---

---

---

                