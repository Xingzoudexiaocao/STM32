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

/* �궨�� ------------------------------------------------------------------*/
#define uchar unsigned char
#define uint unsigned int
	
#define Motor1_SUB 16								//���1 16ϸ��
#define Motor2_SUB 16								//���2 16ϸ��
#define Motor3_SUB 16								//���3 16ϸ��

#define Motor1_DIR PAout( 4 ) 			//���1 ����
#define Motor2_DIR PAout( 5 )				//���2 ����
#define Motor3_DIR PAout( 7 )				//���3 ����

#define Motor1_UP Motor1_DIR = 1 		//���1 ����
#define Motor2_UP Motor2_DIR = 1 		//���2 ����
#define Motor3_UP Motor3_DIR = 1		//���3 ����

#define Motor1_DOWN Motor1_DIR = 0 	//���1 �½�
#define Motor2_DOWN Motor2_DIR = 0 	//���2 �½�
#define Motor3_DOWN Motor3_DIR = 0 	//���3 �½�
	
/* �������� ------------------------------------------------------------------*/
u8 Delay_1s_Finishflag = 0;
u8 KeyTrg = 0; 	//��������
u8 KeyCont = 0; //��������

uint i;	
u16 EXIT0_CNT = 0;
u8 Motor1_OriginFlag = 0; //���1 ԭ���ʶ
u8 Motor2_OriginFlag = 0; //���1 ԭ���ʶ
u8 Motor3_OriginFlag = 0; //���1 ԭ���ʶ	

u8 Motor_Arrived = 0; 		//���  �����ʶ
/* �������� ------------------------------------------------------------------*/
void RTC_configuration( void );
void RCC_Configuration( void );
void KeyRead( void );
void Delay_Ms( u16 time );
void delay_1s( uint time );




//================================== MAIN =======================================
int main( void )
{
	u16 i = 0;
	BUZZER = 0;//��������λ

	GPIOE -> ODR &= 0xffff0000; //LED1 ~ LED8 = 0;	
		
	RCC_Configuration();
//	RTC_configuration();
	GPIO_Configuration();
	NVIC_Configuration();
	EXTI_Configuration();
	
	Motor_Init( 0, 0, 0 );//TIM1�ر�״̬ ���ᴥ��TIM2
	//���������ⲿ�ж�
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
	//���������ⲿ�ж�
	EXTI -> IMR = 0x07;
	while( !Motor1_OriginFlag | !Motor2_OriginFlag | !Motor3_OriginFlag )
	{
		TIM1_TIM2_PWM( 1000,1000,1000, 3200, 3200, 3200 );//��û�лص�ԭλ�ĵ��컬��ص�ԭλ ���ڳ�ʼ״̬�ĵ�ƽ��׼
	}
	
	//���������ⲿ�ж�
	EXTI -> IMR = 0;
	TIM_Cmd( TIM1, DISABLE );//�ر�TIM1
	TIM1 -> CNT  = 0;//��ʱ��1 ��ǰ����ֵ����
	TIM2 -> CNT  = 0;//��ʱ��2 ��ǰ����ֵ����
	Delay_Ms( 1000 );
	
	
	
	TIM_CCxCmd( TIM2, TIM_Channel_1, TIM_CCx_Enable );//ʹ�� TIM2 -> CH1ͨ��PWM���
	TIM_CCxCmd( TIM2, TIM_Channel_2, TIM_CCx_Enable );//ʹ�� TIM2 -> CH2ͨ��PWM���
	TIM_CCxCmd( TIM2, TIM_Channel_3, TIM_CCx_Enable );//ʹ�� TIM2 -> CH3ͨ��PWM���

	
	Motor1_UP;//���1 ����
	Motor2_UP;//���2 ����
	Motor3_UP;//���3 ����
	
	TIM_ITConfig( TIM1, TIM_IT_Update, ENABLE ); //����TIM1�ж�
	Motor_Arrived = 0;
	TIM1_TIM2_PWM( 1000,800,600 ,1600,1000,1000 );
	while( !Motor_Arrived );
	delay_ms( 2000 );
	
	for( i = 0; i < 5; ++i )
	{
		BUZZER = !BUZZER;
		delay_ms( 200 );
	}
	BUZZER = 0;//��������λ
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
