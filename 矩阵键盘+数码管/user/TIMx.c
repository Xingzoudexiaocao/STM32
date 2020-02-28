/**
  ******************************************************************************
  * @file    传感器模块测试程序
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention 精确输出脉冲个数 可调节输出脉冲频率和占空比
  *												
	*							
	*							
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/	
#include "TIMx.h"

/**
  * @brief  TIM1 / TIM2 配置
  * @param  None
  * @retval None
  */
/****************************
**TIM1 -> CH1 使用单脉冲模式
**TIM2 -> CH1( PA0 ) 使用门控方式输出PWM 
**TIM2 -> CH2( PA1 ) 使用门控方式输出PWM
**TIM2 -> CH3( PA2 ) 使用门控方式输出PWM
****************************/
//TIM2per: 重装载值
//Compare1: 比较捕获1的预装载值
void Motor_Init( u16 TIM1per, u16 TIM2per, u16 TIM2Compare1 )
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
	//TIM1工作在单脉冲模式下
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;//时基单元结构体
  TIM_OCInitTypeDef	TIM_OCInitStructure;//输出比较结构体
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;//死区设置
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE ); 	//开启定时器1时钟
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE ); 	//开启定时器2时钟
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );	//使能GPIOA时钟
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); 	//使能复用功能时钟
  
 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8;//PA0 / PA1 / PA2 / PA8
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( GPIOA, &GPIO_InitStruct );

	//TIM1工作在单脉冲模式下
	TIM_InternalClockConfig( TIM1 ); //SMS =000采用内部时钟给TIM1提供时钟源( TIMxCLK -> CK_INT -> CK_PSC -> CK_CNT )
	TIM_TimeBaseStructure.TIM_Prescaler = 7200; //PSC 预分频系数为72MHz / 7200,立即装入,每100us计数一次
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ; //设置计数模式为向上计数
	TIM_TimeBaseStructure.TIM_Period = TIM1per; //ARR 设置计数溢出大小TIM2per,每TIM2per个计数产生一个更新事件
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分频因子( CK_INT -> 数字滤波器( ETR/TIx )输入采样滤波频率 )
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //重复溢出设定次数后才产生中断
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseStructure );
	
	TIM_SelectOnePulseMode( TIM1, TIM_OPMode_Single );//设置TIM1为单脉冲模式
  TIM_OC1PreloadConfig( TIM1, TIM_OCPreload_Enable );//使能TIM1 -> CH1 预装载寄存器
	TIM_SelectMasterSlaveMode( TIM1,TIM_MasterSlaveMode_Enable );//使能TIM1的主从模式
  TIM_SelectOutputTrigger( TIM1, TIM_TRGOSource_OC1Ref );//选择触发源
	
	//----------------------------输出比较产生PWM-----------------------------------------
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//在向上计数时, 一旦TIMx_CNT < TIMx_CCR1时通道1为无效电平,否则为有效电平
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//选择输出比较状态 CH1通道有效
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Enable;//选择互补输出比较状态 CH1N通道有效
	TIM_OCInitStructure.TIM_Pulse = 1;//占空比TIMx_CCR1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//输出极性为高电平
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//互补输出极性
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//选择空闲状态下的非工作状态
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;//选择空闲状态下的非工作状态
	TIM_OC1Init( TIM1, &TIM_OCInitStructure );//对通道1(TIM1_CH1)进行初始化
	
	//---------------------------------BDTR设置--------------------------------------------
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; //锁定级别 不锁定
	TIM_BDTRInitStructure.TIM_DeadTime = 0;  //调整死区大小 0-0xff
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;//空闲模式不允许
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High; //空闲电平极性高
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable; //自动输出使能
	TIM_BDTRConfig( TIM1, &TIM_BDTRInitStructure );

	TIM_CtrlPWMOutputs( TIM1, ENABLE );//TIM1_OCx 通道输出PWM /*注意：不可缺少*/
	TIM_ClearFlag( TIM1, TIM_FLAG_Update ); //清除溢出中断标志位
	TIM_Cmd( TIM1, DISABLE );//先关闭TIM1
  
  //TIM2工作在从模式的门控模式下的PWM输出模式
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//没有时钟分割
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
  TIM_TimeBaseStructure.TIM_Prescaler = 720;//设置预分频值，每10us计数一次
  TIM_TimeBaseStructure.TIM_Period = TIM2per;//重装载值
  TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );
  
  TIM_SelectSlaveMode( TIM2, TIM_SlaveMode_Gated );//TIM2为门控模式
	TIM_SelectMasterSlaveMode( TIM2,TIM_MasterSlaveMode_Enable );//使能TIM2的主从模式
	TIM_OC1PreloadConfig( TIM2, TIM_OCPreload_Enable );//使能TIM2预装载寄存器
	TIM_OC2PreloadConfig( TIM2, TIM_OCPreload_Enable );//使能TIM2预装载寄存器
	TIM_OC3PreloadConfig( TIM2, TIM_OCPreload_Enable );//使能TIM2预装载寄存器
  TIM_SelectInputTrigger( TIM2, TIM_TS_ITR0 );//内部触发,从TIM1触发
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//向上计数时,一旦TIMx_CNT < TIMx_CCR1 CH1为无效电平,否则为有效电平
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出使能
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//有效电平为高
	
  TIM_OCInitStructure.TIM_Pulse = TIM2Compare1;//输出捕获1的预装载值
  TIM_OC1Init( TIM2, &TIM_OCInitStructure );//TIM2 -> CH1 初始化
	
	TIM_OCInitStructure.TIM_Pulse = TIM2Compare1;//输出捕获2的预装载值
	TIM_OC2Init( TIM2, &TIM_OCInitStructure );//TIM2 -> CH2 初始化
	
	TIM_OCInitStructure.TIM_Pulse = TIM2Compare1;//输出捕获1的预装载值
	TIM_OC3Init( TIM2, &TIM_OCInitStructure );//TIM2 -> CH3 初始化
	
  TIM_Cmd( TIM2, ENABLE );//使能TIM2
  
}


//设置PWM的输出
//Cycle:为周期,单位为(us)
//Pulse_Num:为脉冲个数(小于3200)
void TIM1_TIM2_PWM( u16 Cycle,u16 Cycle1,u16 Cycle2,u16 Pulse_Num,u16 Pulse_Num1,u16 Pulse_Num2 )
{
  u16 TIM2per = 0;
	u16 TIM2per1 = 0;
	u16 TIM2per2 = 0;
  u32 Time = 0;
  //设置TIM2的重装载值改变脉冲频率, 设置脉冲占空比为50%
  //设置TIM1预分频值和重装载值改变脉冲个数
    
	if(Cycle!=0)
	{
  Time = Cycle * Pulse_Num;
  Time /= 100;              //预分频值为7200,100us计数一次
  TIM2per = Cycle / 10;     //预分频值为720,10us计数一次
	}	
	if(Cycle1!=0)
	{
  Time = Cycle1 * Pulse_Num1;
  Time /= 100;              //预分频值为7200,100us计数一次
  TIM2per1 = Cycle1 / 10;     //预分频值为720,10us计数一次
	}		
	if(Cycle2!=0)
	{
  Time = Cycle2 * Pulse_Num2;
  Time /= 100;              //预分频值为7200,100us计数一次
  TIM2per2 = Cycle2 / 10;     //预分频值为720,10us计数一次
	}			
  
  TIM_SetAutoreload( TIM1, Time + 1 );//设置TIM1的重装载值
  TIM_SetAutoreload( TIM2, TIM2per - 1 );//设置TIM2的重装载值
  TIM_SetCompare1( TIM2,TIM2per / 2 );//设置TIM2 -> 占空比为50%
	TIM_SetCompare2( TIM2,TIM2per1 / 2 );//设置TIM2 -> 占空比为50%
	TIM_SetCompare3( TIM2,TIM2per2 / 2 );//设置TIM2 -> 占空比为50%
  TIM_Cmd( TIM1, ENABLE );//使能TIM1
}

/**
  * @brief  TIM3 定时器配置
  * @param  None
  * @retval None
  */
void TIM3_Configuration( void )
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;//时基单元结构体
//	TIM_ICInitTypeDef  TIM_ICInitStructure;//输入捕获结构体
  TIM_OCInitTypeDef	TIM_OCInitStructure;//输出比较结构体
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );//开启TIM3时钟
	
	TIM_InternalClockConfig( TIM3 ); //SMS =000采用内部时钟给TIM2提供时钟源( TIMxCLK -> CK_INT -> CK_PSC -> CK_CNT )
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //PSC 预分频系数为900 - 1,计数时钟频率:72MHz / 450 = 160KHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ; //设置计数模式为向上计数
	TIM_TimeBaseStructure.TIM_Period = 4 - 1; //ARR 设置计数溢出大小5 - 1,每5个计数产生一个更新事件( 40KHz )
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分频因子( CK_INT -> 数字滤波器( ETR/TIx )输入采样滤波频率 )
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );
	TIM_PrescalerConfig( TIM3, 450 - 1, TIM_PSCReloadMode_Immediate ); //PSC 预分频系数为360,立即装入
	
//----------------------------输出比较产生PWM-----------------------------------------
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//PWM1模式（边沿对齐模式）
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//CH3通道有效
	TIM_OCInitStructure.TIM_Pulse = 2;//占空比TIMx_CCR1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	//输出极性为低电平
	TIM_OC3Init( TIM3, &TIM_OCInitStructure );//对通道3(TIM3_CH3)进行初始化

//----------------------------输入捕获--------------------------------------------------

//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;// Channel_4 输入捕获选择通道4
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿触发
//  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  //Direct connecte
//  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//register every rising edages
//  TIM_ICInitStructure.TIM_ICFilter = 0x05;//滤波参数
//  TIM_ICInit( TIM3, &TIM_ICInitStructure );
	
//------------------------------------------------------------------------------------		
//	TIM_SelectInputTrigger( TIM3, TIM_TS_TI2FP2 );//选择输入触发源
//	TIM_SelectSlaveMode( TIM3, TIM_SlaveMode_Reset );//触发方式
//	TIM_SelectMasterSlaveMode( TIM3, TIM_MasterSlaveMode_Enable );//启动定时器的被动触发
//------------------------------------------------------------------------------------	

//	TIM_SetCompare4( TIM3, 0 );//设置捕获计数器( TIMx_CCR4 )初值为0
//	TIM_ClearITPendingBit(TIM3, TIM_IT_Update );//清除计时器溢出中断标志位
//  TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);//清除捕获中断标志位
////	TIM_ClearFlag( TIM3, TIM_FLAG_Update );//清除TIM3溢出标志
//	TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE );//TIM3溢出中断允许	
//	TIM_ITConfig( TIM3, TIM_IT_CC4, ENABLE );//打开捕获输入中断

	TIM_Cmd( TIM3, ENABLE );//开启定时器3 PWM波形输出
		
}
/**
  * @brief  TIM4 定时器配置
  * @param  None
  * @retval None
  */
void TIM4_Configuration( void )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义TIM初始化结构体变量
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );//开启TIM4时钟
	
	TIM_DeInit( TIM4 ); //将TIM寄存器重置为缺省值
	TIM_InternalClockConfig( TIM4 ); //SMS =000采用内部时钟给TIM4提供时钟源( TIMxCLK( 72MHz ) -> CK_INT -> CK_PSC -> CK_CNT )
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //PSC 预分频系数为3600 - 1,计数时钟频率:72MHz / 7200 = 10KHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分频因子( CK_INT -> 数字滤波器( ETR/TIx )输入采样滤波频率 )
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //设置计数模式为向上计数
	TIM_TimeBaseStructure.TIM_Period = 3000 - 1; //ARR 设置计数溢出大小100 - 1,每10000个计数产生一个更新事件
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure); //将配置应用到TIM中

	TIM_PrescalerConfig( TIM4, 7200 - 1, TIM_PSCReloadMode_Immediate ); //PSC 预分频系数为7200,立即装入
	
	TIM_ClearFlag( TIM4, TIM_FLAG_Update ); //清除溢出中断标志位
	TIM_ARRPreloadConfig( TIM4, DISABLE ); //禁止ARR预装载缓冲器
	TIM_ITConfig( TIM4, TIM_IT_Update, ENABLE ); //开启TIM4中断

}
