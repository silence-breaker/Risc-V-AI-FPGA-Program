// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vvec_multi_core__Syms.h"


VL_ATTR_COLD void Vvec_multi_core___024root__trace_init_sub__TOP__0(Vvec_multi_core___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_init_sub__TOP__0\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+25,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+26,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+27,0,"i_data_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"i_load_weight",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+29,0,"i_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+33,0,"i_weight",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+34,0,"o_data_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+35,0,"o_result",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("vec_multi_core", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+36,0,"LEN",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+37,0,"DATA_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+25,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+26,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+27,0,"i_data_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"i_load_weight",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+29,0,"i_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+33,0,"i_weight",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+34,0,"o_data_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+35,0,"o_result",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+1,0,"weight_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declArray(c+2,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 511,0);
    tracep->declBit(c+18,0,"product_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+19,0,"sum_temp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBit(c+23,0,"o_valid_stage1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+24,0,"k",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vvec_multi_core___024root__trace_init_top(Vvec_multi_core___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_init_top\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vvec_multi_core___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vvec_multi_core___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vvec_multi_core___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vvec_multi_core___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vvec_multi_core___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vvec_multi_core___024root__trace_register(Vvec_multi_core___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_register\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vvec_multi_core___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vvec_multi_core___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vvec_multi_core___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vvec_multi_core___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vvec_multi_core___024root__trace_const_0_sub_0(Vvec_multi_core___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vvec_multi_core___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_const_0\n"); );
    // Body
    Vvec_multi_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vvec_multi_core___024root*>(voidSelf);
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vvec_multi_core___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vvec_multi_core___024root__trace_const_0_sub_0(Vvec_multi_core___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_const_0_sub_0\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+36,(0x00000010U),32);
    bufp->fullIData(oldp+37,(8U),32);
}

VL_ATTR_COLD void Vvec_multi_core___024root__trace_full_0_sub_0(Vvec_multi_core___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vvec_multi_core___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_full_0\n"); );
    // Body
    Vvec_multi_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vvec_multi_core___024root*>(voidSelf);
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vvec_multi_core___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vvec_multi_core___024root__trace_full_0_sub_0(Vvec_multi_core___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vvec_multi_core___024root__trace_full_0_sub_0\n"); );
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<16>/*511:0*/ __Vtemp_14;
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+1,(vlSelfRef.vec_multi_core__DOT__weight_reg),32);
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
    bufp->fullWData(oldp+2,(__Vtemp_14),512);
    bufp->fullBit(oldp+18,(vlSelfRef.vec_multi_core__DOT__product_ready));
    bufp->fullWData(oldp+19,(vlSelfRef.vec_multi_core__DOT__sum_temp),128);
    bufp->fullBit(oldp+23,(vlSelfRef.vec_multi_core__DOT__o_valid_stage1));
    bufp->fullIData(oldp+24,(vlSelfRef.vec_multi_core__DOT__unnamedblk1__DOT__k),32);
    bufp->fullBit(oldp+25,(vlSelfRef.clk));
    bufp->fullBit(oldp+26,(vlSelfRef.rst_n));
    bufp->fullBit(oldp+27,(vlSelfRef.i_data_valid));
    bufp->fullBit(oldp+28,(vlSelfRef.i_load_weight));
    bufp->fullWData(oldp+29,(vlSelfRef.i_data),128);
    bufp->fullIData(oldp+33,(vlSelfRef.i_weight),32);
    bufp->fullBit(oldp+34,(vlSelfRef.o_data_ready));
    bufp->fullIData(oldp+35,(vlSelfRef.o_result),32);
}
