// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vvec_multi_core.h for the primary calling header

#ifndef VERILATED_VVEC_MULTI_CORE___024ROOT_H_
#define VERILATED_VVEC_MULTI_CORE___024ROOT_H_  // guard

#include "verilated.h"


class Vvec_multi_core__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vvec_multi_core___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(i_data_valid,0,0);
    VL_IN8(i_load_weight,0,0);
    VL_INW(i_data,127,0,4);
    VL_IN(i_weight,31,0);
    VL_OUT8(o_data_ready,0,0);
    IData/*31:0*/ vec_multi_core__DOT__weight_reg;
    CData/*0:0*/ vec_multi_core__DOT__o_valid_stage1;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
    VL_OUT(o_result,31,0);
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__511__03a480__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__479__03a448__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__447__03a416__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__415__03a384__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__383__03a352__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__351__03a320__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__319__03a288__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__287__03a256__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__255__03a224__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__223__03a192__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__191__03a160__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__159__03a128__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__127__03a96__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__95__03a64__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__63__03a32__KET__;
    IData/*31:0*/ vec_multi_core__DOT__product__BRA__31__03a0__KET__;
    VlWide<4>/*127:0*/ vec_multi_core__DOT__sum_temp;
    IData/*31:0*/ vec_multi_core__DOT__unnamedblk1__DOT__k;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;

    // INTERNAL VARIABLES
    Vvec_multi_core__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vvec_multi_core___024root(Vvec_multi_core__Syms* symsp, const char* namep);
    ~Vvec_multi_core___024root();
    VL_UNCOPYABLE(Vvec_multi_core___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
