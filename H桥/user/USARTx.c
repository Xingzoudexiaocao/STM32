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
	*											
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/	
#include "USARTx.h"

/**
  * @brief   ��������
  * @param  None
  * @retval None
  */
	
//USART1��������
void USART1_Configuration( void )
{
	/*-------------����ṹ�����----------*/
	USART_InitTypeDef	USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;	
	/*-------------����USART1ʱ��----------*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE );
	
	/*------------USART1�ĸ�����������----------*/
	USART_InitStructure.USART_BaudRate = 9600; //����USART����Ĳ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//��һ֡���ݴ������ٴ�һλֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//����żУ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //���շ���ʹ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ʧ�ܣ���Ӳ�������ƣ�
	USART_Init( USART1, &USART_InitStructure ); //��ʼ��USART1�ļĴ���
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
  USART_ClockInit( USART1, &USART_ClockInitStructure );
	
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );//USART1 �ж�ʹ��
	USART_Cmd( USART1, ENABLE );	//ʹ��USART1����

}

//USART2��������
void USART2_Configuration( void )
{
	/*-------------����ṹ�����----------*/
	USART_InitTypeDef	USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;	
	/*-------------����USART2ʱ��----------*/
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );
	
	/*------------USART2�ĸ�����������----------*/
	USART_InitStructure.USART_BaudRate = 115200; //����USART����Ĳ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//��һ֡���ݴ������ٴ�һλֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//����żУ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //���շ���ʹ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ʧ�ܣ���Ӳ�������ƣ�
	USART_Init( USART2, &USART_InitStructure ); //��ʼ��USART2�ļĴ���
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
  USART_ClockInit( USART2, &USART_ClockInitStructure );
	
//	USART_ITConfig( USART2, USART_IT_RXNE, ENABLE );//USART2 �ж�ʹ��

	/* Enable USART2 Receive and Transmit interrupts */
	USART_ITConfig( USART2, USART_IT_IDLE, ENABLE );  //��������IDEL�����ж�
	USART_Cmd( USART2, ENABLE );	//ʹ��USART2����
	USART_DMACmd( USART2, USART_DMAReq_Tx, ENABLE );  // ʹ�ܴ���DMA����
  USART_DMACmd( USART2, USART_DMAReq_Rx, ENABLE ); 	// ʹ�ܴ���DMA����	
}

//USART3��������
void USART3_Configuration( void )
{
	/*-------------����ṹ�����----------*/
	USART_InitTypeDef	USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;	
	/*-------------����USART3ʱ��----------*/
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3, ENABLE );
	
	/*------------USART3�ĸ�����������----------*/
	USART_InitStructure.USART_BaudRate = 115200; //����USART����Ĳ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//��һ֡���ݴ������ٴ�һλֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;	//����żУ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //���շ���ʹ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������ʧ�ܣ���Ӳ�������ƣ�
	USART_Init( USART3, &USART_InitStructure ); //��ʼ��USART3�ļĴ���
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
  USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
  USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
  USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
  USART_ClockInit( USART3, &USART_ClockInitStructure );
	
//	USART_ITConfig( USART3, USART_IT_RXNE, ENABLE );//USART3 �ж�ʹ��
	
	USART_Cmd( USART3, ENABLE );	//ʹ��USART3����
}
