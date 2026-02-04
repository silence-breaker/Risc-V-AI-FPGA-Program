# Class HostBackend[#](#class-hostbackend "此标题的永久链接")

* Defined in [File backend.h](file_icraft-backends_hostbackend_backend.h.md#file-icraft-backends-hostbackend-backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public HandleBase< HostBackend, Backend, HostBackendNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class HostBackend : public HandleBase<[HostBackend](#_CPPv4N6icraft3xrt11HostBackendE "icraft::xrt::HostBackend"), Backend, [HostBackendNode](classicraft_1_1xrt_1_1_host_backend_node.md#_CPPv4N6icraft3xrt15HostBackendNodeE "icraft::xrt::HostBackendNode")>[#](#_CPPv4N6icraft3xrt11HostBackendE "永久链接至目标")
:   Host类型后端引用类

    Public Functions

    void setFakeQf(bool fakeQf)[#](#_CPPv4N6icraft3xrt11HostBackend9setFakeQfEb "永久链接至目标")
    :   设置HostBackend是否以fakeQf模式运行，fakeQf模式下定点前向不做截位和饱和， 主要用来对比adapted和generated算子前向结果

        参数:
        :   **fakeQf** – 是否开启fakeQf模式

    bool getFakeQf() const[#](#_CPPv4NK6icraft3xrt11HostBackend9getFakeQfEv "永久链接至目标")
    :   查询是否已开启fakeQf模式

        返回:
        :   是否已开启fakeQf模式

    void setCodeSimFireby(bool enable\_fireby)[#](#_CPPv4N6icraft3xrt11HostBackend16setCodeSimFirebyEb "永久链接至目标")
    :   设置HostBackend指令仿真时是否使用fireby仿真器;

        参数:
        :   **enable\_fireby** – 是否使用fireby仿真

    bool getCodeSimFireby() const[#](#_CPPv4NK6icraft3xrt11HostBackend16getCodeSimFirebyEv "永久链接至目标")
    :   查询是否使用fireby仿真

        返回:
        :   是否使用fireby仿真

    void dumpHiddenFtmp(const std::vector<int64\_t> &ids, const std::string &path, const std::string &format = "")[#](#_CPPv4N6icraft3xrt11HostBackend14dumpHiddenFtmpERKNSt6vectorI7int64_tEERKNSt6stringERKNSt6stringE "永久链接至目标")
    :   仅在BY指令仿真时有效，如果存在的话以指定的格式dump合并算子之后HardOp的中间Ftmps中指定id的Ftmps

        参数:
        :   * **ids** – 希望dump的ftmp
            * **path** – dump文件夹路径
            * **format** – dump的format

    [HostBackendNode](classicraft_1_1xrt_1_1_host_backend_node.md#_CPPv4N6icraft3xrt15HostBackendNodeE "icraft::xrt::HostBackendNode")::HostBkndUtilFuncs \*getUFs() const[#](#_CPPv4NK6icraft3xrt11HostBackend6getUFsEv "永久链接至目标")
    :   (开发接口)获取HostBackendUtilFuncs

        返回:
        :   HostBackendUtilFuncs

    Public Static Functions

    static void setThreadsNum(int num\_threads)[#](#_CPPv4N6icraft3xrt11HostBackend13setThreadsNumEi "永久链接至目标")
    :   设置CPU前向推理时算子库自动启用的线程数, 在某些情况下占用过多资源会导致问题，需要手动降低线程数 该变量是全局变量, 即不同的HostBackend对象共享该设置

        参数:
        :   **num\_threads** – 期望用于CPU推理加速的线程数

    static int getThreadsNum()[#](#_CPPv4N6icraft3xrt11HostBackend13getThreadsNumEv "永久链接至目标")
    :   查询CPU前向推理时算子库自动启用的线程数, 该变量是全局变量, 即不同的HostBackend对象共享该设置

        返回:
        :   线程数
