/**
  ******************************************************************************
  * @file    
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief  
  ******************************************************************************
  * @attention	
  *
  ******************************************************************************
  */ 
	
#ifndef __DMA_H
#define __DMA_H

/* Includes -----------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "printf.h"
#include "delay.h"
#include "main.h"
/* 宏定义 -------------------------------------------------------------------*/
#define uchar unsigned char
#define uint unsigned int
	

	
#define LUMMOD_UART                     USART2
#define LUMMOD_UART_GPIO                GPIOA
#define LUMMOD_UART_CLK                 RCC_APB1Periph_USART2
#define LUMMOD_UART_GPIO_CLK        		RCC_APB2Periph_GPIOA
#define LUMMOD_UART_RxPin               GPIO_Pin_3
#define LUMMOD_UART_TxPin               GPIO_Pin_2
#define LUMMOD_UART_IRQn                USART2_IRQn
#define LUMMOD_UART_DR_Base             ( USART2_BASE + 0x04 )//0x40004404

#define LUMMOD_UART_Tx_DMA_Channel      DMA1_Channel7
#define LUMMOD_UART_Tx_DMA_FLAG         DMA1_FLAG_GL7//DMA1_FLAG_TC7 | DMA1_FLAG_TE7 
#define LUMMOD_UART_Tx_DMA_IRQ          DMA1_Channel7_IRQn

#define LUMMOD_UART_Rx_DMA_Channel      DMA1_Channel6
#define LUMMOD_UART_Rx_DMA_FLAG         DMA1_FLAG_GL6//DMA1_FLAG_TC6 | DMA1_FLAG_TE6
#define LUMMOD_UART_Rx_DMA_IRQ      		DMA1_Channel6_IRQn

/* 变量声明------------------------------------------------------------------*/


/* 函数声明 ------------------------------------------------------------------*/
void USART_DMA_Init( void );
void LumMod_Uart_DAM_Tx_Over( void );
u16 LumMod_Cmd_WriteParam( u16 sample_num, u8 *psz_param );
void LumMod_Uart_Start_DMA_Tx (uint16_t size );
void LumMod_Uart_DMA_Rx_Data( void );


#endif
