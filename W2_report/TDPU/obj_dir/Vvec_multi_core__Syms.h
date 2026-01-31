// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VVEC_MULTI_CORE__SYMS_H_
#define VERILATED_VVEC_MULTI_CORE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vvec_multi_core.h"

// INCLUDE MODULE CLASSES
#include "Vvec_multi_core___024root.h"
#include "Vvec_multi_core___024unit.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vvec_multi_core__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vvec_multi_core* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vvec_multi_core___024root      TOP;

    // CONSTRUCTORS
    Vvec_multi_core__Syms(VerilatedContext* contextp, const char* namep, Vvec_multi_core* modelp);
    ~Vvec_multi_core__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
