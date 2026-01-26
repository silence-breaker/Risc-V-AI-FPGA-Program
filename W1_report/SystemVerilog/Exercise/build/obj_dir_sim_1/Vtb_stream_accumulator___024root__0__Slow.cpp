// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_stream_accumulator.h for the primary calling header

#include "Vtb_stream_accumulator__pch.h"

VL_ATTR_COLD void Vtb_stream_accumulator___024root___eval_static(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_static\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__tb_stream_accumulator__DOT__clk__0 
        = vlSelfRef.tb_stream_accumulator__DOT__clk;
}

VL_ATTR_COLD void Vtb_stream_accumulator___024root___eval_final(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_final\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtb_stream_accumulator___024root___eval_settle(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_settle\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vtb_stream_accumulator___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_stream_accumulator___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtb_stream_accumulator___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_stream_accumulator.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtb_stream_accumulator___024root___ctor_var_reset(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___ctor_var_reset\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_stream_accumulator__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12313359208221668672ull);
    vlSelf->tb_stream_accumulator__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3993841926473176307ull);
    vlSelf->tb_stream_accumulator__DOT__t_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16769494125604878733ull);
    vlSelf->tb_stream_accumulator__DOT__t_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10431459404898293997ull);
    vlSelf->tb_stream_accumulator__DOT__t_last = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13337761664076293373ull);
    vlSelf->tb_stream_accumulator__DOT__t_result = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15956592679116475728ull);
    vlSelf->tb_stream_accumulator__DOT__t_res_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14810355444581699725ull);
    vlSelf->tb_stream_accumulator__DOT__u_dut__DOT__accumulator = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6498808342242827392ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_stream_accumulator__DOT__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
