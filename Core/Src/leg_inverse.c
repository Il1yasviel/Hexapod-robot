// leg_inverse.c

#include "leg_inverse.h"
#include "math.h"
#include "arm_math.h"  // <--- 新增：引入 CMSIS-DSP 库
#include <stdio.h>

/* --- 全局变量定义 --- */
float leg_j1_angle, leg_j2_angle, leg_j3_angle;

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
#define RAD_TO_DEG(rad) ((rad) * 180.0f / M_PI)

/**
 * @brief 计算三自由度机械腿的逆运动学解 (解析解)。
 * @note  此版本完全遵循用户信任的算法结构，仅修正物理参数的应用位置。
 */
bool leg_inverse_calculate(float target_x, float target_y, float target_z)
{
    // --- 【最终修正】机械腿物理尺寸和结构 ---
    // 这是一个固定的结构偏移，不是活动的连杆
    const float Y_OFFSET = 12.0f;
    // 这是两个活动的连杆
    const float FEMUR_LEN  = 6.5f;
    const float TIBIA_LEN  = 10.0f;

    // --- 步骤 1: 计算关节1 (J1) 的角度 ---
    // J1的角度是相对于J1安装点(0, 12, 0)的，而不是世界原点(0,0,0)
    // 所以我们需要用 (target_y - Y_OFFSET) 来计算
    // 注：CMSIS-DSP 未提供 atan2f，保持原样
    leg_j1_angle = RAD_TO_DEG(atan2f(target_x, target_y - Y_OFFSET));

    // --- 步骤 2: 将3D问题简化为2D平面问题 (算法结构不变) ---
    // L 是目标点到J1旋转轴的水平距离 (替换为 DSP 库的开平方)
    float L;
    arm_sqrt_f32(target_x * target_x + (target_y - Y_OFFSET) * (target_y - Y_OFFSET), &L);

    // H 是目标点相对于J1旋转平面的垂直高度。因为J1没有Z偏移，所以H就是target_z
    float H = target_z;

    // D 是从J2关节(与J1同轴)到脚尖的直线距离 (替换为 DSP 库的开平方)
    float D_sq = L*L + H*H;
    float D;
    arm_sqrt_f32(D_sq, &D);

    // --- 步骤 3: 检查目标点对于活动连杆是否可达 ---
    if (D > (FEMUR_LEN + TIBIA_LEN) || D < fabsf(FEMUR_LEN - TIBIA_LEN)) {
        return false; // 目标点够不到
    }

    // --- 步骤 4: 使用余弦定理计算关节3 (J3, Tibia) 的角度 ---
    float cos_j3_val = (FEMUR_LEN*FEMUR_LEN + TIBIA_LEN*TIBIA_LEN - D_sq) / (2.0f * FEMUR_LEN * TIBIA_LEN);
    if (cos_j3_val > 1.0f)  cos_j3_val = 1.0f;
    if (cos_j3_val < -1.0f) cos_j3_val = -1.0f;
    // 注：CMSIS-DSP 未提供 acosf，保持原样
    leg_j3_angle = 180.0f - RAD_TO_DEG(acosf(cos_j3_val));

    // --- 步骤 5: 计算关节2 (J2, Femur) 的角度 ---
    // 注：CMSIS-DSP 未提供 atan2f 和 acosf，保持原样
    float gamma = atan2f(H, L);
    float cos_beta = (D_sq + FEMUR_LEN*FEMUR_LEN - TIBIA_LEN*TIBIA_LEN) / (2.0f * D * FEMUR_LEN);
    if (cos_beta > 1.0f)  cos_beta = 1.0f;
    if (cos_beta < -1.0f) cos_beta = -1.0f;
    float beta = acosf(cos_beta);
    leg_j2_angle = RAD_TO_DEG(gamma + beta);

    return true;
}

