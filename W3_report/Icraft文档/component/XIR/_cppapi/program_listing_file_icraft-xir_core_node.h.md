# Program Listing for File node.h



↰ [Return to documentation for file](file_icraft-xir_core_node.h.md#file-icraft-xir-core-node-h) (`icraft-xir\core\node.h`)


```cpp
#pragma once
#include <icraft-xir/base/dllexport.h>
#include <icraft-xir/base/object.h>
#include <icraft-xir/base/type_trait.h>

#include <string_view>

namespace icraft::xir {

    class ReduceVisitor;
    class AttrVisitor;

    class Node : public Object {
    public:
        static constexpr std::string_view type_key = detail::n<Node>();

        virtual std::string_view typeKey() const override {
            return type_key;
        }

        virtual void accept(AttrVisitor& visitor) = 0;

        virtual bool reduceAccept(Node* other, const ReduceVisitor& reduce) const = 0;
        virtual bool parentReduceAccept(Node* other, const ReduceVisitor& reduce) const = 0;
    };

    XIR_DLL bool ExecOverriveFunc(const Node* self, Node* other, const ReduceVisitor& reduce, std::string_view type_key, bool& ans);

    template <typename ConcreteNode, typename BaseNode>
    class NodeBase : public BaseNode {
    public:
        using ParentNode = BaseNode;

        static constexpr std::string_view type_key = detail::n<ConcreteNode>();

        virtual std::string_view typeKey() const override {
            return type_key;
        }

        bool reduceAccept(ConcreteNode* other, const ReduceVisitor& reduce) const {
            return true;
        }

        virtual bool reduceAccept(Node* other, const ReduceVisitor& reduce) const override {

            bool ans = true;

            if (ExecOverriveFunc(this, other, reduce, ConcreteNode::type_key, ans)) {
                return ans;
            }
            else {
                return static_cast<const ConcreteNode*>(this)->
                    reduceAccept(static_cast<ConcreteNode*>(other), reduce);
            }
        }

        virtual bool parentReduceAccept(Node* other, const ReduceVisitor& reduce) const override {

            if constexpr (std::is_same_v<ParentNode, Node>) {
                return true;
            }
            else {
                bool parent_result = ParentNode::parentReduceAccept(static_cast<BaseNode*>(other), reduce);

                bool ans = true;

                if (ExecOverriveFunc(this, other, reduce, ParentNode::type_key, ans)) {
                    return parent_result && ans;
                }
                else {
                    return parent_result && static_cast<const ParentNode*>(this)->
                        reduceAccept(static_cast<ParentNode*>(other), reduce);
                }
            }
        }
    };

    template <typename ConcreteType, typename BaseType, typename NodeObject>
    class VirtualBase : public BaseType {
    public:
        using NodeType = NodeObject;

        static ConcreteType Get(ObjectPtr<Object> node) {
            auto handle = ConcreteType();
            handle.data_ = std::move(node);
            return handle;
        }

        const NodeType* operator->() const { return static_cast<const NodeType*>(ObjectRef::get()); }

        const NodeType* get() const { return operator->(); }

        template <typename ChildType,
            typename = typename std::enable_if_t<std::is_base_of_v<ConcreteType, ChildType>>>
        bool is() const {
            return (*this)->template isInstance<typename ChildType::NodeType>();
        }

        template <typename ChildType,
            typename = typename std::enable_if_t<std::is_base_of_v<ConcreteType, ChildType>>>
        ChildType cast() const {
            return Downcast<ChildType>(*this);
        }

        ConcreteType clone(int64_t depth = 1) const {
            return Downcast<ConcreteType>(ObjectRef::clone(depth));
        }

    protected:

        NodeType* get_mutable() const { return static_cast<NodeType*>(ObjectRef::get_mutable()); }
    };

    template <typename ConcreteType, typename BaseType, typename NodeObject>
    class HandleBase : public VirtualBase<ConcreteType, BaseType, NodeObject> {
    public:
        static ConcreteType Init() {
            auto node = make_object<NodeObject>();
            return VirtualBase<ConcreteType, BaseType, NodeObject>::Get(std::move(node));
        }
    };

    template <typename ConcreteType, typename BaseType, typename NodeObject>
    class MutableHandleBase : public VirtualBase<ConcreteType, BaseType, NodeObject> {
    public:
        static ConcreteType Init() {
            auto node = make_object<NodeObject>();
            return VirtualBase<ConcreteType, BaseType, NodeObject>::Get(std::move(node));
        }

        using VirtualBase<ConcreteType, BaseType, NodeObject>::get_mutable;
    };

    class Handle : public VirtualBase<Handle, ObjectRef, Node> {};
}
</pre>
```
