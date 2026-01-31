#include <iostream>
#include <iomanip>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vvec_multi_core.h"

// 对应 package_def.sv 的枚举值
#define VAL_W_NEG  0  // 2'b00
#define VAL_W_ZERO 1  // 2'b01
#define VAL_W_POS  2  // 2'b10

vluint64_t main_time = 0;

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vvec_multi_core* top = new Vvec_multi_core;

    // --- 1. 波形配置 ---
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("waveform.vcd");

    auto tick = [&]() {
        top->clk = 1; top->eval();
        tfp->dump(main_time++);
        top->clk = 0; top->eval();
        tfp->dump(main_time++);
    };

    // --- 辅助函数：正确处理 128-bit 输入 ---
    // 能够安全地将 16 个 8位数据写入 Verilator 的宽接口
    auto set_input_data = [&](int8_t val) {
        // Verilator 将 128位接口映射为 4个 32位整数 (4 * 32 = 128)
        for (int k = 0; k < 4; k++) { 
            uint32_t chunk = 0;
            for (int j = 0; j < 4; j++) { 
                // 拼接 4个 8bit 数据为一个 32bit 包
                chunk |= ((uint32_t)(uint8_t)val) << (j * 8);
            }
            top->i_data[k] = chunk; // 写入对应的 32位块
        }
    };

    // --- 2. 复位过程 ---
    std::cout << "[SIM] Resetting..." << std::endl;
    top->rst_n = 0;
    top->i_data_valid = 0;
    top->i_load_weight = 0;
    set_input_data(0); // 初始化输入为0
    for(int i=0; i<10; i++) tick();
    top->rst_n = 1;
    tick();

    // --- Case 1: 全 +1 权重，测试结果锁存 ---
    std::cout << "\n[CASE 1] All Weights = +1 (Should hold 160)" << std::endl;
    
    // 1. 加载权重
    top->i_load_weight = 1;
    uint32_t w_data = 0;
    for(int i=0; i<16; i++) w_data |= (VAL_W_POS << (i * 2));
    top->i_weight = w_data;
    tick();
    top->i_load_weight = 0;

    // 2. 输入有效数据 (输入 10 -> 结果应为 160)
    top->i_data_valid = 1;
    set_input_data(10); 
    tick(); // 数据进入流水线第一级

    // 3. 立即拉低 valid，观察输出是否保持 (锁存效果)
    top->i_data_valid = 0;
    // 即使 valid 变低，i_data 我们也不改，保持 10，看 product 锁存住没
    
    // 等待 10 拍，观察流水线流出后的结果
    for(int i=0; i<10; i++) {
        tick();
        // 打印所有周期的结果，不论 ready 信号如何，验证数值是否保持
        std::cout << "Cycle " << i << ": Result = " << (int)top->o_result 
                  << " (Ready=" << (int)top->o_data_ready << ")" << std::endl;
    }

    // --- Case 2: 全 -1 权重 ---
    std::cout << "\n[CASE 2] All Weights = -1 (Should hold -80)" << std::endl;
    top->i_load_weight = 1;
    w_data = 0;
    for(int i=0; i<16; i++) w_data |= (VAL_W_NEG << (i * 2));
    top->i_weight = w_data;
    tick();
    top->i_load_weight = 0;

    // 输入 5 -> 结果应为 -80
    top->i_data_valid = 1;
    set_input_data(5); 
    tick();

    // 再次拉低 valid，验证锁存
    top->i_data_valid = 0;
    
    for(int i=0; i<10; i++) {
        tick();
        std::cout << "Cycle " << i << ": Result = " << (int)top->o_result << std::endl;
    }

    std::cout << "\n[SIM] Done. Waveform generated." << std::endl;
    top->final();
    tfp->close();
    delete top;
    return 0;
}