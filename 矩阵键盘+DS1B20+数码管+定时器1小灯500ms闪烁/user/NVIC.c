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
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/	
#include "NVIC.h"

/**
  * @brief  EXTI GPIO口 外部中断配置
  * @param  None
  * @retval None
  */
void EXTI_Configuration( void )
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	//清空中断标志
	EXTI_ClearITPendingBit( EXTI_Line0 );
	//清空中断标志
	EXTI_ClearITPendingBit( EXTI_Line1 );
	//清空中断标志
	EXTI_ClearITPendingBit( EXTI_Line2 );
	
	//选择中断引脚
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOD, GPIO_PinSource0 );
	//选择中断引脚
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOD, GPIO_PinSource1 );
	//选择中断引脚
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOD, GPIO_PinSource2 );
	
	//选择中断线路
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2;
	//设置为中断请求 非事件请求
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	//设置中断触发方式为下降沿触发
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	//外部中断使能
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init( &EXTI_InitStructure );
	
}

/**
  * @brief  中断配置
  * @param  None
  * @retval None
  */
void NVIC_Configuration( void )
{
	NVIC_InitTypeDef NVIC_InitStructure; //定义NVIC初始化结构体变量
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 ); //选择中断分组2
	
	//选择外部中断0中断通道
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢断式中断优先级设置为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	
	//选择外部中断1中断通道
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢断式中断优先级设置为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	
	//选择外部中断2中断通道
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢断式中断优先级设置为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	//选择TIM1的中断通道
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢断式中断优先级设置为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	//选择TIM2的中断通道
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢断式中断优先级设置为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	//选择TIM3的中断通道
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢断式中断优先级设置为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应式中断优先级设置为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	//选择TIM4的中断通道
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;	 //选择TIM4的中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢断式中断优先级设置为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应式中断优先级设置为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	
	/* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢断式中断优先级设置为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	
	/* Enable the USART2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢断式中断优先级设置为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	
	/* Enable the USART3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢断式中断优先级设置为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //响应式中断优先级设置为2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能中断
	NVIC_Init( &NVIC_InitStructure ); //将配置应用到NVIC中
	
	/* Enable the DMA Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;  //发送DMA通道的中断配置
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢断式中断优先级设置为0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//响应式中断优先级设置为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );

}
