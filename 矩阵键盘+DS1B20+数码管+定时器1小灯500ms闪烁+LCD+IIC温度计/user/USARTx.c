/**
  ******************************************************************************
  * @file   
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention 
  *												
	*											
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/	
#include "USARTx.h"

/**
  * @brief   串口配置
  * @param  None
  * @retval None
  */
	
//USART1参数配置
void USART1_Configuration( void )
{
	/*-------------定义结构体变量----------*/
	USART_InitTypeDef	USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;	
	/*-------------开启USART1时钟----------*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE );
	
	/*------------USART1的各个参数配置----------*/
	USART_InitStructure.USART_BaudRate = 9600; //设置USART传输的波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//在一帧数据传输完再传一位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;	//无奇偶校验
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收发送使能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制失能（无硬件流控制）
	USART_Init( USART1, &USART_InitStructure ); //初始化USART1的寄存器
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
  USART_ClockInit( USART1, &USART_ClockInitStructure );
	
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );//USART1 中断使能
	USART_Cmd( USART1, ENABLE );	//使能USART1外设

}

//USART2参数配置
void USART2_Configuration( void )
{
	/*-------------定义结构体变量----------*/
	USART_InitTypeDef	USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;	
	/*-------------开启USART2时钟----------*/
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );
	
	/*------------USART2的各个参数配置----------*/
	USART_InitStructure.USART_BaudRate = 115200; //设置USART传输的波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//在一帧数据传输完再传一位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;	//无奇偶校验
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收发送使能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制失能（无硬件流控制）
	USART_Init( USART2, &USART_InitStructure ); //初始化USART2的寄存器
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
  USART_ClockInit( USART2, &USART_ClockInitStructure );
	
//	USART_ITConfig( USART2, USART_IT_RXNE, ENABLE );//USART2 中断使能

	/* Enable USART2 Receive and Transmit interrupts */
	USART_ITConfig( USART2, USART_IT_IDLE, ENABLE );  //开启串口IDEL空闲中断
	USART_Cmd( USART2, ENABLE );	//使能USART2外设
	USART_DMACmd( USART2, USART_DMAReq_Tx, ENABLE );  // 使能串口DMA发送
  USART_DMACmd( USART2, USART_DMAReq_Rx, ENABLE ); 	// 使能串口DMA接收	
}

//USART3参数配置
void USART3_Configuration( void )
{
	/*-------------定义结构体变量----------*/
	USART_InitTypeDef	USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;	
	/*-------------开启USART3时钟----------*/
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3, ENABLE );
	
	/*------------USART3的各个参数配置----------*/
	USART_InitStructure.USART_BaudRate = 115200; //设置USART传输的波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//在一帧数据传输完再传一位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;	//无奇偶校验
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收发送使能
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制失能（无硬件流控制）
	USART_Init( USART3, &USART_InitStructure ); //初始化USART3的寄存器
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
  USART_ClockInit( USART3, &USART_ClockInitStructure );
	
//	USART_ITConfig( USART3, USART_IT_RXNE, ENABLE );//USART3 中断使能
	
	USART_Cmd( USART3, ENABLE );	//使能USART3外设
}
