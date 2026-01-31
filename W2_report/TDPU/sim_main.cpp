#include "Vvec_multi_core.h"  
#include "verilated.h"
#include "verilated_vcd_c.h" 

// 定义枚举映射
#define W_NEG  0  // 2'b00
#define W_ZERO 1  // 2'b01
#define W_POS  2  // 2'b10

vluint64_t main_time = 0;

// =========================================================================
// 辅助函数：帮助你像操作数组一样设置 Packed 信号
// =========================================================================

// 设置 i_weight 的第 index 个权重
// i_weight 是 32位整数，每个权重占 2位
void set_weight(Vvec_multi_core* top, int index, int value) {
    int shift = index * 2;
    // 1. 清除原来的2位 ( & ~(3 << shift) )
    top->i_weight &= ~(3 << shift);
    // 2. 设置新的值
    top->i_weight |= (value << shift);
}

// 设置 i_data 的第 index 个数据
// i_data 是 128位 (VlWide<4>)，每个数据占 8位
// Verilator 将其存储为 4个 32位整数的数组: i_data[0]...i_data[3]
void set_data(Vvec_multi_core* top, int index, int value) {
    // 找到对应的 32位 块索引 (0~3)
    int word_idx = (index * 8) / 32; 
    // 找到块内的偏移量 (0, 8, 16, 24)
    int shift = (index * 8) % 32;
    
    // 1. 清除原来的8位 (0xFF)
    top->i_data[word_idx] &= ~(0xFF << shift);
    // 2. 设置新值
    top->i_data[word_idx] |= (value << shift);
}
// =========================================================================


int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true); 

    Vvec_multi_core* top = new Vvec_multi_core;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    
    top->trace(tfp, 99);  
    tfp->open("wave.vcd"); 

    // === 初始化 ===
    top->clk = 0;
    top->rst_n = 0;
    top->i_data_valid = 0;
    top->i_load_weight = 0;
    
    // 初始化清零
    top->i_weight = 0;
    for(int k=0; k<4; k++) top->i_data[k] = 0; // i_data 是 4个int的数组

    while (main_time < 200 && !Verilated::gotFinish()) {
        
        // [0-10ns] 复位
        if (main_time < 10) top->rst_n = 0;
        else top->rst_n = 1;

        // [20ns] Case 1: 加载全 +1 权重
        if (main_time == 20) {
            printf("[Sim] Loading Weights: All +1\n");
            top->i_load_weight = 1;
            // 使用辅助函数设置权重
            for(int i=0; i<16; i++) set_weight(top, i, W_POS);
        }
        if (main_time == 30) top->i_load_weight = 0;

        // [40ns] 发送全 1 数据 -> 预期结果 16
        if (main_time == 40) {
            printf("[Sim] Sending Data: All 1\n");
            top->i_data_valid = 1;
            // 使用辅助函数设置数据
            for(int i=0; i<16; i++) set_data(top, i, 1);
        }
        if (main_time == 50) {
            top->i_data_valid = 0;
            // 清零数据
            for(int k=0; k<4; k++) top->i_data[k] = 0;
        }

        // [80ns] Case 2: 混合权重 (前8个+1，后8个-1)
        if (main_time == 80) {
            printf("[Sim] Loading Weights: Mixed\n");
            top->i_load_weight = 1;
            for(int i=0; i<16; i++) {
                if(i<8) set_weight(top, i, W_POS);
                else    set_weight(top, i, W_NEG);
            }
        }
        if (main_time == 90) top->i_load_weight = 0;

        // [100ns] 发送数据 2 -> 预期结果 0
        if (main_time == 100) {
            printf("[Sim] Sending Data: 2\n");
            top->i_data_valid = 1;
            for(int i=0; i<16; i++) set_data(top, i, 2);
        }
        if (main_time == 110) top->i_data_valid = 0;


        // --- 时钟翻转 ---
        if (main_time % 5 == 0) top->clk = !top->clk;

        top->eval();
        tfp->dump(main_time); 
        
        if (top->clk == 1 && top->o_data_ready == 1) {
             // 转为有符号打印
             int32_t res = (int32_t)top->o_result;
             printf("[Result] Time %ld: Output = %d\n", main_time, res);
        }

        main_time++;
    }

    top->final();
    tfp->close();
    delete top;
    delete tfp;
    return 0;
}