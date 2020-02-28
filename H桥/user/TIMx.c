/**
  ******************************************************************************
  * @file    ������ģ����Գ���
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention ��ȷ���������� �ɵ����������Ƶ�ʺ�ռ�ձ�
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/	
#include "TIMx.h"
void Tim1_Init(u16 arr , u16 psc)
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;//ʱ����Ԫ�ṹ��
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE ); 	//������ʱ��1ʱ��
	
	//TIM1�����ڵ�����ģʽ��
	TIM_InternalClockConfig( TIM1 ); //SMS =000�����ڲ�ʱ�Ӹ�TIM1�ṩʱ��Դ( TIMxCLK -> CK_INT -> CK_PSC -> CK_CNT )
	TIM_TimeBaseStructure.TIM_Prescaler = arr; //PSC Ԥ��Ƶϵ��Ϊ72MHz / 7200,����װ��,ÿ100us����һ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ; //���ü���ģʽΪ���ϼ���
	TIM_TimeBaseStructure.TIM_Period = psc; //ARR ���ü��������СTIM2per,ÿTIM2per����������һ�������¼�
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷ�Ƶ����( CK_INT -> �����˲���( ETR/TIx )��������˲�Ƶ�� )
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //�ظ�����趨������Ų����ж�
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseStructure );
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_Cmd( TIM1, ENABLE );
}
