/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define User_LED_Pin GPIO_PIN_13
#define User_LED_GPIO_Port GPIOC
#define SW_1_Pin GPIO_PIN_14
#define SW_1_GPIO_Port GPIOC
#define SW_2_Pin GPIO_PIN_15
#define SW_2_GPIO_Port GPIOC
#define Reserve_Pin GPIO_PIN_0
#define Reserve_GPIO_Port GPIOA
#define VR_3_Pin GPIO_PIN_1
#define VR_3_GPIO_Port GPIOA
#define VR_2_Pin GPIO_PIN_4
#define VR_2_GPIO_Port GPIOA
#define VR_1_Pin GPIO_PIN_7
#define VR_1_GPIO_Port GPIOA
#define Audio_Input_Pin GPIO_PIN_0
#define Audio_Input_GPIO_Port GPIOB
#define UART_FET_SW_Pin GPIO_PIN_8
#define UART_FET_SW_GPIO_Port GPIOA
#define UART_Pull_Up_Pin GPIO_PIN_10
#define UART_Pull_Up_GPIO_Port GPIOA
#define Audio_Output_High_Pin GPIO_PIN_4
#define Audio_Output_High_GPIO_Port GPIOB
#define Audio_Output_Low_Pin GPIO_PIN_5
#define Audio_Output_Low_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
