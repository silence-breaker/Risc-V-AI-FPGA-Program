// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvec_multi_core.h for the primary calling header

#include "Vvec_multi_core__pch.h"

VL_ATTR_COLD void Vvec_multi_core___024root___eval_static(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_static\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

VL_ATTR_COLD void Vvec_multi_core___024root___eval_initial(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_initial\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vvec_multi_core___024root___eval_final(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_final\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vvec_multi_core___024root___eval_settle(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_settle\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vvec_multi_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvec_multi_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vvec_multi_core___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vvec_multi_core___024root___ctor_var_reset(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___ctor_var_reset\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->i_data_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15782147128264288011ull);
    vlSelf->i_load_weight = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4599034397521178552ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->i_data, __VscopeHash, 9289791593721341457ull);
    vlSelf->i_weight = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16135871476031686068ull);
    vlSelf->o_data_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12751862293382745632ull);
    vlSelf->o_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3390268084763049377ull);
    vlSelf->vec_multi_core__DOT__weight_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16156540023285174162ull);
    vlSelf->vec_multi_core__DOT__product__BRA__511__03a480__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10959163834170578574ull);
    vlSelf->vec_multi_core__DOT__product__BRA__479__03a448__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18104957539419090559ull);
    vlSelf->vec_multi_core__DOT__product__BRA__447__03a416__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10950089306716789199ull);
    vlSelf->vec_multi_core__DOT__product__BRA__415__03a384__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12654757653160777394ull);
    vlSelf->vec_multi_core__DOT__product__BRA__383__03a352__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6109413736600685081ull);
    vlSelf->vec_multi_core__DOT__product__BRA__351__03a320__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3008970833610916541ull);
    vlSelf->vec_multi_core__DOT__product__BRA__319__03a288__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3643647149201774171ull);
    vlSelf->vec_multi_core__DOT__product__BRA__287__03a256__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4098789701696220716ull);
    vlSelf->vec_multi_core__DOT__product__BRA__255__03a224__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8682389060764349769ull);
    vlSelf->vec_multi_core__DOT__product__BRA__223__03a192__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9847036248500594533ull);
    vlSelf->vec_multi_core__DOT__product__BRA__191__03a160__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16189939919054946293ull);
    vlSelf->vec_multi_core__DOT__product__BRA__159__03a128__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15879812190514820734ull);
    vlSelf->vec_multi_core__DOT__product__BRA__127__03a96__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10795355418870613791ull);
    vlSelf->vec_multi_core__DOT__product__BRA__95__03a64__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14500228222227139239ull);
    vlSelf->vec_multi_core__DOT__product__BRA__63__03a32__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7749640939295441036ull);
    vlSelf->vec_multi_core__DOT__product__BRA__31__03a0__KET__ = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7424879779867248352ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->vec_multi_core__DOT__sum_temp, __VscopeHash, 9359280744562740124ull);
    vlSelf->vec_multi_core__DOT__o_valid_stage1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9257836852897556361ull);
    vlSelf->vec_multi_core__DOT__unnamedblk1__DOT__k = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
