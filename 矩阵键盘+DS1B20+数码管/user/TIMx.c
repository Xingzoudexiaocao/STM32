/**
  ******************************************************************************
  * @file    ������ģ����Գ���
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention ��ȷ���������� �ɵ����������Ƶ�ʺ�ռ�ձ�
  *												
	*							
	*							
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/	
#include "TIMx.h"

/**
  * @brief  TIM1 / TIM2 ����
  * @param  None
  * @retval None
  */
/****************************
**TIM1 -> CH1 ʹ�õ�����ģʽ
**TIM2 -> CH1( PA0 ) ʹ���ſط�ʽ���PWM 
**TIM2 -> CH2( PA1 ) ʹ���ſط�ʽ���PWM
**TIM2 -> CH3( PA2 ) ʹ���ſط�ʽ���PWM
****************************/
//TIM2per: ��װ��ֵ
//Compare1: �Ƚϲ���1��Ԥװ��ֵ
void Motor_Init( u16 TIM1per, u16 TIM2per, u16 TIM2Compare1 )
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
	//TIM1�����ڵ�����ģʽ��
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;//ʱ����Ԫ�ṹ��
  TIM_OCInitTypeDef	TIM_OCInitStructure;//����ȽϽṹ��
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;//��������
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE ); 	//������ʱ��1ʱ��
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2, ENABLE ); 	//������ʱ��2ʱ��
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );	//ʹ��GPIOAʱ��
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); 	//ʹ�ܸ��ù���ʱ��
  
 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_8;//PA0 / PA1 / PA2 / PA8
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( GPIOA, &GPIO_InitStruct );

	//TIM1�����ڵ�����ģʽ��
	TIM_InternalClockConfig( TIM1 ); //SMS =000�����ڲ�ʱ�Ӹ�TIM1�ṩʱ��Դ( TIMxCLK -> CK_INT -> CK_PSC -> CK_CNT )
	TIM_TimeBaseStructure.TIM_Prescaler = 7200; //PSC Ԥ��Ƶϵ��Ϊ72MHz / 7200,����װ��,ÿ100us����һ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ; //���ü���ģʽΪ���ϼ���
	TIM_TimeBaseStructure.TIM_Period = TIM1per; //ARR ���ü��������СTIM2per,ÿTIM2per����������һ�������¼�
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷ�Ƶ����( CK_INT -> �����˲���( ETR/TIx )��������˲�Ƶ�� )
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //�ظ�����趨������Ų����ж�
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseStructure );
	
	TIM_SelectOnePulseMode( TIM1, TIM_OPMode_Single );//����TIM1Ϊ������ģʽ
  TIM_OC1PreloadConfig( TIM1, TIM_OCPreload_Enable );//ʹ��TIM1 -> CH1 Ԥװ�ؼĴ���
	TIM_SelectMasterSlaveMode( TIM1,TIM_MasterSlaveMode_Enable );//ʹ��TIM1������ģʽ
  TIM_SelectOutputTrigger( TIM1, TIM_TRGOSource_OC1Ref );//ѡ�񴥷�Դ
	
	//----------------------------����Ƚϲ���PWM-----------------------------------------
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//�����ϼ���ʱ, һ��TIMx_CNT < TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ,����Ϊ��Ч��ƽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ѡ������Ƚ�״̬ CH1ͨ����Ч
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Enable;//ѡ�񻥲�����Ƚ�״̬ CH1Nͨ����Ч
	TIM_OCInitStructure.TIM_Pulse = 1;//ռ�ձ�TIMx_CCR1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//�������Ϊ�ߵ�ƽ
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//�����������
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//ѡ�����״̬�µķǹ���״̬
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;//ѡ�����״̬�µķǹ���״̬
	TIM_OC1Init( TIM1, &TIM_OCInitStructure );//��ͨ��1(TIM1_CH1)���г�ʼ��
	
	//---------------------------------BDTR����--------------------------------------------
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF; //�������� ������
	TIM_BDTRInitStructure.TIM_DeadTime = 0;  //����������С 0-0xff
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;//����ģʽ������
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High; //���е�ƽ���Ը�
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable; //�Զ����ʹ��
	TIM_BDTRConfig( TIM1, &TIM_BDTRInitStructure );

	TIM_CtrlPWMOutputs( TIM1, ENABLE );//TIM1_OCx ͨ�����PWM /*ע�⣺����ȱ��*/
	TIM_ClearFlag( TIM1, TIM_FLAG_Update ); //�������жϱ�־λ
	TIM_Cmd( TIM1, DISABLE );//�ȹر�TIM1
  
  //TIM2�����ڴ�ģʽ���ſ�ģʽ�µ�PWM���ģʽ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//û��ʱ�ӷָ�
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_Prescaler = 720;//����Ԥ��Ƶֵ��ÿ10us����һ��
  TIM_TimeBaseStructure.TIM_Period = TIM2per;//��װ��ֵ
  TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure );
  
  TIM_SelectSlaveMode( TIM2, TIM_SlaveMode_Gated );//TIM2Ϊ�ſ�ģʽ
	TIM_SelectMasterSlaveMode( TIM2,TIM_MasterSlaveMode_Enable );//ʹ��TIM2������ģʽ
	TIM_OC1PreloadConfig( TIM2, TIM_OCPreload_Enable );//ʹ��TIM2Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig( TIM2, TIM_OCPreload_Enable );//ʹ��TIM2Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig( TIM2, TIM_OCPreload_Enable );//ʹ��TIM2Ԥװ�ؼĴ���
  TIM_SelectInputTrigger( TIM2, TIM_TS_ITR0 );//�ڲ�����,��TIM1����
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//���ϼ���ʱ,һ��TIMx_CNT < TIMx_CCR1 CH1Ϊ��Ч��ƽ,����Ϊ��Ч��ƽ
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//���ʹ��
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч��ƽΪ��
	
  TIM_OCInitStructure.TIM_Pulse = TIM2Compare1;//�������1��Ԥװ��ֵ
  TIM_OC1Init( TIM2, &TIM_OCInitStructure );//TIM2 -> CH1 ��ʼ��
	
	TIM_OCInitStructure.TIM_Pulse = TIM2Compare1;//�������2��Ԥװ��ֵ
	TIM_OC2Init( TIM2, &TIM_OCInitStructure );//TIM2 -> CH2 ��ʼ��
	
	TIM_OCInitStructure.TIM_Pulse = TIM2Compare1;//�������1��Ԥװ��ֵ
	TIM_OC3Init( TIM2, &TIM_OCInitStructure );//TIM2 -> CH3 ��ʼ��
	
  TIM_Cmd( TIM2, ENABLE );//ʹ��TIM2
  
}


//����PWM�����
//Cycle:Ϊ����,��λΪ(us)
//Pulse_Num:Ϊ�������(С��3200)
void TIM1_TIM2_PWM( u16 Cycle,u16 Cycle1,u16 Cycle2,u16 Pulse_Num,u16 Pulse_Num1,u16 Pulse_Num2 )
{
  u16 TIM2per = 0;
	u16 TIM2per1 = 0;
	u16 TIM2per2 = 0;
  u32 Time = 0;
  //����TIM2����װ��ֵ�ı�����Ƶ��, ��������ռ�ձ�Ϊ50%
  //����TIM1Ԥ��Ƶֵ����װ��ֵ�ı��������
    
	if(Cycle!=0)
	{
  Time = Cycle * Pulse_Num;
  Time /= 100;              //Ԥ��ƵֵΪ7200,100us����һ��
  TIM2per = Cycle / 10;     //Ԥ��ƵֵΪ720,10us����һ��
	}	
	if(Cycle1!=0)
	{
  Time = Cycle1 * Pulse_Num1;
  Time /= 100;              //Ԥ��ƵֵΪ7200,100us����һ��
  TIM2per1 = Cycle1 / 10;     //Ԥ��ƵֵΪ720,10us����һ��
	}		
	if(Cycle2!=0)
	{
  Time = Cycle2 * Pulse_Num2;
  Time /= 100;              //Ԥ��ƵֵΪ7200,100us����һ��
  TIM2per2 = Cycle2 / 10;     //Ԥ��ƵֵΪ720,10us����һ��
	}			
  
  TIM_SetAutoreload( TIM1, Time + 1 );//����TIM1����װ��ֵ
  TIM_SetAutoreload( TIM2, TIM2per - 1 );//����TIM2����װ��ֵ
  TIM_SetCompare1( TIM2,TIM2per / 2 );//����TIM2 -> ռ�ձ�Ϊ50%
	TIM_SetCompare2( TIM2,TIM2per1 / 2 );//����TIM2 -> ռ�ձ�Ϊ50%
	TIM_SetCompare3( TIM2,TIM2per2 / 2 );//����TIM2 -> ռ�ձ�Ϊ50%
  TIM_Cmd( TIM1, ENABLE );//ʹ��TIM1
}

/**
  * @brief  TIM3 ��ʱ������
  * @param  None
  * @retval None
  */
void TIM3_Configuration( void )
{
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;//ʱ����Ԫ�ṹ��
//	TIM_ICInitTypeDef  TIM_ICInitStructure;//���벶��ṹ��
  TIM_OCInitTypeDef	TIM_OCInitStructure;//����ȽϽṹ��
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM3, ENABLE );//����TIM3ʱ��
	
	TIM_InternalClockConfig( TIM3 ); //SMS =000�����ڲ�ʱ�Ӹ�TIM2�ṩʱ��Դ( TIMxCLK -> CK_INT -> CK_PSC -> CK_CNT )
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //PSC Ԥ��Ƶϵ��Ϊ900 - 1,����ʱ��Ƶ��:72MHz / 450 = 160KHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ; //���ü���ģʽΪ���ϼ���
	TIM_TimeBaseStructure.TIM_Period = 4 - 1; //ARR ���ü��������С5 - 1,ÿ5����������һ�������¼�( 40KHz )
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷ�Ƶ����( CK_INT -> �����˲���( ETR/TIx )��������˲�Ƶ�� )
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseStructure );
	TIM_PrescalerConfig( TIM3, 450 - 1, TIM_PSCReloadMode_Immediate ); //PSC Ԥ��Ƶϵ��Ϊ360,����װ��
	
//----------------------------����Ƚϲ���PWM-----------------------------------------
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//PWM1ģʽ�����ض���ģʽ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//CH3ͨ����Ч
	TIM_OCInitStructure.TIM_Pulse = 2;//ռ�ձ�TIMx_CCR1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	//�������Ϊ�͵�ƽ
	TIM_OC3Init( TIM3, &TIM_OCInitStructure );//��ͨ��3(TIM3_CH3)���г�ʼ��

//----------------------------���벶��--------------------------------------------------

//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;// Channel_4 ���벶��ѡ��ͨ��4
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //�����ش���
//  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  //Direct connecte
//  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//register every rising edages
//  TIM_ICInitStructure.TIM_ICFilter = 0x05;//�˲�����
//  TIM_ICInit( TIM3, &TIM_ICInitStructure );
	
//------------------------------------------------------------------------------------		
//	TIM_SelectInputTrigger( TIM3, TIM_TS_TI2FP2 );//ѡ�����봥��Դ
//	TIM_SelectSlaveMode( TIM3, TIM_SlaveMode_Reset );//������ʽ
//	TIM_SelectMasterSlaveMode( TIM3, TIM_MasterSlaveMode_Enable );//������ʱ���ı�������
//------------------------------------------------------------------------------------	

//	TIM_SetCompare4( TIM3, 0 );//���ò��������( TIMx_CCR4 )��ֵΪ0
//	TIM_ClearITPendingBit(TIM3, TIM_IT_Update );//�����ʱ������жϱ�־λ
//  TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);//��������жϱ�־λ
////	TIM_ClearFlag( TIM3, TIM_FLAG_Update );//���TIM3�����־
//	TIM_ITConfig( TIM3, TIM_IT_Update, ENABLE );//TIM3����ж�����	
//	TIM_ITConfig( TIM3, TIM_IT_CC4, ENABLE );//�򿪲��������ж�

	TIM_Cmd( TIM3, ENABLE );//������ʱ��3 PWM�������
		
}
/**
  * @brief  TIM4 ��ʱ������
  * @param  None
  * @retval None
  */
void TIM4_Configuration( void )
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //����TIM��ʼ���ṹ�����
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );//����TIM4ʱ��
	
	TIM_DeInit( TIM4 ); //��TIM�Ĵ�������Ϊȱʡֵ
	TIM_InternalClockConfig( TIM4 ); //SMS =000�����ڲ�ʱ�Ӹ�TIM4�ṩʱ��Դ( TIMxCLK( 72MHz ) -> CK_INT -> CK_PSC -> CK_CNT )
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //PSC Ԥ��Ƶϵ��Ϊ3600 - 1,����ʱ��Ƶ��:72MHz / 7200 = 10KHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷ�Ƶ����( CK_INT -> �����˲���( ETR/TIx )��������˲�Ƶ�� )
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ü���ģʽΪ���ϼ���
	TIM_TimeBaseStructure.TIM_Period = 3000 - 1; //ARR ���ü��������С100 - 1,ÿ10000����������һ�������¼�
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure); //������Ӧ�õ�TIM��

	TIM_PrescalerConfig( TIM4, 7200 - 1, TIM_PSCReloadMode_Immediate ); //PSC Ԥ��Ƶϵ��Ϊ7200,����װ��
	
	TIM_ClearFlag( TIM4, TIM_FLAG_Update ); //�������жϱ�־λ
	TIM_ARRPreloadConfig( TIM4, DISABLE ); //��ֹARRԤװ�ػ�����
	TIM_ITConfig( TIM4, TIM_IT_Update, ENABLE ); //����TIM4�ж�

}
