# Program Listing for File json.h



↰ [Return to documentation for file](file_icraft-xir_serialize_json.h.md#file-icraft-xir-serialize-json-h) (`icraft-xir\serialize\json.h`)


```cpp
#pragma once
#include <icraft-xir/core/reflection.h>
#include <icraft-xir/utils/json.hpp>

namespace icraft::xir {

    using Json = nlohmann::json;

    class JsonPrinter : public AttrVisitor {
    private:
        XIR_DLL virtual void _visit(std::string_view key, float& value);
        XIR_DLL virtual void _visit(std::string_view key, int64_t& value);
        XIR_DLL virtual void _visit(std::string_view key, uint64_t& value);
        XIR_DLL virtual void _visit(std::string_view key, int& value);
        XIR_DLL virtual void _visit(std::string_view key, bool& value);
        XIR_DLL virtual void _visit(std::string_view key, std::string& value, std::string_view tinfo = "");
        XIR_DLL virtual void _visit(std::string_view key, ObjectRef& value, std::string_view tinfo);

        XIR_DLL Json dumpArray(const ObjectRef& ref, std::string_view tinfo);

    public:
        XIR_DLL Json dump(const ObjectRef& ref, std::string_view tinfo = TypeName<ObjectRef>());

        Json _json;
    };

    class Network;

    class JsonParser : public AttrVisitor {
    private:
        XIR_DLL virtual void _visit(std::string_view key, float& value);
        XIR_DLL virtual void _visit(std::string_view key, int64_t& value);
        XIR_DLL virtual void _visit(std::string_view key, uint64_t& value);
        XIR_DLL virtual void _visit(std::string_view key, int& value);
        XIR_DLL virtual void _visit(std::string_view key, bool& value);
        XIR_DLL virtual void _visit(std::string_view key, std::string& value, std::string_view tinfo = "");
        XIR_DLL virtual void _visit(std::string_view key, ObjectRef& value, std::string_view tinfo);

        XIR_DLL ObjectRef parseArray(Json& json, std::string_view tinfo);

        XIR_DLL Operation parseOperation(Json& j_op);

    public:
        XIR_DLL ObjectRef parse(Json& json, std::string_view tinfo = TypeName<ObjectRef>());

        Json _json;
    };

    class ParamsDumper : public AttrVisitor {
    private:
        virtual void _visit(std::string_view key, float& value) {}
        virtual void _visit(std::string_view key, int64_t& value) {}
        virtual void _visit(std::string_view key, uint64_t& value) {}
        virtual void _visit(std::string_view key, int& value) {}
        virtual void _visit(std::string_view key, bool& value) {}
        virtual void _visit(std::string_view key, std::string& value, std::string_view tinfo = "") {}

        virtual void _visit(std::string_view key, ObjectRef& value, std::string_view tinfo) {
            genParamsTable(value);
        }

        XIR_DLL void genParamsTable(const ObjectRef& ref);

        std::unordered_map<int, std::tuple<uint64_t, const char*>> params_table_;
        std::ostream& stream_;

    public:
        ParamsDumper(std::ostream& stream) : stream_(stream) {}

        XIR_DLL uint64_t dump(const ObjectRef& ref);

        XIR_DLL uint64_t calcMd5(const ObjectRef& ref);
    };

    class ParamsLoader : public AttrVisitor {
    private:
        virtual void _visit(std::string_view key, float& value) {}
        virtual void _visit(std::string_view key, int64_t& value) {}
        virtual void _visit(std::string_view key, uint64_t& value) {}
        virtual void _visit(std::string_view key, int& value) {}
        virtual void _visit(std::string_view key, bool& value) {}
        virtual void _visit(std::string_view key, std::string& value, std::string_view tinfo = "") {}

        virtual void _visit(std::string_view key, ObjectRef& value, std::string_view tinfo) {
            loadParams(value);
        }

        XIR_DLL void loadParams(ObjectRef& ref);

        std::unordered_map<int, uint64_t> offset_map_;
        std::istream& stream_;

    public:
        ParamsLoader(std::istream& stream) : stream_(stream) {}

        XIR_DLL void load(ObjectRef& ref);
    };

    class ParamsLazyLoader : public AttrVisitor {
    private:
        virtual void _visit(std::string_view key, float& value) {}
        virtual void _visit(std::string_view key, int64_t& value) {}
        virtual void _visit(std::string_view key, uint64_t& value) {}
        virtual void _visit(std::string_view key, int& value) {}
        virtual void _visit(std::string_view key, bool& value) {}
        virtual void _visit(std::string_view key, std::string& value, std::string_view tinfo = "") {}

        virtual void _visit(std::string_view key, ObjectRef& value, std::string_view tinfo) {
            loadParams(value);
        }

        XIR_DLL void loadParams(ObjectRef& ref);

        static void null_deleter(const char*) {}

        std::unordered_map<int, uint64_t> offset_map_;
        char* mapped_ptr_;

    public:
        ParamsLazyLoader(char* mapped_ptr) : mapped_ptr_(mapped_ptr) {}

        XIR_DLL void load(ObjectRef& ref);
    };

    XIR_DLL std::string CalcMD5(std::istream& stream);

    XIR_DLL std::string CalcMD5(char* ptr, uint64_t byte_size);

    XIR_DLL std::ostream& operator<<(std::ostream& os, const ObjectRef& ref);

    XIR_DLL std::ostream& operator<<(std::ostream& os, const Object* obj);
}
</pre>
```
