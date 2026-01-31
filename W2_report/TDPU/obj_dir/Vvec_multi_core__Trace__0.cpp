// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vvec_multi_core__Syms.h"


void Vvec_multi_core___024root__trace_chg_0_sub_0(Vvec_multi_core___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vvec_multi_core___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_chg_0\n"); );
    // Body
    Vvec_multi_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vvec_multi_core___024root*>(voidSelf);
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vvec_multi_core___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vvec_multi_core___024root__trace_chg_0_sub_0(Vvec_multi_core___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_chg_0_sub_0\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<16>/*511:0*/ __Vtemp_14;
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity
                      [2U])))) {
        __Vtemp_14[0U] = vlSelfRef.vec_multi_core__DOT__product__BRA__31__03a0__KET__;
        __Vtemp_14[1U] = vlSelfRef.vec_multi_core__DOT__product__BRA__63__03a32__KET__;
        __Vtemp_14[2U] = vlSelfRef.vec_multi_core__DOT__product__BRA__95__03a64__KET__;
        __Vtemp_14[3U] = vlSelfRef.vec_multi_core__DOT__product__BRA__127__03a96__KET__;
        __Vtemp_14[4U] = vlSelfRef.vec_multi_core__DOT__product__BRA__159__03a128__KET__;
        __Vtemp_14[5U] = vlSelfRef.vec_multi_core__DOT__product__BRA__191__03a160__KET__;
        __Vtemp_14[6U] = vlSelfRef.vec_multi_core__DOT__product__BRA__223__03a192__KET__;
        __Vtemp_14[7U] = vlSelfRef.vec_multi_core__DOT__product__BRA__255__03a224__KET__;
        __Vtemp_14[8U] = vlSelfRef.vec_multi_core__DOT__product__BRA__287__03a256__KET__;
        __Vtemp_14[9U] = vlSelfRef.vec_multi_core__DOT__product__BRA__319__03a288__KET__;
        __Vtemp_14[0x0000000aU] = vlSelfRef.vec_multi_core__DOT__product__BRA__351__03a320__KET__;
        __Vtemp_14[0x0000000bU] = vlSelfRef.vec_multi_core__DOT__product__BRA__383__03a352__KET__;
        __Vtemp_14[0x0000000cU] = vlSelfRef.vec_multi_core__DOT__product__BRA__415__03a384__KET__;
        __Vtemp_14[0x0000000dU] = vlSelfRef.vec_multi_core__DOT__product__BRA__447__03a416__KET__;
        __Vtemp_14[0x0000000eU] = (IData)((((QData)((IData)(vlSelfRef.vec_multi_core__DOT__product__BRA__511__03a480__KET__)) 
                                            << 0x00000020U) 
                                           | (QData)((IData)(vlSelfRef.vec_multi_core__DOT__product__BRA__479__03a448__KET__))));
        __Vtemp_14[0x0000000fU] = (IData)(((((QData)((IData)(vlSelfRef.vec_multi_core__DOT__product__BRA__511__03a480__KET__)) 
                                             << 0x00000020U) 
                                            | (QData)((IData)(vlSelfRef.vec_multi_core__DOT__product__BRA__479__03a448__KET__))) 
                                           >> 0x00000020U));
        bufp->chgWData(oldp+0,(__Vtemp_14),512);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[2U]))) {
        bufp->chgIData(oldp+16,(vlSelfRef.vec_multi_core__DOT__weight_reg),32);
        bufp->chgWData(oldp+17,(vlSelfRef.vec_multi_core__DOT__sum_temp),128);
        bufp->chgBit(oldp+21,(vlSelfRef.vec_multi_core__DOT__o_valid_stage1));
        bufp->chgIData(oldp+22,(vlSelfRef.vec_multi_core__DOT__unnamedblk1__DOT__k),32);
    }
    bufp->chgBit(oldp+23,(vlSelfRef.clk));
    bufp->chgBit(oldp+24,(vlSelfRef.rst_n));
    bufp->chgBit(oldp+25,(vlSelfRef.i_data_valid));
    bufp->chgBit(oldp+26,(vlSelfRef.i_load_weight));
    bufp->chgWData(oldp+27,(vlSelfRef.i_data),128);
    bufp->chgIData(oldp+31,(vlSelfRef.i_weight),32);
    bufp->chgBit(oldp+32,(vlSelfRef.o_data_ready));
    bufp->chgIData(oldp+33,(vlSelfRef.o_result),32);
}

void Vvec_multi_core___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_cleanup\n"); );
    // Body
    Vvec_multi_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vvec_multi_core___024root*>(voidSelf);
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
