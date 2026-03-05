/*
 * weapon.h
 *
 *  Created on: Mar 5, 2026
 *      Author: ch258
 */

/* FILE: weapon.h */
/* FILE: weapon.h */
#ifndef __WEAPON_H
#define __WEAPON_H

#include <stdint.h>

// 武器动作枚举
typedef enum {
    WEAPON_ACTION_CHARGE,
    WEAPON_ACTION_FIRE,
    WEAPON_ACTION_AUTO    // <--- 新增：一键发射
} Weapon_Action_t;

// 函数声明
void Weapon_Init(void);
void Weapon_Control(Weapon_Action_t action);
void Weapon_Process(void);

#endif /* __WEAPON_H */


