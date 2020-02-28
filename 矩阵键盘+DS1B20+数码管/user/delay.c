/**
  ******************************************************************************
  * @file    传感器模块测试程序/delay();
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	
  *							SYSTICK 非中断方式实现精确延时 	SYSTICK时钟固定为HCLK的时钟1/8					
	*							选用内部时钟源72M 所以SYSTICK的时钟为9M 即SYSTICK定时器以9M的频率递减
	*							SysTick 主要包括CTRL LOAD VAL CALIB 4个寄存器
	*
	*
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/	
#include "delay.h"
/**
  * @brief  实现us精确延时
  * @param  None
  * @retval None
  */
void delay_us( u32 nus )
{
	u32 temp;
	SysTick -> LOAD = 9 * nus;
	SysTick -> VAL = 0X00;//清空计数器
	SysTick -> CTRL = 0X01;//使能 减到零是无动作 采用外部时钟源
	
	do
	{
		temp = SysTick -> CTRL;//读取当前倒计数值
	}while( ( temp & 0x01 ) && ( ! ( temp & ( 1 << 16 ) ) ) );//等待时间到达
	
	SysTick -> CTRL = 0x00; //关闭计数器
	SysTick -> VAL = 0X00; //清空计数器
}
/**
  * @brief  实现ms精确延时
  * @param  None
  * @retval None
  */
void delay_ms( u16 nms )
{
	u32 temp;
	SysTick -> LOAD = 9000 * nms;
	SysTick -> VAL = 0X00;//清空计数器
	SysTick -> CTRL = 0X01;//使能 减到零是无动作 采用外部时钟源
	do
	{
		temp=SysTick -> CTRL;////读取当前倒计数值
	}while( ( temp & 0x01 ) && ( !( temp & ( 1 << 16 ) ) ) );//等待时间到达
	
	SysTick -> CTRL = 0x00; //关闭计数器
	SysTick -> VAL = 0X00; //清空计数器
}
