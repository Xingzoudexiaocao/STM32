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
#include "ds18b20.h"
/* 宏定义 ------------------------------------------------------------------*/
#define uchar unsigned char
#define uint unsigned int
#define LED1 PEout( 0 )
#define LED2 PEout( 1 )
#define LED3 PEout( 2 )
#define LED4 PEout( 3 )
#define LED5 PEout( 4 )
#define LED6 PEout( 5 )
#define LED7 PEout( 6 )
#define LED8 PEout( 7 )
#define LOW 0
#define HIGH 1


/* 变量定义 ------------------------------------------------------------------*/
u8 Delay_1s_Finishflag = 0;
u8 KeyTrg = 0; 	//按键触发
u8 KeyCont = 0; //按键长按

uint32_t hhh=0;
unsigned char display_code[]={	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x80,0x40,0x00,
																0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef };
unsigned char display_cache[]={12,12,12,12};
u8 Motor_Arrived = 0; 		//电机  到达标识
/* 函数声明 ------------------------------------------------------------------*/
void RTC_configuration( void );
void RCC_Configuration( void );
void KeyRead( void );
void Delay_Ms( u16 time );
void delay_1s( uint time );
void delay1(uint32_t ntime);
void SysTick_Handler(void);
unsigned char key_value(void);
void display_led(unsigned char *p);
//================================== MAIN =======================================
int main( void )
{
	
	RCC_Configuration();
//	RTC_configuration();
	GPIO_Configuration();
	NVIC_Configuration();
	EXTI_Configuration();
	Tim1_Init(4999,7199);
//	if(SysTick_Config(SystemCoreClock/1000))
//	{
//		while(1);
//	}
	u8 key;
	unsigned char temp=117;
  while ( 1 )
  { 
		while ( 1 );
		temp= read_temp(); 
		
		if(temp/1000==0)
			display_cache[0]=12;
		else
			display_cache[0]=temp/1000;
		
		if((temp/100%10==0)&&(temp/1000==0))
			display_cache[1]=12;
		else
			display_cache[1]=temp/100%10;
		
		if((temp/100%10==0)&&(temp/1000==0)&&(temp/10%10==0))
			display_cache[2]=12;
		else
			display_cache[2]=temp/10%10;
		
		display_cache[3]=temp%10;
		display_led(display_cache);
//		if(init_ds18b20()==0)
//			LED8=1;
//		else
//			LED8=0;
			
		
//		key = key_value( );
//		if(key == 0xff )
//			key = key;
//		if(key==0x00)	
//			LED1 = 1;
//		else
//			LED1 = 0;
//		if(key==0x05)	
//			LED2 = 1;
//		else 
//			LED2 = 0;
//		if(key==0x0A)	
//			LED3 = 1;
//		else 
//			LED3 = 0;
//		if(key==0x0F)	
//			LED4 = 1;
//		else
//			LED4 = 0;
//		
//		if(PCin(8)==LOW)	
//			LED5 = 1;
//		else
//			LED5 = 0;
//		if(PCin(9)==LOW)	
//			LED6 = 1;
//		else
//			LED6 = 0;
//		if(PCin(10)==LOW)	
//			LED7 = 1;
//		else
//			LED7 = 0;
		if(PCin(11)==LOW)	
			LED8 = 1;
		else
			LED8 = 0;
		
  }
}
void display_led(unsigned char *p)
{
	static unsigned char disnum=0;
	
	switch (disnum)
	{
		case 0 : 	PBout(11)=1;
							PBout(13)=1;
							PBout(15)=0;
			break;
		case 1 : 	PBout(11)=0;
							PBout(13)=1;
							PBout(15)=0;
			break;
		case 2 : 	PBout(11)=1;
							PBout(13)=0;
							PBout(15)=0;
			break;
		case 3 : 	PBout(11)=0;
							PBout(13)=0;
							PBout(15)=0;
			break;
		default :
			break;
	}
		PBout(0)=display_code[p[disnum]]&0x01;
		PBout(2)=(display_code[p[disnum]]&0x02)>>1;
		PBout(1)=(display_code[p[disnum]]&0x04)>>2;
		PBout(9)=(display_code[p[disnum]]&0x08)>>3;
		PBout(7)=(display_code[p[disnum]]&0x10)>>4;
		PBout(10)=(display_code[p[disnum]]&0x20)>>5;
		PBout(12)=(display_code[p[disnum]]&0x40)>>6;
		PBout(5)=(display_code[p[disnum]]&0x80)>>7;
		
		if(PAin(12)==0)
			LED8=1;
		else
			LED8=0;
		
			disnum++;
		if(disnum==4)
			disnum=0;
		//DBUG_LED
		if(PBin(0)==1)
			LED1 = 1;
		else
			LED1 = 0;	
		if(PBin(2)==1)
			LED2 = 1;
		else
			LED2 = 0;	
		if(PBin(1)==1)
			LED3 = 1;
		else
			LED3 = 0;	
		if(PBin(9)==1)
			LED4 = 1;
		else
			LED4 = 0;	
		if(PBin(7)==1)
			LED5 = 1;
		else
			LED5 = 0;	
		if(PBin(10)==1)
			LED6 = 1;
		else
			LED6 = 0;	
		if(PBin(12)==1)
			LED7 = 1;
		else
			LED7 = 0;	
//		if(PBin(5)==1)
//			LED8 = 1;
//		else
//			LED8 = 0;	
}

unsigned char key_value(void)
{
	unsigned char ret_value=0xFF;
	unsigned char for_num=8;
	
	for(;for_num<12;for_num++)
	{
		PCout(for_num)=LOW;
		if((PCin(0)==LOW)||(PCin(1)==LOW)||(PCin(2)==LOW)||(PCin(3)==LOW))
		{	
			
			switch(for_num)
			{
				case 8 : 	if(PCin(0)==LOW)	ret_value = 0x00;
									else if(PCin(1)==LOW)	ret_value = 0x01;
									else if(PCin(2)==LOW)	ret_value = 0x02;
									else if(PCin(3)==LOW)	ret_value = 0x03;
									
				break;
				case 9 :  if(PCin(0)==LOW)	ret_value = 0x04;
									else if(PCin(1)==LOW)	ret_value = 0x05;
									else if(PCin(2)==LOW)	ret_value = 0x06;
									else if(PCin(3)==LOW)	ret_value = 0x07;
				break;	
				case 10 : if(PCin(0)==LOW)	ret_value = 0x08;
									else if(PCin(1)==LOW)	ret_value = 0x09;
									else if(PCin(2)==LOW)	ret_value = 0x0A;
									else if(PCin(3)==LOW)	ret_value = 0x0B;
				break;	
				case 11 : if(PCin(0)==LOW)	ret_value = 0x0C;
									else if(PCin(1)==LOW)	ret_value = 0x0D;
									else if(PCin(2)==LOW)	ret_value = 0x0E;
									else if(PCin(3)==LOW)	ret_value = 0x0F;
				break;
				default :break;
			}
		}
		PCout(for_num)=HIGH;
	}
	return ret_value;
	
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
  		for( j = 10; j > 0; j-- );
}

/**
  * @brief  TIM4 精确延时
  * @param  None
  * @retval None
  */
//void delay_1s( uint time ) //延时1s函数
//{ 
//	uint i;
//	for( i = 0; i < time; i++ )
//	{
//		TIM_Cmd( TIM4, ENABLE ); //开启定时器TIM4
//		while( !Delay_1s_Finishflag );
//		Delay_1s_Finishflag = 0;
//	}
//}
//void delay1(uint32_t ntime)
//{
//	hhh=ntime;
//	while(hhh != 0);
//}
//void SysTick_Handler(void)
//{
//	if(hhh!=0x00)
//	{ 
//		hhh--;
//	}
//}
