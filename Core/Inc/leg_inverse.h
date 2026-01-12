// leg_inverse.h

#ifndef LEG_INVERSE_H
#define LEG_INVERSE_H

#include <stdbool.h>

/* --- 全局变量 --- */
// 最终计算出的三个腿部关节角度 (作为函数的输出)
// extern 关键字用于“声明”这些变量，实际的内存定义在 .c 文件中。
extern float leg_j1_angle; // 髋关节 (旋转, Yaw)
extern float leg_j2_angle; // 髋关节 (俯仰, Pitch)
extern float leg_j3_angle; // 膝关节 (Knee)

/**
 * @brief 计算三自由度机械腿的逆运动学解。
 *
 * @param target_x 目标末端点 (脚尖) 的 X 坐标。
 * @param target_y 目标末端点 (脚尖) 的 Y 坐标。
 * @param target_z 目标末端点 (脚尖) 的 Z 坐标。
 * @return bool 如果找到有效的解则返回 true, 否则返回 false。
 */
bool leg_inverse_calculate(float target_x, float target_y, float target_z);

#endif // LEG_INVERSE_H

