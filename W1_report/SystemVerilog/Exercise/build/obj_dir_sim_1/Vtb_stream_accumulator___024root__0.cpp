// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtb_stream_accumulator.h for the primary calling header

#include "Vtb_stream_accumulator__pch.h"

VlCoroutine Vtb_stream_accumulator___024root___eval_initial__TOP__Vtiming__0(Vtb_stream_accumulator___024root* vlSelf);
VlCoroutine Vtb_stream_accumulator___024root___eval_initial__TOP__Vtiming__1(Vtb_stream_accumulator___024root* vlSelf);

void Vtb_stream_accumulator___024root___eval_initial(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_initial\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtb_stream_accumulator___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vtb_stream_accumulator___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

VlCoroutine Vtb_stream_accumulator___024root___eval_initial__TOP__Vtiming__0(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_stream_accumulator__DOT__clk = 0U;
    while (true) {
        co_await vlSelfRef.__VdlySched.delay(5ULL, 
                                             nullptr, 
                                             "tb_stream_accumulator.sv", 
                                             26);
        vlSelfRef.tb_stream_accumulator__DOT__clk = 
            (1U & (~ (IData)(vlSelfRef.tb_stream_accumulator__DOT__clk)));
    }
    co_return;}

VlCoroutine Vtb_stream_accumulator___024root___eval_initial__TOP__Vtiming__1(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_stream_accumulator__DOT__send_packet__Vstatic__i;
    tb_stream_accumulator__DOT__send_packet__Vstatic__i = 0;
    IData/*31:0*/ __Vtask_tb_stream_accumulator__DOT__send_packet__0__length;
    __Vtask_tb_stream_accumulator__DOT__send_packet__0__length = 0;
    IData/*31:0*/ __Vtask_tb_stream_accumulator__DOT__send_packet__0__start_value;
    __Vtask_tb_stream_accumulator__DOT__send_packet__0__start_value = 0;
    IData/*31:0*/ __Vtask_tb_stream_accumulator__DOT__send_packet__0__step;
    __Vtask_tb_stream_accumulator__DOT__send_packet__0__step = 0;
    IData/*31:0*/ __Vtask_tb_stream_accumulator__DOT__send_packet__1__length;
    __Vtask_tb_stream_accumulator__DOT__send_packet__1__length = 0;
    IData/*31:0*/ __Vtask_tb_stream_accumulator__DOT__send_packet__1__start_value;
    __Vtask_tb_stream_accumulator__DOT__send_packet__1__start_value = 0;
    IData/*31:0*/ __Vtask_tb_stream_accumulator__DOT__send_packet__1__step;
    __Vtask_tb_stream_accumulator__DOT__send_packet__1__step = 0;
    // Body
    VL_WRITEF_NX("===========================================\n   Testbench: Stream Accumulator Start\n===========================================\n",0);
    vlSymsp->_vm_contextp__->dumpfile("stream_acc.vcd"s);
    VL_PRINTF_MT("-Info: tb_stream_accumulator.sv:58: $dumpvar ignored, as Verilated without --trace\n");
    vlSelfRef.tb_stream_accumulator__DOT__rst_n = 0U;
    vlSelfRef.tb_stream_accumulator__DOT__t_valid = 0U;
    vlSelfRef.tb_stream_accumulator__DOT__t_last = 0U;
    vlSelfRef.tb_stream_accumulator__DOT__t_data = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000001eULL, 
                                         nullptr, "tb_stream_accumulator.sv", 
                                         65);
    vlSelfRef.tb_stream_accumulator__DOT__rst_n = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x0000000000000014ULL, 
                                         nullptr, "tb_stream_accumulator.sv", 
                                         67);
    __Vtask_tb_stream_accumulator__DOT__send_packet__0__step = 0x0000000aU;
    __Vtask_tb_stream_accumulator__DOT__send_packet__0__start_value = 0x0000000aU;
    __Vtask_tb_stream_accumulator__DOT__send_packet__0__length = 4U;
    VL_WRITEF_NX("[Time %0t] Sending Packet: Len=%0d, Start=%0d, Step=%0d\n",0,
                 64,VL_TIME_UNITED_Q(1),-12,32,__Vtask_tb_stream_accumulator__DOT__send_packet__0__length,
                 32,__Vtask_tb_stream_accumulator__DOT__send_packet__0__start_value,
                 32,__Vtask_tb_stream_accumulator__DOT__send_packet__0__step);
    tb_stream_accumulator__DOT__send_packet__Vstatic__i = 0U;
    while (VL_LTS_III(32, tb_stream_accumulator__DOT__send_packet__Vstatic__i, __Vtask_tb_stream_accumulator__DOT__send_packet__0__length)) {
        co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_stream_accumulator.clk)", 
                                                             "tb_stream_accumulator.sv", 
                                                             36);
        vlSelfRef.tb_stream_accumulator__DOT__t_valid = 1U;
        vlSelfRef.tb_stream_accumulator__DOT__t_data 
            = (0x0000ffffU & (__Vtask_tb_stream_accumulator__DOT__send_packet__0__start_value 
                              + VL_MULS_III(32, tb_stream_accumulator__DOT__send_packet__Vstatic__i, __Vtask_tb_stream_accumulator__DOT__send_packet__0__step)));
        vlSelfRef.tb_stream_accumulator__DOT__t_last 
            = (tb_stream_accumulator__DOT__send_packet__Vstatic__i 
               == (__Vtask_tb_stream_accumulator__DOT__send_packet__0__length 
                   - (IData)(1U)));
        tb_stream_accumulator__DOT__send_packet__Vstatic__i 
            = ((IData)(1U) + tb_stream_accumulator__DOT__send_packet__Vstatic__i);
    }
    co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_stream_accumulator.clk)", 
                                                         "tb_stream_accumulator.sv", 
                                                         44);
    vlSelfRef.tb_stream_accumulator__DOT__t_valid = 0U;
    vlSelfRef.tb_stream_accumulator__DOT__t_last = 0U;
    vlSelfRef.tb_stream_accumulator__DOT__t_data = 0U;
    while ((1U & (~ (IData)(vlSelfRef.tb_stream_accumulator__DOT__t_res_valid)))) {
        co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_stream_accumulator.clk)", 
                                                             "tb_stream_accumulator.sv", 
                                                             74);
    }
    if (VL_LIKELY(((0x00000064U == vlSelfRef.tb_stream_accumulator__DOT__t_result)))) {
        VL_WRITEF_NX("[PASS] Case 1 (Standard): Result = 100\n",0);
    } else {
        VL_WRITEF_NX("[%0t] %%Error: tb_stream_accumulator.sv:77: Assertion failed in %Ntb_stream_accumulator: [FAIL] Case 1: Expected 100, Got %0d\n",0,
                     64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name(),
                     32,vlSelfRef.tb_stream_accumulator__DOT__t_result);
        VL_STOP_MT("tb_stream_accumulator.sv", 77, "");
    }
    co_await vlSelfRef.__VdlySched.delay(0x0000000000000014ULL, 
                                         nullptr, "tb_stream_accumulator.sv", 
                                         79);
    __Vtask_tb_stream_accumulator__DOT__send_packet__1__step = 0U;
    __Vtask_tb_stream_accumulator__DOT__send_packet__1__start_value = 0x00000037U;
    __Vtask_tb_stream_accumulator__DOT__send_packet__1__length = 1U;
    VL_WRITEF_NX("[Time %0t] Sending Packet: Len=%0d, Start=%0d, Step=%0d\n",0,
                 64,VL_TIME_UNITED_Q(1),-12,32,__Vtask_tb_stream_accumulator__DOT__send_packet__1__length,
                 32,__Vtask_tb_stream_accumulator__DOT__send_packet__1__start_value,
                 32,__Vtask_tb_stream_accumulator__DOT__send_packet__1__step);
    tb_stream_accumulator__DOT__send_packet__Vstatic__i = 0U;
    while (VL_LTS_III(32, tb_stream_accumulator__DOT__send_packet__Vstatic__i, __Vtask_tb_stream_accumulator__DOT__send_packet__1__length)) {
        co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_stream_accumulator.clk)", 
                                                             "tb_stream_accumulator.sv", 
                                                             36);
        vlSelfRef.tb_stream_accumulator__DOT__t_valid = 1U;
        vlSelfRef.tb_stream_accumulator__DOT__t_data 
            = (0x0000ffffU & (__Vtask_tb_stream_accumulator__DOT__send_packet__1__start_value 
                              + VL_MULS_III(32, tb_stream_accumulator__DOT__send_packet__Vstatic__i, __Vtask_tb_stream_accumulator__DOT__send_packet__1__step)));
        vlSelfRef.tb_stream_accumulator__DOT__t_last 
            = (tb_stream_accumulator__DOT__send_packet__Vstatic__i 
               == (__Vtask_tb_stream_accumulator__DOT__send_packet__1__length 
                   - (IData)(1U)));
        tb_stream_accumulator__DOT__send_packet__Vstatic__i 
            = ((IData)(1U) + tb_stream_accumulator__DOT__send_packet__Vstatic__i);
    }
    co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_stream_accumulator.clk)", 
                                                         "tb_stream_accumulator.sv", 
                                                         44);
    vlSelfRef.tb_stream_accumulator__DOT__t_valid = 0U;
    vlSelfRef.tb_stream_accumulator__DOT__t_last = 0U;
    vlSelfRef.tb_stream_accumulator__DOT__t_data = 0U;
    while ((1U & (~ (IData)(vlSelfRef.tb_stream_accumulator__DOT__t_res_valid)))) {
        co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_stream_accumulator.clk)", 
                                                             "tb_stream_accumulator.sv", 
                                                             84);
    }
    if (VL_LIKELY(((0x00000037U == vlSelfRef.tb_stream_accumulator__DOT__t_result)))) {
        VL_WRITEF_NX("[PASS] Case 2 (Single): Result = 55\n",0);
    } else {
        VL_WRITEF_NX("[%0t] %%Error: tb_stream_accumulator.sv:87: Assertion failed in %Ntb_stream_accumulator: [FAIL] Case 2: Expected 55, Got %0d\n",0,
                     64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name(),
                     32,vlSelfRef.tb_stream_accumulator__DOT__t_result);
        VL_STOP_MT("tb_stream_accumulator.sv", 87, "");
    }
    co_await vlSelfRef.__VdlySched.delay(0x0000000000000014ULL, 
                                         nullptr, "tb_stream_accumulator.sv", 
                                         89);
    VL_WRITEF_NX("[Time %0t] Starting Back-to-Back Test...\n",0,
                 64,VL_TIME_UNITED_Q(1),-12);
    co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_stream_accumulator.clk)", 
                                                         "tb_stream_accumulator.sv", 
                                                         95);
    vlSelfRef.tb_stream_accumulator__DOT__t_valid = 1U;
    vlSelfRef.tb_stream_accumulator__DOT__t_data = 1U;
    vlSelfRef.tb_stream_accumulator__DOT__t_last = 0U;
    co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_stream_accumulator.clk)", 
                                                         "tb_stream_accumulator.sv", 
                                                         99);
    vlSelfRef.tb_stream_accumulator__DOT__t_valid = 1U;
    vlSelfRef.tb_stream_accumulator__DOT__t_data = 1U;
    vlSelfRef.tb_stream_accumulator__DOT__t_last = 1U;
    co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_stream_accumulator.clk)", 
                                                         "tb_stream_accumulator.sv", 
                                                         105);
    vlSelfRef.tb_stream_accumulator__DOT__t_valid = 1U;
    vlSelfRef.tb_stream_accumulator__DOT__t_data = 0x000aU;
    vlSelfRef.tb_stream_accumulator__DOT__t_last = 0U;
    if (VL_UNLIKELY((((IData)(vlSelfRef.tb_stream_accumulator__DOT__t_res_valid) 
                      & (2U == vlSelfRef.tb_stream_accumulator__DOT__t_result))))) {
        VL_WRITEF_NX("[PASS] Back-to-Back Part A: Result = 2\n",0);
    }
    co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_stream_accumulator.clk)", 
                                                         "tb_stream_accumulator.sv", 
                                                         114);
    vlSelfRef.tb_stream_accumulator__DOT__t_valid = 1U;
    vlSelfRef.tb_stream_accumulator__DOT__t_data = 0x000aU;
    vlSelfRef.tb_stream_accumulator__DOT__t_last = 1U;
    co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_stream_accumulator.clk)", 
                                                         "tb_stream_accumulator.sv", 
                                                         119);
    vlSelfRef.tb_stream_accumulator__DOT__t_valid = 0U;
    vlSelfRef.tb_stream_accumulator__DOT__t_last = 0U;
    while ((1U & (~ (IData)(vlSelfRef.tb_stream_accumulator__DOT__t_res_valid)))) {
        co_await vlSelfRef.__VtrigSched_he0f41604__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_stream_accumulator.clk)", 
                                                             "tb_stream_accumulator.sv", 
                                                             124);
    }
    if (VL_LIKELY(((0x00000014U == vlSelfRef.tb_stream_accumulator__DOT__t_result)))) {
        VL_WRITEF_NX("[PASS] Back-to-Back Part B: Result = 20\n",0);
    } else {
        VL_WRITEF_NX("[%0t] %%Error: tb_stream_accumulator.sv:126: Assertion failed in %Ntb_stream_accumulator: [FAIL] Back-to-Back Part B: Expected 20, Got %0d\n",0,
                     64,VL_TIME_UNITED_Q(1),-12,vlSymsp->name(),
                     32,vlSelfRef.tb_stream_accumulator__DOT__t_result);
        VL_STOP_MT("tb_stream_accumulator.sv", 126, "");
    }
    co_await vlSelfRef.__VdlySched.delay(0x0000000000000032ULL, 
                                         nullptr, "tb_stream_accumulator.sv", 
                                         128);
    VL_WRITEF_NX("===========================================\n",0);
    VL_FINISH_MT("tb_stream_accumulator.sv", 130, "");
    co_return;}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtb_stream_accumulator___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vtb_stream_accumulator___024root___eval_triggers__act(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_triggers__act\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.tb_stream_accumulator__DOT__clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_stream_accumulator__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_stream_accumulator__DOT__clk__0 
        = vlSelfRef.tb_stream_accumulator__DOT__clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtb_stream_accumulator___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vtb_stream_accumulator___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___trigger_anySet__act\n"); );
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

void Vtb_stream_accumulator___024root___nba_sequent__TOP__0(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___nba_sequent__TOP__0\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator;
    __Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator = 0;
    // Body
    __Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
        = vlSelfRef.tb_stream_accumulator__DOT__u_dut__DOT__accumulator;
    if (vlSelfRef.tb_stream_accumulator__DOT__rst_n) {
        vlSelfRef.tb_stream_accumulator__DOT__t_res_valid = 0U;
        if (vlSelfRef.tb_stream_accumulator__DOT__t_valid) {
            if (vlSelfRef.tb_stream_accumulator__DOT__t_last) {
                vlSelfRef.tb_stream_accumulator__DOT__t_res_valid = 1U;
                vlSelfRef.tb_stream_accumulator__DOT__t_result 
                    = (vlSelfRef.tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
                       + VL_EXTENDS_II(32,16, (IData)(vlSelfRef.tb_stream_accumulator__DOT__t_data)));
                __Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator = 0U;
            } else {
                __Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
                    = (vlSelfRef.tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
                       + VL_EXTENDS_II(32,16, (IData)(vlSelfRef.tb_stream_accumulator__DOT__t_data)));
            }
        }
    } else {
        vlSelfRef.tb_stream_accumulator__DOT__t_res_valid = 0U;
        vlSelfRef.tb_stream_accumulator__DOT__t_result = 0U;
        __Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator = 0U;
    }
    vlSelfRef.tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
        = __Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator;
}

void Vtb_stream_accumulator___024root___eval_nba(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_nba\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vinline__nba_sequent__TOP__0___Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator;
    __Vinline__nba_sequent__TOP__0___Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator = 0;
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__0___Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
            = vlSelfRef.tb_stream_accumulator__DOT__u_dut__DOT__accumulator;
        if (vlSelfRef.tb_stream_accumulator__DOT__rst_n) {
            vlSelfRef.tb_stream_accumulator__DOT__t_res_valid = 0U;
            if (vlSelfRef.tb_stream_accumulator__DOT__t_valid) {
                if (vlSelfRef.tb_stream_accumulator__DOT__t_last) {
                    vlSelfRef.tb_stream_accumulator__DOT__t_res_valid = 1U;
                    vlSelfRef.tb_stream_accumulator__DOT__t_result 
                        = (vlSelfRef.tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
                           + VL_EXTENDS_II(32,16, (IData)(vlSelfRef.tb_stream_accumulator__DOT__t_data)));
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator = 0U;
                } else {
                    __Vinline__nba_sequent__TOP__0___Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
                        = (vlSelfRef.tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
                           + VL_EXTENDS_II(32,16, (IData)(vlSelfRef.tb_stream_accumulator__DOT__t_data)));
                }
            }
        } else {
            vlSelfRef.tb_stream_accumulator__DOT__t_res_valid = 0U;
            vlSelfRef.tb_stream_accumulator__DOT__t_result = 0U;
            __Vinline__nba_sequent__TOP__0___Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator = 0U;
        }
        vlSelfRef.tb_stream_accumulator__DOT__u_dut__DOT__accumulator 
            = __Vinline__nba_sequent__TOP__0___Vdly__tb_stream_accumulator__DOT__u_dut__DOT__accumulator;
    }
}

void Vtb_stream_accumulator___024root___timing_commit(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___timing_commit\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((! (1ULL & vlSelfRef.__VactTriggered[0U]))) {
        vlSelfRef.__VtrigSched_he0f41604__0.commit(
                                                   "@(posedge tb_stream_accumulator.clk)");
    }
}

void Vtb_stream_accumulator___024root___timing_resume(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___timing_resume\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_he0f41604__0.resume(
                                                   "@(posedge tb_stream_accumulator.clk)");
    }
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vtb_stream_accumulator___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_stream_accumulator___024root___eval_phase__act(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_phase__act\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vtb_stream_accumulator___024root___eval_triggers__act(vlSelf);
    Vtb_stream_accumulator___024root___timing_commit(vlSelf);
    Vtb_stream_accumulator___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vtb_stream_accumulator___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        Vtb_stream_accumulator___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

void Vtb_stream_accumulator___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtb_stream_accumulator___024root___eval_phase__nba(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_phase__nba\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtb_stream_accumulator___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtb_stream_accumulator___024root___eval_nba(vlSelf);
        Vtb_stream_accumulator___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtb_stream_accumulator___024root___eval(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtb_stream_accumulator___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb_stream_accumulator.sv", 1, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtb_stream_accumulator___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("tb_stream_accumulator.sv", 1, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vtb_stream_accumulator___024root___eval_phase__act(vlSelf));
    } while (Vtb_stream_accumulator___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vtb_stream_accumulator___024root___eval_debug_assertions(Vtb_stream_accumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_stream_accumulator___024root___eval_debug_assertions\n"); );
    Vtb_stream_accumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
