# Class HostBkndOpFuncManager[#](#class-hostbkndopfuncmanager "此标题的永久链接")

* Defined in [File backend.h](file_icraft-backends_hostbackend_backend.h.md#file-icraft-backends-hostbackend-backend-h)

## Class Documentation[#](#class-documentation "此标题的永久链接")

class HostBkndOpFuncManager[#](#_CPPv4N6icraft3xrt21HostBkndOpFuncManagerE "永久链接至目标")
:   HostBackend算子注册辅助类，用来管理HostBackend各Target上的Op初始化和前向函数

    Public Functions

    ~HostBkndOpFuncManager()[#](#_CPPv4N6icraft3xrt21HostBkndOpFuncManagerD0Ev "永久链接至目标")

    HostBkndOpFuncManager(std::string\_view op\_type)[#](#_CPPv4N6icraft3xrt21HostBkndOpFuncManager21HostBkndOpFuncManagerENSt11string_viewE "永久链接至目标")

    void add\_init(std::string\_view target\_type, [HostFInitOp](typedef_backend_8h_1a7c8a56d56bde6d3f5274890ee4545a30.md#_CPPv4N6icraft3xrt11HostFInitOpE "icraft::xrt::HostFInitOp") init\_func)[#](#_CPPv4N6icraft3xrt21HostBkndOpFuncManager8add_initENSt11string_viewE11HostFInitOp "永久链接至目标")

    void add\_forward(std::string\_view target\_type, [HostFForwardOp](typedef_backend_8h_1a6b0001607b3b1f8d277b2470ca591af6.md#_CPPv4N6icraft3xrt14HostFForwardOpE "icraft::xrt::HostFForwardOp") forward\_func)[#](#_CPPv4N6icraft3xrt21HostBkndOpFuncManager11add_forwardENSt11string_viewE14HostFForwardOp "永久链接至目标")

    void run\_op\_init\_func(const xir::Operation &op, [HostBackend](classicraft_1_1xrt_1_1_host_backend.md#_CPPv4N6icraft3xrt11HostBackendE "icraft::xrt::HostBackend") backend)[#](#_CPPv4N6icraft3xrt21HostBkndOpFuncManager16run_op_init_funcERKN3xir9OperationE11HostBackend "永久链接至目标")

    std::vector<xrt::Tensor> run\_op\_forward\_func(const xir::Operation &op, const std::vector<Tensor> &inputs, const std::vector<Tensor> &outputs, [HostBackend](classicraft_1_1xrt_1_1_host_backend.md#_CPPv4N6icraft3xrt11HostBackendE "icraft::xrt::HostBackend") backend)[#](#_CPPv4N6icraft3xrt21HostBkndOpFuncManager19run_op_forward_funcERKN3xir9OperationERKNSt6vectorI6TensorEERKNSt6vectorI6TensorEE11HostBackend "永久链接至目标")
