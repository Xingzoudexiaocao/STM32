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

/* �궨�� ------------------------------------------------------------------*/
#define uchar unsigned char
#define uint unsigned int
#define LED1 PEout( 0 )
#define LOW 0
#define HIGH 1
	
/* �������� ------------------------------------------------------------------*/
u8 Delay_1s_Finishflag = 0;
u8 KeyTrg = 0; 	//��������
u8 KeyCont = 0; //��������

uint32_t hhh=0;

u8 Motor_Arrived = 0; 		//���  �����ʶ
/* �������� ------------------------------------------------------------------*/
void RTC_configuration( void );
void RCC_Configuration( void );
void KeyRead( void );
void Delay_Ms( u16 time );
void delay_1s( uint time );
void delay1(uint32_t ntime);
void SysTick_Handler(void);

//================================== MAIN =======================================
int main( void )
{
	RCC_Configuration();
//	RTC_configuration();
	GPIO_Configuration();
	NVIC_Configuration();
	EXTI_Configuration();
	if(SysTick_Config(SystemCoreClock/1000))
	{
		while(1);
	}
  while ( 1 )
  { 
		
		if(PBin(1)==0)
		LED1 = 1;
		else
		LED1 = 0;
		delay1( 500 );	
  }
}

//==========================�ӳ������=================================
/**
  * @brief  ʱ������
  * @param  None
  * @retval None
  */
//�ⲿ����Ϊ8M, PLLCLK=SYSCLK=72M, HCLK=72M, P2CLK=72M, P1CLK=36M, ADCCLK=36M, USBCLK=48M, TIMCLK=72M
void RCC_Configuration( void )
{
	ErrorStatus HSEStartUpStatus; //�������״̬ö�ٱ���ERROR, SUCCESS 
	
	RCC_DeInit(); //RCC�Ĵ�����������ΪĬ��ֵ
	RCC_HSEConfig( RCC_HSE_ON ); //���ⲿ����ʱ�Ӿ���
	HSEStartUpStatus = RCC_WaitForHSEStartUp();//�ȴ��ⲿ����ʱ�ӹ���
	if(HSEStartUpStatus == SUCCESS)
	{

		RCC_HCLKConfig( RCC_SYSCLK_Div1 ); //����AHB����Ƶ, HCLK = SYSCLK
		RCC_PCLK2Config( RCC_HCLK_Div1 ); //����APB2����Ƶ, P2CLK = HCLK
		RCC_PCLK1Config( RCC_HCLK_Div2 ); //����APB1Ϊ2��Ƶ,P1CLK = HCLK / 2
		
		FLASH_SetLatency( FLASH_Latency_2 ); //����FLASH������ʱ	   
		FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable ); //����Ԥȡָ����
		
		RCC_PLLConfig( RCC_PLLSource_HSE_Div1, RCC_PLLMul_9 ); //����PLLʱ��,�ⲿʱ�Ӳ���Ƶ,ΪHSE��9��Ƶ,8MhZ * 9 = 72MHZ
		RCC_PLLCmd(ENABLE); //ʹ��PLL
		
		while(RCC_GetFlagStatus( RCC_FLAG_PLLRDY) == RESET ); //�ȴ�PLL׼������
		RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK ); //����PLLΪϵͳʱ��Դ
		while( RCC_GetSYSCLKSource() != 0x08 ); //�ж�PLL�Ƿ�Ϊϵͳʱ��Դ
		
	}
}

/**
  * @brief  RTCʵʱʱ������
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
  * @brief  STM32���尴�� ��ѯ����
  * @param  None
  * @retval None
  */	
void KeyRead( void )
{
	u8 ReadKey_Data; //��ȡ������������
	ReadKey_Data = GPIOC -> IDR ^ 0x0f;
	KeyTrg = ReadKey_Data & ( ReadKey_Data ^ KeyCont );
	KeyCont = ReadKey_Data;
}	

/**
  * @brief  �����ʱ����
  * @param  None
  * @retval None
  */
void Delay_Ms( u16 time ) //��ʱ1ms����
{ 
	u16 i,j;
	for( i = 0; i < time; i++ )
  		for( j = 10000; j > 0; j-- );
}

/**
  * @brief  TIM4 ��ȷ��ʱ
  * @param  None
  * @retval None
  */
void delay_1s( uint time ) //��ʱ1s����
{ 
	uint i;
	for( i = 0; i < time; i++ )
	{
		TIM_Cmd( TIM4, ENABLE ); //������ʱ��TIM4
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
