/**
  ******************************************************************************
  * @file    传感器模块测试程序
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	延时函数
  *
  ******************************************************************************
  */ 
	
#ifndef __TIMX_H
#define __TIMX_H

/* Includes -----------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"
/* 宏定义 -------------------------------------------------------------------*/

/* 变量定义 ------------------------------------------------------------------*/
void Tim1_Init(u16 arr , u16 psc );
void Motor_Init( u16 TIM2per, u16 TIM3per, u16 TIM3Compare1 );
void TIM1_TIM2_PWM( u16 Cycle,u16 Cycle1,u16 Cycle2,u16 Pulse_Num,u16 Pulse_Num1,u16 Pulse_Num2 );
void TIM3_Configuration( void );
void TIM4_Configuration( void );

/* 函数声明 ------------------------------------------------------------------*/


#endif
