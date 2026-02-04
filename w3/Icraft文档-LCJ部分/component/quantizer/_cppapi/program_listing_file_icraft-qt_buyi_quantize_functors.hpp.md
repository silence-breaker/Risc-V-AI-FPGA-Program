# Program Listing for File functors.hpp

# Program Listing for File functors.hpp

↰ [Return to documentation for file](file_icraft-qt_buyi_quantize_functors.hpp.md#file-icraft-qt-buyi-quantize-functors-hpp) (`icraft-qt\buyi\quantize\functors.hpp`)

```
#pragma once
#include <icraft-xir/core/functor.h>

#include <icraft-qt/core/quantizer_options.h>
#include <icraft-qt/core/quantizer_logger.h>

namespace icraft::qt {
    class BuyiQuantize : public icraft::xir::OpTraitFunctor<
        BuyiQuantize,
        void(const icraft::xir::Operation&, const QuantizerOptions& options, icraft::qt::QuantizerLogger& logger)
    > {
    public:
        template <typename T>
        explicit BuyiQuantize(T t) : OpTraitFunctor(std::move(t)) {}
    protected:
        QT_API static FunctorType& VTable();
    };
}
```