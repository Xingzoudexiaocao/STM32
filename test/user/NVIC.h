/**
  ******************************************************************************
  * @file    
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	�ж�����
  *
  ******************************************************************************
  */ 
	
#ifndef __NVIC_H
#define __NVIC_H

/* Includes -----------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"
/* �궨�� -------------------------------------------------------------------*/
	
/* �������� ------------------------------------------------------------------*/

/* �������� ------------------------------------------------------------------*/
void EXTI_Configuration( void );
void NVIC_Configuration( void );

#endif