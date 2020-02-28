/**
  ******************************************************************************
  * @file    ������ģ����Գ���/delay();
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	
  *							SYSTICK ���жϷ�ʽʵ�־�ȷ��ʱ 	SYSTICKʱ�ӹ̶�ΪHCLK��ʱ��1/8					
	*							ѡ���ڲ�ʱ��Դ72M ����SYSTICK��ʱ��Ϊ9M ��SYSTICK��ʱ����9M��Ƶ�ʵݼ�
	*							SysTick ��Ҫ����CTRL LOAD VAL CALIB 4���Ĵ���
	*
	*
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/	
#include "delay.h"
/**
  * @brief  ʵ��us��ȷ��ʱ
  * @param  None
  * @retval None
  */
void delay_us( u32 nus )
{
	u32 temp;
	SysTick -> LOAD = 9 * nus;
	SysTick -> VAL = 0X00;//��ռ�����
	SysTick -> CTRL = 0X01;//ʹ�� ���������޶��� �����ⲿʱ��Դ
	
	do
	{
		temp = SysTick -> CTRL;//��ȡ��ǰ������ֵ
	}while( ( temp & 0x01 ) && ( ! ( temp & ( 1 << 16 ) ) ) );//�ȴ�ʱ�䵽��
	
	SysTick -> CTRL = 0x00; //�رռ�����
	SysTick -> VAL = 0X00; //��ռ�����
}
/**
  * @brief  ʵ��ms��ȷ��ʱ
  * @param  None
  * @retval None
  */
void delay_ms( u16 nms )
{
	u32 temp;
	SysTick -> LOAD = 9000 * nms;
	SysTick -> VAL = 0X00;//��ռ�����
	SysTick -> CTRL = 0X01;//ʹ�� ���������޶��� �����ⲿʱ��Դ
	do
	{
		temp=SysTick -> CTRL;////��ȡ��ǰ������ֵ
	}while( ( temp & 0x01 ) && ( !( temp & ( 1 << 16 ) ) ) );//�ȴ�ʱ�䵽��
	
	SysTick -> CTRL = 0x00; //�رռ�����
	SysTick -> VAL = 0X00; //��ռ�����
}
