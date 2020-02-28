/**
  ******************************************************************************
  * @file    传感器模块测试程序
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
/* 变量定义 ------------------------------------------------------------------*/
u8 LumMod_Tx_Buf[ 20 ];
u8 LumMod_Rx_Buf[ 20 ];
uint LumMod_Rx_Data_index = 0;
uint LUMMOD_TX_BSIZE = 0;
uint LUMMOD_RX_BSIZE = 0;

/**
  * @brief  USART_DMA_Init USART1 DMA通道配置
  * @param  None
  * @retval None
  */
void USART_DMA_Init( void )
{
	DMA_InitTypeDef DMA_InitStructure;
	
	/* DMA1 clock enable */
	RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE ); //开启DMA1时钟


	/*--- LUMMOD_UART_Tx_DMA_Channel DMA Config ---*/
	DMA_Cmd( DMA1_Channel7, DISABLE );                         											// 关闭DMA通道7
	DMA_DeInit( DMA1_Channel7 );                                		 								// 恢复DMA通道配置缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t )( &USART2 -> DR );				// 设置串口发送数据寄存器地址
	DMA_InitStructure.DMA_MemoryBaseAddr = ( uint32_t )LumMod_Tx_Buf;         									// 设置发送数据缓冲区首地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                      				// 设置数据传输方向 双向传输 内存缓冲区 -> 外设寄存器
	DMA_InitStructure.DMA_BufferSize = LUMMOD_TX_BSIZE;                     				// 需要发送的字节数 这里可以设置为0 实际要发送数据时会重新设置次值
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        				// 设置外设递增模式 因为该通道只连接一个外设 所以不需要递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 				// 设置DMA内存缓冲区地址递增模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 				// 外设数据宽度为8位 1个字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         				// 内存数据宽度为8位 1个字节
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           				// 设置DMA传输方式 单次传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 				// 优先级设为很高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            				// 关闭内存到内存的DMA方式
	DMA_Init( DMA1_Channel7, &DMA_InitStructure ); 																	// DMA通道初始化
	
	DMA_ClearFlag( DMA1_FLAG_GL7 );        						// 清除DMA所有标志
	DMA_Cmd( DMA1_Channel7, DISABLE ); 								// 失能DMA
	DMA_ITConfig( DMA1_Channel7, DMA_IT_TC, ENABLE ); // 开启发送DMA中断  

	/*--- LUMMOD_UART_Rx_DMA_Channel DMA Config ---*/
	DMA_Cmd( DMA1_Channel6, DISABLE );                           										// 关闭DMA通道6
	DMA_DeInit( DMA1_Channel6 );                                 										// 恢复DMA通道配置缺省值
	DMA_InitStructure.DMA_PeripheralBaseAddr = LUMMOD_UART_DR_Base;									// 设置串口接收数据寄存器地址
	DMA_InitStructure.DMA_MemoryBaseAddr = ( uint32_t )LumMod_Rx_Buf;         			// 设置接收数据缓冲区首地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      				// 设置数据传输方向 双向传输 外设寄存器 -> 内存缓冲区
	DMA_InitStructure.DMA_BufferSize = LUMMOD_RX_BSIZE;                     				// 设置最大接收字节数
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        				// 设置外设递增模式 因为该通道只连接一个外设 所以不需要递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 				// 设置DMA内存缓冲区地址递增模式
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 				// 外设数据宽度为8位 1个字节
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         				// 内存数据宽度为8位 1个字节
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                           				// 设置DMA传输方式 单次传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;                 				// 优先级设为很高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            				// 关闭内存到内存的DMA方式
	DMA_Init( DMA1_Channel6, &DMA_InitStructure );  																// DMA通道初始化
	
	DMA_ClearFlag( DMA1_FLAG_GL6 );       // 清除DMA所有标志                     			
	DMA_Cmd( DMA1_Channel6, ENABLE ); 	  // 开启DAM接收通道 等待接收数据   
}


/**
  * @brief  DMA1 -> CH7 USART2发送数据完成DMA中断处理
  * @param  None
  * @retval None
  */
void LumMod_Uart_DAM_Tx_Over( void )
{
	DMA_ClearFlag( DMA1_FLAG_GL7 );      // 清除标志位
	DMA_Cmd( DMA1_Channel7, DISABLE );   // 关闭DMA通道
	DMA1_Channel7 -> CNDTR = 0; 				 // 清除数据长度
//	OSMboxPost( mbLumModule_Tx, ( void * ) 1 );       // 设置标志位
}
/**
  * @brief  USART2要发送数据处理
  * @param  None
  * @retval None
  */
u16 LumMod_Cmd_WriteParam( u16 sample_num, u8 *psz_param )
{
//	uint err;
	uint LumMod_Tx_Index ;
	
	if( !sample_num ) //判断数据长度是否有效
		return 0;
  while ( DMA_GetCurrDataCounter( DMA1_Channel7 ) );//检查DMA通道内是否还有数据
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
  * @brief  USART1要发送数据字节数目高速DMA并开启DMA传输
  * @param  None
  * @retval None
  */
void LumMod_Uart_Start_DMA_Tx ( uint16_t size )
{
	DMA1_Channel7 -> CNDTR = ( uint16_t )size; // 设置要发送的字节数目
	DMA_Cmd( DMA1_Channel7, ENABLE );        	 // 开启DMA发送
}

/**
  * @brief  DMA1 -> CH3 USART1接收数据完成DMA中断入口
  * @param  None
  * @retval None
  */
void LumMod_Uart_DMA_Rx_Data( void )
{
	DMA_Cmd( LUMMOD_UART_Rx_DMA_Channel, DISABLE );	// 关闭DMA防止干扰
	DMA_ClearFlag( LUMMOD_UART_Rx_DMA_FLAG );     	// 清除DNA标志位
	LumMod_Rx_Data_index = LUMMOD_RX_BSIZE - DMA_GetCurrDataCounter( DMA1_Channel3 ); //获得接收的字节数
	LUMMOD_UART_Rx_DMA_Channel -> CNDTR = LUMMOD_RX_BSIZE;	// 重新设置计数值 必须大于等于可能接收到的数据帧数目 
	DMA_Cmd( LUMMOD_UART_Rx_DMA_Channel, ENABLE );					//DMA开启 等待数据接收
/**
	*如果中断发送数据帧的速率很快 MCu来不及处理此次中断接收的数据 中断又发来新的数据 这里不能开启 否则数据会被覆盖
	*有一下两种解决方法
	*1 - 重新开启DMA接收数据之前 将LumMod_Rx_Buf缓冲区的数据复制到另一个数组中 再开启DMA 然后马上处理数组中的数据
	*2 - 建立双缓冲 在LumMod_Uart_DMA_Rx_Data()函数中 重新配置DMA_MemoryBaseAddr的缓冲区地址  那么下次接收到的数据
	*		 会被保存到新的缓冲区 不会被覆盖
	*/	
//	OSMboxPost( mbLumModule_Rx,  LumMod_Rx_Buf ); // 
}
