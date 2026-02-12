# Program Listing for File hard_op.h



↰ [Return to documentation for file](file_icraft-xir_ops_hard_op.h.md#file-icraft-xir-ops-hard-op-h) (`icraft-xir\ops\hard_op.h`)


```cpp
#pragma once
#include <icraft-xir/core/operation.h>

namespace icraft::xir {

    class HardOpNode;

    class HardOp : public OpBase<HardOp, HardOpNode> {
    public:
        HardOp() = default;

        XIR_DLL HardOp(
            Array<Value> inputs,
            Array<Params> instr,
            Array<Params> params,
            Array<int64_t> origin_ops_id,
            Map<String, IntImm> device_info,
            int64_t layer_count = 0,
            Array<HardOp> sub_hard_ops = {}
        );

        HardOp(
            Array<Value> inputs,
            Params instr,
            Params params,
            Array<int64_t> origin_ops_id,
            Map<String, IntImm> device_info,
            int64_t layer_count = 0,
            Array<HardOp> sub_hard_ops = {}
        ) : HardOp(
            inputs,
            Array<Params>{ instr  },
            Array<Params>{ params },
            origin_ops_id,
            device_info,
            layer_count,
            sub_hard_ops
        ) {}
    };

    class HardOpNode : public OpNodeBase<HardOpNode> {
    public:
        Array<Params> instr;
        Array<Params> params;
        Array<int64_t> origin_ops_id;
        Map<String, IntImm> device_info;

        int64_t layer_count;
        Array<HardOp> sub_hard_ops;

        ICRAFT_DECLARE_ATTRS(HardOpNode) {
            ICRAFT_ATTR_FIELD(instr);
            ICRAFT_ATTR_FIELD(params);
            ICRAFT_ATTR_FIELD(origin_ops_id);
            ICRAFT_ATTR_FIELD(device_info);
            ICRAFT_ATTR_FIELD(layer_count).set_default(0);
            ICRAFT_ATTR_FIELD(sub_hard_ops);
        }

        XIR_DLL virtual void validate() const override;
    };
}
</pre>
```
