/**
  ******************************************************************************
  * @file    printf.c ��ӡ��������ض���
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	printf() �����ӡ����
  *
  ******************************************************************************
  */

#include <SC32F5832.h>
#include <DevInit.h>
#include "printf.h"
#include "UART.h"

/*******************************************************************************
* Function Name  : 
* Description    : ȡ��ARM�İ���������ģʽ
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
* Description    : �ض���printf() ����
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
int fputc( int ch, FILE *f )
{
	
	
	UART0 -> UARTDR = ch;
	while( UART0 -> UARTFR_b.TXFE != 1 );	//�ȴ��������
//	USART3 -> SR;  //USART_GetFlagStatus( USART1, USART_FLAG_TC ) �����һ���ַ�����ʧ�ܵ�����
//	USART_SendData( USART3, ( unsigned char ) ch ); 	//˳�����ַ�
//	while( USART_GetFlagStatus( USART3, USART_FLAG_TC )!= SET );	//�ȴ��������
	return( ch );
}
/*******************************************************************************
* Function Name  : fgetc
* Description    : �ض���scanf() ����
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
//int fgetc( FILE *f )
//{
//	
////	while ( USART_GetFlagStatus( USART3, USART_FLAG_RXNE ) == RESET ); //�ȴ�����1��������

////	return (int)USART_ReceiveData( USART3 );
//}
