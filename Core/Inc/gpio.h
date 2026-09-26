/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define KEY_NO_PRESS 		0		//没有按键按下
#define KEY_SHAKE_STATE 1		//按键进入消抖状态

#define Open_Led()	 	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET)
#define Close_Led() 	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET)
#define Toggle_LED()	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_7)

#define SN_LED1 0x01
#define SN_LED2 0x02
#define SN_DIG  0x03

extern uint8_t key_state;
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void SN74HC595_Send_Data(unsigned char sn_num,unsigned int sendValue);
void ShowNum(uint8_t row, uint8_t column, uint8_t value);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

