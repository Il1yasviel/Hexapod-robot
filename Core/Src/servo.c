#include "servo.h"

/* Private variables ---------------------------------------------------------*/
// 使用静态变量存储硬件配置，避免每次调用函数都传递硬件参数
static UART_HandleTypeDef *servo_huart;
static GPIO_TypeDef* servo_de_port;
static uint16_t servo_de_pin;

/* Private function prototypes -----------------------------------------------*/
// 内部发送函数，处理RS485的DE引脚控制
static void Servo_Transmit(uint8_t *data, uint16_t size);

/* Public function implementations -------------------------------------------*/

void Servo_Init(UART_HandleTypeDef *huart, GPIO_TypeDef* de_port, uint16_t de_pin)
{
    servo_huart = huart;
    servo_de_port = de_port;
    servo_de_pin = de_pin;
}

void Servo_Move(uint8_t id, uint8_t angle, uint16_t time_ms)
{
    uint8_t command_packet[10];

    command_packet[0] = 0xFA; // 帧头1
    command_packet[1] = 0xAF; // 帧头2
    command_packet[2] = id;   // 舵机ID
    command_packet[3] = 0x01; // 命令: 转动
    command_packet[4] = angle; // 参数1: 目标角度
    command_packet[5] = (uint8_t)(time_ms / 20); // 参数2: 运动时间
    command_packet[6] = 0x00; // 锁定时间高位
    command_packet[7] = 0x00; // 锁定时间低位

    uint8_t checksum = 0;
    for (int i = 2; i <= 7; i++) {
        checksum += command_packet[i];
    }
    command_packet[8] = checksum; // 校验和
    command_packet[9] = 0xED;     // 帧尾

    Servo_Transmit(command_packet, sizeof(command_packet));
}

void Servo_Set_ID(uint8_t new_id)
{
    uint8_t command_packet[10];

    command_packet[0] = 0xFA; // 帧头1
    command_packet[1] = 0xAF; // 帧头2
    command_packet[2] = 0x00; // 使用广播ID
    command_packet[3] = 0xCD; // 命令: 修改ID
    command_packet[4] = 0x00; // 参数
    command_packet[5] = new_id; // 参数: 新ID
    command_packet[6] = 0x00; // 参数
    command_packet[7] = 0x00; // 参数

    uint8_t checksum = 0;
    for (int i = 2; i <= 7; i++) {
        checksum += command_packet[i];
    }
    command_packet[8] = checksum; // 校验和
    command_packet[9] = 0xED;     // 帧尾

    Servo_Transmit(command_packet, sizeof(command_packet));
}

/* Private function implementations ------------------------------------------*/

/**
  * @brief  通过UART发送数据包，并自动管理RS485的DE引脚.
  * @param  data: 指向要发送数据的指针.
  * @param  size: 要发送的数据字节数.
  * @retval None
  */
static void Servo_Transmit(uint8_t *data, uint16_t size)
{
    // 如果配置了DE引脚 (即非TTL模式)，则设置为发送模式
    if (servo_de_port != NULL) {
        HAL_GPIO_WritePin(servo_de_port, servo_de_pin, GPIO_PIN_SET);
    }

    // 发送数据
    HAL_UART_Transmit(servo_huart, data, size, HAL_MAX_DELAY);

    // 如果配置了DE引脚，则设置回接收模式
    // 注意: HAL_UART_Transmit是阻塞函数，完成后再切换模式是安全的
    if (servo_de_port != NULL) {
        HAL_GPIO_WritePin(servo_de_port, servo_de_pin, GPIO_PIN_RESET);
    }
}

