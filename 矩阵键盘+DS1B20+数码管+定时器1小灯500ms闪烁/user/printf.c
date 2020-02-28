/**
  ******************************************************************************
  * @file    传感器模块测试程序/LCD12864/LCD12864_main.c 
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	printf() 输出打印函数
  *
  ******************************************************************************
  */ 
#include "printf.h"

/*******************************************************************************
* Function Name  : fputc
* Description    : 重定向printf() 函数
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
int fputc( int ch, FILE *f )
{
	USART2 -> SR;  //USART_GetFlagStatus( USART1, USART_FLAG_TC ) 解决第一个字符发送失败的问题
	USART_SendData( USART2, ( unsigned char ) ch ); 	//顺序发送字符
	while( USART_GetFlagStatus( USART2, USART_FLAG_TC )!= SET );	//等待发送完成
	
	return( ch );
}
/*******************************************************************************
* Function Name  : fgetc
* Description    : 重定向scanf() 函数
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
int fgetc( FILE *f )
{
	
	while ( USART_GetFlagStatus( USART3, USART_FLAG_RXNE ) == RESET ); //等待串口1输入数据

	return (int)USART_ReceiveData( USART3 );
}
