/* FILE: gait.h */

#ifndef __GAIT_H
#define __GAIT_H

#include "stm32f1xx_hal.h" // 包含HAL库定义
#include <stdint.h>        // 包含标准整数类型
#include <stdbool.h>       // 包含布尔类型定义

// 定义腿的ID，方便代码阅读和管理
typedef enum {
    LEG_LEFT_FRONT   = 0,
    LEG_LEFT_MIDDLE  = 1,
    LEG_LEFT_REAR    = 2,
    LEG_RIGHT_FRONT  = 3,
    LEG_RIGHT_MIDDLE = 4,
    LEG_RIGHT_REAR   = 5
} Leg_ID_t;


/**
 * @brief 步态模块初始化 (当前为空，为未来扩展保留)
 */
void Gait_Init(void);

/**
 * @brief 控制机器人站立到准备姿态
 */
void Gait_Stand_Still(void);

/**
 * @brief 执行前进三角步态
 * @param steps 行走的步数
 */
void Gait_Tripod_Forward(uint8_t steps);

/**
 * @brief 执行后退三角步态
 * @param steps 后退的步数
 */
void Gait_Tripod_Backward(uint8_t steps);

/**
 * @brief 执行前进波动步态
 * @param steps 行走的步数
 */
void Gait_Wave_Forward(uint8_t steps);

/**
 * @brief 执行后退波动步态
 * @param steps 后退的步数
 */
void Gait_Wave_Backward(uint8_t steps);

/**
 * @brief 执行波动步态原地左转
 * @param steps 转动的步数 (一个完整循环算一步)
 */
void Gait_Wave_TurnLeft(uint8_t steps);

/**
 * @brief 执行波动步态原地右转
 * @param steps 转动的步数 (一个完整循环算一步)
 */
void Gait_Wave_TurnRight(uint8_t steps);

/**
 * @brief 执行前进涟漪步态
 * @param steps 行走的步数 (一个完整循环算一步)
 */
void Gait_Ripple_Forward(uint8_t steps);

/**
 * @brief 执行后退涟漪步态
 * @param steps 后退的步数 (一个完整循环算一步)
 */
void Gait_Ripple_Backward(uint8_t steps); // <--- 核心修正：添加此行声明

/**
 * @brief 执行前进对角/快步步态
 * @param steps 行走的步数 (一个完整循环算一步)
 */
void Gait_Trot_Forward(uint8_t steps);


/**
 * @brief (调试用) 单腿执行一次前进摆动序列
 * @param leg_id 要控制的腿的ID
 */
void Leg_Action_Forward(Leg_ID_t leg_id);

/**
 * @brief (调试用) 单腿执行一次后退摆动序列
 * @param leg_id 要控制的腿的ID
 */
void Leg_Action_Backward(Leg_ID_t leg_id);


#endif /* __GAIT_H */

