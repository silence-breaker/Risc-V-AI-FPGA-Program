# Program Listing for File pattern.h



↰ [Return to documentation for file](file_icraft-xir_core_pattern.h.md#file-icraft-xir-core-pattern-h) (`icraft-xir\core\pattern.h`)


```cpp
#pragma once
#include <icraft-xir/base/any.h>
#include <icraft-xir/base/string.h>
#include <icraft-xir/core/compile_target.h>
#include <icraft-xir/core/data.h>

namespace icraft::xir {

    class PatternNode : public NodeBase<PatternNode, Node> {
    public:
        virtual void accept(AttrVisitor& visitor) override {};
    };

    class Pattern : public VirtualBase<Pattern, Handle, PatternNode> {};

    class AttrPatternNode : public NodeBase<AttrPatternNode, PatternNode> {
    public:
        std::string key;
        Any value;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;
    };

    class AttrPattern : public HandleBase<AttrPattern, Pattern, AttrPatternNode> {
    public:
        AttrPattern() = default;

        XIR_DLL AttrPattern(std::string key, Any value);
    };

    class AnycardsPatternNode : public NodeBase<AnycardsPatternNode, PatternNode> {};

    class AnycardsPattern : public HandleBase<AnycardsPattern, Pattern, AnycardsPatternNode> {};

    class OpPatternNode;
    class OptionalOpPatternNode;
    class ValuePattern;

    class OpPattern : public HandleBase<OpPattern, Pattern, OpPatternNode> {
    public:
        OpPattern() = default;

        XIR_DLL explicit OpPattern(std::vector<std::string_view> op_types);

        XIR_DLL OpPattern& operator()(Array<ValuePattern> inputs);

        template <typename... Args>
        OpPattern& operator()(Args... args) {
            return operator()({std::forward<Args>(args)...});
        }

        XIR_DLL ValuePattern operator[](uint64_t index) const;

        XIR_DLL OpPattern& hasAttr(std::string key, Any value = Any());

        template <typename T, typename = typename std::enable_if_t<std::is_base_of_v<CompileTarget, T>>>
        OpPattern& onTarget();

        XIR_DLL OpPattern& onTarget(std::string type_key);

        XIR_DLL OpPattern& setConstraint(std::function<bool(const Operation& op)> cfunc);
    };

    class OptionalOpPattern : public HandleBase<OptionalOpPattern, OpPattern, OptionalOpPatternNode> {
    public:
        OptionalOpPattern() = default;

        XIR_DLL explicit OptionalOpPattern(std::vector<std::string_view> op_types);

        XIR_DLL OptionalOpPattern& operator()(Array<ValuePattern> inputs);
    };

    class ValuePatternNode : public NodeBase<ValuePatternNode, PatternNode> {
    public:
        OpPattern op_pattern;
        int64_t index = -1;
        int64_t uses = -1;
        TensorType dtype;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;
    };

    class ValuePattern : public HandleBase<ValuePattern, Pattern, ValuePatternNode> {
    public:
        ValuePattern() = default;

        XIR_DLL ValuePattern(OpPattern op_pattern, int64_t index = -1, int64_t uses = -1, TensorType dtype = TensorType());

        ValuePattern(AnycardsPattern) {}

        XIR_DLL ValuePattern hasUses(uint32_t uses);

        XIR_DLL ValuePattern hasDtype(TensorType dtype);

        XIR_DLL bool isWildcard() const;

        XIR_DLL bool isAnycards() const;
    };

    class OpPatternNode : public NodeBase<OpPatternNode, PatternNode> {
    public:
        Array<String> op_type;
        Array<AttrPattern> attrs;
        Array<ValuePattern> inputs;
        std::string target_type;
        std::function<bool(const Operation& op)> cfunc;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;
    };

    class OptionalOpPatternNode : public NodeBase<OptionalOpPatternNode, OpPatternNode> {
    public:
        XIR_DLL virtual void accept(AttrVisitor& visitor) override;
    };

    template <typename T, typename>
    OpPattern& OpPattern::onTarget() {
        get_mutable()->target_type = T::NodeType::type_key;
        return *this;
    }

    class OrPatternNode : public NodeBase<OrPatternNode, PatternNode> {
    public:
        Pattern left;
        Pattern right;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;
    };

    class OrPattern : public HandleBase<OrPattern, Pattern, OrPatternNode> {
    public:
        OrPattern() = default;

        XIR_DLL OrPattern(Pattern left, Pattern right);
    };

    template<typename T>
    struct IsOneOf {
        template<typename... Args>
        static constexpr bool value = std::disjunction_v<std::is_same<T, Args>...>;
    };

    template <typename P, typename = typename std::enable_if_t<
        IsOneOf<P>::template value<OpPattern, OrPattern>>,
        typename Q, typename = typename std::enable_if_t<
        IsOneOf<Q>::template value<OpPattern, OrPattern>>>
    OrPattern operator||(P left, Q right) { return OrPattern(left, right); }

    inline ValuePattern Wildcard() { return ValuePattern::Init(); }

    inline AnycardsPattern Anycards() { return AnycardsPattern::Init(); }

    template <typename... Ts>
    struct are_all_operations : std::conjunction<std::is_base_of<Operation, Ts>...> {};

    template <typename... T,
        typename = typename std::enable_if_t<are_all_operations<T...>::value>, typename... Args>
    OpPattern IsOp(Args... args) {
        auto op_types = std::vector<std::string_view>{ T::NodeType::type_key... };
        return OpPattern(op_types)({std::forward<Args>(args)...});
    }

    template <typename... T,
        typename = typename std::enable_if_t<are_all_operations<T...>::value>, typename... Args>
    OptionalOpPattern IsOptionalOp(Args... args) {
        auto op_types = std::vector<std::string_view>{ T::NodeType::type_key... };
        return OptionalOpPattern(op_types)({ std::forward<Args>(args)... });
    }

    using MatchGroup = std::unordered_map<OpPattern, Operation, ObjectPtrHash, ObjectPtrEqual>;
}

#define PATTERN_REQUIRE(x) if (!(x)) return false
</pre>
```
