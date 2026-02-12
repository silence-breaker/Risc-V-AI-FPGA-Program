# Class HostBackendNode[#](#class-hostbackendnode "此标题的永久链接")

* Defined in [File backend.h](file_icraft-backends_hostbackend_backend.h.md#file-icraft-backends-hostbackend-backend-h)

## Inheritance Relationships[#](#inheritance-relationships "此标题的永久链接")

### Base Type[#](#base-type "此标题的永久链接")

* `public NodeBase< HostBackendNode, BackendNode >`

## Class Documentation[#](#class-documentation "此标题的永久链接")

class HostBackendNode : public NodeBase<[HostBackendNode](#_CPPv4N6icraft3xrt15HostBackendNodeE "icraft::xrt::HostBackendNode"), BackendNode>[#](#_CPPv4N6icraft3xrt15HostBackendNodeE "永久链接至目标")
:   表示Host类型后端, 后端表示一种计算资源，包含了所有其所支持的算子在该计算资源的前向实现

    Public Functions

    HostBackendNode()[#](#_CPPv4N6icraft3xrt15HostBackendNode15HostBackendNodeEv "永久链接至目标")

    virtual void init(const NetworkView &networkview, const Device &device) override[#](#_CPPv4N6icraft3xrt15HostBackendNode4initERK11NetworkViewRK6Device "永久链接至目标")

    virtual void deinit() override[#](#_CPPv4N6icraft3xrt15HostBackendNode6deinitEv "永久链接至目标")

    inline virtual void apply() override[#](#_CPPv4N6icraft3xrt15HostBackendNode5applyEv "永久链接至目标")

    inline virtual void view(uint64\_t start\_index, uint64\_t end\_index) override[#](#_CPPv4N6icraft3xrt15HostBackendNode4viewE8uint64_t8uint64_t "永久链接至目标")

    virtual Backend fork() override[#](#_CPPv4N6icraft3xrt15HostBackendNode4forkEv "永久链接至目标")

    virtual MergedOps autoMerge() override[#](#_CPPv4N6icraft3xrt15HostBackendNode9autoMergeEv "永久链接至目标")

    virtual Operation serialize(int64\_t op\_id) override[#](#_CPPv4N6icraft3xrt15HostBackendNode9serializeE7int64_t "永久链接至目标")

    ~HostBackendNode()[#](#_CPPv4N6icraft3xrt15HostBackendNodeD0Ev "永久链接至目标")

    Friends

    *friend class* HostBackend
