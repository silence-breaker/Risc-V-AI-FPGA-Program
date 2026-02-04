// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vvec_multi_core__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vvec_multi_core::Vvec_multi_core(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vvec_multi_core__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , i_data_valid{vlSymsp->TOP.i_data_valid}
    , i_load_weight{vlSymsp->TOP.i_load_weight}
    , i_data{vlSymsp->TOP.i_data}
    , i_weight{vlSymsp->TOP.i_weight}
    , o_data_ready{vlSymsp->TOP.o_data_ready}
    , o_result{vlSymsp->TOP.o_result}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vvec_multi_core::Vvec_multi_core(const char* _vcname__)
    : Vvec_multi_core(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vvec_multi_core::~Vvec_multi_core() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vvec_multi_core___024root___eval_debug_assertions(Vvec_multi_core___024root* vlSelf);
#endif  // VL_DEBUG
void Vvec_multi_core___024root___eval_static(Vvec_multi_core___024root* vlSelf);
void Vvec_multi_core___024root___eval_initial(Vvec_multi_core___024root* vlSelf);
void Vvec_multi_core___024root___eval_settle(Vvec_multi_core___024root* vlSelf);
void Vvec_multi_core___024root___eval(Vvec_multi_core___024root* vlSelf);

void Vvec_multi_core::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vvec_multi_core::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vvec_multi_core___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vvec_multi_core___024root___eval_static(&(vlSymsp->TOP));
        Vvec_multi_core___024root___eval_initial(&(vlSymsp->TOP));
        Vvec_multi_core___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vvec_multi_core___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vvec_multi_core::eventsPending() { return false; }

uint64_t Vvec_multi_core::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vvec_multi_core::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vvec_multi_core___024root___eval_final(Vvec_multi_core___024root* vlSelf);

VL_ATTR_COLD void Vvec_multi_core::final() {
    Vvec_multi_core___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vvec_multi_core::hierName() const { return vlSymsp->name(); }
const char* Vvec_multi_core::modelName() const { return "Vvec_multi_core"; }
unsigned Vvec_multi_core::threads() const { return 1; }
void Vvec_multi_core::prepareClone() const { contextp()->prepareClone(); }
void Vvec_multi_core::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vvec_multi_core::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vvec_multi_core___024root__trace_decl_types(VerilatedVcd* tracep);

void Vvec_multi_core___024root__trace_init_top(Vvec_multi_core___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vvec_multi_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vvec_multi_core___024root*>(voidSelf);
    Vvec_multi_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vvec_multi_core___024root__trace_decl_types(tracep);
    Vvec_multi_core___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vvec_multi_core___024root__trace_register(Vvec_multi_core___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vvec_multi_core::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vvec_multi_core::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vvec_multi_core___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
