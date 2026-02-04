# Program Listing for File layout.h



↰ [Return to documentation for file](file_icraft-xir_core_layout.h.md#file-icraft-xir-core-layout-h) (`icraft-xir\core\layout.h`)


```cpp
#pragma once
#include <icraft-xir/base/dllexport.h>
#include <icraft-xir/base/optional.h>
#include <icraft-xir/core/node.h>

namespace icraft::xir {

    class AxisNameNode : public NodeBase<AxisNameNode, Node> {
    public:
        std::string name;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(AxisNameNode* other, const ReduceVisitor& reduce) const;
    };

    class AxisName : public HandleBase<AxisName, Handle, AxisNameNode> {
    public:
        AxisName() = default;

        XIR_DLL explicit AxisName(char name);

        XIR_DLL bool operator==(const AxisName& other) const;
    };

    class AxisUnitNode : public NodeBase<AxisUnitNode, AxisNameNode> {
    public:
        uint64_t unit;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(AxisUnitNode* other, const ReduceVisitor& reduce) const;
    };

    class AxisUnit : public HandleBase<AxisUnit, AxisName, AxisUnitNode> {
    public:
        AxisUnit() = default;

        XIR_DLL AxisUnit(char name, uint64_t unit);

        explicit AxisUnit(char name) : AxisUnit(name, 0) {}

        XIR_DLL AxisUnit& setUnit(uint64_t unit);

        XIR_DLL bool operator==(const AxisUnit& other) const;
    };

    class LayoutNode : public NodeBase<LayoutNode, Node> {
    public:
        Array<AxisName> axis_names;

        XIR_DLL virtual void accept(AttrVisitor& visitor) override;

        XIR_DLL bool reduceAccept(LayoutNode* other, const ReduceVisitor& reduce) const;
    };

    class Layout : public HandleBase<Layout, Handle, LayoutNode> {
    public:
        Layout() = default;

        XIR_DLL Layout(Array<AxisName> axis);

        XIR_DLL explicit Layout(const std::string& layout);

        XIR_DLL static Layout Default(int64_t size = 0);

        XIR_DLL static Layout NHWC();

        XIR_DLL static Layout NCHW();

        XIR_DLL static Layout HWIO();

        XIR_DLL static Layout OIHW();

        XIR_DLL bool has(char c) const;

        XIR_DLL Optional<AxisName> get(char c) const;

        XIR_DLL Layout& N();

        XIR_DLL Layout& L();

        XIR_DLL Layout& H();

        XIR_DLL Layout& W();

        XIR_DLL Layout& D();

        XIR_DLL Layout& C();

        XIR_DLL Layout& I();

        XIR_DLL Layout& O();

        XIR_DLL Layout& X(uint32_t num = 1);

        XIR_DLL Layout& n(int64_t unit);

        XIR_DLL uint64_t n() const;

        XIR_DLL Layout& l(int64_t unit);

        XIR_DLL uint64_t l() const;

        XIR_DLL Layout& h(int64_t unit);

        XIR_DLL uint64_t h() const;

        XIR_DLL Layout& w(int64_t unit);

        XIR_DLL uint64_t w() const;

        XIR_DLL Layout& d(int64_t unit);

        XIR_DLL uint64_t d() const;

        XIR_DLL Layout& c(int64_t unit);

        XIR_DLL uint64_t c() const;

        XIR_DLL Layout& i(int64_t unit);

        XIR_DLL uint64_t i() const;

        XIR_DLL Layout& o(int64_t unit);

        XIR_DLL uint64_t o() const;

        XIR_DLL bool isDefault() const;

        XIR_DLL uint64_t numAxis() const;

        XIR_DLL uint64_t getIndexOf(char c) const;

        XIR_DLL char getAxisCharName(int64_t index) const;

        XIR_DLL AxisName operator[](int64_t index) const;

        XIR_DLL Layout& swapAxis(int64_t left_index, int64_t right_index);

        XIR_DLL Layout& insertAxis(int64_t index, AxisName axis_name);

        XIR_DLL Layout& eraseAxis(int64_t index);

        XIR_DLL static bool CheckAxisNameUpper(char c);

        XIR_DLL void validate() const;

        XIR_DLL std::string toString() const;

    private:
        inline static std::string_view valid_names = "NLHWDCIO*";
    };
}
</pre>
```
