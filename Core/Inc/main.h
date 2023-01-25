/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32l4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DOWN_Pin GPIO_PIN_0
#define DOWN_GPIO_Port GPIOC
#define DOWN_EXTI_IRQn EXTI0_IRQn
#define RIGHT_Pin GPIO_PIN_1
#define RIGHT_GPIO_Port GPIOC
#define RIGHT_EXTI_IRQn EXTI1_IRQn
#define LEFT_Pin GPIO_PIN_4
#define LEFT_GPIO_Port GPIOA
#define LEFT_EXTI_IRQn EXTI4_IRQn
#define UP_Pin GPIO_PIN_6
#define UP_GPIO_Port GPIOA
#define UP_EXTI_IRQn EXTI9_5_IRQn
#define SD_Pin GPIO_PIN_10
#define SD_GPIO_Port GPIOB
#define SEL2_Pin GPIO_PIN_7
#define SEL2_GPIO_Port GPIOC
#define SW2_Pin GPIO_PIN_8
#define SW2_GPIO_Port GPIOC
#define SW2_EXTI_IRQn EXTI9_5_IRQn
#define SW1_Pin GPIO_PIN_9
#define SW1_GPIO_Port GPIOC
#define SW1_EXTI_IRQn EXTI9_5_IRQn
#define SC_Pin GPIO_PIN_8
#define SC_GPIO_Port GPIOA
#define SB_Pin GPIO_PIN_9
#define SB_GPIO_Port GPIOA
#define SA_Pin GPIO_PIN_10
#define SA_GPIO_Port GPIOA
#define SG_Pin GPIO_PIN_3
#define SG_GPIO_Port GPIOB
#define SF_Pin GPIO_PIN_4
#define SF_GPIO_Port GPIOB
#define SE_Pin GPIO_PIN_5
#define SE_GPIO_Port GPIOB
#define SEL1_Pin GPIO_PIN_6
#define SEL1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

void setPWM(uint16_t, uint16_t);
void stopPWM();
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
