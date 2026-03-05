/* FILE: weapon.c */
#include "weapon.h"
#include "main.h" // 包含 main.h 以获取 GPIOB, GPIO_Pin, SWITCH_Pin 以及 HAL_GetTick()
#include <stdio.h>

// --- 定义武器系统的内部状态 ---
typedef enum {
    WEAPON_STATE_IDLE,           // 空闲状态
    WEAPON_STATE_CHARGING,       // 正在普通充电 (2s)
    WEAPON_STATE_AUTO_CHARGING,  // 一键发射：正在充电阶段 (2s)
    WEAPON_STATE_AUTO_WAITING,   // 一键发射：安全缓冲阶段 (0.5s，全关)
    WEAPON_STATE_FIRING          // 正在发射阶段 (1s)
} Weapon_State_t;

// 记录当前状态和动作开始的时间戳
static Weapon_State_t current_weapon_state = WEAPON_STATE_IDLE;
static uint32_t action_start_tick = 0;

// ==========================================================
// 底层引脚控制函数实现
// ==========================================================
void GPIO(uint8_t state)
{
    if (state) {
        HAL_GPIO_WritePin(GPIOB, GPIO_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_Pin, GPIO_PIN_RESET);
    }
}

void SWITCH(uint8_t state)
{
    if (state) {
        HAL_GPIO_WritePin(GPIOB, SWITCH_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIOB, SWITCH_Pin, GPIO_PIN_RESET);
    }
}

// ==========================================================
// 业务逻辑函数
// ==========================================================

/**
 * @brief 武器系统初始化
 */
void Weapon_Init(void)
{
    GPIO(0);
    SWITCH(0);
    current_weapon_state = WEAPON_STATE_IDLE;
}

/**
 * @brief 控制武器系统的充电与发射 (非阻塞，仅触发动作)
 * @param action WEAPON_ACTION_CHARGE, WEAPON_ACTION_FIRE, 或 WEAPON_ACTION_AUTO
 */
void Weapon_Control(Weapon_Action_t action)
{
    // 如果当前不是空闲状态（正在运行中），则拒绝新的指令，防止状态混乱
    if (current_weapon_state != WEAPON_STATE_IDLE)
    {
        printf("警告: 武器正在运行中，指令被忽略！\r\n");
        return;
    }

    // 【绝对安全互锁】：任何动作开始前，强制将两者都拉低
    GPIO(0);
    SWITCH(0);

    if (action == WEAPON_ACTION_CHARGE)
    {
        printf("执行: 机构单次充电开始 (持续2秒)...\r\n");
        GPIO(0);
        SWITCH(1);
        current_weapon_state = WEAPON_STATE_CHARGING;
        action_start_tick = HAL_GetTick();
    }
    else if (action == WEAPON_ACTION_FIRE)
    {
        printf("执行: 机构单次发射 (持续1秒)...\r\n");
        SWITCH(0);
        GPIO(1);
        current_weapon_state = WEAPON_STATE_FIRING;
        action_start_tick = HAL_GetTick();
    }
    else if (action == WEAPON_ACTION_AUTO)
    {
        // 按照要求：先充电 2 秒
        printf("执行: 一键发射 -> 步骤1: 充电开始 (持续2秒)...\r\n");
        GPIO(0);
        SWITCH(1);
        current_weapon_state = WEAPON_STATE_AUTO_CHARGING;
        action_start_tick = HAL_GetTick();
    }
}

/**
 * @brief 武器系统时间监听函数 (需要在主循环 while(1) 中不断调用)
 */
void Weapon_Process(void)
{
    uint32_t current_tick = HAL_GetTick();

    switch (current_weapon_state)
    {
        case WEAPON_STATE_IDLE:
            break;

        case WEAPON_STATE_CHARGING:
            // 单独充电命令：满 2000 毫秒后停止并回到空闲
            if (current_tick - action_start_tick >= 2000)
            {
                SWITCH(0);
                GPIO(0);
                current_weapon_state = WEAPON_STATE_IDLE;
                printf("执行: 单次充电完成.\r\n");
            }
            break;

        case WEAPON_STATE_AUTO_CHARGING:
            // 一键发射的步骤1：充电满 2000 毫秒后，进入安全缓冲阶段
            if (current_tick - action_start_tick >= 2000)
            {
                // 安全死区：强制关闭所有引脚
                SWITCH(0);
                GPIO(0);

                printf("执行: 一键发射 -> 步骤2: 安全缓冲等待 (持续0.5秒)...\r\n");

                // 切换到等待状态，并重新开始计时
                current_weapon_state = WEAPON_STATE_AUTO_WAITING;
                action_start_tick = HAL_GetTick();
            }
            break;

        case WEAPON_STATE_AUTO_WAITING:
            // 一键发射的步骤2：安全缓冲满 500 毫秒后，立刻转为发射状态
            if (current_tick - action_start_tick >= 500)
            {
                // 再次确保 SWITCH 关死，然后开启 GPIO
                SWITCH(0);
                GPIO(1);

                printf("执行: 一键发射 -> 步骤3: 开始发射 (持续1秒)...\r\n");

                // 切换到发射状态，并重新开始计时
                current_weapon_state = WEAPON_STATE_FIRING;
                action_start_tick = HAL_GetTick();
            }
            break;

        case WEAPON_STATE_FIRING:
            // 发射阶段（单次发射和一键发射共用）：满 1000 毫秒后停止并回到空闲
            if (current_tick - action_start_tick >= 1000)
            {
                GPIO(0);
                SWITCH(0);
                current_weapon_state = WEAPON_STATE_IDLE;
                printf("执行: 发射流程彻底完成.\r\n");
            }
            break;
    }
}

