// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_vec_dot_prod.h for the primary calling header

#ifndef VERILATED_VTB_VEC_DOT_PROD___024ROOT_H_
#define VERILATED_VTB_VEC_DOT_PROD___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_vec_dot_prod__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_vec_dot_prod___024root final {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ tb_vec_dot_prod__DOT__t_vec_data;
    CData/*7:0*/ tb_vec_dot_prod__DOT__t_vec_weight;
    CData/*0:0*/ __VstlFirstIteration;
    SData/*15:0*/ tb_vec_dot_prod__DOT__t_result;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlDelayScheduler __VdlySched;

    // INTERNAL VARIABLES
    Vtb_vec_dot_prod__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_vec_dot_prod___024root(Vtb_vec_dot_prod__Syms* symsp, const char* namep);
    ~Vtb_vec_dot_prod___024root();
    VL_UNCOPYABLE(Vtb_vec_dot_prod___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
