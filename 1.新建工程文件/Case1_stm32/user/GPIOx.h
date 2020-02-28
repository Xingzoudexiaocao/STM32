/**
  ******************************************************************************
  * @file    1����stm32�����ɶȻ�����
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	GPIO �˿ڶ���
  *
  ******************************************************************************
  */ 
	
#ifndef __GPIOX_H
#define __GPIOX_H

/* Includes -----------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"
/* �궨�� -------------------------------------------------------------------*/	
#define LED1 PEout( 0 )				//������ģ��stm32 LED1
#define LED2 PEout( 1 )				//������ģ��stm32 LED2
#define LED3 PEout( 2 )				//������ģ��stm32 LED3
#define LED4 PEout( 3 )				//������ģ��stm32 LED4
#define LED5 PEout( 4 )				//������ģ��stm32 LED5
#define LED6 PEout( 5 )				//������ģ��stm32 LED6
#define LED7 PEout( 6 )				//������ģ��stm32 LED7
#define LED8 PEout( 7 )				//������ģ��stm32 LED8

#define S1 PCin( 0 )					//������ģ��stm32 S1
#define S2 PCin( 1 )					//������ģ��stm32 S2
#define S3 PCin( 2 )					//������ģ��stm32 S3
#define S4 PCin( 3 )					//������ģ��stm32 S4
#define BUZZER PCout( 4 )			//������ģ��stm32 S4

#define LS1 PDin( 0 )					//�Թ���������λ���� LS1
#define LS2 PDin( 1 )					//�Թ���������λ���� LS2
#define LS3 PDin( 2 )					//�Թ���������λ���� LS3

#define K1 PBout( 9 )					//������ģ��stm32 RELAY K1
#define K2 PBout( 11 )				//������ģ��stm32 RELAY K2
#define K3 PBout( 13 )				//������ģ��stm32 RELAY K3
#define K4 PBout( 15 )				//������ģ��stm32 RELAY K4
	
/* �������� ------------------------------------------------------------------*/

/* �������� ------------------------------------------------------------------*/
void GPIO_Configuration( void );

#endif
