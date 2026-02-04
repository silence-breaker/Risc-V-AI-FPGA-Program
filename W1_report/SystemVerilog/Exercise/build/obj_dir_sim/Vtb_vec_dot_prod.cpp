// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtb_vec_dot_prod__pch.h"

//============================================================
// Constructors

Vtb_vec_dot_prod::Vtb_vec_dot_prod(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtb_vec_dot_prod__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtb_vec_dot_prod::Vtb_vec_dot_prod(const char* _vcname__)
    : Vtb_vec_dot_prod(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtb_vec_dot_prod::~Vtb_vec_dot_prod() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtb_vec_dot_prod___024root___eval_debug_assertions(Vtb_vec_dot_prod___024root* vlSelf);
#endif  // VL_DEBUG
void Vtb_vec_dot_prod___024root___eval_static(Vtb_vec_dot_prod___024root* vlSelf);
void Vtb_vec_dot_prod___024root___eval_initial(Vtb_vec_dot_prod___024root* vlSelf);
void Vtb_vec_dot_prod___024root___eval_settle(Vtb_vec_dot_prod___024root* vlSelf);
void Vtb_vec_dot_prod___024root___eval(Vtb_vec_dot_prod___024root* vlSelf);

void Vtb_vec_dot_prod::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtb_vec_dot_prod::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtb_vec_dot_prod___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtb_vec_dot_prod___024root___eval_static(&(vlSymsp->TOP));
        Vtb_vec_dot_prod___024root___eval_initial(&(vlSymsp->TOP));
        Vtb_vec_dot_prod___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtb_vec_dot_prod___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtb_vec_dot_prod::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vtb_vec_dot_prod::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vtb_vec_dot_prod::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtb_vec_dot_prod___024root___eval_final(Vtb_vec_dot_prod___024root* vlSelf);

VL_ATTR_COLD void Vtb_vec_dot_prod::final() {
    Vtb_vec_dot_prod___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtb_vec_dot_prod::hierName() const { return vlSymsp->name(); }
const char* Vtb_vec_dot_prod::modelName() const { return "Vtb_vec_dot_prod"; }
unsigned Vtb_vec_dot_prod::threads() const { return 1; }
void Vtb_vec_dot_prod::prepareClone() const { contextp()->prepareClone(); }
void Vtb_vec_dot_prod::atClone() const {
    contextp()->threadPoolpOnClone();
}
