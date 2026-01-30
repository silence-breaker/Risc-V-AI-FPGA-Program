// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_vec_dot_prod.h for the primary calling header

#include "Vtb_vec_dot_prod__pch.h"

VlCoroutine Vtb_vec_dot_prod___024root___eval_initial__TOP__Vtiming__0(Vtb_vec_dot_prod___024root* vlSelf);

void Vtb_vec_dot_prod___024root___eval_initial(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___eval_initial\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_vec_dot_prod___024root___eval_initial__TOP__Vtiming__0(vlSelf);
}

VlCoroutine Vtb_vec_dot_prod___024root___eval_initial__TOP__Vtiming__0(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VL_WRITEF_NX("--- Mission 2 Start (Parallelism = 4) ---\n",0);
    vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data = 0x01010101U;
    vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight = 0x55U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "tb_vec_dot_prod.sv", 
                                         36);
    if (VL_LIKELY(((4U == (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result))))) {
        VL_WRITEF_NX("Case 1 PASS: 1+1+1+1 = 4\n",0);
    } else {
        VL_WRITEF_NX("[%0t] %%Error: tb_vec_dot_prod.sv:38: Assertion failed in %Ntb_vec_dot_prod: Case 1 FAIL: Got %6d\n",0,
                     64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name(),
                     16,(IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result));
        VL_STOP_MT("tb_vec_dot_prod.sv", 38, "");
    }
    vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data = 0x0a141e28U;
    vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight = 0x71U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "tb_vec_dot_prod.sv", 
                                         49);
    if (VL_LIKELY(((0x001eU == (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result))))) {
        VL_WRITEF_NX("Case 2 PASS: 10-20+0+40 = 30\n",0);
    } else {
        VL_WRITEF_NX("[%0t] %%Error: tb_vec_dot_prod.sv:51: Assertion failed in %Ntb_vec_dot_prod: Case 2 FAIL: Got %6d\n",0,
                     64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name(),
                     16,(IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result));
        VL_STOP_MT("tb_vec_dot_prod.sv", 51, "");
    }
    VL_FINISH_MT("tb_vec_dot_prod.sv", 53, "");
    co_return;}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_vec_dot_prod___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vtb_vec_dot_prod___024root___eval_triggers__act(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___eval_triggers__act\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(vlSelfRef.__VdlySched.awaitingCurrentTime()));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_vec_dot_prod___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vtb_vec_dot_prod___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtb_vec_dot_prod___024root___act_sequent__TOP__0(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___act_sequent__TOP__0\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ VL_ONEHOT_I((((0U == (3U & (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight))) 
                               << 2U) | (((1U == (3U 
                                                  & (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight))) 
                                          << 1U) | 
                                         (3U == (3U 
                                                 & (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight))))))))) {
        if ((0U != (((0U == (3U & (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight))) 
                     << 2U) | (((1U == (3U & (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight))) 
                                << 1U) | (3U == (3U 
                                                 & (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vector_dot_product.sv:20: Assertion failed in %Ntb_vec_dot_prod.u_dut.unnamedblk1.dot_parr: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1),
                             -12,vlSymsp->name(),2,
                             (3U & (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight)));
                VL_STOP_MT("vector_dot_product.sv", 20, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((0U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                             >> 2U))) 
                               << 2U) | (((1U == (3U 
                                                  & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                                     >> 2U))) 
                                          << 1U) | 
                                         (3U == (3U 
                                                 & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                                    >> 2U))))))))) {
        if ((0U != (((0U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                   >> 2U))) << 2U) 
                    | (((1U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                      >> 2U))) << 1U) 
                       | (3U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                       >> 2U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vector_dot_product.sv:20: Assertion failed in %Ntb_vec_dot_prod.u_dut.unnamedblk1.dot_parr: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1),
                             -12,vlSymsp->name(),2,
                             (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                    >> 2U)));
                VL_STOP_MT("vector_dot_product.sv", 20, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((0U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                             >> 4U))) 
                               << 2U) | (((1U == (3U 
                                                  & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                                     >> 4U))) 
                                          << 1U) | 
                                         (3U == (3U 
                                                 & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                                    >> 4U))))))))) {
        if ((0U != (((0U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                   >> 4U))) << 2U) 
                    | (((1U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                      >> 4U))) << 1U) 
                       | (3U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                       >> 4U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vector_dot_product.sv:20: Assertion failed in %Ntb_vec_dot_prod.u_dut.unnamedblk1.dot_parr: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1),
                             -12,vlSymsp->name(),2,
                             (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                    >> 4U)));
                VL_STOP_MT("vector_dot_product.sv", 20, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((0U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                             >> 6U))) 
                               << 2U) | (((1U == (3U 
                                                  & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                                     >> 6U))) 
                                          << 1U) | 
                                         (3U == (3U 
                                                 & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                                    >> 6U))))))))) {
        if ((0U != (((0U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                   >> 6U))) << 2U) 
                    | (((1U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                      >> 6U))) << 1U) 
                       | (3U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                       >> 6U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vector_dot_product.sv:20: Assertion failed in %Ntb_vec_dot_prod.u_dut.unnamedblk1.dot_parr: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1),
                             -12,vlSymsp->name(),2,
                             (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                                    >> 6U)));
                VL_STOP_MT("vector_dot_product.sv", 20, "");
            }
        }
    }
    vlSelfRef.tb_vec_dot_prod__DOT__t_result = 0U;
    if ((3U == (3U & (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight)))) {
        vlSelfRef.tb_vec_dot_prod__DOT__t_result = 
            (0x0000ffffU & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result) 
                            - VL_EXTENDS_II(16,8, (0x000000ffU 
                                                   & vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data))));
    } else if ((1U == (3U & (IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight)))) {
        vlSelfRef.tb_vec_dot_prod__DOT__t_result = 
            (0x0000ffffU & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result) 
                            + VL_EXTENDS_II(16,8, (0x000000ffU 
                                                   & vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data))));
    }
    if ((3U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                      >> 2U)))) {
        vlSelfRef.tb_vec_dot_prod__DOT__t_result = 
            (0x0000ffffU & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result) 
                            - VL_EXTENDS_II(16,8, (0x000000ffU 
                                                   & (vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data 
                                                      >> 8U)))));
    } else if ((1U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                             >> 2U)))) {
        vlSelfRef.tb_vec_dot_prod__DOT__t_result = 
            (0x0000ffffU & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result) 
                            + VL_EXTENDS_II(16,8, (0x000000ffU 
                                                   & (vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data 
                                                      >> 8U)))));
    }
    if ((3U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                      >> 4U)))) {
        vlSelfRef.tb_vec_dot_prod__DOT__t_result = 
            (0x0000ffffU & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result) 
                            - VL_EXTENDS_II(16,8, (0x000000ffU 
                                                   & (vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data 
                                                      >> 0x10U)))));
    } else if ((1U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                             >> 4U)))) {
        vlSelfRef.tb_vec_dot_prod__DOT__t_result = 
            (0x0000ffffU & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result) 
                            + VL_EXTENDS_II(16,8, (0x000000ffU 
                                                   & (vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data 
                                                      >> 0x10U)))));
    }
    if ((3U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                      >> 6U)))) {
        vlSelfRef.tb_vec_dot_prod__DOT__t_result = 
            (0x0000ffffU & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result) 
                            - VL_EXTENDS_II(16,8, (vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data 
                                                   >> 0x18U))));
    } else if ((1U == (3U & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_vec_weight) 
                             >> 6U)))) {
        vlSelfRef.tb_vec_dot_prod__DOT__t_result = 
            (0x0000ffffU & ((IData)(vlSelfRef.tb_vec_dot_prod__DOT__t_result) 
                            + VL_EXTENDS_II(16,8, (vlSelfRef.tb_vec_dot_prod__DOT__t_vec_data 
                                                   >> 0x18U))));
    }
}

void Vtb_vec_dot_prod___024root___eval_act(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___eval_act\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        Vtb_vec_dot_prod___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vtb_vec_dot_prod___024root___eval_nba(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___eval_nba\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtb_vec_dot_prod___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vtb_vec_dot_prod___024root___timing_resume(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___timing_resume\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_vec_dot_prod___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_vec_dot_prod___024root___eval_phase__act(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___eval_phase__act\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_vec_dot_prod___024root___eval_triggers__act(vlSelf);
    Vtb_vec_dot_prod___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_vec_dot_prod___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        Vtb_vec_dot_prod___024root___timing_resume(vlSelf);
        Vtb_vec_dot_prod___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void Vtb_vec_dot_prod___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_vec_dot_prod___024root___eval_phase__nba(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___eval_phase__nba\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_vec_dot_prod___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_vec_dot_prod___024root___eval_nba(vlSelf);
        Vtb_vec_dot_prod___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_vec_dot_prod___024root___eval(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___eval\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_vec_dot_prod___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb_vec_dot_prod.sv", 2, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtb_vec_dot_prod___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("tb_vec_dot_prod.sv", 2, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vtb_vec_dot_prod___024root___eval_phase__act(vlSelf));
    } while (Vtb_vec_dot_prod___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vtb_vec_dot_prod___024root___eval_debug_assertions(Vtb_vec_dot_prod___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_vec_dot_prod___024root___eval_debug_assertions\n"); );
    Vtb_vec_dot_prod__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
