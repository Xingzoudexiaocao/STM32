/**
  ******************************************************************************
  * @file   ϵͳ�δ�ʱ����ȷ��ʱ/delay();
  * @author  Jerry01
  * @version V1.0
  * @date    10-03-2019
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
#include <SC32F5832.h>
#include <DevInit.h>
#include "delay.h"
/**
  * @brief  ʵ��us��ȷ��ʱ
  * @param  None
  * @retval None
  */
void ST_delay_us( uint32_t nus )
{
	uint32_t temp;
	
	CHIPKEY_ENABLE;
	CHIPCTL -> CLKCFG1_b.SYSTICKSEL = 2;// systickʱ��Դѡ��rch16M��16��Ƶ

	SysTick -> LOAD = 1  * nus;	// 1Mhz��Ϊ1us
	SysTick -> VAL = 0x00ul;//��ռ�����
	SysTick -> CTRL = 0x01ul;//ʹ�� ���������޶��� �����ڲ�ʱ��Դ  
	
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
void ST_delay_ms( uint16_t nms )
{
	uint32_t temp;
	
	CHIPKEY_ENABLE;
	CHIPCTL -> CLKCFG1_b.SYSTICKSEL = 2;// systickʱ��Դѡ��rch16M��16��Ƶ
	
	SysTick -> LOAD = 1000 * nms;
	SysTick -> VAL = 0x00ul;//��ռ�����
	SysTick -> CTRL = 0x01ul;//ʹ�� ���������޶��� �����ڲ�ʱ��Դ  
	do
	{
		temp=SysTick -> CTRL;////��ȡ��ǰ������ֵ
	}while( ( temp & 0x01 ) && ( !( temp & ( 1 << 16 ) ) ) );//�ȴ�ʱ�䵽��
	
	SysTick -> CTRL = 0x00; //�رռ�����
	SysTick -> VAL = 0X00; //��ռ�����
}
