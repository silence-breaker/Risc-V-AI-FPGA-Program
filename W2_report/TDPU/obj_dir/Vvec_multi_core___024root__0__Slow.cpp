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

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvec_multi_core___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vvec_multi_core___024root___eval_phase__stl(Vvec_multi_core___024root* vlSelf);

VL_ATTR_COLD void Vvec_multi_core___024root___eval_settle(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_settle\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vvec_multi_core___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("vec_multi_core.sv", 7, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vvec_multi_core___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vvec_multi_core___024root___eval_triggers__stl(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_triggers__stl\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vvec_multi_core___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vvec_multi_core___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvec_multi_core___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vvec_multi_core___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vvec_multi_core___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vvec_multi_core___024root___stl_sequent__TOP__0(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___stl_sequent__TOP__0\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & vlSelfRef.vec_multi_core__DOT__weight_reg)) 
                               << 2U) | (((0U == (3U 
                                                  & vlSelfRef.vec_multi_core__DOT__weight_reg)) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & vlSelfRef.vec_multi_core__DOT__weight_reg)))))))) {
        if ((0U != (((1U == (3U & vlSelfRef.vec_multi_core__DOT__weight_reg)) 
                     << 2U) | (((0U == (3U & vlSelfRef.vec_multi_core__DOT__weight_reg)) 
                                << 1U) | (2U == (3U 
                                                 & vlSelfRef.vec_multi_core__DOT__weight_reg)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[0]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & vlSelfRef.vec_multi_core__DOT__weight_reg));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 2U))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 2U))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 2U))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 2U))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 2U))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 2U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[1]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 2U)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 4U))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 4U))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 4U))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 4U))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 4U))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 4U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[2]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 4U)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 6U))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 6U))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 6U))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 6U))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 6U))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 6U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[3]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 6U)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 8U))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 8U))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 8U))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 8U))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 8U))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 8U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[4]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 8U)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x0aU))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x0aU))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x0aU))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x0aU))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x0aU))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x0aU))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[5]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x0aU)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x0cU))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x0cU))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x0cU))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x0cU))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x0cU))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x0cU))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[6]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x0cU)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x0eU))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x0eU))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x0eU))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x0eU))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x0eU))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x0eU))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[7]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x0eU)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x10U))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x10U))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x10U))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x10U))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x10U))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x10U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[8]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x10U)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x12U))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x12U))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x12U))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x12U))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x12U))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x12U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[9]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x12U)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x14U))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x14U))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x14U))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x14U))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x14U))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x14U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[10]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x14U)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x16U))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x16U))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x16U))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x16U))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x16U))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x16U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[11]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x16U)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x18U))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x18U))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x18U))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x18U))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x18U))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x18U))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[12]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x18U)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x1aU))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x1aU))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x1aU))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x1aU))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x1aU))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x1aU))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[13]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x1aU)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                             >> 0x1cU))) 
                               << 2U) | (((0U == (3U 
                                                  & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x1cU))) 
                                          << 1U) | 
                                         (2U == (3U 
                                                 & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                    >> 0x1cU))))))))) {
        if ((0U != (((1U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                   >> 0x1cU))) << 2U) 
                    | (((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                      >> 0x1cU))) << 1U) 
                       | (2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x1cU))))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[14]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(3U 
                                                   & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x1cU)));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    if ((1U & (~ VL_ONEHOT_I((((1U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                       >> 0x1eU)) << 2U) 
                              | (((0U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                          >> 0x1eU)) 
                                  << 1U) | (2U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x1eU)))))))) {
        if ((0U != (((1U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x1eU)) << 2U) | ((
                                                   (0U 
                                                    == 
                                                    (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                     >> 0x1eU)) 
                                                   << 1U) 
                                                  | (2U 
                                                     == 
                                                     (vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                      >> 0x1eU)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: vec_multi_core.sv:44: Assertion failed in %Nvec_multi_core.gen_PE[15]: unique case, but multiple matches found for '2'h%x'\n",0,
                             64,VL_TIME_UNITED_Q(1000),
                             -9,vlSymsp->name(),2,(vlSelfRef.vec_multi_core__DOT__weight_reg 
                                                   >> 0x1eU));
                VL_STOP_MT("vec_multi_core.sv", 44, "");
            }
        }
    }
    vlSelfRef.vec_multi_core__DOT__product__BRA__31__03a0__KET__ 
        = ((2U == (3U & vlSelfRef.vec_multi_core__DOT__weight_reg))
            ? VL_EXTENDS_II(32,8, (0x000000ffU & vlSelfRef.i_data[0U]))
            : ((0U == (3U & vlSelfRef.vec_multi_core__DOT__weight_reg))
                ? (- VL_EXTENDS_II(32,8, (0x000000ffU 
                                          & vlSelfRef.i_data[0U])))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__63__03a32__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 2U))) ? VL_EXTENDS_II(32,8, 
                                                  (0x000000ffU 
                                                   & (vlSelfRef.i_data[0U] 
                                                      >> 8U)))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 2U))) ? (- VL_EXTENDS_II(32,8, 
                                                         (0x000000ffU 
                                                          & (vlSelfRef.i_data[0U] 
                                                             >> 8U))))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__95__03a64__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 4U))) ? VL_EXTENDS_II(32,8, 
                                                  (0x000000ffU 
                                                   & (vlSelfRef.i_data[0U] 
                                                      >> 0x00000010U)))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 4U))) ? (- VL_EXTENDS_II(32,8, 
                                                         (0x000000ffU 
                                                          & (vlSelfRef.i_data[0U] 
                                                             >> 0x00000010U))))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__127__03a96__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 6U))) ? VL_EXTENDS_II(32,8, 
                                                  (vlSelfRef.i_data[0U] 
                                                   >> 0x00000018U))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 6U))) ? (- VL_EXTENDS_II(32,8, 
                                                         (vlSelfRef.i_data[0U] 
                                                          >> 0x00000018U)))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__159__03a128__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 8U))) ? VL_EXTENDS_II(32,8, 
                                                  (0x000000ffU 
                                                   & vlSelfRef.i_data[1U]))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 8U))) ? (- VL_EXTENDS_II(32,8, 
                                                         (0x000000ffU 
                                                          & vlSelfRef.i_data[1U])))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__191__03a160__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x0000000aU))) ? VL_EXTENDS_II(32,8, 
                                                           (0x000000ffU 
                                                            & (vlSelfRef.i_data[1U] 
                                                               >> 8U)))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x0000000aU))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (0x000000ffU 
                                                                 & (vlSelfRef.i_data[1U] 
                                                                    >> 8U))))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__223__03a192__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x0000000cU))) ? VL_EXTENDS_II(32,8, 
                                                           (0x000000ffU 
                                                            & (vlSelfRef.i_data[1U] 
                                                               >> 0x00000010U)))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x0000000cU))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (0x000000ffU 
                                                                 & (vlSelfRef.i_data[1U] 
                                                                    >> 0x00000010U))))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__255__03a224__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x0000000eU))) ? VL_EXTENDS_II(32,8, 
                                                           (vlSelfRef.i_data[1U] 
                                                            >> 0x00000018U))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x0000000eU))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (vlSelfRef.i_data[1U] 
                                                                 >> 0x00000018U)))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__287__03a256__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x00000010U))) ? VL_EXTENDS_II(32,8, 
                                                           (0x000000ffU 
                                                            & vlSelfRef.i_data[2U]))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x00000010U))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (0x000000ffU 
                                                                 & vlSelfRef.i_data[2U])))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__319__03a288__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x00000012U))) ? VL_EXTENDS_II(32,8, 
                                                           (0x000000ffU 
                                                            & (vlSelfRef.i_data[2U] 
                                                               >> 8U)))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x00000012U))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (0x000000ffU 
                                                                 & (vlSelfRef.i_data[2U] 
                                                                    >> 8U))))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__351__03a320__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x00000014U))) ? VL_EXTENDS_II(32,8, 
                                                           (0x000000ffU 
                                                            & (vlSelfRef.i_data[2U] 
                                                               >> 0x00000010U)))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x00000014U))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (0x000000ffU 
                                                                 & (vlSelfRef.i_data[2U] 
                                                                    >> 0x00000010U))))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__383__03a352__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x00000016U))) ? VL_EXTENDS_II(32,8, 
                                                           (vlSelfRef.i_data[2U] 
                                                            >> 0x00000018U))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x00000016U))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (vlSelfRef.i_data[2U] 
                                                                 >> 0x00000018U)))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__415__03a384__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x00000018U))) ? VL_EXTENDS_II(32,8, 
                                                           (0x000000ffU 
                                                            & vlSelfRef.i_data[3U]))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x00000018U))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (0x000000ffU 
                                                                 & vlSelfRef.i_data[3U])))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__447__03a416__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x0000001aU))) ? VL_EXTENDS_II(32,8, 
                                                           (0x000000ffU 
                                                            & (vlSelfRef.i_data[3U] 
                                                               >> 8U)))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x0000001aU))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (0x000000ffU 
                                                                 & (vlSelfRef.i_data[3U] 
                                                                    >> 8U))))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__479__03a448__KET__ 
        = ((2U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                         >> 0x0000001cU))) ? VL_EXTENDS_II(32,8, 
                                                           (0x000000ffU 
                                                            & (vlSelfRef.i_data[3U] 
                                                               >> 0x00000010U)))
            : ((0U == (3U & (vlSelfRef.vec_multi_core__DOT__weight_reg 
                             >> 0x0000001cU))) ? (- 
                                                  VL_EXTENDS_II(32,8, 
                                                                (0x000000ffU 
                                                                 & (vlSelfRef.i_data[3U] 
                                                                    >> 0x00000010U))))
                : 0U));
    vlSelfRef.vec_multi_core__DOT__product__BRA__511__03a480__KET__ 
        = ((2U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                   >> 0x0000001eU)) ? VL_EXTENDS_II(32,8, 
                                                    (vlSelfRef.i_data[3U] 
                                                     >> 0x00000018U))
            : ((0U == (vlSelfRef.vec_multi_core__DOT__weight_reg 
                       >> 0x0000001eU)) ? (- VL_EXTENDS_II(32,8, 
                                                           (vlSelfRef.i_data[3U] 
                                                            >> 0x00000018U)))
                : 0U));
}

VL_ATTR_COLD void Vvec_multi_core___024root____Vm_traceActivitySetAll(Vvec_multi_core___024root* vlSelf);

VL_ATTR_COLD void Vvec_multi_core___024root___eval_stl(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_stl\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vvec_multi_core___024root___stl_sequent__TOP__0(vlSelf);
        Vvec_multi_core___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD bool Vvec_multi_core___024root___eval_phase__stl(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___eval_phase__stl\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vvec_multi_core___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vvec_multi_core___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vvec_multi_core___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vvec_multi_core___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vvec_multi_core___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vvec_multi_core___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

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

VL_ATTR_COLD void Vvec_multi_core___024root____Vm_traceActivitySetAll(Vvec_multi_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root____Vm_traceActivitySetAll\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
}

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
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
