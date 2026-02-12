# Program Listing for File session.h

```cpp
#pragma once
#ifndef XRT_SESSION_PCH_GUARD
#define XRT_SESSION_PCH_GUARD
//#include "filesystem/filesystem.h"
#include <icraft-xrt/core/backend.h>
#include <icraft-xir/core/network.h>

namespace icraft::xrt {
    using xir::Network;
    using xir::Array;

    class SessionNode : public NodeBase<SessionNode, Node> {
    public:
        std::vector<Backend> backends;
        NetworkView network_view;

        virtual void accept(AttrVisitor& visitor) override {};

        XRT_DLL ~SessionNode();

    private:
        std::vector<std::tuple<Operation, Backend, FForwardOp, std::vector<int64_t>, std::vector<int64_t>>> forwards_;
        std::unordered_map<int64_t, Tensor> tmap_;
        std::unordered_map<int64_t, uint64_t> tuses_;
        std::unordered_map<int64_t, uint64_t> index_map_;
        std::vector<int64_t> network_input_ids_;
        std::vector<int64_t> network_output_ids_;

        uint64_t current_index_ = 0;

        bool time_profile_ = false;
        bool applied = false;
        std::unordered_map<int64_t, double> wall_times_;
        std::chrono::nanoseconds total_time_;

        bool backends_need_deinit = false;

        bool log_time_ = false;
        bool log_io_ = false;

        char* map_ptr = nullptr;
        uint64_t map_byte_size;

        bool dump_output_ = false;
        std::string dump_path_;
        std::string dump_format_;

        friend class Session;
    };

    using TimeProfileResults = std::unordered_map<int64_t, std::tuple<double, double, double, double>>;

    class Session : public HandleBase<Session, Handle, SessionNode> {
    public:
        Session() = default;

        template <typename... BackendType>
        static Session Create(const NetworkView& network, const std::vector<Device>& devices) {
            auto backends = std::vector<Backend>{ BackendType::Init()... };
            auto sess = Session::Init();
            sess.bindToBackendsByOrder(network, std::move(backends), devices, true);
            return sess;
        }

        XRT_DLL static Session CreateByOrder(
            const NetworkView& network,
            std::vector<Backend> backends,
            const std::vector<Device>& devices
        );

        XRT_DLL static Session CreateWithBackends(const NetworkView& network, const std::vector<Backend>& backends);

        XRT_DLL Session sub(int64_t start_index, int64_t end_index) const;

        XRT_DLL Session sub(int64_t start_index) const;

        XRT_DLL void apply();

        XRT_DLL void enableTimeProfile(bool enable);

        XRT_DLL std::vector<Tensor> stepTo(int64_t op_id, const std::vector<Tensor>& inputs = {});

        XRT_DLL std::vector<Tensor> forward(const std::vector<Tensor>& inputs);

        XRT_DLL void forward(const std::vector<Tensor>& inputs, const std::vector<Tensor>& outputs);

        XRT_DLL std::unordered_map<int64_t, Backend> backendBindings() const;

        XRT_DLL TimeProfileResults timeProfileResults() const;

        template <typename T>
        double totalTime() const {
            return std::chrono::duration<double, typename T::period>((*this)->total_time_).count();
        }

        using CallBackFunc = std::function<void(const Session& sess, const Operation& op, const Backend& backend, std::vector<Tensor>& output_tensors)>;

        XRT_DLL void setPreCallBack(CallBackFunc func);

        XRT_DLL void setPostCallBack(CallBackFunc func);

        using ForwardOps = std::vector<std::tuple<Operation, Backend, FForwardOp, std::vector<int64_t>, std::vector<int64_t>>>;

        XRT_DLL const ForwardOps& getForwards();

        XRT_DLL void setLogIO(bool flag);

        XRT_DLL void setLogTime(bool flag);

        XRT_DLL void setDumpOutputs(bool flag, const std::string& file_path, const std::string& format);

        XRT_DLL void dumpSnapshot(const std::string& filePath);

        XRT_DLL static Session CreateWithSnapshot(
            const std::string& filePath,
            std::vector<Backend> backends,
            const std::vector<Device>& devices);


    private:
        XRT_DLL void bindToBackendsByOrder(
            const NetworkView& network,
            std::vector<Backend> backends,
            const std::vector<Device>& devices,
            bool backends_need_deinit
        );
        CallBackFunc pre_callback_;
        CallBackFunc post_callback_;

        void logIO(const Operation& op, Backend& backend);
        void logTime(const Operation& op, Backend& backend);
        void dumpOutput(const std::vector<Tensor>& output_tensors, const std::vector<xir::Value>& outputs);
    };
}
#endif //XRT_SESSION_PCH_GUARD
```

[Return to documentation for file](file_icraft-xrt_core_session.h.md#file-icraft-xrt-core-session-h)
