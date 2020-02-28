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
  * @brief  EXTI GPIO�� �ⲿ�ж�����
  * @param  None
  * @retval None
  */
void EXTI_Configuration( void )
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	//����жϱ�־
	EXTI_ClearITPendingBit( EXTI_Line0 );
	//����жϱ�־
	EXTI_ClearITPendingBit( EXTI_Line1 );
	//����жϱ�־
	EXTI_ClearITPendingBit( EXTI_Line2 );
	
	//ѡ���ж�����
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOD, GPIO_PinSource0 );
	//ѡ���ж�����
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOD, GPIO_PinSource1 );
	//ѡ���ж�����
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOD, GPIO_PinSource2 );
	
	//ѡ���ж���·
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2;
	//����Ϊ�ж����� ���¼�����
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	//�����жϴ�����ʽΪ�½��ش���
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	//�ⲿ�ж�ʹ��
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init( &EXTI_InitStructure );
	
}

/**
  * @brief  �ж�����
  * @param  None
  * @retval None
  */
void NVIC_Configuration( void )
{
	NVIC_InitTypeDef NVIC_InitStructure; //����NVIC��ʼ���ṹ�����
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 ); //ѡ���жϷ���2
	
	//ѡ���ⲿ�ж�0�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //����ʽ�ж����ȼ�����Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	
	//ѡ���ⲿ�ж�1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //����ʽ�ж����ȼ�����Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	
	//ѡ���ⲿ�ж�2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //����ʽ�ж����ȼ�����Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	//ѡ��TIM1���ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //����ʽ�ж����ȼ�����Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	//ѡ��TIM2���ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //����ʽ�ж����ȼ�����Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	//ѡ��TIM3���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //����ʽ�ж����ȼ�����Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧʽ�ж����ȼ�����Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	//ѡ��TIM4���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;	 //ѡ��TIM4���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //����ʽ�ж����ȼ�����Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧʽ�ж����ȼ�����Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	
	/* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //����ʽ�ж����ȼ�����Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	
	/* Enable the USART2 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //����ʽ�ж����ȼ�����Ϊ1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	
	/* Enable the USART3 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //����ʽ�ж����ȼ�����Ϊ0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //��Ӧʽ�ж����ȼ�����Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�
	NVIC_Init( &NVIC_InitStructure ); //������Ӧ�õ�NVIC��
	
	/* Enable the DMA Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;  //����DMAͨ�����ж�����
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //����ʽ�ж����ȼ�����Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//��Ӧʽ�ж����ȼ�����Ϊ1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );

}
