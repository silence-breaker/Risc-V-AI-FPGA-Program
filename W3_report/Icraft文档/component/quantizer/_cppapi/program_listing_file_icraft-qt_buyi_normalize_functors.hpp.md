# Program Listing for File functors.hpp

# Program Listing for File functors.hpp

↰ [Return to documentation for file](file_icraft-qt_buyi_normalize_functors.hpp.md#file-icraft-qt-buyi-normalize-functors-hpp) (`icraft-qt\buyi\normalize\functors.hpp`)

```
#pragma once
#include <icraft-xir/core/functor.h>

#include <icraft-qt/core/quantizer_options.h>
#include <icraft-qt/core/quantizer_logger.h>

namespace icraft::qt {
    class BuyiNormratio : public icraft::xir::OpTraitFunctor<
        BuyiNormratio,
        void(const icraft::xir::Operation&, const QuantizerOptions& options, QuantizerLogger& logger)
    > {
    public:
        template <typename T>
        explicit BuyiNormratio(T t) : OpTraitFunctor(std::move(t)) {}
    protected:
        QT_API static FunctorType& VTable();
    };

    class BuyiNormalize : public icraft::xir::OpTraitFunctor<
        BuyiNormalize,
        void(const icraft::xir::Operation&, const QuantizerOptions& options, QuantizerLogger& logger)
    > {
    public:
        template <typename T>
        explicit BuyiNormalize(T t) : OpTraitFunctor(std::move(t)) {}
    protected:
        QT_API static FunctorType& VTable();
    };
}
```