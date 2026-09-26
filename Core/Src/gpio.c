/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "main.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
//0~9，外加一个小数点
static uint16_t sgh_value[11]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x80};

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through
        * the Code Generation settings)
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED2_SER_Pin|LED2_RCLK_Pin|LED2_SCLK_Pin|DIG_SER_Pin
                          |DIG_RCLK_Pin|DIG_SCLK_Pin|LED1_RCLK_Pin|LED1_SCLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED1_SER_GPIO_Port, LED1_SER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_TEST_GPIO_Port, LED_TEST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = LED2_SER_Pin|LED2_RCLK_Pin|LED2_SCLK_Pin|DIG_SER_Pin
                          |DIG_RCLK_Pin|DIG_SCLK_Pin|LED1_RCLK_Pin|LED1_SCLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA6 PA7 PA10 PA11
                           PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB3 PB4 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = LED1_SER_Pin|LED_TEST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = WAKE_KEY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(WAKE_KEY_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/* USER CODE BEGIN 2 */

/*
	函数内容：SN74HC595发送数据函数
	函数参数：unsigned char sn_num-哪一个595器件
						unsigned char sendValue--数据值
	返回值：	无
*/
void SN74HC595_Send_Data(unsigned char sn_num,unsigned int sendValue)
{
	uint8_t i = 0;
	if(sn_num == SN_LED1)	//第一个数码管
	{
		for(i = 0;i < 8;i++)
		{
			if(((sendValue << i)&0x80)!=0)	//如果数据第一位是1
			{
				HAL_GPIO_WritePin(LED1_SER_GPIO_Port,LED1_SER_Pin,GPIO_PIN_SET);		//高电平
			}
			else
			{
				HAL_GPIO_WritePin(LED1_SER_GPIO_Port,LED1_SER_Pin,GPIO_PIN_RESET);	//低电平
			}
			HAL_GPIO_WritePin(LED1_SCLK_GPIO_Port,LED1_SCLK_Pin,GPIO_PIN_RESET);	//产生一个SCLK上升沿
			HAL_GPIO_WritePin(LED1_SCLK_GPIO_Port,LED1_SCLK_Pin,GPIO_PIN_SET);
			}
		HAL_GPIO_WritePin(LED1_RCLK_GPIO_Port,LED1_RCLK_Pin,GPIO_PIN_RESET);	//产生一个RCLK上升沿
		HAL_GPIO_WritePin(LED1_RCLK_GPIO_Port,LED1_RCLK_Pin,GPIO_PIN_SET);
	}
	else if(sn_num == SN_LED2)
	{
		for(i = 0;i < 8;i++)
		{
			if(((sendValue << i)&0x80)!=0)
			{
				HAL_GPIO_WritePin(LED2_SER_GPIO_Port,LED2_SER_Pin,GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(LED2_SER_GPIO_Port,LED2_SER_Pin,GPIO_PIN_RESET);
			}
			HAL_GPIO_WritePin(LED2_SCLK_GPIO_Port,LED2_SCLK_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED2_SCLK_GPIO_Port,LED2_SCLK_Pin,GPIO_PIN_SET);
			}
		HAL_GPIO_WritePin(LED2_RCLK_GPIO_Port,LED2_RCLK_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_RCLK_GPIO_Port,LED2_RCLK_Pin,GPIO_PIN_SET);	
	}
	else if(sn_num == SN_DIG)
	{
		for(i = 0;i < 8;i++)
		{
			if(((sendValue << i)&0x80)!=0)
			{
				HAL_GPIO_WritePin(DIG_SER_GPIO_Port,DIG_SER_Pin,GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIG_SER_GPIO_Port,DIG_SER_Pin,GPIO_PIN_RESET);
			}
			HAL_GPIO_WritePin(DIG_SCLK_GPIO_Port,DIG_SCLK_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(DIG_SCLK_GPIO_Port,DIG_SCLK_Pin,GPIO_PIN_SET);
			}
		HAL_GPIO_WritePin(DIG_RCLK_GPIO_Port,DIG_RCLK_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DIG_RCLK_GPIO_Port,DIG_RCLK_Pin,GPIO_PIN_SET);	
	}
}

/* 64Mhz时钟时，当ulCount为1，函数耗时3个时钟，延时=3*1/64us */
__asm void SysCtlDelay(unsigned long ulCount)
{
	SUBS r0,#1;
	BNE SysCtlDelay;
	BX lr;
}

/*
	函数内容：数码管显示数据函数
	函数参数：uint8_t row----行号
						uint8_t column-列号
						uint8_t value--显示数据
	返回值：无
*/
void ShowNum(uint8_t row, uint8_t column, uint8_t value)
{
	if(row == 1)
	{
		switch(column)
		{
			case 1:	//如果是第一排第一个
					SN74HC595_Send_Data(SN_DIG,0xFE);
					SN74HC595_Send_Data(SN_LED1,sgh_value[value]);//显示值对应16进制数
				break;
			case 2:
					SN74HC595_Send_Data(SN_DIG,0xFD);
					SN74HC595_Send_Data(SN_LED1,(sgh_value[value]|0x80));
				break;
			case 3:
					SN74HC595_Send_Data(SN_DIG,0xFB);
					SN74HC595_Send_Data(SN_LED1,sgh_value[value]);
				break;
			default:
				break;
		}
		SysCtlDelay(1000);	//大致延时50us
		SN74HC595_Send_Data(SN_LED1,0x00);	//消影，防止错位
	}
	else
	{
		switch(column)
		{
			case 1:
					SN74HC595_Send_Data(SN_DIG,0xF7);
					SN74HC595_Send_Data(SN_LED2,sgh_value[value]);
				break;
			case 2:
					SN74HC595_Send_Data(SN_DIG,0xEF);
					SN74HC595_Send_Data(SN_LED2,(sgh_value[value]|0x80));
				break;
			case 3:
					SN74HC595_Send_Data(SN_DIG,0xDF);
					SN74HC595_Send_Data(SN_LED2,sgh_value[value]);
				break;
			default:
				break;
		}
		SysCtlDelay(1000);	//大致延时50us
		SN74HC595_Send_Data(SN_LED2,0x00);
	}
}

/*
	函数内容：GPIO 下降沿中断服务函数
	函数参数：uint16_t GPIO_Pin--哪一个GPIO
	返回值：	无
*/
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_5)
	{	
		device_paramter.KeyStatus = KEY_SHAKE_STATE;	//设置按键状态为消抖状态
		HAL_ResumeTick();															//恢复滴答定时器
	}
}
/* USER CODE END 2 */
