/**
  ******************************************************************************
  * @file    printf.c 打印输出函数重定向
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	printf() 输出打印函数
  *
  ******************************************************************************
  */

#include <SC32F5832.h>
#include <DevInit.h>
#include "printf.h"
#include "UART.h"

/*******************************************************************************
* Function Name  : 
* Description    : 取消ARM的半主机工作模式
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
#pragma import(__use_no_semihosting)                             
struct __FILE { 
    int handle; 
}; 

FILE __stdout;          
int _sys_exit(int x) 
{ 
    x = x;
 return 0;	
}


/*******************************************************************************
* Function Name  : fputc
* Description    : 重定向printf() 函数
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
int fputc( int ch, FILE *f )
{
	
	
	UART0 -> UARTDR = ch;
	while( UART0 -> UARTFR_b.TXFE != 1 );	//等待发送完成
//	USART3 -> SR;  //USART_GetFlagStatus( USART1, USART_FLAG_TC ) 解决第一个字符发送失败的问题
//	USART_SendData( USART3, ( unsigned char ) ch ); 	//顺序发送字符
//	while( USART_GetFlagStatus( USART3, USART_FLAG_TC )!= SET );	//等待发送完成
	return( ch );
}
/*******************************************************************************
* Function Name  : fgetc
* Description    : 重定向scanf() 函数
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
//int fgetc( FILE *f )
//{
//	
////	while ( USART_GetFlagStatus( USART3, USART_FLAG_RXNE ) == RESET ); //等待串口1输入数据

////	return (int)USART_ReceiveData( USART3 );
//}
