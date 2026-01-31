// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vvec_multi_core.h for the primary calling header

#include "Vvec_multi_core__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvec_multi_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vvec_multi_core___024root___eval_triggers__act(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_triggers__act\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.rst_n)) 
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0)) 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vvec_multi_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vvec_multi_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___trigger_anySet__act\n"); );
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

void Vvec_multi_core___024root___nba_sequent__TOP__0(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___nba_sequent__TOP__0\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__31__03a0__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__31__03a0__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__63__03a32__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__63__03a32__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__95__03a64__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__95__03a64__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__127__03a96__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__127__03a96__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__159__03a128__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__159__03a128__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__191__03a160__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__191__03a160__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__223__03a192__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__223__03a192__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__255__03a224__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__255__03a224__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__287__03a256__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__287__03a256__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__319__03a288__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__319__03a288__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__351__03a320__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__351__03a320__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__383__03a352__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__383__03a352__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__415__03a384__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__415__03a384__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__447__03a416__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__447__03a416__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__479__03a448__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__479__03a448__KET__ = 0;
    IData/*31:0*/ __Vdly__vec_multi_core__DOT__product__BRA__511__03a480__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__511__03a480__KET__ = 0;
    // Body
    __Vdly__vec_multi_core__DOT__product__BRA__31__03a0__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__31__03a0__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__63__03a32__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__63__03a32__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__95__03a64__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__95__03a64__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__127__03a96__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__127__03a96__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__159__03a128__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__159__03a128__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__191__03a160__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__191__03a160__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__223__03a192__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__223__03a192__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__255__03a224__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__255__03a224__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__287__03a256__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__287__03a256__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__319__03a288__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__319__03a288__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__351__03a320__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__351__03a320__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__383__03a352__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__383__03a352__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__415__03a384__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__415__03a384__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__447__03a416__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__447__03a416__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__479__03a448__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__479__03a448__KET__;
    __Vdly__vec_multi_core__DOT__product__BRA__511__03a480__KET__ 
        = vlSelfRef.vec_multi_core__DOT__product__BRA__511__03a480__KET__;
    if ((1U & (~ (IData)(vlSelfRef.rst_n)))) {
        vlSelfRef.vec_multi_core__DOT__unnamedblk1__DOT__k = 4U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & vlSelfRef.vec_multi_core__DOT__weight_reg)) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & vlSelfRef.vec_multi_core__DOT__weight_reg)) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & vlSelfRef.vec_multi_core__DOT__weight_reg)))))))))) {
                if ((0U != (((1U == (3U & vlSelfRef.vec_multi_core__DOT__weight_reg)) 
                             << 2U) | (((0U == (3U 
                                                & vlSelfRef.vec_multi_core__DOT__weight_reg)) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & vlSelfRef.vec_multi_core__DOT__weight_reg)))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[0]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & vlSelfRef.vec_multi_core__DOT__weight_reg));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__31__03a0__KET__ 
                = ((2U == (3U & vlSelfRef.vec_multi_core__DOT__weight_reg))
                    ? VL_EXTENDS_II(32,8, (0x000000ffU 
                                           & vlSelfRef.i_data[0U]))
                    : ((0U == (3U & vlSelfRef.vec_multi_core__DOT__weight_reg))
                        ? (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                                  & vlSelfRef.i_data[0U])))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__31__03a0__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__31__03a0__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__31__03a0__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 2U))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 2U))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 2U))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 2U))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 2U))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 2U))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[1]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 2U)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__63__03a32__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 2U))) ? VL_EXTENDS_II(32,8, 
                                                          (0x000000ffU 
                                                           & (vlSelfRef.i_data[0U] 
                                                              >> 8U)))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 2U))) ? (- 
                                                 VL_EXTENDS_II(32,8, 
                                                               (0x000000ffU 
                                                                & (vlSelfRef.i_data[0U] 
                                                                   >> 8U))))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__63__03a32__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__63__03a32__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__63__03a32__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 4U))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 4U))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 4U))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 4U))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 4U))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 4U))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[2]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 4U)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__95__03a64__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 4U))) ? VL_EXTENDS_II(32,8, 
                                                          (0x000000ffU 
                                                           & (vlSelfRef.i_data[0U] 
                                                              >> 0x00000010U)))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 4U))) ? (- 
                                                 VL_EXTENDS_II(32,8, 
                                                               (0x000000ffU 
                                                                & (vlSelfRef.i_data[0U] 
                                                                   >> 0x00000010U))))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__95__03a64__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__95__03a64__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__95__03a64__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 6U))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 6U))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 6U))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 6U))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 6U))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 6U))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[3]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 6U)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__127__03a96__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 6U))) ? VL_EXTENDS_II(32,8, 
                                                          (vlSelfRef.i_data[0U] 
                                                           >> 0x00000018U))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 6U))) ? (- 
                                                 VL_EXTENDS_II(32,8, 
                                                               (vlSelfRef.i_data[0U] 
                                                                >> 0x00000018U)))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__127__03a96__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__127__03a96__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__127__03a96__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 8U))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 8U))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 8U))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 8U))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 8U))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 8U))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[4]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 8U)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__159__03a128__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 8U))) ? VL_EXTENDS_II(32,8, 
                                                          (0x000000ffU 
                                                           & vlSelfRef.i_data[1U]))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 8U))) ? (- 
                                                 VL_EXTENDS_II(32,8, 
                                                               (0x000000ffU 
                                                                & vlSelfRef.i_data[1U])))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__159__03a128__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__159__03a128__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__159__03a128__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x0aU))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x0aU))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x0aU))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x0aU))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x0aU))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x0aU))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[5]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x0aU)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__191__03a160__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x0aU))) ? VL_EXTENDS_II(32,8, 
                                                             (0x000000ffU 
                                                              & (vlSelfRef.i_data[1U] 
                                                                 >> 8U)))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x0aU))) ? 
                       (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                               & (vlSelfRef.i_data[1U] 
                                                  >> 8U))))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__191__03a160__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__191__03a160__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__191__03a160__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x0cU))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x0cU))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x0cU))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x0cU))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x0cU))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x0cU))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[6]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x0cU)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__223__03a192__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x0cU))) ? VL_EXTENDS_II(32,8, 
                                                             (0x000000ffU 
                                                              & (vlSelfRef.i_data[1U] 
                                                                 >> 0x00000010U)))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x0cU))) ? 
                       (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                               & (vlSelfRef.i_data[1U] 
                                                  >> 0x00000010U))))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__223__03a192__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__223__03a192__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__223__03a192__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x0eU))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x0eU))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x0eU))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x0eU))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x0eU))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x0eU))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[7]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x0eU)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__255__03a224__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x0eU))) ? VL_EXTENDS_II(32,8, 
                                                             (vlSelfRef.i_data[1U] 
                                                              >> 0x00000018U))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x0eU))) ? 
                       (- VL_EXTENDS_II(32,8, (vlSelfRef.i_data[1U] 
                                               >> 0x00000018U)))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__255__03a224__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__255__03a224__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__255__03a224__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x10U))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x10U))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x10U))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x10U))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x10U))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x10U))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[8]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x10U)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__287__03a256__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x10U))) ? VL_EXTENDS_II(32,8, 
                                                             (0x000000ffU 
                                                              & vlSelfRef.i_data[2U]))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x10U))) ? 
                       (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                               & vlSelfRef.i_data[2U])))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__287__03a256__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__287__03a256__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__287__03a256__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x12U))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x12U))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x12U))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x12U))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x12U))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x12U))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[9]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x12U)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__319__03a288__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x12U))) ? VL_EXTENDS_II(32,8, 
                                                             (0x000000ffU 
                                                              & (vlSelfRef.i_data[2U] 
                                                                 >> 8U)))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x12U))) ? 
                       (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                               & (vlSelfRef.i_data[2U] 
                                                  >> 8U))))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__319__03a288__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__319__03a288__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__319__03a288__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x14U))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x14U))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x14U))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x14U))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x14U))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x14U))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[10]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x14U)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__351__03a320__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x14U))) ? VL_EXTENDS_II(32,8, 
                                                             (0x000000ffU 
                                                              & (vlSelfRef.i_data[2U] 
                                                                 >> 0x00000010U)))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x14U))) ? 
                       (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                               & (vlSelfRef.i_data[2U] 
                                                  >> 0x00000010U))))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__351__03a320__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__351__03a320__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__351__03a320__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x16U))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x16U))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x16U))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x16U))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x16U))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x16U))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[11]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x16U)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__383__03a352__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x16U))) ? VL_EXTENDS_II(32,8, 
                                                             (vlSelfRef.i_data[2U] 
                                                              >> 0x00000018U))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x16U))) ? 
                       (- VL_EXTENDS_II(32,8, (vlSelfRef.i_data[2U] 
                                               >> 0x00000018U)))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__383__03a352__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__383__03a352__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__383__03a352__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x18U))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x18U))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x18U))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x18U))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x18U))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x18U))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[12]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x18U)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__415__03a384__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x18U))) ? VL_EXTENDS_II(32,8, 
                                                             (0x000000ffU 
                                                              & vlSelfRef.i_data[3U]))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x18U))) ? 
                       (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                               & vlSelfRef.i_data[3U])))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__415__03a384__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__415__03a384__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__415__03a384__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x1aU))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x1aU))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x1aU))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x1aU))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x1aU))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x1aU))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[13]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x1aU)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__447__03a416__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x1aU))) ? VL_EXTENDS_II(32,8, 
                                                             (0x000000ffU 
                                                              & (vlSelfRef.i_data[3U] 
                                                                 >> 8U)))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x1aU))) ? 
                       (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                               & (vlSelfRef.i_data[3U] 
                                                  >> 8U))))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__447__03a416__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__447__03a416__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__447__03a416__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x1cU))) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (3U 
                                                         & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                            >> 0x1cU))) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (3U 
                                                          & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                             >> 0x1cU))))))))))) {
                if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                           >> 0x1cU))) 
                             << 2U) | (((0U == (3U 
                                                & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x1cU))) 
                                        << 1U) | (2U 
                                                  == 
                                                  (3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x1cU))))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[14]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                              >> 0x1cU)));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__479__03a448__KET__ 
                = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                 >> 0x1cU))) ? VL_EXTENDS_II(32,8, 
                                                             (0x000000ffU 
                                                              & (vlSelfRef.i_data[3U] 
                                                                 >> 0x00000010U)))
                    : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x1cU))) ? 
                       (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                               & (vlSelfRef.i_data[3U] 
                                                  >> 0x00000010U))))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__479__03a448__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__479__03a448__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__479__03a448__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        if (vlSelfRef.i_data_valid) {
            if (VL_UNLIKELY(((1U & (~ VL_ONEHOT_I((
                                                   ((1U 
                                                     == 
                                                     (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x1eU)) 
                                                    << 2U) 
                                                   | (((0U 
                                                        == 
                                                        (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                         >> 0x1eU)) 
                                                       << 1U) 
                                                      | (2U 
                                                         == 
                                                         (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                          >> 0x1eU)))))))))) {
                if ((0U != (((1U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                     >> 0x1eU)) << 2U) 
                            | (((0U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                        >> 0x1eU)) 
                                << 1U) | (2U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                 >> 0x1eU)))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:47: Assertion failed in %Nvec_multi_core.gen_PE[15]: unique case, but multiple matches found for '2'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     2,(vlSelfRef.vec_multi_core__DOT__weight_reg 
                                        >> 0x1eU));
                        VL_STOP_MT("vec_multi_core.sv", 47, "");
                    }
                }
            }
            __Vdly__vec_multi_core__DOT__product__BRA__511__03a480__KET__ 
                = ((2U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                           >> 0x1eU)) ? VL_EXTENDS_II(32,8, 
                                                      (vlSelfRef.i_data[3U] 
                                                       >> 0x00000018U))
                    : ((0U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                               >> 0x1eU)) ? (- VL_EXTENDS_II(32,8, 
                                                             (vlSelfRef.i_data[3U] 
                                                              >> 0x00000018U)))
                        : 0U));
        } else {
            __Vdly__vec_multi_core__DOT__product__BRA__511__03a480__KET__ 
                = vlSelfRef.vec_multi_core__DOT__product__BRA__511__03a480__KET__;
        }
    } else {
        __Vdly__vec_multi_core__DOT__product__BRA__511__03a480__KET__ = 0U;
    }
    if (vlSelfRef.rst_n) {
        vlSelfRef.o_result = (((vlSelfRef.vec_multi_core__DOT__sum_temp[0U] 
                                + vlSelfRef.vec_multi_core__DOT__sum_temp[1U]) 
                               + vlSelfRef.vec_multi_core__DOT__sum_temp[2U]) 
                              + vlSelfRef.vec_multi_core__DOT__sum_temp[3U]);
        if (vlSelfRef.i_load_weight) {
            vlSelfRef.vec_multi_core__DOT__weight_reg 
                = vlSelfRef.i_weight;
        }
        vlSelfRef.vec_multi_core__DOT__sum_temp[0U] 
            = (IData)((((QData)((IData)(((vlSelfRef.vec_multi_core__DOT__product__BRA__159__03a128__KET__ 
                                          + vlSelfRef.vec_multi_core__DOT__product__BRA__191__03a160__KET__) 
                                         + (vlSelfRef.vec_multi_core__DOT__product__BRA__223__03a192__KET__ 
                                            + vlSelfRef.vec_multi_core__DOT__product__BRA__255__03a224__KET__)))) 
                        << 0x00000020U) | (QData)((IData)(
                                                          ((vlSelfRef.vec_multi_core__DOT__product__BRA__31__03a0__KET__ 
                                                            + vlSelfRef.vec_multi_core__DOT__product__BRA__63__03a32__KET__) 
                                                           + 
                                                           (vlSelfRef.vec_multi_core__DOT__product__BRA__95__03a64__KET__ 
                                                            + vlSelfRef.vec_multi_core__DOT__product__BRA__127__03a96__KET__))))));
        vlSelfRef.vec_multi_core__DOT__sum_temp[1U] 
            = (IData)(((((QData)((IData)(((vlSelfRef.vec_multi_core__DOT__product__BRA__159__03a128__KET__ 
                                           + vlSelfRef.vec_multi_core__DOT__product__BRA__191__03a160__KET__) 
                                          + (vlSelfRef.vec_multi_core__DOT__product__BRA__223__03a192__KET__ 
                                             + vlSelfRef.vec_multi_core__DOT__product__BRA__255__03a224__KET__)))) 
                         << 0x00000020U) | (QData)((IData)(
                                                           ((vlSelfRef.vec_multi_core__DOT__product__BRA__31__03a0__KET__ 
                                                             + vlSelfRef.vec_multi_core__DOT__product__BRA__63__03a32__KET__) 
                                                            + 
                                                            (vlSelfRef.vec_multi_core__DOT__product__BRA__95__03a64__KET__ 
                                                             + vlSelfRef.vec_multi_core__DOT__product__BRA__127__03a96__KET__))))) 
                       >> 0x00000020U));
        vlSelfRef.vec_multi_core__DOT__sum_temp[2U] 
            = (IData)((((QData)((IData)(((vlSelfRef.vec_multi_core__DOT__product__BRA__415__03a384__KET__ 
                                          + vlSelfRef.vec_multi_core__DOT__product__BRA__447__03a416__KET__) 
                                         + (vlSelfRef.vec_multi_core__DOT__product__BRA__479__03a448__KET__ 
                                            + vlSelfRef.vec_multi_core__DOT__product__BRA__511__03a480__KET__)))) 
                        << 0x00000020U) | (QData)((IData)(
                                                          ((vlSelfRef.vec_multi_core__DOT__product__BRA__287__03a256__KET__ 
                                                            + vlSelfRef.vec_multi_core__DOT__product__BRA__319__03a288__KET__) 
                                                           + 
                                                           (vlSelfRef.vec_multi_core__DOT__product__BRA__351__03a320__KET__ 
                                                            + vlSelfRef.vec_multi_core__DOT__product__BRA__383__03a352__KET__))))));
        vlSelfRef.vec_multi_core__DOT__sum_temp[3U] 
            = (IData)(((((QData)((IData)(((vlSelfRef.vec_multi_core__DOT__product__BRA__415__03a384__KET__ 
                                           + vlSelfRef.vec_multi_core__DOT__product__BRA__447__03a416__KET__) 
                                          + (vlSelfRef.vec_multi_core__DOT__product__BRA__479__03a448__KET__ 
                                             + vlSelfRef.vec_multi_core__DOT__product__BRA__511__03a480__KET__)))) 
                         << 0x00000020U) | (QData)((IData)(
                                                           ((vlSelfRef.vec_multi_core__DOT__product__BRA__287__03a256__KET__ 
                                                             + vlSelfRef.vec_multi_core__DOT__product__BRA__319__03a288__KET__) 
                                                            + 
                                                            (vlSelfRef.vec_multi_core__DOT__product__BRA__351__03a320__KET__ 
                                                             + vlSelfRef.vec_multi_core__DOT__product__BRA__383__03a352__KET__))))) 
                       >> 0x00000020U));
    } else {
        vlSelfRef.o_result = 0U;
        vlSelfRef.vec_multi_core__DOT__weight_reg = 0x55555555U;
        vlSelfRef.vec_multi_core__DOT__sum_temp[0U] = 0U;
        vlSelfRef.vec_multi_core__DOT__sum_temp[1U] = 0U;
        vlSelfRef.vec_multi_core__DOT__sum_temp[2U] = 0U;
        vlSelfRef.vec_multi_core__DOT__sum_temp[3U] = 0U;
    }
    vlSelfRef.o_data_ready = ((IData)(vlSelfRef.rst_n) 
                              && (IData)(vlSelfRef.vec_multi_core__DOT__o_valid_stage1));
    vlSelfRef.vec_multi_core__DOT__o_valid_stage1 = 
        ((IData)(vlSelfRef.rst_n) && (IData)(vlSelfRef.i_data_valid));
    vlSelfRef.vec_multi_core__DOT__product__BRA__159__03a128__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__159__03a128__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__191__03a160__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__191__03a160__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__223__03a192__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__223__03a192__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__255__03a224__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__255__03a224__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__31__03a0__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__31__03a0__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__63__03a32__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__63__03a32__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__95__03a64__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__95__03a64__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__127__03a96__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__127__03a96__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__415__03a384__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__415__03a384__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__447__03a416__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__447__03a416__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__479__03a448__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__479__03a448__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__511__03a480__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__511__03a480__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__287__03a256__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__287__03a256__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__319__03a288__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__319__03a288__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__351__03a320__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__351__03a320__KET__;
    vlSelfRef.vec_multi_core__DOT__product__BRA__383__03a352__KET__ 
        = __Vdly__vec_multi_core__DOT__product__BRA__383__03a352__KET__;
}

void Vvec_multi_core___024root___eval_nba(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_nba\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vvec_multi_core___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

void Vvec_multi_core___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vvec_multi_core___024root___eval_phase__act(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_phase__act\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vvec_multi_core___024root___eval_triggers__act(vlSelf);
    Vvec_multi_core___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vvec_multi_core___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vvec_multi_core___024root___eval_phase__nba(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_phase__nba\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vvec_multi_core___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vvec_multi_core___024root___eval_nba(vlSelf);
        Vvec_multi_core___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vvec_multi_core___024root___eval(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vvec_multi_core___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("vec_multi_core.sv", 7, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vvec_multi_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("vec_multi_core.sv", 7, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vvec_multi_core___024root___eval_phase__act(vlSelf));
    } while (Vvec_multi_core___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vvec_multi_core___024root___eval_debug_assertions(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_debug_assertions\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");
    }
    if (VL_UNLIKELY(((vlSelfRef.i_data_valid & 0xfeU)))) {
        Verilated::overWidthError("i_data_valid");
    }
    if (VL_UNLIKELY(((vlSelfRef.i_load_weight & 0xfeU)))) {
        Verilated::overWidthError("i_load_weight");
    }
}
#endif  // VL_DEBUG
