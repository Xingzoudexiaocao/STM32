/**
  ******************************************************************************
  * @file    1方案stm32三自由度机器人
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	GPIO 端口定义
  *
  ******************************************************************************
  */ 
	
#ifndef __GPIOX_H
#define __GPIOX_H

/* Includes -----------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"
/* 宏定义 -------------------------------------------------------------------*/	
#define LED1 PEout( 0 )				//传感器模块stm32 LED1
#define LED2 PEout( 1 )				//传感器模块stm32 LED2
#define LED3 PEout( 2 )				//传感器模块stm32 LED3
#define LED4 PEout( 3 )				//传感器模块stm32 LED4
#define LED5 PEout( 4 )				//传感器模块stm32 LED5
#define LED6 PEout( 5 )				//传感器模块stm32 LED6
#define LED7 PEout( 6 )				//传感器模块stm32 LED7
#define LED8 PEout( 7 )				//传感器模块stm32 LED8

#define S1 PCin( 0 )					//传感器模块stm32 S1
#define S2 PCin( 1 )					//传感器模块stm32 S2
#define S3 PCin( 2 )					//传感器模块stm32 S3
#define S4 PCin( 3 )					//传感器模块stm32 S4
#define BUZZER PCout( 4 )			//传感器模块stm32 S4

#define LS1 PDin( 0 )					//迷宫机器人限位开关 LS1
#define LS2 PDin( 1 )					//迷宫机器人限位开关 LS2
#define LS3 PDin( 2 )					//迷宫机器人限位开关 LS3

#define K1 PBout( 9 )					//传感器模块stm32 RELAY K1
#define K2 PBout( 11 )				//传感器模块stm32 RELAY K2
#define K3 PBout( 13 )				//传感器模块stm32 RELAY K3
#define K4 PBout( 15 )				//传感器模块stm32 RELAY K4
	
/* 变量定义 ------------------------------------------------------------------*/

/* 函数声明 ------------------------------------------------------------------*/
void GPIO_Configuration( void );

#endif
