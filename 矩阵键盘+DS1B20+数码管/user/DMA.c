/**
  ******************************************************************************
  * @file    ������ģ����Գ���
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   
  ******************************************************************************
  * @attention	
  *
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/	
#include "DMA.h"
#include <stdio.h>
#include <string.h> 
/* �������� ------------------------------------------------------------------*/
u8 LumMod_Tx_Buf[ 20 ];
u8 LumMod_Rx_Buf[ 20 ];
uint LumMod_Rx_Data_index = 0;
uint LUMMOD_TX_BSIZE = 0;
uint LUMMOD_RX_BSIZE = 0;

/**
  * @brief  USART_DMA_Init USART1 DMAͨ������
  * @param  None
  * @retval None
  */
void USART_DMA_Init( void )
{
	DMA_InitTypeDef DMA_InitStructure;
	
	/* DMA1 clock enable */
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE ); //����DMA1ʱ��


	/*--- LUMMOD_UART_Tx_DMA_Channel DMA Config ---*/
	DMA_Cmd( DMA1_Channel7, DISABLE );                         											// �ر�DMAͨ��7
	DMA_DeInit( DMA1_Channel7 );                                		 								// �ָ�DMAͨ������ȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t )( &USART2 -> DR );				// ���ô��ڷ������ݼĴ�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = ( uint32_t )LumMod_Tx_Buf;         									// ���÷������ݻ������׵�ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                      				// �������ݴ��䷽�� ˫���� �ڴ滺���� -> ����Ĵ���
	DMA_InitStructure.DMA_BufferSize = LUMMOD_TX_BSIZE;                     				// ��Ҫ���͵��ֽ��� �����������Ϊ0 ʵ��Ҫ��������ʱ���������ô�ֵ
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        				// �����������ģʽ ��Ϊ��ͨ��ֻ����һ������ ���Բ���Ҫ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 				// ����DMA�ڴ滺������ַ����ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 				// �������ݿ��Ϊ8λ 1���ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         				// �ڴ����ݿ��Ϊ8λ 1���ֽ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           				// ����DMA���䷽ʽ ���δ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 				// ���ȼ���Ϊ�ܸ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            				// �ر��ڴ浽�ڴ��DMA��ʽ
	DMA_Init( DMA1_Channel7, &DMA_InitStructure ); 																	// DMAͨ����ʼ��
	
	DMA_ClearFlag( DMA1_FLAG_GL7 );        						// ���DMA���б�־
	DMA_Cmd( DMA1_Channel7, DISABLE ); 								// ʧ��DMA
	DMA_ITConfig( DMA1_Channel7, DMA_IT_TC, ENABLE ); // ��������DMA�ж�  

	/*--- LUMMOD_UART_Rx_DMA_Channel DMA Config ---*/
	DMA_Cmd( DMA1_Channel6, DISABLE );                           										// �ر�DMAͨ��6
	DMA_DeInit( DMA1_Channel6 );                                 										// �ָ�DMAͨ������ȱʡֵ
	DMA_InitStructure.DMA_PeripheralBaseAddr = LUMMOD_UART_DR_Base;									// ���ô��ڽ������ݼĴ�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = ( uint32_t )LumMod_Rx_Buf;         			// ���ý������ݻ������׵�ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      				// �������ݴ��䷽�� ˫���� ����Ĵ��� -> �ڴ滺����
	DMA_InitStructure.DMA_BufferSize = LUMMOD_RX_BSIZE;                     				// �����������ֽ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        				// �����������ģʽ ��Ϊ��ͨ��ֻ����һ������ ���Բ���Ҫ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 				// ����DMA�ڴ滺������ַ����ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 				// �������ݿ��Ϊ8λ 1���ֽ�
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         				// �ڴ����ݿ��Ϊ8λ 1���ֽ�
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           				// ����DMA���䷽ʽ ���δ���ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 				// ���ȼ���Ϊ�ܸ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            				// �ر��ڴ浽�ڴ��DMA��ʽ
	DMA_Init( DMA1_Channel6, &DMA_InitStructure );  																// DMAͨ����ʼ��
	
	DMA_ClearFlag( DMA1_FLAG_GL6 );       // ���DMA���б�־                     			
	DMA_Cmd( DMA1_Channel6, ENABLE ); 	  // ����DAM����ͨ�� �ȴ���������   
}


/**
  * @brief  DMA1 -> CH7 USART2�����������DMA�жϴ���
  * @param  None
  * @retval None
  */
void LumMod_Uart_DAM_Tx_Over( void )
{
	DMA_ClearFlag( DMA1_FLAG_GL7 );      // �����־λ
	DMA_Cmd( DMA1_Channel7, DISABLE );   // �ر�DMAͨ��
	DMA1_Channel7 -> CNDTR = 0; 				 // ������ݳ���
//	OSMboxPost( mbLumModule_Tx, ( void * ) 1 );       // ���ñ�־λ
}
/**
  * @brief  USART2Ҫ�������ݴ���
  * @param  None
  * @retval None
  */
u16 LumMod_Cmd_WriteParam( u16 sample_num, u8 *psz_param )
{
//	uint err;
	uint LumMod_Tx_Index ;
	
	if( !sample_num ) //�ж����ݳ����Ƿ���Ч
		return 0;
  while ( DMA_GetCurrDataCounter( DMA1_Channel7 ) );//���DMAͨ�����Ƿ�������
	if( psz_param )
		memcpy( LumMod_Tx_Buf, psz_param, ( sample_num > 1024 ? 1024 : sample_num ) );
	LumMod_Tx_Index = 0;
	LumMod_Tx_Buf[ LumMod_Tx_Index++ ] = 1;
	LumMod_Tx_Buf[ LumMod_Tx_Index++ ] = 2;
	LumMod_Tx_Buf[ LumMod_Tx_Index++ ] = 3;
	LumMod_Tx_Buf[ LumMod_Tx_Index++ ] = 4;
	LumMod_Tx_Buf[ LumMod_Tx_Index++ ] = 5;
	LumMod_Tx_Buf[ LumMod_Tx_Index++ ] = 6;
	LumMod_Tx_Buf[ LumMod_Tx_Index++ ] = 7;
	LumMod_Tx_Buf[ LumMod_Tx_Index++ ] = 8;

	LumMod_Uart_Start_DMA_Tx( LumMod_Tx_Index );
//	OSMboxPend( mbLumModule_Tx, 0, &err );
	return sample_num;	
}
/**
  * @brief  USART1Ҫ���������ֽ���Ŀ����DMA������DMA����
  * @param  None
  * @retval None
  */
void LumMod_Uart_Start_DMA_Tx ( uint16_t size )
{
	DMA1_Channel7 -> CNDTR = ( uint16_t )size; // ����Ҫ���͵��ֽ���Ŀ
	DMA_Cmd( DMA1_Channel7, ENABLE );        	 // ����DMA����
}

/**
  * @brief  DMA1 -> CH3 USART1�����������DMA�ж����
  * @param  None
  * @retval None
  */
void LumMod_Uart_DMA_Rx_Data( void )
{
	DMA_Cmd( LUMMOD_UART_Rx_DMA_Channel, DISABLE );	// �ر�DMA��ֹ����
	DMA_ClearFlag( LUMMOD_UART_Rx_DMA_FLAG );     	// ���DNA��־λ
	LumMod_Rx_Data_index = LUMMOD_RX_BSIZE - DMA_GetCurrDataCounter( DMA1_Channel3 ); //��ý��յ��ֽ���
	LUMMOD_UART_Rx_DMA_Channel -> CNDTR = LUMMOD_RX_BSIZE;	// �������ü���ֵ ������ڵ��ڿ��ܽ��յ�������֡��Ŀ 
	DMA_Cmd( LUMMOD_UART_Rx_DMA_Channel, ENABLE );					//DMA���� �ȴ����ݽ���
/**
	*����жϷ�������֡�����ʺܿ� MCu����������˴��жϽ��յ����� �ж��ַ����µ����� ���ﲻ�ܿ��� �������ݻᱻ����
	*��һ�����ֽ������
	*1 - ���¿���DMA��������֮ǰ ��LumMod_Rx_Buf�����������ݸ��Ƶ���һ�������� �ٿ���DMA Ȼ�����ϴ��������е�����
	*2 - ����˫���� ��LumMod_Uart_DMA_Rx_Data()������ ��������DMA_MemoryBaseAddr�Ļ�������ַ  ��ô�´ν��յ�������
	*		 �ᱻ���浽�µĻ����� ���ᱻ����
	*/	
//	OSMboxPost( mbLumModule_Rx,  LumMod_Rx_Buf ); // 
}
