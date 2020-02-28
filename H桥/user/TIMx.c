/**
  ******************************************************************************
  * @file    传感器模块测试程序
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention 精确输出脉冲个数 可调节输出脉冲频率和占空比
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/	
#include "TIMx.h"
void Tim1_Init(u16 arr , u16 psc)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;//时基单元结构体
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE ); 	//开启定时器1时钟
	
	//TIM1工作在单脉冲模式下
	TIM_InternalClockConfig( TIM1 ); //SMS =000采用内部时钟给TIM1提供时钟源( TIMxCLK -> CK_INT -> CK_PSC -> CK_CNT )
	TIM_TimeBaseStructure.TIM_Prescaler = arr; //PSC 预分频系数为72MHz / 7200,立即装入,每100us计数一次
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ; //设置计数模式为向上计数
	TIM_TimeBaseStructure.TIM_Period = psc; //ARR 设置计数溢出大小TIM2per,每TIM2per个计数产生一个更新事件
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分频因子( CK_INT -> 数字滤波器( ETR/TIx )输入采样滤波频率 )
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //重复溢出设定次数后才产生中断
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseStructure );
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_Cmd( TIM1, ENABLE );
}
