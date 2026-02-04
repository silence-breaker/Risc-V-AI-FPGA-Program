# Program Listing for File backend.h[#](#program-listing-for-file-backend-h "此标题的永久链接")

↰ [Return to documentation for file](file_icraft-backends_hostbackend_backend.h.md#file-icraft-backends-hostbackend-backend-h) (`icraft-backends\hostbackend\backend.h`)

```
#pragma once
#ifndef HOSTBKND_BACKEND_PCH_GUARD
#define HOSTBKND_BACKEND_PCH_GUARD
#include <icraft-xrt/core/backend.h>
#include <icraft-xrt/core/device.h>
#include "icraft-backends/hostbackend/dllexport.h"

namespace icraft {
    namespace xrt {
        class HostBackendNode : public NodeBase<HostBackendNode, BackendNode> {
        public:

            HOSTBKND_DLL HostBackendNode();

            HOSTBKND_DLL virtual void init(const NetworkView& networkview, const Device& device) override;

            HOSTBKND_DLL virtual void deinit() override;

            HOSTBKND_DLL virtual void apply() override {};

            HOSTBKND_DLL virtual void view(uint64_t start_index, uint64_t end_index) override {};

            HOSTBKND_DLL virtual Backend fork() override;

            HOSTBKND_DLL virtual MergedOps autoMerge() override;

            HOSTBKND_DLL virtual Operation serialize(int64_t op_id) override;

            //HOSTBKND_DLL virtual std::tuple < SerializeOp,
            //  std::vector< SerializeFtmp>> serialize(FlatbufferBuilder& builder, int64_t op_id) override;

            ~HostBackendNode();

            friend class HostBackend;

        private:
            struct HostBkndParams;
            std::unique_ptr<HostBkndParams> params_;
            class HostBkndUtilFuncs;
            std::unique_ptr<HostBkndUtilFuncs> ufs_;
        };

        class HostBackend : public HandleBase<HostBackend, Backend, HostBackendNode> {
        public:
            HOSTBKND_DLL void setFakeQf(bool fakeQf);

            HOSTBKND_DLL bool getFakeQf() const;

            HOSTBKND_DLL void setCodeSimFireby(bool enable_fireby);

            HOSTBKND_DLL bool getCodeSimFireby() const;

            HOSTBKND_DLL static void setThreadsNum(int num_threads);

            HOSTBKND_DLL static int getThreadsNum();

            HOSTBKND_DLL void dumpHiddenFtmp(const std::vector<int64_t>& ids, const std::string& path, const std::string& format = "");

            HOSTBKND_DLL HostBackendNode::HostBkndUtilFuncs* getUFs() const;
        };

        using HostFInitOp = std::function<void(const xir::Operation&, HostBackend)>;
        using HostFForwardOp = std::function<std::vector<Tensor>(
            const xir::Operation&,
            const std::vector<Tensor>&,
            const std::vector<Tensor>&,
            HostBackend)>;

        class HostBkndOpFuncManager {
        public:
            //HostBkndOpFuncManager();
            ~HostBkndOpFuncManager();
            HostBkndOpFuncManager(std::string_view op_type);

            void add_init(std::string_view target_type, HostFInitOp init_func);

            void add_forward(std::string_view target_type, HostFForwardOp forward_func);

            void run_op_init_func(const xir::Operation& op, HostBackend backend);

            std::vector<xrt::Tensor> run_op_forward_func(
                const xir::Operation& op,
                const std::vector<Tensor>& inputs,
                const std::vector<Tensor>& outputs,
                HostBackend backend
            );

        private:
            HostBkndOpFuncManager& operator=(const HostBkndOpFuncManager&) = delete;
            struct ManagerParams;
            std::unique_ptr<ManagerParams> params_;
        };

        class HostBkndOpFuncRegister {
        public:
            template <
                typename OpType,
                typename TargetType,
                typename = typename std::enable_if_t<
                std::is_base_of_v<Operation, OpType>>,
                typename = typename std::enable_if_t<
                std::is_base_of_v<xir::CompileTarget, TargetType>>
                >
                static HostBkndOpFuncRegister* RegOpTargetFuncs(
                    std::function<void(const OpType&, HostBackend)> initFuncParam,
                    std::function<std::vector<Tensor>(
                        const OpType&,
                        const std::vector<Tensor>& ,
                        const std::vector<Tensor>&,
                        HostBackend)> forwardFuncParam
                )
            {
                auto instance = getInstance();
                auto& func_map = instance->hostbknd_op_func_manager_map;
                if (func_map.find(OpType::NodeType::type_key) == func_map.end()) {
                    std::string_view op_type = OpType::NodeType::type_key;
                    func_map.emplace(op_type, std::make_unique<HostBkndOpFuncManager>(op_type));
                    auto& new_op_func_manager = func_map[OpType::NodeType::type_key];
                    auto op_init_func =
                        [&new_op_func_manager](const xir::Operation& op, HostBackend backend) {
                        new_op_func_manager->run_op_init_func(op, backend);
                        };
                    auto op_forward_func =
                        [&new_op_func_manager](const xir::Operation& op, const std::vector<Tensor>& inputs, const std::vector<Tensor>& outputs, HostBackend backend) {
                        return new_op_func_manager->run_op_forward_func(op, inputs, outputs, backend);
                        };
                    ICRAFT_ADD_OP_TO_BACKEND(OpType, HostBackend)
                        .set_init(op_init_func)
                        .set_forward(op_forward_func);
                }
                auto& op_func_manager = func_map[OpType::NodeType::type_key];
                auto f_init = [=](const xir::Operation& op, Backend backend) {
                    initFuncParam(op.cast<OpType>(), backend.cast<HostBackend>());
                    };
                op_func_manager->add_init(TargetType::NodeType::type_key, f_init);
                auto f_forward = [=](const xir::Operation& op, const std::vector<Tensor>& inputs, const std::vector<Tensor>& outputs, Backend backend) {
                    return forwardFuncParam(op.cast<OpType>(), inputs, outputs, backend.cast<HostBackend>());
                    };
                op_func_manager->add_forward(TargetType::NodeType::type_key, f_forward);
                return instance;
            };
        private:
            static HostBkndOpFuncRegister* getInstance();
            HostBkndOpFuncRegister() {};
            ~HostBkndOpFuncRegister();
            HostBkndOpFuncRegister(const HostBkndOpFuncRegister&) = delete;
            HostBkndOpFuncRegister& operator=(const HostBkndOpFuncRegister&) = delete;
            //内部维护的ManagerMap
            std::unordered_map<std::string_view, std::unique_ptr<HostBkndOpFuncManager>>  hostbknd_op_func_manager_map = {};
        };
    }
}

#define ICRAFT_HOSTBKND_REG_OP_FUNC_VAR_DEF             \
  static ICRAFT_ATTRIBUTE_UNUSED auto __reg_op_hostbknd_func_var_def

#define ICRAFT_ADD_HOSTBKND_OP(OpType, TargetType, initFunc, forwardFunc)   \
ICRAFT_STR_CONCAT(ICRAFT_HOSTBKND_REG_OP_FUNC_VAR_DEF, __COUNTER__) = \
icraft::xrt::HostBkndOpFuncRegister::RegOpTargetFuncs<OpType, TargetType>(initFunc, forwardFunc)

#endif //HOSTBKND_BACKEND_PCH_GUARD
```
