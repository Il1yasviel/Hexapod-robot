/* FILE: gait.c */

#include "gait.h"
#include <math.h>
#include "main.h"
#include <stdbool.h>

// --- 外部函数声明 (由 main.c 提供) ---
void Set_Leg_Position(Leg_ID_t leg_id, float target_x, float target_y, float target_z);
void Apply_All_Servo_Positions(uint16_t move_time);

// --- 内部辅助函数 ---
static void _Set_Prepare_Pose(Leg_ID_t leg_id)
{
    switch (leg_id)
    {
    case LEG_LEFT_FRONT:   Set_Leg_Position(leg_id, 2.0, 16.4, -13.5); break;
    case LEG_LEFT_MIDDLE:  Set_Leg_Position(leg_id, -2.0, 16.4, -13.5); break;
    case LEG_LEFT_REAR:    Set_Leg_Position(leg_id, 0.0, 16.4, -13.5); break;
    case LEG_RIGHT_FRONT:  Set_Leg_Position(leg_id, 2.0, 16.4, -13.5); break;
    case LEG_RIGHT_MIDDLE: Set_Leg_Position(leg_id, -2.0, 16.4, -13.5); break;
    case LEG_RIGHT_REAR:   Set_Leg_Position(leg_id, 0.0, 16.4, -13.5); break;
    }
}

// --- 步态初始化和站立 ---
void Gait_Init(void) {}

void Gait_Stand_Still(void)
{
    const Leg_ID_t all_legs[] = {LEG_LEFT_FRONT, LEG_LEFT_MIDDLE, LEG_LEFT_REAR, LEG_RIGHT_FRONT, LEG_RIGHT_MIDDLE, LEG_RIGHT_REAR};
    for(int i=0; i<6; i++) {
        _Set_Prepare_Pose(all_legs[i]);
    }
    Apply_All_Servo_Positions(500);
    HAL_Delay(500);
}

// --- 三角步态实现 ---
void Gait_Tripod_Forward(uint8_t steps)
{
    const uint16_t T_LIFT = 200;
    const uint16_t T_SWING = 300;
    const uint16_t T_DROP = 200;
    const float BODY_Y_ON_GROUND = 16.4f;

    for (uint8_t i = 0; i < steps; i++)
    {
        // Frame 1
        Set_Leg_Position(LEG_LEFT_FRONT,   6.0, 21.0, -1.5);
        Set_Leg_Position(LEG_LEFT_REAR,    0.0, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -4.5, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_FRONT,  2.86, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   0.57, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -1.29, BODY_Y_ON_GROUND, -13.5);
        Apply_All_Servo_Positions(T_LIFT); HAL_Delay(T_LIFT);

        // Frame 2
        Set_Leg_Position(LEG_LEFT_FRONT,   -2.0, 22.0, -1.5);
        Set_Leg_Position(LEG_LEFT_REAR,    -7.0, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -7.0, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_FRONT,  4.14, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   1.43, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -0.22, BODY_Y_ON_GROUND, -13.5);
        Apply_All_Servo_Positions(T_SWING); HAL_Delay(T_SWING);

        // Frame 3
        Set_Leg_Position(LEG_LEFT_FRONT,   0.0, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_LEFT_REAR,    -3.5, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -4.0, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_RIGHT_FRONT,  5.0, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   2.0, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_LEFT_MIDDLE,  0.5, BODY_Y_ON_GROUND, -13.5);
        Apply_All_Servo_Positions(T_DROP); HAL_Delay(T_DROP);

        // Frame 4
        Set_Leg_Position(LEG_RIGHT_FRONT,  6.0, 21.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   6.0, 21.0, -1.5);
        Set_Leg_Position(LEG_LEFT_MIDDLE,  0.5, 20.4, -1.5);
        Set_Leg_Position(LEG_LEFT_FRONT,   1.43, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_LEFT_REAR,    -1.93, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -2.71, BODY_Y_ON_GROUND, -13.5);
        Apply_All_Servo_Positions(T_LIFT); HAL_Delay(T_LIFT);

        // Frame 5
        Set_Leg_Position(LEG_RIGHT_FRONT,  -2.0, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   -7.0, 22.0, -1.5);
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -7.0, 22.0, -1.5);
        Set_Leg_Position(LEG_LEFT_FRONT,   3.57, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_LEFT_REAR,    0.43, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -0.78, BODY_Y_ON_GROUND, -13.5);
        Apply_All_Servo_Positions(T_SWING); HAL_Delay(T_SWING);

        // Frame 6
        Set_Leg_Position(LEG_RIGHT_FRONT,  0.0,  BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   -3.5, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -4.0, BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_LEFT_FRONT,   5.0,  BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_LEFT_REAR,    2.0,  BODY_Y_ON_GROUND, -13.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 0.5,  BODY_Y_ON_GROUND, -13.5);
        Apply_All_Servo_Positions(T_DROP); HAL_Delay(T_DROP);
    }
    Gait_Stand_Still();
}

void Gait_Tripod_Backward(uint8_t steps)
{
    for (uint8_t i = 0; i < steps; i++)
    {
        // 【第 1 帧】: A组抬腿
        Set_Leg_Position(LEG_LEFT_FRONT,   6.0, 21.0, -1.5);
        Set_Leg_Position(LEG_LEFT_REAR,    0.0, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -4.5, 22.0, -1.5);
        Apply_All_Servo_Positions(200); HAL_Delay(200);

        // 【第 2 帧】: A组向后摆, B组向前蹬
        Set_Leg_Position(LEG_LEFT_FRONT,   11.0, 16.0, -1.5);
        Set_Leg_Position(LEG_LEFT_REAR,    2.0, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 1.0, 22.0, -1.5);
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -3.0, 16.4, -13.5);
        Set_Leg_Position(LEG_RIGHT_FRONT,  -1.0, 16.4, -13.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   -2.0, 16.0, -13.5);
        Apply_All_Servo_Positions(300); HAL_Delay(300);

        // 【第 3 帧】: A组落腿
        Set_Leg_Position(LEG_LEFT_FRONT,   5.0, 13.0, -13.5);
        Set_Leg_Position(LEG_LEFT_REAR,    2.0, 16.4, -13.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 0.0, 16.4, -13.5);
        Apply_All_Servo_Positions(200); HAL_Delay(200);

        // 【第 4 帧】: B组抬腿
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -4.0, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_FRONT,  -1.0, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   -2.0, 21.0, -1.5);
        Apply_All_Servo_Positions(200); HAL_Delay(200);

        // 【第 5 帧】: B组向后摆, A组向前蹬
        Set_Leg_Position(LEG_LEFT_MIDDLE,  1.0, 22.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_FRONT,  11.0, 16.0, -1.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   2.0, 22.0, -1.5);
        Set_Leg_Position(LEG_LEFT_FRONT,   -1.0, 16.4, -13.5);
        Set_Leg_Position(LEG_LEFT_REAR,    -2.0, 16.0, -13.5);
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -3.0, 16.4, -13.5);
        Apply_All_Servo_Positions(300); HAL_Delay(300);

        // 【第 6 帧】: B组落腿
        Set_Leg_Position(LEG_LEFT_MIDDLE,  0.0, 16.4, -13.5);
        Set_Leg_Position(LEG_RIGHT_FRONT,  5.0, 13.0, -13.5);
        Set_Leg_Position(LEG_RIGHT_REAR,   2.0, 16.4, -13.5);
        Apply_All_Servo_Positions(200); HAL_Delay(200);
    }
    Gait_Stand_Still();
}

// ===================================================================
// =================== 核心新增: 三角步态原地转向 ====================
// ===================================================================
void Gait_Tripod_TurnLeft(uint8_t steps)
{
    for (uint8_t i = 0; i < steps; i++)
    {
        // --- 周期 1: A组(1,3,5)摆动, B组(2,4,6)支撑 ---

        // 【第 1 帧】: A组抬腿
        Set_Leg_Position(LEG_LEFT_FRONT,   6.0, 21.0, -1.5);   // c1
        Set_Leg_Position(LEG_LEFT_REAR,    0.0, 22.0, -1.5);   // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -4.5, 22.0, -1.5);  // c5
        // B组保持站立姿态
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -2.0, 16.4, -13.5); // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  2.0, 16.4, -13.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   0.0, 16.4, -13.5);  // c6
        Apply_All_Servo_Positions(200); HAL_Delay(200);

        // 【第 2 帧】: A组转向摆动, B组蹬地
        Set_Leg_Position(LEG_LEFT_FRONT,   11.0, 16.0, -1.5);  // c1
        Set_Leg_Position(LEG_LEFT_REAR,    2.0, 22.0, -1.5);   // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -7.0, 22.0, -1.5);  // c5
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -3.0, 16.4, -13.5); // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  5.0, 14.0, -13.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   2.0, 16.0, -13.5);  // c6
        Apply_All_Servo_Positions(300); HAL_Delay(300);

        // 【第 3 帧】: A组落腿
        Set_Leg_Position(LEG_LEFT_FRONT,   5.0, 13.0, -13.5);  // c1
        Set_Leg_Position(LEG_LEFT_REAR,    2.0, 16.4, -13.5);  // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 0.0, 16.4, -13.5);  // c5
        // B组保持蹬地结束位置
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -3.0, 16.4, -13.5); // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  5.0, 14.0, -13.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   2.0, 16.0, -13.5);  // c6
        Apply_All_Servo_Positions(200); HAL_Delay(200);

        // --- 周期 2: B组(2,4,6)摆动, A组(1,3,5)支撑 ---

        // 【第 4 帧】: B组抬腿
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -4.0, 22.0, -1.5);  // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  -1.0, 22.0, -1.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   6.0, 21.0, -1.5);   // c6
        // A组保持站立姿态
        Set_Leg_Position(LEG_LEFT_FRONT,   5.0, 13.0, -13.5);  // c1
        Set_Leg_Position(LEG_LEFT_REAR,    2.0, 16.4, -13.5);  // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 0.0, 16.4, -13.5);  // c5
        Apply_All_Servo_Positions(200); HAL_Delay(200);

        // 【第 5 帧】: B组转向摆动, A组蹬地
        Set_Leg_Position(LEG_LEFT_MIDDLE,  1.0, 22.0, -1.5);   // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  -2.0, 22.0, -1.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   -7.0, 22.0, -1.5);  // c6
        Set_Leg_Position(LEG_LEFT_FRONT,   -1.0, 16.4, -13.5); // c1
        Set_Leg_Position(LEG_LEFT_REAR,    -2.0, 16.0, -13.5); // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -3.0, 16.4, -13.5); // c5
        Apply_All_Servo_Positions(300); HAL_Delay(300);

        // 【第 6 帧】: B组落腿
        Set_Leg_Position(LEG_LEFT_MIDDLE,  0.0, 16.4, -13.5);  // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  0.0, 16.4, -13.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   -3.5, 16.4, -13.5); // c6
        // A组保持蹬地结束位置
        Set_Leg_Position(LEG_LEFT_FRONT,   -1.0, 16.4, -13.5); // c1
        Set_Leg_Position(LEG_LEFT_REAR,    -2.0, 16.0, -13.5); // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -3.0, 16.4, -13.5); // c5
        Apply_All_Servo_Positions(200); HAL_Delay(200);
    }
    Gait_Stand_Still();
}

void Gait_Tripod_TurnRight(uint8_t steps)
{
    for (uint8_t i = 0; i < steps; i++)
    {
        // --- 周期 1: A组(1,3,5)摆动, B组(2,4,6)支撑 ---

        // 【第 1 帧】: A组抬腿
        Set_Leg_Position(LEG_LEFT_FRONT,   6.0, 21.0, -1.5);   // c1
        Set_Leg_Position(LEG_LEFT_REAR,    0.0, 22.0, -1.5);   // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, -4.5, 22.0, -1.5);  // c5
        // B组保持站立姿态
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -2.0, 16.4, -13.5); // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  2.0, 16.4, -13.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   0.0, 16.4, -13.5);  // c6
        Apply_All_Servo_Positions(200); HAL_Delay(200);

        // 【第 2 帧】: A组转向摆动, B组蹬地
        Set_Leg_Position(LEG_LEFT_FRONT,   -2.0, 22.0, -1.5);  // c1
        Set_Leg_Position(LEG_LEFT_REAR,    -7.0, 22.0, -1.5);  // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 1.0, 22.0, -1.5);   // c5
        Set_Leg_Position(LEG_LEFT_MIDDLE,  0.5, 16.4, -13.5);  // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  -1.0, 16.4, -13.5); // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   -2.0, 16.0, -13.5); // c6
        Apply_All_Servo_Positions(300); HAL_Delay(300);

        // 【第 3 帧】: A组落腿
        Set_Leg_Position(LEG_LEFT_FRONT,   0.0, 16.4, -13.5);  // c1
        Set_Leg_Position(LEG_LEFT_REAR,    -3.5, 16.4, -13.5); // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 0.0, 16.4, -13.5);  // c5
        // B组保持蹬地结束位置
        Set_Leg_Position(LEG_LEFT_MIDDLE,  0.5, 16.4, -13.5);  // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  -1.0, 16.4, -13.5); // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   -2.0, 16.0, -13.5); // c6
        Apply_All_Servo_Positions(200); HAL_Delay(200);

        // --- 周期 2: B组(2,4,6)摆动, A组(1,3,5)支撑 ---

        // 【第 4 帧】: B组抬腿
        Set_Leg_Position(LEG_LEFT_MIDDLE,  0.5, 20.4, -1.5);   // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  -1.0, 22.0, -1.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   -2.0, 21.0, -1.5);  // c6
        // A组保持站立姿态
        Set_Leg_Position(LEG_LEFT_FRONT,   0.0, 16.4, -13.5);  // c1
        Set_Leg_Position(LEG_LEFT_REAR,    -3.5, 16.4, -13.5); // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 0.0, 16.4, -13.5);  // c5
        Apply_All_Servo_Positions(200); HAL_Delay(200);

        // 【第 5 帧】: B组转向摆动, A组蹬地
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -7.0, 22.0, -1.5);  // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  11.0, 16.0, -1.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   2.0, 22.0, -1.5);   // c6
        Set_Leg_Position(LEG_LEFT_FRONT,   5.0, 14.0, -13.5);  // c1
        Set_Leg_Position(LEG_LEFT_REAR,    2.0, 16.0, -13.5);  // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 0.5, 16.4, -13.5);  // c5
        Apply_All_Servo_Positions(300); HAL_Delay(300);

        // 【第 6 帧】: B组落腿
        Set_Leg_Position(LEG_LEFT_MIDDLE,  -4.0, 16.4, -13.5); // c2
        Set_Leg_Position(LEG_RIGHT_FRONT,  5.0, 13.0, -13.5);  // c4
        Set_Leg_Position(LEG_RIGHT_REAR,   2.0, 16.4, -13.5);  // c6
        // A组保持蹬地结束位置
        Set_Leg_Position(LEG_LEFT_FRONT,   5.0, 14.0, -13.5);  // c1
        Set_Leg_Position(LEG_LEFT_REAR,    2.0, 16.0, -13.5);  // c3
        Set_Leg_Position(LEG_RIGHT_MIDDLE, 0.5, 16.4, -13.5);  // c5
        Apply_All_Servo_Positions(200); HAL_Delay(200);
    }
    Gait_Stand_Still();
}

// --- 关键帧数据结构体 (被多种步态共享) ---
typedef struct {
    float land_x,  land_y,  land_z;
    float lift_x,  lift_y,  lift_z;
    float swing_x, swing_y, swing_z;
    float push_end_x, push_end_y, push_end_z;
} Leg_Keyframes_t;

// ===================================================================
// ============ 步态 2: 波动步态 (Wave Gait) =========================
// ===================================================================
void Gait_Wave_Forward(uint8_t steps)
{
    const uint16_t T_LIFT  = 200;
    const uint16_t T_SWING = 300;
    const uint16_t T_DROP  = 200;
    const float BODY_Y_ON_GROUND = 16.4f;

    const Leg_Keyframes_t leg_paths[6] = {
        [LEG_LEFT_FRONT] = {
            .land_x = 0.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 6.0, .lift_y = 21.0, .lift_z = -1.5,
            .swing_x= -2.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 5.0, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_LEFT_MIDDLE] = {
            .land_x = -4.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 0.5, .lift_y = 20.4, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 0.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_LEFT_REAR] = {
            .land_x = -3.5, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 0.0, .lift_y = 22.0, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 2.0, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_RIGHT_FRONT] = {
            .land_x = 0.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 6.0, .lift_y = 21.0, .lift_z = -1.5,
            .swing_x= -2.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 5.0, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_RIGHT_MIDDLE] = {
            .land_x = -4.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = -4.5, .lift_y = 22.0, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 0.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_RIGHT_REAR] = {
            .land_x = -3.5, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 6.0, .lift_y = 21.0, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 2.0, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        }
    };

    const Leg_ID_t leg_lift_order[] = {
        LEG_RIGHT_REAR, LEG_RIGHT_MIDDLE, LEG_RIGHT_FRONT,
        LEG_LEFT_REAR, LEG_LEFT_MIDDLE, LEG_LEFT_FRONT
    };

    const float num_phases = 5.0f;
    float current_x[6], current_y[6], current_z[6];

    for (int i = 0; i < 6; i++) {
        Leg_ID_t leg = leg_lift_order[i];
        float phase_progress = (float)(5 - i) / num_phases;
        if (i == 0) phase_progress = 1.0f;
        if (i == 5) phase_progress = 0.0f;

        current_x[leg] = leg_paths[leg].land_x + (leg_paths[leg].push_end_x - leg_paths[leg].land_x) * phase_progress;
        current_y[leg] = leg_paths[leg].land_y;
        current_z[leg] = leg_paths[leg].land_z;
        Set_Leg_Position(leg, current_x[leg], current_y[leg], current_z[leg]);
    }
    Apply_All_Servo_Positions(500); HAL_Delay(500);

    for (uint8_t s = 0; s < steps; s++)
    {
        for (int i = 0; i < 6; i++)
        {
            Leg_ID_t swing_leg = leg_lift_order[i];

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].lift_x, leg_paths[swing_leg].lift_y, leg_paths[swing_leg].lift_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * T_LIFT / 700.0f, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_LIFT); HAL_Delay(T_LIFT);

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].swing_x, leg_paths[swing_leg].swing_y, leg_paths[swing_leg].swing_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * (T_LIFT + T_SWING) / 700.0f, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_SWING); HAL_Delay(T_SWING);

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].land_x, leg_paths[swing_leg].land_y, leg_paths[swing_leg].land_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_DROP); HAL_Delay(T_DROP);

            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) {
                    current_x[leg] = leg_paths[leg].land_x;
                } else {
                    float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                    current_x[leg] += dx_per_phase;
                }
            }
        }
    }
    Gait_Stand_Still();
}

void Gait_Wave_Backward(uint8_t steps)
{
    const uint16_t T_LIFT  = 200;
    const uint16_t T_SWING = 300;
    const uint16_t T_DROP  = 200;
    const float BODY_Y_ON_GROUND = 16.4f;

    const Leg_Keyframes_t leg_paths[6] = {
        [LEG_LEFT_FRONT]   = {.land_x = 5.0, .push_end_x = 0.0,  .lift_x = -2.0, .swing_x = 6.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 21.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_LEFT_MIDDLE]  = {.land_x = 0.5, .push_end_x = -4.0, .lift_x = -7.0, .swing_x = 0.5, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 20.4, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_LEFT_REAR]    = {.land_x = 2.0, .push_end_x = -3.5, .lift_x = -7.0, .swing_x = 0.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_FRONT]  = {.land_x = 5.0, .push_end_x = 0.0,  .lift_x = -2.0, .swing_x = 6.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 21.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_MIDDLE] = {.land_x = 0.5, .push_end_x = -4.0, .lift_x = -7.0, .swing_x = -4.5,.land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_REAR]   = {.land_x = 2.0, .push_end_x = -3.5, .lift_x = -7.0, .swing_x = 6.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 21.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5}
    };

    const Leg_ID_t leg_lift_order[] = {
        LEG_LEFT_FRONT, LEG_LEFT_MIDDLE, LEG_LEFT_REAR,
        LEG_RIGHT_FRONT, LEG_RIGHT_MIDDLE, LEG_RIGHT_REAR
    };

    const float num_phases = 5.0f;
    float current_x[6], current_y[6], current_z[6];

    for (int i = 0; i < 6; i++) {
        Leg_ID_t leg = leg_lift_order[i];
        float phase_progress = (float)(5 - i) / num_phases;
        if (i == 0) phase_progress = 1.0f;
        if (i == 5) phase_progress = 0.0f;

        current_x[leg] = leg_paths[leg].land_x + (leg_paths[leg].push_end_x - leg_paths[leg].land_x) * phase_progress;
        current_y[leg] = leg_paths[leg].land_y;
        current_z[leg] = leg_paths[leg].land_z;
        Set_Leg_Position(leg, current_x[leg], current_y[leg], current_z[leg]);
    }
    Apply_All_Servo_Positions(500); HAL_Delay(500);

    for (uint8_t s = 0; s < steps; s++)
    {
        for (int i = 0; i < 6; i++)
        {
            Leg_ID_t swing_leg = leg_lift_order[i];

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].lift_x, leg_paths[swing_leg].lift_y, leg_paths[swing_leg].lift_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * T_LIFT / 700.0f, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_LIFT); HAL_Delay(T_LIFT);

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].swing_x, leg_paths[swing_leg].swing_y, leg_paths[swing_leg].swing_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * (T_LIFT + T_SWING) / 700.0f, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_SWING); HAL_Delay(T_SWING);

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].land_x, leg_paths[swing_leg].land_y, leg_paths[swing_leg].land_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_DROP); HAL_Delay(T_DROP);

            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) {
                    current_x[leg] = leg_paths[leg].land_x;
                } else {
                    float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                    current_x[leg] += dx_per_phase;
                }
            }
        }
    }
    Gait_Stand_Still();
}

static void _Gait_Wave_Turn_Engine(uint8_t steps, bool is_left_turn)
{
    const uint16_t T_LIFT  = 200;
    const uint16_t T_SWING = 300;
    const uint16_t T_DROP  = 200;
    const float BODY_Y_ON_GROUND = 16.4f;

    const Leg_Keyframes_t leg_paths_fwd[6] = {
        [LEG_LEFT_FRONT]   = {.land_x = 0.0, .push_end_x = 5.0,  .lift_x = 6.0, .swing_x = -2.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 21.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_LEFT_MIDDLE]  = {.land_x = -4.0,.push_end_x = 0.5,  .lift_x = 0.5, .swing_x = -7.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 20.4, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_LEFT_REAR]    = {.land_x = -3.5,.push_end_x = 2.0,  .lift_x = 0.0, .swing_x = -7.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_FRONT]  = {.land_x = 0.0, .push_end_x = 5.0,  .lift_x = 6.0, .swing_x = -2.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 21.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_MIDDLE] = {.land_x = -4.0,.push_end_x = 0.5,  .lift_x = -4.5,.swing_x = -7.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_REAR]   = {.land_x = -3.5,.push_end_x = 2.0,  .lift_x = 6.0, .swing_x = -7.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 21.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5}
    };
    const Leg_Keyframes_t leg_paths_bwd[6] = {
        [LEG_LEFT_FRONT]   = {.land_x = 5.0, .push_end_x = 0.0,  .lift_x = -2.0, .swing_x = 6.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 21.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_LEFT_MIDDLE]  = {.land_x = 0.5, .push_end_x = -4.0, .lift_x = -7.0, .swing_x = 0.5, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 20.4, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_LEFT_REAR]    = {.land_x = 2.0, .push_end_x = -3.5, .lift_x = -7.0, .swing_x = 0.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_FRONT]  = {.land_x = 5.0, .push_end_x = 0.0,  .lift_x = -2.0, .swing_x = 6.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 21.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_MIDDLE] = {.land_x = 0.5, .push_end_x = -4.0, .lift_x = -7.0, .swing_x = -4.5,.land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_REAR]   = {.land_x = 2.0, .push_end_x = -3.5, .lift_x = -7.0, .swing_x = 6.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 21.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5}
    };

    const Leg_ID_t leg_lift_order[] = {
        LEG_RIGHT_REAR, LEG_RIGHT_MIDDLE, LEG_RIGHT_FRONT,
        LEG_LEFT_REAR, LEG_LEFT_MIDDLE, LEG_LEFT_FRONT
    };

    const float num_phases = 5.0f;
    float current_x[6], current_y[6], current_z[6];

    for (int i = 0; i < 6; i++) {
        Leg_ID_t leg = leg_lift_order[i];
        const Leg_Keyframes_t* paths;

        bool is_left_leg = (leg <= LEG_LEFT_REAR);
        if ((is_left_turn && is_left_leg) || (!is_left_turn && !is_left_leg)) {
            paths = leg_paths_bwd;
        } else {
            paths = leg_paths_fwd;
        }

        float phase_progress = (float)(5 - i) / num_phases;
        if (i == 0) phase_progress = 1.0f;
        if (i == 5) phase_progress = 0.0f;

        current_x[leg] = paths[leg].land_x + (paths[leg].push_end_x - paths[leg].land_x) * phase_progress;
        current_y[leg] = paths[leg].land_y;
        current_z[leg] = paths[leg].land_z;
        Set_Leg_Position(leg, current_x[leg], current_y[leg], current_z[leg]);
    }
    Apply_All_Servo_Positions(500); HAL_Delay(500);

    for (uint8_t s = 0; s < steps; s++)
    {
        for (int i = 0; i < 6; i++)
        {
            Leg_ID_t swing_leg = leg_lift_order[i];
            const Leg_Keyframes_t* swing_paths;

            bool is_swing_leg_left = (swing_leg <= LEG_LEFT_REAR);
            if ((is_left_turn && is_swing_leg_left) || (!is_left_turn && !is_swing_leg_left)) {
                swing_paths = leg_paths_bwd;
            } else {
                swing_paths = leg_paths_fwd;
            }

            Set_Leg_Position(swing_leg, swing_paths[swing_leg].lift_x, swing_paths[swing_leg].lift_y, swing_paths[swing_leg].lift_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                const Leg_Keyframes_t* stance_paths;
                bool is_stance_leg_left = (leg <= LEG_LEFT_REAR);
                if ((is_left_turn && is_stance_leg_left) || (!is_left_turn && !is_stance_leg_left)) {
                    stance_paths = leg_paths_bwd;
                } else {
                    stance_paths = leg_paths_fwd;
                }
                float dx_per_phase = (stance_paths[leg].push_end_x - stance_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * T_LIFT / 700.0f, stance_paths[leg].land_y, stance_paths[leg].land_z);
            }
            Apply_All_Servo_Positions(T_LIFT); HAL_Delay(T_LIFT);

            Set_Leg_Position(swing_leg, swing_paths[swing_leg].swing_x, swing_paths[swing_leg].swing_y, swing_paths[swing_leg].swing_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                const Leg_Keyframes_t* stance_paths;
                bool is_stance_leg_left = (leg <= LEG_LEFT_REAR);
                if ((is_left_turn && is_stance_leg_left) || (!is_left_turn && !is_stance_leg_left)) {
                    stance_paths = leg_paths_bwd;
                } else {
                    stance_paths = leg_paths_fwd;
                }
                float dx_per_phase = (stance_paths[leg].push_end_x - stance_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * (T_LIFT + T_SWING) / 700.0f, stance_paths[leg].land_y, stance_paths[leg].land_z);
            }
            Apply_All_Servo_Positions(T_SWING); HAL_Delay(T_SWING);

            Set_Leg_Position(swing_leg, swing_paths[swing_leg].land_x, swing_paths[swing_leg].land_y, swing_paths[swing_leg].land_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                const Leg_Keyframes_t* stance_paths;
                bool is_stance_leg_left = (leg <= LEG_LEFT_REAR);
                if ((is_left_turn && is_stance_leg_left) || (!is_left_turn && !is_stance_leg_left)) {
                    stance_paths = leg_paths_bwd;
                } else {
                    stance_paths = leg_paths_fwd;
                }
                float dx_per_phase = (stance_paths[leg].push_end_x - stance_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase, stance_paths[leg].land_y, stance_paths[leg].land_z);
            }
            Apply_All_Servo_Positions(T_DROP); HAL_Delay(T_DROP);

            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                const Leg_Keyframes_t* paths;
                bool is_leg_left = (leg <= LEG_LEFT_REAR);
                if ((is_left_turn && is_leg_left) || (!is_left_turn && !is_leg_left)) {
                    paths = leg_paths_bwd;
                } else {
                    paths = leg_paths_fwd;
                }

                if (leg == swing_leg) {
                    current_x[leg] = paths[leg].land_x;
                } else {
                    float dx_per_phase = (paths[leg].push_end_x - paths[leg].land_x) / num_phases;
                    current_x[leg] += dx_per_phase;
                }
            }
        }
    }
    Gait_Stand_Still();
}

void Gait_Wave_TurnLeft(uint8_t steps)
{
    _Gait_Wave_Turn_Engine(steps, true);
}

void Gait_Wave_TurnRight(uint8_t steps)
{
    _Gait_Wave_Turn_Engine(steps, false);
}

// ===================================================================
// =================== 步态 3: 涟漪步态 (Ripple Gait) ================
// ===================================================================
void Gait_Ripple_Forward(uint8_t steps)
{
    const uint16_t T_LIFT  = 200;
    const uint16_t T_SWING = 300;
    const uint16_t T_DROP  = 200;
    const float BODY_Y_ON_GROUND = 16.4f;

    const Leg_Keyframes_t leg_paths[6] = {
        [LEG_LEFT_FRONT] = {
            .land_x = 0.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 6.0, .lift_y = 21.0, .lift_z = -1.5,
            .swing_x= -2.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 5.0, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_LEFT_MIDDLE] = {
            .land_x = -4.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 0.5, .lift_y = 20.4, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 0.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_LEFT_REAR] = {
            .land_x = -3.5, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 0.0, .lift_y = 22.0, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 2.0, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_RIGHT_FRONT] = {
            .land_x = 0.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 6.0, .lift_y = 21.0, .lift_z = -1.5,
            .swing_x= -2.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 5.0, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_RIGHT_MIDDLE] = {
            .land_x = -4.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = -4.5, .lift_y = 22.0, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 0.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        },
        [LEG_RIGHT_REAR] = {
            .land_x = -3.5, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5,
            .lift_x = 6.0, .lift_y = 21.0, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y= 22.0, .swing_z= -1.5,
            .push_end_x = 2.0, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5
        }
    };

    const Leg_ID_t leg_lift_order[] = {
        LEG_RIGHT_REAR, LEG_LEFT_REAR,
        LEG_RIGHT_MIDDLE, LEG_LEFT_MIDDLE,
        LEG_RIGHT_FRONT, LEG_LEFT_FRONT
    };

    const float num_phases = 5.0f;
    float current_x[6], current_y[6], current_z[6];

    for (int i = 0; i < 6; i++) {
        Leg_ID_t leg = leg_lift_order[i];
        float phase_progress = (float)(5 - i) / num_phases;
        if (i == 0) phase_progress = 1.0f;
        if (i == 5) phase_progress = 0.0f;

        current_x[leg] = leg_paths[leg].land_x + (leg_paths[leg].push_end_x - leg_paths[leg].land_x) * phase_progress;
        current_y[leg] = leg_paths[leg].land_y;
        current_z[leg] = leg_paths[leg].land_z;
        Set_Leg_Position(leg, current_x[leg], current_y[leg], current_z[leg]);
    }
    Apply_All_Servo_Positions(500); HAL_Delay(500);

    for (uint8_t s = 0; s < steps; s++)
    {
        for (int i = 0; i < 6; i++)
        {
            Leg_ID_t swing_leg = leg_lift_order[i];

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].lift_x, leg_paths[swing_leg].lift_y, leg_paths[swing_leg].lift_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * T_LIFT / 700.0f, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_LIFT); HAL_Delay(T_LIFT);

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].swing_x, leg_paths[swing_leg].swing_y, leg_paths[swing_leg].swing_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * (T_LIFT + T_SWING) / 700.0f, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_SWING); HAL_Delay(T_SWING);

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].land_x, leg_paths[swing_leg].land_y, leg_paths[swing_leg].land_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_DROP); HAL_Delay(T_DROP);

            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) {
                    current_x[leg] = leg_paths[leg].land_x;
                } else {
                    float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                    current_x[leg] += dx_per_phase;
                }
            }
        }
    }
    Gait_Stand_Still();
}

void Gait_Ripple_Backward(uint8_t steps)
{
    const uint16_t T_LIFT  = 200;
    const uint16_t T_SWING = 300;
    const uint16_t T_DROP  = 200;
    const float BODY_Y_ON_GROUND = 16.4f;

    const Leg_Keyframes_t leg_paths[6] = {
        [LEG_LEFT_FRONT]   = {.land_x = 5.0, .push_end_x = 0.0,  .lift_x = -2.0, .swing_x = 6.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 21.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_LEFT_MIDDLE]  = {.land_x = 0.5, .push_end_x = -4.0, .lift_x = -7.0, .swing_x = 0.5, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 20.4, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_LEFT_REAR]    = {.land_x = 2.0, .push_end_x = -3.5, .lift_x = -7.0, .swing_x = 0.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_FRONT]  = {.land_x = 5.0, .push_end_x = 0.0,  .lift_x = -2.0, .swing_x = 6.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 21.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_MIDDLE] = {.land_x = 0.5, .push_end_x = -4.0, .lift_x = -7.0, .swing_x = -4.5,.land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 22.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5},
        [LEG_RIGHT_REAR]   = {.land_x = 2.0, .push_end_x = -3.5, .lift_x = -7.0, .swing_x = 6.0, .land_y = BODY_Y_ON_GROUND, .land_z = -13.5, .lift_y = 22.0, .lift_z = -1.5, .swing_y = 21.0, .swing_z = -1.5, .push_end_y = BODY_Y_ON_GROUND, .push_end_z = -13.5}
    };

    const Leg_ID_t leg_lift_order[] = {
        LEG_LEFT_FRONT, LEG_RIGHT_FRONT,
        LEG_LEFT_MIDDLE, LEG_RIGHT_MIDDLE,
        LEG_LEFT_REAR, LEG_RIGHT_REAR
    };

    const float num_phases = 5.0f;
    float current_x[6], current_y[6], current_z[6];

    for (int i = 0; i < 6; i++) {
        Leg_ID_t leg = leg_lift_order[i];
        float phase_progress = (float)(5 - i) / num_phases;
        if (i == 0) phase_progress = 1.0f;
        if (i == 5) phase_progress = 0.0f;

        current_x[leg] = leg_paths[leg].land_x + (leg_paths[leg].push_end_x - leg_paths[leg].land_x) * phase_progress;
        current_y[leg] = leg_paths[leg].land_y;
        current_z[leg] = leg_paths[leg].land_z;
        Set_Leg_Position(leg, current_x[leg], current_y[leg], current_z[leg]);
    }
    Apply_All_Servo_Positions(500); HAL_Delay(500);

    for (uint8_t s = 0; s < steps; s++)
    {
        for (int i = 0; i < 6; i++)
        {
            Leg_ID_t swing_leg = leg_lift_order[i];

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].lift_x, leg_paths[swing_leg].lift_y, leg_paths[swing_leg].lift_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * T_LIFT / 700.0f, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_LIFT); HAL_Delay(T_LIFT);

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].swing_x, leg_paths[swing_leg].swing_y, leg_paths[swing_leg].swing_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase * (T_LIFT + T_SWING) / 700.0f, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_SWING); HAL_Delay(T_SWING);

            Set_Leg_Position(swing_leg, leg_paths[swing_leg].land_x, leg_paths[swing_leg].land_y, leg_paths[swing_leg].land_z);
            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) continue;
                float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                Set_Leg_Position(leg, current_x[leg] + dx_per_phase, BODY_Y_ON_GROUND, current_z[leg]);
            }
            Apply_All_Servo_Positions(T_DROP); HAL_Delay(T_DROP);

            for(int k=0; k<6; k++) {
                Leg_ID_t leg = (Leg_ID_t)k;
                if (leg == swing_leg) {
                    current_x[leg] = leg_paths[leg].land_x;
                } else {
                    float dx_per_phase = (leg_paths[leg].push_end_x - leg_paths[leg].land_x) / num_phases;
                    current_x[leg] += dx_per_phase;
                }
            }
        }
    }
    Gait_Stand_Still();
}

// ===================================================================
// =================== 步态 4: 对角/快步步态 (Trot Gait) ================
// ===================================================================
void Gait_Trot_Forward(uint8_t steps)
{
    const uint16_t T_LIFT = 200;
    const uint16_t T_SWING = 300;
    const uint16_t T_DROP = 200;
    const float TOTAL_SWING_TIME = T_LIFT + T_SWING + T_DROP;

    const Leg_Keyframes_t leg_paths[6] = {
        [LEG_LEFT_FRONT] = {
            .land_x = 0.0, .land_y = 16.4, .land_z = -13.5,
            .lift_x = 6.0, .lift_y = 21.0, .lift_z = -1.5,
            .swing_x= -2.0, .swing_y = 22.0, .swing_z = -1.5,
            .push_end_x = 5.0, .push_end_y = 16.4, .push_end_z = -13.5
        },
        [LEG_LEFT_MIDDLE] = {
            .land_x = -4.0, .land_y = 16.4, .land_z = -13.5,
            .lift_x = 0.5, .lift_y = 20.4, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y = 22.0, .swing_z = -1.5,
            .push_end_x = 0.5, .push_end_y = 16.4, .push_end_z = -13.5
        },
        [LEG_LEFT_REAR] = {
            .land_x = -3.5, .land_y = 16.4, .land_z = -13.5,
            .lift_x = 0.0, .lift_y = 22.0, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y = 22.0, .swing_z = -1.5,
            .push_end_x = 2.0, .push_end_y = 16.4, .push_end_z = -13.5
        },
        [LEG_RIGHT_FRONT] = {
            .land_x = 0.0, .land_y = 16.4, .land_z = -13.5,
            .lift_x = 6.0, .lift_y = 21.0, .lift_z = -1.5,
            .swing_x= -2.0, .swing_y = 22.0, .swing_z = -1.5,
            .push_end_x = 5.0, .push_end_y = 16.4, .push_end_z = -13.5
        },
        [LEG_RIGHT_MIDDLE] = {
            .land_x = -4.0, .land_y = 16.4, .land_z = -13.5,
            .lift_x = -4.5, .lift_y = 22.0, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y = 22.0, .swing_z = -1.5,
            .push_end_x = 0.5, .push_end_y = 16.4, .push_end_z = -13.5
        },
        [LEG_RIGHT_REAR] = {
            .land_x = -3.5, .land_y = 16.4, .land_z = -13.5,
            .lift_x = 6.0, .lift_y = 21.0, .lift_z = -1.5,
            .swing_x= -7.0, .swing_y = 22.0, .swing_z = -1.5,
            .push_end_x = 2.0, .push_end_y = 16.4, .push_end_z = -13.5
        }
    };

    const Leg_ID_t leg_pairs[3][2] = {
        {LEG_LEFT_FRONT, LEG_RIGHT_REAR},
        {LEG_RIGHT_FRONT, LEG_LEFT_REAR},
        {LEG_LEFT_MIDDLE, LEG_RIGHT_MIDDLE}
    };

    const Leg_ID_t all_legs[] = {LEG_LEFT_FRONT, LEG_LEFT_MIDDLE, LEG_LEFT_REAR, LEG_RIGHT_FRONT, LEG_RIGHT_MIDDLE, LEG_RIGHT_REAR};

    for (uint8_t s = 0; s < steps; s++)
    {
        for (int i = 0; i < 3; i++)
        {
            Leg_ID_t swing_leg1 = leg_pairs[i][0];
            Leg_ID_t swing_leg2 = leg_pairs[i][1];

            // --- 1. 抬起阶段 (LIFT) ---
            Set_Leg_Position(swing_leg1, leg_paths[swing_leg1].lift_x, leg_paths[swing_leg1].lift_y, leg_paths[swing_leg1].lift_z);
            Set_Leg_Position(swing_leg2, leg_paths[swing_leg2].lift_x, leg_paths[swing_leg2].lift_y, leg_paths[swing_leg2].lift_z);
            for(int k=0; k<6; k++){
                Leg_ID_t stance_leg = all_legs[k];
                if(stance_leg == swing_leg1 || stance_leg == swing_leg2) continue;
                float progress = (float)T_LIFT / TOTAL_SWING_TIME;
                float target_x = leg_paths[stance_leg].land_x + (leg_paths[stance_leg].push_end_x - leg_paths[stance_leg].land_x) * progress;
                Set_Leg_Position(stance_leg, target_x, leg_paths[stance_leg].land_y, leg_paths[stance_leg].land_z);
            }
            Apply_All_Servo_Positions(T_LIFT); HAL_Delay(T_LIFT);

            // --- 2. 前摆阶段 (SWING) ---
            Set_Leg_Position(swing_leg1, leg_paths[swing_leg1].swing_x, leg_paths[swing_leg1].swing_y, leg_paths[swing_leg1].swing_z);
            Set_Leg_Position(swing_leg2, leg_paths[swing_leg2].swing_x, leg_paths[swing_leg2].swing_y, leg_paths[swing_leg2].swing_z);
            for(int k=0; k<6; k++){
                Leg_ID_t stance_leg = all_legs[k];
                if(stance_leg == swing_leg1 || stance_leg == swing_leg2) continue;
                float progress = (float)(T_LIFT + T_SWING) / TOTAL_SWING_TIME;
                float target_x = leg_paths[stance_leg].land_x + (leg_paths[stance_leg].push_end_x - leg_paths[stance_leg].land_x) * progress;
                Set_Leg_Position(stance_leg, target_x, leg_paths[stance_leg].land_y, leg_paths[stance_leg].land_z);
            }
            Apply_All_Servo_Positions(T_SWING); HAL_Delay(T_SWING);

            // --- 3. 落地阶段 (DROP) ---
            Set_Leg_Position(swing_leg1, leg_paths[swing_leg1].land_x, leg_paths[swing_leg1].land_y, leg_paths[swing_leg1].land_z);
            Set_Leg_Position(swing_leg2, leg_paths[swing_leg2].land_x, leg_paths[swing_leg2].land_y, leg_paths[swing_leg2].land_z);
            for(int k=0; k<6; k++){
                Leg_ID_t stance_leg = all_legs[k];
                if(stance_leg == swing_leg1 || stance_leg == swing_leg2) continue;
                Set_Leg_Position(stance_leg, leg_paths[stance_leg].push_end_x, leg_paths[stance_leg].push_end_y, leg_paths[stance_leg].push_end_z);
            }
            Apply_All_Servo_Positions(T_DROP); HAL_Delay(T_DROP);
        }
    }
    Gait_Stand_Still();
}

// --- 单腿动作序列 (调试用) ---
void Leg_Action_Forward(Leg_ID_t leg_id)
{
    switch (leg_id)
    {
    case LEG_LEFT_FRONT:   Set_Leg_Position(leg_id, 6.0, 21.0, -1.5); break;
    case LEG_LEFT_MIDDLE:  Set_Leg_Position(leg_id, 0.5, 20.4, -1.5); break;
    case LEG_LEFT_REAR:    Set_Leg_Position(leg_id, 0.0, 22.0, -1.5); break;
    case LEG_RIGHT_FRONT:  Set_Leg_Position(leg_id, 6.0, 21.0, -1.5); break;
    case LEG_RIGHT_MIDDLE: Set_Leg_Position(leg_id, -4.5, 22.0, -1.5); break;
    case LEG_RIGHT_REAR:   Set_Leg_Position(leg_id, 6.0, 21.0, -1.5); break;
    }
    Apply_All_Servo_Positions(200); HAL_Delay(200);

    switch (leg_id)
    {
    case LEG_LEFT_FRONT:   Set_Leg_Position(leg_id, -2.0, 22.0, -1.5); break;
    case LEG_LEFT_MIDDLE:  Set_Leg_Position(leg_id, -7.0, 22.0, -1.5); break;
    case LEG_LEFT_REAR:    Set_Leg_Position(leg_id, -7.0, 22.0, -1.5); break;
    case LEG_RIGHT_FRONT:  Set_Leg_Position(leg_id, -2.0, 22.0, -1.5); break;
    case LEG_RIGHT_MIDDLE: Set_Leg_Position(leg_id, -7.0, 22.0, -1.5); break;
    case LEG_RIGHT_REAR:   Set_Leg_Position(leg_id, -7.0, 22.0, -1.5); break;
    }
    Apply_All_Servo_Positions(300); HAL_Delay(300);

    switch (leg_id)
    {
    case LEG_LEFT_FRONT:   Set_Leg_Position(leg_id, 0.0, 16.4, -13.5); break;
    case LEG_LEFT_MIDDLE:  Set_Leg_Position(leg_id, -4.0, 16.4, -13.5); break;
    case LEG_LEFT_REAR:    Set_Leg_Position(leg_id, -3.5, 16.4, -13.5); break;
    case LEG_RIGHT_FRONT:  Set_Leg_Position(leg_id, 0.0, 16.4, -13.5); break;
    case LEG_RIGHT_MIDDLE: Set_Leg_Position(leg_id, -4.0, 16.4, -13.5); break;
    case LEG_RIGHT_REAR:   Set_Leg_Position(leg_id, -3.5, 16.4, -13.5); break;
    }
    Apply_All_Servo_Positions(200); HAL_Delay(200);

    _Set_Prepare_Pose(leg_id);
    Apply_All_Servo_Positions(300); HAL_Delay(300);
}

void Leg_Action_Backward(Leg_ID_t leg_id)
{
    // 暂时留空
}

