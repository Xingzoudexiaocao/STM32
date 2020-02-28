/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "main.h"
#include "delay.h"
#include "DMA.h"
#include "TIMx.h"
#include "GPIOx.h"
#include "NVIC.h"
#include "USARTx.h"

/* 宏定义 ------------------------------------------------------------------*/
#define uchar unsigned char
#define uint unsigned int
	
#define Motor1_SUB 16								//电机1 16细分
#define Motor2_SUB 16								//电机2 16细分
#define Motor3_SUB 16								//电机3 16细分

#define Motor1_DIR PAout( 4 ) 			//电机1 方向
#define Motor2_DIR PAout( 5 )				//电机2 方向
#define Motor3_DIR PAout( 7 )				//电机3 方向

#define Motor1_UP Motor1_DIR = 1 		//电机1 上升
#define Motor2_UP Motor2_DIR = 1 		//电机2 上升
#define Motor3_UP Motor3_DIR = 1		//电机3 上升

#define Motor1_DOWN Motor1_DIR = 0 	//电机1 下降
#define Motor2_DOWN Motor2_DIR = 0 	//电机2 下降
#define Motor3_DOWN Motor3_DIR = 0 	//电机3 下降
	
/* 变量定义 ------------------------------------------------------------------*/
u8 Delay_1s_Finishflag = 0;
u8 KeyTrg = 0; 	//按键触发
u8 KeyCont = 0; //按键长按

uint i;	
u16 EXIT0_CNT = 0;
u8 Motor1_OriginFlag = 0; //电机1 原点标识
u8 Motor2_OriginFlag = 0; //电机1 原点标识
u8 Motor3_OriginFlag = 0; //电机1 原点标识	

u8 Motor_Arrived = 0; 		//电机  到达标识
/* 函数声明 ------------------------------------------------------------------*/
void RTC_configuration( void );
void RCC_Configuration( void );
void KeyRead( void );
void Delay_Ms( u16 time );
void delay_1s( uint time );




//================================== MAIN =======================================
int main( void )
{
	u16 i = 0;
	BUZZER = 0;//蜂鸣器复位

	GPIOE -> ODR &= 0xffff0000; //LED1 ~ LED8 = 0;	
		
	RCC_Configuration();
//	RTC_configuration();
	GPIO_Configuration();
	NVIC_Configuration();
	EXTI_Configuration();
	
	Motor_Init( 0, 0, 0 );//TIM1关闭状态 不会触发TIM2
	//屏蔽所有外部中断
	EXTI -> IMR = 0;
	if( LS1 )
	{
		TIM_CCxCmd( TIM2, TIM_Channel_1, TIM_CCx_Disable );
		Motor1_OriginFlag = 1;
	}
	if( LS2 )
	{
		TIM_CCxCmd( TIM2, TIM_Channel_2, TIM_CCx_Disable );
		Motor2_OriginFlag = 1;
	}
	if( LS3 )
	{
		TIM_CCxCmd( TIM2, TIM_Channel_3, TIM_CCx_Disable );
		Motor3_OriginFlag = 1;
	}
	
	Delay_Ms( 1000 );
	//开启所有外部中断
	EXTI -> IMR = 0x07;
	while( !Motor1_OriginFlag | !Motor2_OriginFlag | !Motor3_OriginFlag )
	{
		TIM1_TIM2_PWM( 1000,1000,1000, 3200, 3200, 3200 );//让没有回到原位的导轨滑块回到原位 用于初始状态的调平基准
	}
	
	//屏蔽所有外部中断
	EXTI -> IMR = 0;
	TIM_Cmd( TIM1, DISABLE );//关闭TIM1
	TIM1 -> CNT  = 0;//定时器1 当前计数值清零
	TIM2 -> CNT  = 0;//定时器2 当前计数值清零
	Delay_Ms( 1000 );
	
	
	
	TIM_CCxCmd( TIM2, TIM_Channel_1, TIM_CCx_Enable );//使能 TIM2 -> CH1通道PWM输出
	TIM_CCxCmd( TIM2, TIM_Channel_2, TIM_CCx_Enable );//使能 TIM2 -> CH2通道PWM输出
	TIM_CCxCmd( TIM2, TIM_Channel_3, TIM_CCx_Enable );//使能 TIM2 -> CH3通道PWM输出

	
	Motor1_UP;//电机1 上升
	Motor2_UP;//电机2 上升
	Motor3_UP;//电机3 上升
	
	TIM_ITConfig( TIM1, TIM_IT_Update, ENABLE ); //开启TIM1中断
	Motor_Arrived = 0;
	TIM1_TIM2_PWM( 1000,800,600 ,1600,1000,1000 );
	while( !Motor_Arrived );
	delay_ms( 2000 );
	
	for( i = 0; i < 5; ++i )
	{
		BUZZER = !BUZZER;
		delay_ms( 200 );
	}
	BUZZER = 0;//蜂鸣器复位
  while ( 1 )
  { 
		
		LED2 = 1;
		LED3 = 1;
		LED1 = 1;
		delay_ms( 1000 );
		LED1 = 0;
		delay_ms( 1000 );	
  }
}

//==========================子程序入口=================================
/**
  * @brief  时钟配置
  * @param  None
  * @retval None
  */
//外部晶振为8M, PLLCLK=SYSCLK=72M, HCLK=72M, P2CLK=72M, P1CLK=36M, ADCCLK=36M, USBCLK=48M, TIMCLK=72M
void RCC_Configuration( void )
{
	ErrorStatus HSEStartUpStatus; //定义错误状态枚举变量ERROR, SUCCESS 
	
	RCC_DeInit(); //RCC寄存器重新设置为默认值
	RCC_HSEConfig( RCC_HSE_ON ); //打开外部高速时钟晶振
	HSEStartUpStatus = RCC_WaitForHSEStartUp();//等待外部高速时钟工作
	if(HSEStartUpStatus == SUCCESS)
	{

		RCC_HCLKConfig( RCC_SYSCLK_Div1 ); //设置AHB不分频, HCLK = SYSCLK
		RCC_PCLK2Config( RCC_HCLK_Div1 ); //设置APB2不分频, P2CLK = HCLK
		RCC_PCLK1Config( RCC_HCLK_Div2 ); //设置APB1为2分频,P1CLK = HCLK / 2
		
		FLASH_SetLatency( FLASH_Latency_2 ); //设置FLASH代码延时	   
		FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable ); //设置预取指缓存
		
		RCC_PLLConfig( RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 ); //设置PLL时钟,外部时钟不分频,为HSE的9倍频,8MhZ * 9 = 72MHZ
		RCC_PLLCmd(ENABLE); //使能PLL
		
		while(RCC_GetFlagStatus( RCC_FLAG_PLLRDY) == RESET ); //等待PLL准备就绪
		RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK ); //设置PLL为系统时钟源
		while( RCC_GetSYSCLKSource() != 0x08 ); //判断PLL是否为系统时钟源
		
	}
}

/**
  * @brief  RTC实时时钟配置
  * @param  None
  * @retval None
  */
void RTC_configuration( void )
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP|RCC_APB1Periph_PWR,ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSEConfig(RCC_LSE_ON); 
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();

	RTC_WaitForLastTask();
	RTC_SetPrescaler( 32767 );
	RTC_WaitForLastTask(); 
	PWR_BackupAccessCmd(DISABLE);
}

/**
  * @brief  STM32主板按键 查询函数
  * @param  None
  * @retval None
  */	
void KeyRead( void )
{
	u8 ReadKey_Data; //读取按键输入数据
	ReadKey_Data = GPIOC -> IDR ^ 0x0f;
	KeyTrg = ReadKey_Data & ( ReadKey_Data ^ KeyCont );
	KeyCont = ReadKey_Data;
}	

/**
  * @brief  软件延时函数
  * @param  None
  * @retval None
  */
void Delay_Ms( u16 time ) //延时1ms函数
{ 
	u16 i,j;
	for( i = 0; i < time; i++ )
  		for( j = 10000; j > 0; j-- );
}

/**
  * @brief  TIM4 精确延时
  * @param  None
  * @retval None
  */
void delay_1s( uint time ) //延时1s函数
{ 
	uint i;
	for( i = 0; i < time; i++ )
	{
		TIM_Cmd( TIM4, ENABLE ); //开启定时器TIM4
		while( !Delay_1s_Finishflag );
		Delay_1s_Finishflag = 0;
	}
}
