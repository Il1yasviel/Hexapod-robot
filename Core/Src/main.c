/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "leg_inverse.h"
#include "servo.h"
#include "gait.h"
#include "weapon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h> // For isdigit()
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SERVO_DE_PORT GPIOA
#define SERVO_DE_PIN  GPIO_PIN_8
#define RX_CMD_BUFFER_SIZE 64
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define CLAMP(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern float leg_j1_angle, leg_j2_angle, leg_j3_angle;
static uint16_t servo1_angle, servo2_angle, servo3_angle, servo4_angle, servo5_angle, servo6_angle, servo7_angle, servo8_angle, servo9_angle, servo10_angle, servo11_angle, servo12_angle, servo13_angle, servo14_angle, servo15_angle, servo16_angle, servo17_angle, servo18_angle;

uint8_t rx_data;
uint8_t rx_cmd_buffer[RX_CMD_BUFFER_SIZE];
volatile uint16_t rx_cmd_index = 0;
volatile uint8_t g_command_ready = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Set_Single_Servo(uint8_t id, uint16_t angle);
void Set_Leg_Position(Leg_ID_t leg_id, float target_x, float target_y, float target_z);
void Set_All_Legs_Position(float target_x, float target_y, float target_z);
void Apply_All_Servo_Positions(uint16_t move_time);
void Process_Command(const char* cmd);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        if (g_command_ready == 0)
        {
            if (rx_data == '\r' || rx_data == '\n')
            {
                if (rx_cmd_index > 0)
                {
                    rx_cmd_buffer[rx_cmd_index] = '\0';
                    g_command_ready = 1;
                }
                rx_cmd_index = 0;
            }
            else
            {
                if (rx_cmd_index < RX_CMD_BUFFER_SIZE - 1)
                {
                    rx_cmd_buffer[rx_cmd_index++] = rx_data;
                }
            }
        }
        HAL_UART_Receive_IT(&huart3, &rx_data, 1);
    }
}

void Set_Single_Servo(uint8_t id, uint16_t angle)
{
    if (id == 1 || id == 2 || id == 4 || id == 5 || id == 8 || id == 10 || id == 11 || id == 13 || id == 14 || id == 16 || id == 17)
    {
        angle = 240 - angle;
    }
    switch (id)
    {
    case 1:  servo1_angle = angle; break;
    case 2:  servo2_angle = angle; break;
    case 3:  servo3_angle = angle; break;
    case 4:  servo4_angle = angle; break;
    case 5:  servo5_angle = angle; break;
    case 6:  servo6_angle = angle; break;
    case 7:  servo7_angle = angle; break;
    case 8:  servo8_angle = angle; break;
    case 9:  servo9_angle = angle; break;
    case 10: servo10_angle = angle; break;
    case 11: servo11_angle = angle; break;
    case 12: servo12_angle = angle; break;
    case 13: servo13_angle = angle; break;
    case 14: servo14_angle = angle; break;
    case 15: servo15_angle = angle; break;
    case 16: servo16_angle = angle; break;
    case 17: servo17_angle = angle; break;
    case 18: servo18_angle = angle; break;
    default: break;
    }
}

void Set_Leg_Position(Leg_ID_t leg_id, float target_x, float target_y, float target_z)
{
    uint8_t id1 = 0, id2 = 0, id3 = 0;
    bool is_inverted = false;

    switch (leg_id)
    {
    case LEG_LEFT_FRONT:   id1 = 1;  id2 = 2;  id3 = 3;  is_inverted = false; break;
    case LEG_LEFT_MIDDLE:  id1 = 4;  id2 = 5;  id3 = 6;  is_inverted = false; break;
    case LEG_LEFT_REAR:    id1 = 7;  id2 = 8;  id3 = 9;  is_inverted = false; break;
    case LEG_RIGHT_FRONT:  id1 = 10; id2 = 11; id3 = 12; is_inverted = true;  break;
    case LEG_RIGHT_MIDDLE: id1 = 13; id2 = 14; id3 = 15; is_inverted = true;  break;
    case LEG_RIGHT_REAR:   id1 = 16; id2 = 17; id3 = 18; is_inverted = true;  break;
    }

    if (leg_inverse_calculate(target_x, target_y, target_z))
    {
        if (is_inverted)
        {
            Set_Single_Servo(id1, (uint16_t)(120.0f - leg_j1_angle));
            Set_Single_Servo(id2, (uint16_t)(120.0f + leg_j2_angle));
            Set_Single_Servo(id3, (uint16_t)(120.0f + leg_j3_angle));
        }
        else
        {
            Set_Single_Servo(id1, (uint16_t)(120.0f + leg_j1_angle));
            Set_Single_Servo(id2, (uint16_t)(120.0f - leg_j2_angle));
            Set_Single_Servo(id3, (uint16_t)(120.0f - leg_j3_angle));
        }
    }
    else
    {
        printf("错误: 腿 %d 逆解失败, 目标点 (%.1f, %.1f, %.1f) 无法到达.\r\n", (int)leg_id + 1, target_x, target_y, target_z);
    }
}

void Apply_All_Servo_Positions(uint16_t move_time)
{
    Servo_Move(1,  (uint8_t)CLAMP(servo1_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(2,  (uint8_t)CLAMP(servo2_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(3,  (uint8_t)CLAMP(servo3_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(4,  (uint8_t)CLAMP(servo4_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(5,  (uint8_t)CLAMP(servo5_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(6,  (uint8_t)CLAMP(servo6_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(7,  (uint8_t)CLAMP(servo7_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(8,  (uint8_t)CLAMP(servo8_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(9,  (uint8_t)CLAMP(servo9_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(10, (uint8_t)CLAMP(servo10_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(11, (uint8_t)CLAMP(servo11_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(12, (uint8_t)CLAMP(servo12_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(13, (uint8_t)CLAMP(servo13_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(14, (uint8_t)CLAMP(servo14_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(15, (uint8_t)CLAMP(servo15_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(16, (uint8_t)CLAMP(servo16_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(17, (uint8_t)CLAMP(servo17_angle, 0, 240), move_time); HAL_Delay(5);
    Servo_Move(18, (uint8_t)CLAMP(servo18_angle, 0, 240), move_time); HAL_Delay(5);
}

void Process_Command(const char* cmd)
{
    char cmd_copy[RX_CMD_BUFFER_SIZE];
    strcpy(cmd_copy, cmd);

    char* main_cmd = strtok(cmd_copy, ":");
    if (main_cmd == NULL) {
        printf("错误: 空命令.\r\n");
        return;
    }

    // --- 步态命令解析 ---
    if (strcmp(main_cmd, "tripod") == 0 || strcmp(main_cmd, "wave") == 0 || strcmp(main_cmd, "ripple") == 0 || strcmp(main_cmd, "trot") == 0)
    {
        char* action = strtok(NULL, ":");
        if (action == NULL) {
            printf("错误: 命令 '%s' 缺少动作 (e.g., 'forward').\r\n", main_cmd);
            return;
        }

        char* steps_str = strtok(NULL, ":");
        uint8_t steps = (steps_str != NULL && atoi(steps_str) > 0) ? atoi(steps_str) : 1;

        printf("执行: %s 步态, 动作: %s, 步数: %d\r\n", main_cmd, action, steps);

        if (strcmp(main_cmd, "tripod") == 0) {
            if (strcmp(action, "forward") == 0)       Gait_Tripod_Forward(steps);
            else if (strcmp(action, "backward") == 0) Gait_Tripod_Backward(steps);
            else if (strcmp(action, "turn_left") == 0)  Gait_Tripod_TurnLeft(steps);
            else if (strcmp(action, "turn_right") == 0) Gait_Tripod_TurnRight(steps);
            else printf("错误: 'tripod' 步态不支持动作 '%s'.\r\n", action);
        }
        else if (strcmp(main_cmd, "wave") == 0) {
            if (strcmp(action, "forward") == 0)       Gait_Wave_Forward(steps);
            else if (strcmp(action, "backward") == 0)   Gait_Wave_Backward(steps);
            else if (strcmp(action, "turn_left") == 0)  Gait_Wave_TurnLeft(steps);
            else if (strcmp(action, "turn_right") == 0) Gait_Wave_TurnRight(steps);
            else printf("错误: 'wave' 步态不支持动作 '%s'.\r\n", action);
        }
        else if (strcmp(main_cmd, "ripple") == 0) {
            if (strcmp(action, "forward") == 0)       Gait_Ripple_Forward(steps);
            else if (strcmp(action, "backward") == 0) Gait_Ripple_Backward(steps);
            else printf("错误: 'ripple' 步态不支持动作 '%s'.\r\n", action);
        }
        else if (strcmp(main_cmd, "trot") == 0) {
            if (strcmp(action, "forward") == 0)       Gait_Trot_Forward(steps);
            else printf("错误: 'trot' 步态不支持动作 '%s'.\r\n", action);
        }
    }
    else if (strcmp(main_cmd, "stand") == 0)
    {
        printf("执行: 站立\r\n");
        Gait_Stand_Still();
    }

    // --- 新增：武器系统指令解析 ---
	else if (strcmp(main_cmd, "weapon") == 0)
	{
		char* action_cmd = strtok(NULL, ":");
		if (action_cmd == NULL)
		{
			printf("错误: 'weapon' 命令缺少动作 (例如: 'charge', 'fire', 'auto').\r\n");
			return;
		}

		if (strcmp(action_cmd, "charge") == 0)
		{
			Weapon_Control(WEAPON_ACTION_CHARGE);
		}
		else if (strcmp(action_cmd, "fire") == 0)
		{
			Weapon_Control(WEAPON_ACTION_FIRE);
		}
		else if (strcmp(action_cmd, "auto") == 0) // <--- 新增的解析分支
		{
			Weapon_Control(WEAPON_ACTION_AUTO);
		}
		else
		{
			printf("错误: 未知的武器动作 '%s'.\r\n", action_cmd);
		}
	}


    else if (main_cmd[0] == 'c')
    {
        char* action_cmd = strtok(NULL, ":");
        if (action_cmd == NULL)
        {
            printf("错误: 调试命令缺少动作部分 (例如: 'set_point', 'forward').\r\n");
            return;
        }

        if (strcmp(action_cmd, "set_point") == 0)
        {
            char* x_str = strtok(NULL, ":");
            char* y_str = strtok(NULL, ":");
            char* z_str = strtok(NULL, ":");
            char* time_str = strtok(NULL, ":");

            if (x_str == NULL || y_str == NULL || z_str == NULL || time_str == NULL)
            {
                printf("错误: set_point 命令缺少参数. 格式: c[腿号...]:set_point:x:y:z:time\r\n");
                return;
            }
            float x = atof(x_str);
            float y = atof(y_str);
            float z = atof(z_str);
            uint16_t time = atoi(time_str);

            printf("执行: 腿 [%s] 设置坐标点 (%.1f, %.1f, %.1f) 时间 %dms\r\n", main_cmd, x, y, z, time);

            for (int i = 1; main_cmd[i] != '\0'; i++)
            {
                if (isdigit((unsigned char)main_cmd[i]))
                {
                    int leg_num = main_cmd[i] - '0';
                    if (leg_num >= 1 && leg_num <= 6)
                    {
                        Leg_ID_t leg_id = (Leg_ID_t)(leg_num - 1);
                        Set_Leg_Position(leg_id, x, y, z);
                    }
                }
            }
            Apply_All_Servo_Positions(time);
        }
        else if (strcmp(action_cmd, "forward") == 0 || strcmp(action_cmd, "backward") == 0)
        {
            printf("执行: 腿 [%s] 顺序执行 '%s' 动作\r\n", main_cmd, action_cmd);
            for (int i = 1; main_cmd[i] != '\0'; i++)
            {
                if (isdigit((unsigned char)main_cmd[i]))
                {
                    int leg_num = main_cmd[i] - '0';
                    if (leg_num >= 1 && leg_num <= 6)
                    {
                        Leg_ID_t leg_id = (Leg_ID_t)(leg_num - 1);
                        if (strcmp(action_cmd, "forward") == 0)
                        {
                            Leg_Action_Forward(leg_id);
                        }
                        else
                        {
                            Leg_Action_Backward(leg_id);
                        }
                    }
                }
            }
        }
        else
        {
            printf("错误: 未知调试动作 '%s'.\r\n", action_cmd);
        }
    }
    else
    {
        printf("错误: 未知命令或步态 '%s'.\r\n", main_cmd);
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

	Servo_Init(&huart1, SERVO_DE_PORT, SERVO_DE_PIN);
	HAL_Delay(100);
	Gait_Init();
	Gait_Stand_Still();

    Weapon_Init();//初始化电磁炮

	HAL_Delay(1000);

	HAL_UART_Receive_IT(&huart3, &rx_data, 1);

	printf("\r\n六足机器人控制器已就绪.\r\n");
	printf("--- 命令格式: gait_name:action[:steps] ---\r\n");
	printf("  stand\r\n");
	printf("  tripod:forward[:steps]\r\n");
	printf("  tripod:backward[:steps]\r\n");
	printf("  tripod:turn_left[:steps]\r\n");
	printf("  tripod:turn_right[:steps]\r\n");
	printf("  wave:forward[:steps]\r\n");
	printf("  wave:backward[:steps]\r\n");
	printf("  wave:turn_left[:steps]\r\n");
	printf("  wave:turn_right[:steps]\r\n");
	printf("  ripple:forward[:steps]\r\n");
	printf("  ripple:backward[:steps]\r\n");
	printf("  trot:forward[:steps]\r\n");

    // --- 新增：打印武器命令提示 ---
    printf("--- 武器系统命令 ---\r\n");
    printf("  weapon:charge  (充电2秒)\r\n");
    printf("  weapon:fire    (发射1秒)\r\n");

	printf("--- 调试命令 ---\r\n");
	printf("  c[腿号...]:set_point:x:y:z:time (同步)\r\n");
	printf("  c[腿号...]:[forward|backward] (顺序)\r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	Weapon_Process(); // <--- 新增：非阻塞状态机处理，实时检查时间

    if (g_command_ready)
    {
        Process_Command((const char*)rx_cmd_buffer);

        memset(rx_cmd_buffer, 0, RX_CMD_BUFFER_SIZE);
        rx_cmd_index = 0;
        g_command_ready = 0;
    }
    HAL_Delay(10);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
