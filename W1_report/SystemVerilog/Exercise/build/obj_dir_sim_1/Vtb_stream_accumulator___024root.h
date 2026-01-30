// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtb_stream_accumulator.h for the primary calling header

#ifndef VERILATED_VTB_STREAM_ACCUMULATOR___024ROOT_H_
#define VERILATED_VTB_STREAM_ACCUMULATOR___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vtb_stream_accumulator__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtb_stream_accumulator___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_stream_accumulator__DOT__clk;
    CData/*0:0*/ tb_stream_accumulator__DOT__rst_n;
    CData/*0:0*/ tb_stream_accumulator__DOT__t_valid;
    CData/*0:0*/ tb_stream_accumulator__DOT__t_last;
    CData/*0:0*/ tb_stream_accumulator__DOT__t_res_valid;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_stream_accumulator__DOT__clk__0;
    SData/*15:0*/ tb_stream_accumulator__DOT__t_data;
    IData/*31:0*/ tb_stream_accumulator__DOT__t_result;
    IData/*31:0*/ tb_stream_accumulator__DOT__u_dut__DOT__accumulator;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_he0f41604__0;

    // INTERNAL VARIABLES
    Vtb_stream_accumulator__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vtb_stream_accumulator___024root(Vtb_stream_accumulator__Syms* symsp, const char* namep);
    ~Vtb_stream_accumulator___024root();
    VL_UNCOPYABLE(Vtb_stream_accumulator___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
