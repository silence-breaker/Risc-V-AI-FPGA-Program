# Program Listing for File network.h



↰ [Return to documentation for file](file_icraft-xir_core_network.h.md#file-icraft-xir-core-network-h) (`icraft-xir\core\network.h`)


```cpp
#pragma once
#include <icraft-xir/base/map.h>
#include <icraft-xir/base/string.h>
#include <icraft-xir/core/operation.h>
#include <icraft-xir/core/pattern.h>
#include <icraft-xir/utils/wise_enum.h>
#include <icraft-utils/dll.h>
#include <icraft-utils/midware/filestream.hpp>

namespace icraft::xir {

    // enum class Framework {
    //  PYTORCH,        ///< Pytorch框架
    //  CAFFE,          ///< Caffe框架
    //  TENSORFLOW,     ///< Tensorflow框架
    //  DARKNET,        ///< Darknet框架
    //  ONNX            ///< ONNX框架
    // };

    // enum class Serialize {
    //  JSON,           ///< Json
    //  RAW,            ///< Raw
    //  MESSAGEPACK,    ///< MessagePack
    //  FLATBUFFERS     ///< FlatBuffers
    // };
    WISE_ENUM_CLASS(Framework, PYTORCH, CAFFE, TENSORFLOW, DARKNET, ONNX);
    WISE_ENUM_CLASS(Serialize, JSON, RAW, MESSAGEPACK, FLATBUFFERS);

    class NetworkRewriter;
    class NetworkView;

    class NetworkBaseNode : public NodeBase<NetworkBaseNode, Node> {
    public:
        Array<Operation> ops;
        CompileTarget ai_target = BuyiTarget::Init();

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(NetworkBaseNode* other, const ReduceVisitor& reduce) const;

    protected:
        std::map<int64_t, int64_t> op_index_map_;
        std::map<int64_t, Value> value_map_;
        std::map<int64_t, std::map<int64_t, int64_t>> value_uses_map_;

    private:
        XIR_DLL virtual const Array<Value>& inputs() const;
        XIR_DLL virtual const Array<Value>& outputs() const;

        friend class NetworkBase;
    };

    class NetworkBase : public HandleBase<NetworkBase, Handle, NetworkBaseNode> {
    public:
        XIR_DLL const Array<Value>& inputs() const;

        XIR_DLL const Array<Value>& outputs() const;

        XIR_DLL Operation operator[](int64_t index) const;

        XIR_DLL Operation getOpById(int64_t op_id) const;

        XIR_DLL Array<Operation> getOpsById(const Array<int64_t>& op_ids) const;

        XIR_DLL const Value& getValueById(int64_t v_id) const;

        XIR_DLL Array<Params> allParams() const;

        XIR_DLL Array<Value> getValuesById(const Array<int64_t>& value_ids) const;

        XIR_DLL Array<Operation> getUsesOpByValueId(int64_t v_id) const;

        XIR_DLL size_t getUsesNumByValueId(int64_t v_id) const;

        XIR_DLL int64_t getOpIndexById(int64_t op_id) const;

        XIR_DLL Operation getPreOpById(int64_t op_id) const;

        XIR_DLL Operation getNextOpById(int64_t op_id) const;

        XIR_DLL Array<Operation> getProducersByOpId(int64_t op_id, bool sorted = false) const;

        XIR_DLL Array<Operation> getConsumersByOpId(int64_t op_id, bool sorted = false) const;

        XIR_DLL NetworkView view(Array<Operation> ops) const;

        XIR_DLL NetworkView view(const std::vector<int64_t>& op_ids) const;

        XIR_DLL NetworkView viewExcept(const std::vector<int64_t>& op_ids) const;

        XIR_DLL NetworkView view(int64_t start_index, int64_t end_index) const;

        XIR_DLL NetworkView viewByOpId(int64_t start_op_id, int64_t end_op_id) const;

        XIR_DLL NetworkView view(int64_t start_index = 0) const;

        XIR_DLL NetworkView view(std::function<bool(const Operation& op)> judge) const;

        XIR_DLL NetworkBase& setAITarget(const CompileTarget& ai_target);

    protected:
        void removeValueUses(const Value& v, int64_t op_id);
        void removeValueUsesById(int64_t v_id, int64_t op_id);
        void addValueUses(const Value& v, int64_t op_id);
        void addValueUsesById(int64_t v_id, int64_t op_id);

        void changeOpIdById(int64_t old_id, int64_t new_id);
        void changeValueIdById(int64_t old_id, int64_t new_id);

        bool checkIsFirstOpById(int64_t op_id) const;
        bool checkIsLastOpById(int64_t op_id) const;
        void replaceValue(Value src, Value dest);

        bool isInOrder() const;

        void reorderExecutionSequence();
    };

    class NetworkNode : public NodeBase<NetworkNode, NetworkBaseNode> {
    public:
        std::string name;
        Framework framework_kind;
        std::string framework_version;
        std::string icraft_xir_version;
        std::string icraft_version;
        uint64_t params_bytes = 0;
        std::string params_md5 = "d41d8cd98f00b204e9800998ecf8427e";
        Map<String, ObjectRef> tags;

    private:
        NetworkRewriter* rewriter_;

        int64_t values_id_ = 0;
        int64_t ops_id_ = 0;
        void* mapped_addr_ = nullptr;
        uint64_t mapped_byte_size_;
        friend Network;

        XIR_DLL virtual const Array<Value>& inputs() const override;
        XIR_DLL virtual const Array<Value>& outputs() const override;

    public:
        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(NetworkNode* other, const ReduceVisitor& reduce) const;

        XIR_DLL ~NetworkNode();
    };

    class Network : public HandleBase<Network, NetworkBase, NetworkNode> {
    public:
        Network() = default;

        XIR_DLL Network(const std::string& name, Framework framework_kind, const std::string& framework_version, CompileTarget ai_target = BuyiTarget::Init());

        XIR_DLL Network& setName(const std::string& name);

        XIR_DLL Network& setTag(const std::string& key, ObjectRef value);

        XIR_DLL std::optional<ObjectRef> getTag(const std::string& key) const;

        XIR_DLL bool removeTag(const std::string& key);

        XIR_DLL Network& insertOp(const Array<Operation>::const_iterator& it, Operation op);

        XIR_DLL Network& insertOp(int64_t op_index, Operation op);

        XIR_DLL Network& insertOpById(int64_t op_id, Operation op);

        XIR_DLL Network& addOp(Operation op);

        XIR_DLL Network& removeOpById(int64_t op_id);

        XIR_DLL Network& removeOpsById(const std::vector<int64_t>& op_ids);

        template <typename F, typename = std::enable_if_t<std::is_same_v<bool, std::invoke_result_t<F, Operation>>>>
        Network& removeOp(F f) {

            for (auto&& op : (*this)->ops) {
                if (f(op)) {
                    removeOpById(op->op_id);
                }
            }

            return *this;
        }

        XIR_DLL Network& replaceOpById(int64_t op_id, Operation op);

        XIR_DLL Network& replaceOpByIdKeepUses(int64_t op_id, Operation op);

        XIR_DLL Network& replaceOp(Operation src, Operation dest);

        XIR_DLL Network& replaceOpKeepUses(Operation src, Operation dest);

        XIR_DLL void dumpJson(std::ostream& stream, bool calc_md5 = true) const;

        //XIR_DLL void dumpMSG(std::ostream& stream, bool calc_md5 = true) const;

        XIR_DLL void dumpFlat(std::ostream& stream, bool calc_md5 = true) const;

        XIR_DLL void dumpParams(std::ostream& stream) const;

        XIR_DLL void dumpToFile(const icraft::midware::path& file_path, Serialize mode, bool calc_md5 = true, bool validate = true) const;
        #if !defined(_BAREME)
        XIR_DLL void dumpToFile(const std::filesystem::path& file_path, Serialize mode, bool calc_md5 = true, bool validate = true) const;
        #endif
        XIR_DLL void dumpJsonToFile(const icraft::midware::path& file_path, bool calc_md5 = true, bool validate = true) const;
        #if !defined(_BAREME)
        XIR_DLL void dumpJsonToFile(const std::filesystem::path& file_path, bool calc_md5 = true, bool validate = true) const;
        #endif
        XIR_DLL void dumpParamsToFile(const icraft::midware::path& file_path) const;
        #if !defined(_BAREME)
        XIR_DLL void dumpParamsToFile(const std::filesystem::path& file_path) const;
        #endif

        //XIR_DLL void dumpMSGToFile(const icraft::midware::path& file_path, bool calc_md5 = true, bool validate = true) const;

        XIR_DLL void dumpFlatToFile(const icraft::midware::path& file_path, bool calc_md5 = true, bool validate = true) const;
        #if !defined(_BAREME)
        XIR_DLL void dumpFlatToFile(const std::filesystem::path& file_path, bool calc_md5 = true, bool validate = true) const;
        #endif

        XIR_DLL static Network CreateFromJsonFile(const icraft::midware::path& file_path);
        #if !defined(_BAREME)
        XIR_DLL static Network CreateFromJsonFile(const std::filesystem::path& file_path);
        #endif

        // XIR_DLL static Network CreateFromMSGFile(const icraft::midware::path& file_path);

        XIR_DLL static Network CreateFromFlatFile(const icraft::midware::path& file_path);
        #if !defined(_BAREME)
        XIR_DLL static Network CreateFromFlatFile(const std::filesystem::path& file_path);
        #endif
        XIR_DLL void loadParams(std::istream& stream, bool calc_md5 = true);

        XIR_DLL void loadParamsFromFile(const icraft::midware::path& file_path, bool calc_md5 = true);
        #if !defined(_BAREME)
        XIR_DLL void loadParamsFromFile(const std::filesystem::path& file_path, bool calc_md5 = true);
        #endif

        XIR_DLL void lazyLoadParams(char* mapped_ptr, uint64_t byte_size, bool calc_md5 = true);

        XIR_DLL void lazyLoadParamsFromFile(const icraft::midware::path& file_path, bool calc_md5 = true);
        XIR_DLL void lazyLoadParamsFromFile(const std::string& file_path, bool calc_md5 = true);
        #if !defined(_BAREME)
        XIR_DLL void lazyLoadParamsFromFile(const std::filesystem::path& file_path, bool calc_md5);
        #endif

        XIR_DLL std::vector<MatchGroup> search(const Pattern& pattern) const;

        XIR_DLL MatchGroup searchOnce(const Pattern& pattern) const;

        using PatternCallback = std::function<void(Network& network, const MatchGroup& result)>;

        XIR_DLL void rewrite(const Pattern& pattern, PatternCallback callback, uint64_t times = 10000);

        XIR_DLL Network& replaceGroup(const MatchGroup& src, Operation dest);

        using ValueUsesInfo = std::vector<std::tuple<Operation, std::set<int64_t>>>;

        XIR_DLL ValueUsesInfo getUsesInfo(const Value& v) const;

        XIR_DLL ValueUsesInfo getUsesInfoExceptMatch(const Value& v, const MatchGroup& match) const;

        XIR_DLL Network& connect(const Value& from, Operation to, uint64_t index);

        XIR_DLL Network& connect(const Value& from, Operation to);

        XIR_DLL Network& connect(const Value& from, const ValueUsesInfo& to);

        XIR_DLL NetworkRewriter& rewriter() const;

        XIR_DLL operator NetworkView() const;

        XIR_DLL void validate() const;

    private:
        int64_t genValueId();
        int64_t genOpId();
        void calcMd5(bool enable = true) const;

        friend class Operation;
        friend class Value;
    };

    class NetworkRewriter {
    public:
        void Continue() { is_continue = true; }

        void Break() { is_break = true; }

    private:
        bool is_continue = false;
        bool is_break = false;
        uint64_t current = 0;

        XIR_DLL void rewrite(Network& network, const Pattern& pattern, Network::PatternCallback callback, uint64_t times);

        friend class Network;
    };

    class NetworkViewNode : public NodeBase<NetworkViewNode, NetworkBaseNode> {
    public:
        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(NetworkViewNode* other, const ReduceVisitor& reduce) const;

    private:
        Array<Value> inputs_;
        Array<Value> outputs_;
        Network network_;
        friend class NetworkView;

        XIR_DLL virtual const Array<Value>& inputs() const override;
        XIR_DLL virtual const Array<Value>& outputs() const override;
    };

    class NetworkView : public HandleBase<NetworkView, NetworkBase, NetworkViewNode> {
    public:
        NetworkView() = default;

    private:
        XIR_DLL NetworkView(const NetworkBase& network, Array<Operation> ops);

        friend class NetworkBase;

    public:
        XIR_DLL Network network() const;

        XIR_DLL Network toNetwork() const;

        XIR_DLL NetworkView& setOutputsOrderByValueIds(const std::vector<int64_t>& value_ids);
    };
}
</pre>
```
