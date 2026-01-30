// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_stream_accumulator.h for the primary calling header

#include "Vtb_stream_accumulator__pch.h"

void Vtb_stream_accumulator___024root___ctor_var_reset(Vtb_stream_accumulator___024root* vlSelf);

Vtb_stream_accumulator___024root::Vtb_stream_accumulator___024root(Vtb_stream_accumulator__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtb_stream_accumulator___024root___ctor_var_reset(this);
}

void Vtb_stream_accumulator___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtb_stream_accumulator___024root::~Vtb_stream_accumulator___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
