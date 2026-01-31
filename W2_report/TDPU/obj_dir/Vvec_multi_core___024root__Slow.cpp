// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvec_multi_core.h for the primary calling header

#include "Vvec_multi_core__pch.h"

void Vvec_multi_core___024root___ctor_var_reset(Vvec_multi_core___024root* vlSelf);

Vvec_multi_core___024root::Vvec_multi_core___024root(Vvec_multi_core__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vvec_multi_core___024root___ctor_var_reset(this);
}

void Vvec_multi_core___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vvec_multi_core___024root::~Vvec_multi_core___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
