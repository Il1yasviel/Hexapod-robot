#ifndef __SERVO_H
#define __SERVO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h" // 包含此文件以获取HAL库的数据类型，如 UART_HandleTypeDef

/* Public function prototypes -----------------------------------------------*/

/**
  * @brief  初始化舵机控制库.
  * @param  huart: 用于与舵机通信的UART句柄指针.
  * @param  de_port: RS485收发器的数据使能(DE)引脚所在的GPIO端口.
  *                  如果直接使用TTL连接，请传入 NULL.
  * @param  de_pin: DE引脚的引脚号.
  * @retval None
  */
void Servo_Init(UART_HandleTypeDef *huart, GPIO_TypeDef* de_port, uint16_t de_pin);

/**
  * @brief  控制舵机转动到指定角度.
  * @param  id: 舵机ID (0为广播).
  * @param  angle: 目标角度 (0-240).
  * @param  time_ms: 运动所需时间 (毫秒).
  * @retval None
  */
void Servo_Move(uint8_t id, uint8_t angle, uint16_t time_ms);

/**
  * @brief  通过广播模式设置舵机的新ID.
  * @note   重要: 调用此函数时，总线上应只连接一个舵机!
  * @param  new_id: 要设置的新ID (1-240).
  * @retval None
  */
void Servo_Set_ID(uint8_t new_id);


#ifdef __cplusplus
}
#endif

#endif /* __SERVO_H */

