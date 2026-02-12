# Program Listing for File compile_target.h



↰ [Return to documentation for file](file_icraft-xir_core_compile_target.h.md#file-icraft-xir-core-compile-target-h) (`icraft-xir\core\compile_target.h`)


```cpp
#pragma once
#include <icraft-xir/core/node.h>
#include <icraft-xir/utils/wise_enum.h>

namespace icraft::xir {

    class CompileTargetNode : public NodeBase<CompileTargetNode, Node> {
    public:
        virtual void accept(AttrVisitor& visitor) override {}
    };

    class CompileTarget : public VirtualBase<CompileTarget, Handle, CompileTargetNode> {};

    class HostTargetNode : public NodeBase<HostTargetNode, CompileTargetNode> {};

    class HostTarget : public HandleBase<HostTarget, CompileTarget, HostTargetNode> {};

    class FPGATargetNode : public NodeBase<FPGATargetNode, CompileTargetNode> {};

    class FPGATarget : public HandleBase<FPGATarget, CompileTarget, FPGATargetNode> {};

    class CustomTargetNode : public NodeBase<CustomTargetNode, CompileTargetNode> {};

    class CustomTarget : public HandleBase<CustomTarget, CompileTarget, CustomTargetNode> {};

    class BuyiTargetNode : public NodeBase<BuyiTargetNode, CompileTargetNode> {};

    class BuyiTarget : public HandleBase<BuyiTarget, CompileTarget, BuyiTargetNode> {};

    class ZhugeTargetNode : public NodeBase<ZhugeTargetNode, CompileTargetNode> {
    public:
        WISE_ENUM_CLASS_MEMBER(Core, ZG330, ZG340, ZG30S);

        Core core = Core::ZG330;

        XIR_DLL void accept(AttrVisitor& visitor);

        XIR_DLL bool reduceAccept(ZhugeTargetNode* other, const ReduceVisitor& reduce) const;
    };

    class ZhugeTarget : public HandleBase<ZhugeTarget, CompileTarget, ZhugeTargetNode> {
    public:
        using Core = ZhugeTargetNode::Core;

        ZhugeTarget() = default;

        XIR_DLL ZhugeTarget(Core core);
    };

    class WolongTargetNode : public NodeBase<WolongTargetNode, CompileTargetNode> {};

    class WolongTarget : public HandleBase<WolongTarget, CompileTarget, WolongTargetNode> {};
}
</pre>
```
