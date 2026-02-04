// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvec_multi_core.h for the primary calling header

#include "Vvec_multi_core__pch.h"

void Vvec_multi_core___024unit___ctor_var_reset(Vvec_multi_core___024unit* vlSelf);

void Vvec_multi_core___024unit::ctor(Vvec_multi_core__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vvec_multi_core___024unit___ctor_var_reset(this);
}

void Vvec_multi_core___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vvec_multi_core___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
