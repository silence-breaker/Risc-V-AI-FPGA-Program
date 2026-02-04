#include <iostream>
#include <iomanip>
#include <vector>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vvec_multi_core.h"

// 对应 SystemVerilog 中的 package_def 定义
#define VAL_W_NEG  0  // 2'b00
#define VAL_W_ZERO 1  // 2'b01
#define VAL_W_POS  2  // 2'b10

// 全局仿真时间
vluint64_t main_time = 0;

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vvec_multi_core* top = new Vvec_multi_core;

    // --- 1. 波形配置 ---
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99); // 追踪深度
    tfp->open("waveform.vcd");

    // --- 2. 辅助函数定义 ---

    // 时钟跳变函数
    auto tick = [&]() {
        top->clk = 1; top->eval();
        tfp->dump(main_time++); // 记录高电平
        top->clk = 0; top->eval();
        tfp->dump(main_time++); // 记录低电平
    };

    // [关键] 安全设置 128-bit 输入数据 (避免内存越界)
    // 将 val 赋给所有 16 个输入通道
    auto set_all_inputs = [&](int8_t val) {
        // Verilator 将 logic [15:0][7:0] i_data 映射为 4个 uint32_t
        for (int k = 0; k < 4; k++) {
            uint32_t chunk = 0;
            for (int j = 0; j < 4; j++) {
                // 将 8-bit 数据拼接到 32-bit 块中
                chunk |= ((uint32_t)(uint8_t)val) << (j * 8);
            }
            top->i_data[k] = chunk;
        }
    };

    // [关键] 安全设置 1.58-bit 权重
    // val_type: VAL_W_POS, VAL_W_NEG, or VAL_W_ZERO
    auto set_all_weights = [&](int val_type) {
        uint32_t w_data = 0;
        for(int i=0; i<16; i++) {
            w_data |= (val_type << (i * 2));
        }
        top->i_weight = w_data;
    };

    // --- 3. 仿真开始 ---
    
    // 初始化所有信号 (消除红线/不定态)
    top->clk = 0;
    top->rst_n = 0;
    top->i_data_valid = 0;
    top->i_load_weight = 0;
    set_all_weights(VAL_W_ZERO);
    set_all_inputs(0);
    
    std::cout << "[SIM] Starting Simulation..." << std::endl;
    
    // 复位保持 10 个周期
    for(int i=0; i<10; i++) tick();
    top->rst_n = 1; // 释放复位
    tick();

    // ==========================================
    // Case 1: 全 +1 权重 (1.58-bit Positive)
    // ==========================================
    std::cout << "\n[CASE 1] Loading Weights: All +1" << std::endl;
    top->i_load_weight = 1;
    set_all_weights(VAL_W_POS);
    tick(); // 打一拍加载权重
    top->i_load_weight = 0;

    std::cout << "[CASE 1] Input: 10. Expected Output: 160" << std::endl;
    top->i_data_valid = 1;
    set_all_inputs(10); 
    tick(); // 数据进入流水线 Stage 0

    // 验证"锁存特性": 立即拉低 valid，不再输入新数据
    // 期望：Ready 信号只亮 1 拍，但 Result 信号更新为 160 后一直保持
    top->i_data_valid = 0; 
    
    // 观察 10 拍
    for(int i=0; i<10; i++) {
        tick();
        // 打印 Result 和 Ready 状态
        std::cout << "  Cycle " << i << ": Result=" << (int)top->o_result 
                  << " | Ready=" << (int)top->o_data_ready << std::endl;
    }

    // ==========================================
    // Case 2: 全 -1 权重 (1.58-bit Negative)
    // ==========================================
    std::cout << "\n[CASE 2] Loading Weights: All -1" << std::endl;
    top->i_load_weight = 1;
    set_all_weights(VAL_W_NEG);
    tick();
    top->i_load_weight = 0;

    std::cout << "[CASE 2] Input: 5. Expected Output: -80" << std::endl;
    top->i_data_valid = 1;
    set_all_inputs(5);
    tick();
    
    top->i_data_valid = 0; // 再次拉低，测试锁存
    for(int i=0; i<10; i++) {
        tick();
        std::cout << "  Cycle " << i << ": Result=" << (int)top->o_result 
                  << " | Ready=" << (int)top->o_data_ready << std::endl;
    }

    // ==========================================
    // Case 3: 连续数据流测试 (Pipeline Burst)
    // ==========================================
    std::cout << "\n[CASE 3] Pipeline Burst (Continuous Inputs)" << std::endl;
    // 保持权重为 -1 不变
    top->i_data_valid = 1;
    
    // 连续输入 3 个不同的数: 1, 2, 3
    // 对应输出应为: -16, -32, -48
    int inputs[] = {1, 2, 3};
    
    for(int k=0; k<3; k++) {
        set_all_inputs(inputs[k]);
        tick();
    }
    
    top->i_data_valid = 0; // 结束输入
    
    // 观察输出流出过程
    for(int i=0; i<8; i++) {
        tick();
        if (top->o_data_ready) {
            std::cout << "  [Burst Output] Result=" << (int)top->o_result << std::endl;
        }
    }

    // --- 4. 结束仿真 ---
    top->final();
    tfp->close();
    delete top;
    
    std::cout << "\n[SIM] Done. Waveform saved to waveform.vcd" << std::endl;
    return 0;
}