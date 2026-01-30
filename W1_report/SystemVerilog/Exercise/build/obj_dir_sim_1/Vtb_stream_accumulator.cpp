// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_stream_accumulator__pch.h"

//============================================================
// Constructors

Vtb_stream_accumulator::Vtb_stream_accumulator(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_stream_accumulator__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_stream_accumulator::Vtb_stream_accumulator(const char* _vcname__)
    : Vtb_stream_accumulator(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_stream_accumulator::~Vtb_stream_accumulator() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_stream_accumulator___024root___eval_debug_assertions(Vtb_stream_accumulator___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_stream_accumulator___024root___eval_static(Vtb_stream_accumulator___024root* vlSelf);
void Vtb_stream_accumulator___024root___eval_initial(Vtb_stream_accumulator___024root* vlSelf);
void Vtb_stream_accumulator___024root___eval_settle(Vtb_stream_accumulator___024root* vlSelf);
void Vtb_stream_accumulator___024root___eval(Vtb_stream_accumulator___024root* vlSelf);

void Vtb_stream_accumulator::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_stream_accumulator::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_stream_accumulator___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_stream_accumulator___024root___eval_static(&(vlSymsp->TOP));
        Vtb_stream_accumulator___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_stream_accumulator___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_stream_accumulator___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_stream_accumulator::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vtb_stream_accumulator::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_stream_accumulator::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_stream_accumulator___024root___eval_final(Vtb_stream_accumulator___024root* vlSelf);

VL_ATTR_COLD void Vtb_stream_accumulator::final() {
    Vtb_stream_accumulator___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_stream_accumulator::hierName() const { return vlSymsp->name(); }
const char* Vtb_stream_accumulator::modelName() const { return "Vtb_stream_accumulator"; }
unsigned Vtb_stream_accumulator::threads() const { return 1; }
void Vtb_stream_accumulator::prepareClone() const { contextp()->prepareClone(); }
void Vtb_stream_accumulator::atClone() const {
    contextp()->threadPoolpOnClone();
}
