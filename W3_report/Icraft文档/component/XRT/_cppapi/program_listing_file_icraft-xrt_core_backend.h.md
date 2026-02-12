# Program Listing for File backend.h

```cpp
#pragma once
#ifndef XRT_BACKEND_PCH_GUARD
#define XRT_BACKEND_PCH_GUARD
#include <icraft-xrt/base/dllexport.h>
#include <icraft-xir/core/data.h>
#include <icraft-xir/core/network.h>
#include <icraft-xrt/core/tensor.h>
#include <icraft-xir/core/operation.h>
#include <string_view>
#include <unordered_map>
//#include <icraft-xrt/utils/serialize.h>

namespace icraft::xrt {
    using icraft::xir::Operation;
    using icraft::xir::NetworkView;

    class Backend;
    using FInitOp = std::function<void(const xir::Operation&, Backend)>;
    using FForwardOp = std::function<std::vector<Tensor>(const xir::Operation&, const std::vector<Tensor>&, const std::vector<Tensor>&, Backend)>;

    using MergedOp = std::pair<Operation, std::vector<Operation>>;
    using MergedOps = std::vector<MergedOp>;

    class BackendNode;

    class Backend : public VirtualBase<Backend, Handle, BackendNode> {
    public:
        XRT_DLL std::optional<FInitOp> getInitFunc(const Operation& op) const;

        XRT_DLL std::optional<FForwardOp> getForwardFunc(const Operation& op) const;

        XRT_DLL bool isOpSupported(const Operation& op) const;

        XRT_DLL void initOp(const Operation& op);

        XRT_DLL std::vector<Tensor> forwardOp(const Operation& op, const std::vector<Tensor>& inputs, const std::vector<Tensor>& outputs = {});

        XRT_DLL void init(const NetworkView& network_view, const Device& device);

        XRT_DLL void deinit();

        XRT_DLL void apply();

        XRT_DLL void enableTimeProfile(bool enable);

        XRT_DLL void setTimeElapses(int64_t op_id, double memcpy_time, double hard_time);


        XRT_DLL std::optional<const std::tuple<double, double>> getTimeElapses(int64_t op_id) const;

        XRT_DLL void view(uint64_t start_index, uint64_t end_index);

        XRT_DLL MergedOps autoMerge();

        XRT_DLL Backend fork();

        XRT_DLL Operation serialize(int64_t op_id);

        //XRT_DLL std::tuple < SerializeOp,
            //std::vector< SerializeFtmp>> serialize(FlatbufferBuilder& builder, int64_t op_id);

        XRT_DLL Backend& setDevice(Device device);

        template <typename BackendType>
        static BackendType Create(const NetworkView& network_view, const Device& device) {
            auto backend = BackendType::Init();
            backend.init(network_view, device);
            return backend;
        }

        XRT_DLL void enableSnapshot(bool enable);

    };

    class BackendNode : public NodeBase<BackendNode, Node> {
    public:
        NetworkView network_view;
        Device device;
        bool time_profile = false;
        bool snapshot = false;

    private:
        std::unordered_map<int64_t, std::tuple<double, double>> time_elapses_;

        virtual void accept(AttrVisitor& visitor) override {}

        virtual void init(const NetworkView& network_view, const Device& device) = 0;

        virtual void deinit() = 0;

        virtual void apply() = 0;

        virtual void view(uint64_t start_index, uint64_t end_index) = 0;

        virtual MergedOps autoMerge() = 0;

        virtual Backend fork() = 0;

        virtual Operation serialize(int64_t op_id){
            return Operation();
        }

        //virtual std::tuple < SerializeOp,
            //std::vector< SerializeFtmp>> serialize(FlatbufferBuilder& builder, int64_t op_id) = 0;

        friend class Backend;
        friend class Session;
    };

    using FOpConstraint = std::function<bool(const xir::Operation&, Backend)>;
    class BackendOpRegistry {
    public:
        class Manager;

        XRT_DLL BackendOpRegistry& set_init(FInitOp f);

        XRT_DLL BackendOpRegistry& set_forward(FForwardOp f);

        XRT_DLL BackendOpRegistry& set_constraint(FOpConstraint f);

        XRT_DLL static BackendOpRegistry& Register(std::string_view backend, std::string_view op, bool can_override = false);

        XRT_DLL static bool Remove(std::string_view backend, std::string_view op);

        XRT_DLL static std::optional<FInitOp> GetInitFunc(std::string_view backend, std::string_view op);

        XRT_DLL static std::optional<FForwardOp> GetForwardFunc(std::string_view backend, std::string_view op);

        XRT_DLL static std::optional<FOpConstraint> GetConstraintFunc(std::string_view backend, std::string_view op);

        XRT_DLL std::vector<std::vector<std::string_view>> ListNames();

    private:
        FInitOp finit_;
        FForwardOp fforward_;
        FOpConstraint fconstraint_;
    };

    template <
        typename OpType,
        typename BackendType,
        typename = typename std::enable_if_t<
        std::is_base_of_v<Operation, OpType>>,
        typename = typename std::enable_if_t<
        std::is_base_of_v<Backend, BackendType>>
    >
    class BackendOpRegisterHelper {
    public:
        BackendOpRegisterHelper()
            : registry_(BackendOpRegistry::Register(BackendType::NodeType::type_key, OpType::NodeType::type_key))
            {}

        BackendOpRegisterHelper& set_init(std::function<void(const OpType&, BackendType)> func) {
            auto f = [=](const xir::Operation& op, Backend backend) {
                func(op.cast<OpType>(), backend.cast<BackendType>());
            };
            registry_.set_init(f);
            return *this;
        }

        BackendOpRegisterHelper& set_forward(
            std::function<std::vector<Tensor>(const OpType&, const std::vector<Tensor>&, const std::vector<Tensor>&, BackendType)> func
        ) {
            auto f = [=](const xir::Operation& op, const std::vector<Tensor>& inputs, const std::vector<Tensor>& outputs, Backend backend) {
                return func(op.cast<OpType>(), inputs, outputs, backend.cast<BackendType>());
            };
            registry_.set_forward(f);
            return *this;
        }

        BackendOpRegisterHelper& set_constraint(
            std::function<bool(const OpType&, BackendType)> func
        ) {
            auto f = [=](const xir::Operation& op, Backend backend) {
                return func(op.cast<OpType>(), backend.cast<BackendType>());
            };
            registry_.set_constraint(f);
            return *this;
        }
    private:
        BackendOpRegistry& registry_;
    };
}

#define ICRAFT_ADD_OP_TO_BACKEND_IMPL_VAR_DEF           \
  static ICRAFT_ATTRIBUTE_UNUSED auto __add_op_to_backend_impl

#define ICRAFT_ADD_OP_TO_BACKEND(OpType, BackendType)   \
ICRAFT_STR_CONCAT(ICRAFT_ADD_OP_TO_BACKEND_IMPL_VAR_DEF, __COUNTER__) = \
icraft::xrt::BackendOpRegisterHelper<OpType, BackendType>()

#endif //XRT_BACKEND_PCH_GUARD
```

[Return to documentation for file](file_icraft-xrt_core_backend.h.md#file-icraft-xrt-core-backend-h)
