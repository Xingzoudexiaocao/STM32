/**
  ******************************************************************************
  * @file    ������ģ����Գ���/LCD12864/LCD12864_main.c 
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	printf() �����ӡ����
  *
  ******************************************************************************
  */ 
#include "printf.h"

/*******************************************************************************
* Function Name  : fputc
* Description    : �ض���printf() ����
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
int fputc( int ch, FILE *f )
{
	USART2 -> SR;  //USART_GetFlagStatus( USART1, USART_FLAG_TC ) �����һ���ַ�����ʧ�ܵ�����
	USART_SendData( USART2, ( unsigned char ) ch ); 	//˳�����ַ�
	while( USART_GetFlagStatus( USART2, USART_FLAG_TC )!= SET );	//�ȴ��������
	
	return( ch );
}
/*******************************************************************************
* Function Name  : fgetc
* Description    : �ض���scanf() ����
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
int fgetc( FILE *f )
{
	
	while ( USART_GetFlagStatus( USART3, USART_FLAG_RXNE ) == RESET ); //�ȴ�����1��������

	return (int)USART_ReceiveData( USART3 );
}
