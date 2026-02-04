# Program Listing for File pass.h



↰ [Return to documentation for file](file_icraft-xir_core_pass.h.md#file-icraft-xir-core-pass-h) (`icraft-xir\core\pass.h`)


```cpp
#pragma once
#include <icraft-xir/core/node.h>
#include <icraft-xir/core/reflection.h>
#include <icraft-xir/base/array.h>
#include <icraft-xir/base/map.h>
#include <icraft-xir/base/string.h>
#include <icraft-xir/base/with.h>
#include <icraft-utils/dll.h>

namespace icraft::xir {

    class PassContextNode : public NodeBase<PassContextNode, Node> {
    public:
        uint64_t top_level{ LLONG_MAX };
        Array<String> required_passes;
        Array<String> disabled_passes;
        Map<String, ObjectRef> config;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;
    };

    class PassInfo;

    class PassContext : public HandleBase<PassContext, Handle, PassContextNode> {
    public:
        PassContext() = default;

        XIR_DLL explicit PassContext(uint64_t top_level, Array<String> required_passes = {},
            Array<String> disabled_passes = {}, Map<String, ObjectRef> config = {});

        XIR_DLL static PassContext Init();

        XIR_DLL static PassContext& Current();

        XIR_DLL PassContext& requirePass(const std::string& pass_name);

        XIR_DLL PassContext& removeRequiredPass(const std::string& pass_name);

        XIR_DLL PassContext& disablePass(const std::string& pass_name);

        XIR_DLL PassContext& removeDisabledPass(const std::string& pass_name);

        XIR_DLL PassContext& setConfig(const std::string& key, ObjectRef value);

        template <typename T, typename = typename std::enable_if_t<(std::is_base_of_v<ObjectRef, T>)>>
        Optional<T> getConfig(const std::string& key, Optional<T> default_value = NullOpt) const {

            if (!(*this)->config.defined()) {
                return default_value;
            }

            if ((*this)->config.count(key)) {
                return Downcast<Optional<T>>((*this)->config[key]);
            }

            return default_value;
        }

        template <typename T, typename = typename std::enable_if_t<(std::is_base_of_v<ObjectRef, T>)>>
        Optional<T> getConfig(const std::string& key, T default_value) const {
            return getConfig<T>(key, Optional<T>(default_value));
        }

        XIR_DLL bool isPassEnabled(const PassInfo& info) const;

        XIR_DLL void _enterWithScope();
        XIR_DLL void _exitWithScope();
    };

    class PassInfoNode : public NodeBase<PassInfoNode, Node> {
    public:
        String name;
        uint64_t opt_level;
        Array<String> required_passes;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;
    };

    class PassInfo : public HandleBase<PassInfo, Handle, PassInfoNode> {
    public:
        PassInfo() = default;

        XIR_DLL PassInfo(String name, uint64_t opt_level = 0, Array<String> required_passes = {});
    };

    class Network;

    class PassNode : public NodeBase<PassNode, Node> {
    public:
        PassInfo pass_info;

        virtual void accept(AttrVisitor& visitor) override {
            visitor.visit("pass_info", pass_info);
        };

        virtual Network operator()(Network network, const PassContext& pass_ctx) const = 0;
    };

    class Pass : public VirtualBase<Pass, Handle, PassNode> {
    public:
        XIR_DLL Network operator()(Network network, const PassContext& pass_ctx = PassContext::Current()) const;

        XIR_DLL static Pass Create(const std::string& name, const icraft::midware::path& dll_path = {}, const std::string& env_var = "");
        #if !defined(_BAREME)
        XIR_DLL static Pass Create(const std::string& name, const std::filesystem::path& dll_path, const std::string& env_var = "");
        #endif
        XIR_DLL Pass& setName(String name);

        XIR_DLL Pass& setOptLevel(uint64_t opt_level);

        XIR_DLL Pass& setRequiredPasses(Array<String> required_passes);

        XIR_DLL Pass& setPassInfo(PassInfo pass_info);
    };

    class NetworkPassNode : public NodeBase<NetworkPassNode, PassNode> {
    public:
        std::function<Network(Network, const PassContext&)> pass_func;

        XIR_DLL virtual Network operator()(Network network, const PassContext& pass_ctx) const override final;
    };

    class NetworkPass : public HandleBase<NetworkPass, Pass, NetworkPassNode> {
    public:
        NetworkPass() = default;

        NetworkPass(
            std::function<Network(Network, const PassContext&)> pass_func,
            String name,
            uint64_t opt_level = 0,
            Array<String> required_passes = {}
        ) : NetworkPass(pass_func, PassInfo(std::move(name), opt_level, std::move(required_passes)))
        {}

        XIR_DLL NetworkPass(std::function<Network(Network, const PassContext&)> pass_func, PassInfo pass_info);
    };

    class SequentialPassNode : public NodeBase<SequentialPassNode, PassNode> {
    public:
        Array<Pass> passes;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL virtual Network operator()(Network network, const PassContext& pass_ctx) const override final;
    };

    class SequentialPass : public HandleBase<SequentialPass, Pass, SequentialPassNode> {
    public:
        SequentialPass() = default;

        SequentialPass(
            const std::vector<std::string>& pass_names,
            String name,
            uint64_t opt_level = 0,
            Array<String> required_passes = {},
            const std::string& env_var = ""
        ) : SequentialPass(pass_names, PassInfo(std::move(name), opt_level, std::move(required_passes)), env_var)
        {}

        SequentialPass(
            Array<Pass> passes,
            String name,
            uint64_t opt_level = 0,
            Array<String> required_passes = {}
        ) : SequentialPass(std::move(passes), PassInfo(std::move(name), opt_level, std::move(required_passes)))
        {}

        XIR_DLL SequentialPass(
            const std::vector<std::string>& pass_names,
            PassInfo pass_info = PassInfo("sequential"),
            const std::string& env_var = ""
        );

        XIR_DLL SequentialPass(Array<Pass> passes, PassInfo pass_info = PassInfo("sequential"));
    };
}
</pre>
```
