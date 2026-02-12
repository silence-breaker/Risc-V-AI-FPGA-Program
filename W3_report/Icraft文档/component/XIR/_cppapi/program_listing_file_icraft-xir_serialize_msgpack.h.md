# Program Listing for File msgpack.h



↰ [Return to documentation for file](file_icraft-xir_serialize_msgpack.h.md#file-icraft-xir-serialize-msgpack-h) (`icraft-xir\serialize\msgpack.h`)


```cpp
#pragma once
#include <icraft-xir/core/network.h>
#include <icraft-xir/core/reflection.h>

namespace icraft::xir {

    class GetAttrNums : public AttrVisitor {
    private:
        virtual void _visit(std::string_view key, float& value) { attrCount++; }
        virtual void _visit(std::string_view key, int64_t& value) { attrCount++; }
        virtual void _visit(std::string_view key, uint64_t& value) { attrCount++; }
        virtual void _visit(std::string_view key, int& value) { attrCount++; }
        virtual void _visit(std::string_view key, bool& value) { attrCount++; }
        virtual void _visit(std::string_view key, std::string& value, std::string_view tinfo = "") { attrCount++; }
        virtual void _visit(std::string_view key, ObjectRef& value, std::string_view tinfo) { attrCount++; }

        int attrCount = 0;

    public:
        int getAttrNums(const ObjectRef& ref) {
            auto node = ref.as_mutable<Node>();
            node->accept(*this);
            return this->attrCount;
        }
    };

    class MSGDumper : public AttrVisitor {
    private:
        XIR_DLL virtual void _visit(std::string_view key, float& value);
        XIR_DLL virtual void _visit(std::string_view key, int64_t& value);
        XIR_DLL virtual void _visit(std::string_view key, uint64_t& value);
        XIR_DLL virtual void _visit(std::string_view key, int& value);
        XIR_DLL virtual void _visit(std::string_view key, bool& value);
        XIR_DLL virtual void _visit(std::string_view key, std::string& value, std::string_view tinfo = "");

        XIR_DLL virtual void _visit(std::string_view key, ObjectRef& value, std::string_view tinfo);

        XIR_DLL void dumpArray(const ObjectRef& ref, std::string_view tinfo);

    public:
        XIR_DLL MSGDumper();

        XIR_DLL void dump(const ObjectRef& ref, std::string_view tinfo = TypeName<ObjectRef>());

        XIR_DLL void write(std::ostream& stream);

        struct Impl_MSGD;
        std::shared_ptr<Impl_MSGD> impl_msgd;
    };

    class MSGParser : public AttrVisitor {
    private:
        XIR_DLL virtual void _visit(std::string_view key, float& value);
        XIR_DLL virtual void _visit(std::string_view key, int64_t& value);
        XIR_DLL virtual void _visit(std::string_view key, uint64_t& value);
        XIR_DLL virtual void _visit(std::string_view key, int& value);
        XIR_DLL virtual void _visit(std::string_view key, bool& value);
        XIR_DLL virtual void _visit(std::string_view key, std::string& value, std::string_view tinfo = "");

        XIR_DLL virtual void _visit(std::string_view key, ObjectRef& value, std::string_view tinfo);

    public:
        XIR_DLL MSGParser();

        XIR_DLL void read(const std::string& buffer);

        template<typename RefType> RefType parse() {
            auto node = make_object<typename RefType::NodeType>();
            node->accept(*this);
            return RefType::Get(node);
        }

        struct Impl_MSGP;
        std::shared_ptr<Impl_MSGP> impl_msgp;
    };

    Network CreateNetworkFromMSG(const std::string& buffer);
}
</pre>
```
