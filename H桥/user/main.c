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
#define LED1 PEout( 0 )
#define LOW 0
#define HIGH 1
#define AIN1_1 PAout(8)	
#define AIN1_2 PAout(10)	
#define BIN1_1 PAout(12)	
#define BIN1_2 PAout(9)	
unsigned char L_or_R=0;
/* 变量定义 ------------------------------------------------------------------*/
u8 Delay_1s_Finishflag = 0;
u8 KeyTrg = 0; 	//按键触发
u8 KeyCont = 0; //按键长按

uint32_t hhh=0;

u8 Motor_Arrived = 0; 		//电机  到达标识
/* 函数声明 ------------------------------------------------------------------*/
void RTC_configuration( void );
void RCC_Configuration( void );
void KeyRead( void );
void Delay_Ms( u16 time );
void delay_1s( uint time );
void delay1(uint32_t ntime);
void SysTick_Handler(void);
void stepping_motor(unsigned char L_or_R,unsigned int time,unsigned int speed);
//================================== MAIN =======================================
int main( void )
{

	RCC_Configuration();
//	RTC_configuration();
	GPIO_Configuration();
	NVIC_Configuration();
	EXTI_Configuration();
		Tim1_Init( 7200, 18);
	if(SysTick_Config(SystemCoreClock/1000))
	{
		while(1);
	}
  while ( 1 )
  {
//		stepping_motor(1,100,1800);
//	
		TIM_Cmd( TIM1, ENABLE );
		L_or_R=1;
		delay_ms(1200);
		TIM_Cmd( TIM1, DISABLE );
		AIN1_1=AIN1_2=BIN1_1=BIN1_2=0;
		delay_ms(1200);
//		stepping_motor(0,100,1800);
		TIM_Cmd( TIM1, ENABLE );
		L_or_R=0;
		delay_ms(1200);
		TIM_Cmd( TIM1, DISABLE );
		AIN1_1=AIN1_2=BIN1_1=BIN1_2=0;
		delay_ms(500);
//		
//		
  }
}
//==========================子程序入口=================================
void stepping_motor(unsigned char L_or_R,unsigned int time,unsigned int speed)
{
	unsigned int num=0;
	if(L_or_R==1)
	{
		for(num=0;num<time;num++)
		{
			AIN1_1=1; AIN1_2=0; BIN1_1=1; BIN1_2=0; delay_us(speed); //1拍 1.8°
			AIN1_1=0; AIN1_2=1; BIN1_1=1; BIN1_2=0; delay_us(speed); //2拍
			AIN1_1=0; AIN1_2=1; BIN1_1=0; BIN1_2=1; delay_us(speed); //3拍
			AIN1_1=1; AIN1_2=0; BIN1_1=0; BIN1_2=1; delay_us(speed); //4拍
		}
	}
	else if(L_or_R==0)
	{
		for(num=0;num<time;num++)
		{	
			AIN1_1=1; AIN1_2=0; BIN1_1=0; BIN1_2=1; delay_us(1800); //4拍
			AIN1_1=0; AIN1_2=1; BIN1_1=0; BIN1_2=1; delay_us(1800); //3拍
			AIN1_1=0; AIN1_2=1; BIN1_1=1; BIN1_2=0; delay_us(1800); //2拍
			AIN1_1=1; AIN1_2=0; BIN1_1=1; BIN1_2=0; delay_us(1800); //1拍
		}
	}
}
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
void delay1(uint32_t ntime)
{
	hhh=ntime;
	while(hhh != 0);
}
void SysTick_Handler(void)
{
	if(hhh!=0x00)
	{ 
		hhh--;
	}
}
