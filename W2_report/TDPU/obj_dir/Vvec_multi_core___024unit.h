// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vvec_multi_core.h for the primary calling header

#ifndef VERILATED_VVEC_MULTI_CORE___024UNIT_H_
#define VERILATED_VVEC_MULTI_CORE___024UNIT_H_  // guard

#include "verilated.h"


class Vvec_multi_core__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vvec_multi_core___024unit final {
  public:

    // INTERNAL VARIABLES
    Vvec_multi_core__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vvec_multi_core___024unit() = default;
    ~Vvec_multi_core___024unit() = default;
    void ctor(Vvec_multi_core__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vvec_multi_core___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
