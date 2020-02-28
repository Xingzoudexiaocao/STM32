/**
* @file          : ETIMER.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for ETIMER module configuration.
* @version       : Ver. 1.00

* H/W Platform   : SL_FOC FOR MOTOR CONTROL

*------------------------------------------------------------------------------
 
* Compiler info  : Keil v5.20
 
*------------------------------------------------------------------------------
 
* Note: In this software, the function is used in motor control.

*------------------------------------------------------------------------------

*  History:  

*              mm/dd/yyyy ver. x.y.z author

*              mm1/dd1/yyyy1 ver. x.y.z author1

*------------------------------------------------------------------------------
* @attention
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, SLMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.

* <h2><center>&copy; COPYRIGHT 2017 SLMicroelectronics</center></h2>
*******************************************************************************
*/

/*******************************************************************
���ļ�����ͨ�����벶���ܺ͵�ͨ��PWM���Ϊ����չʾ��TIMER0�ĳ�ʼ�����ù��̡�
**********************************************************************/

#include <SC32F5832.h>
#include <DevInit.h>


/**********************************************************************
				��TIMER0����Ϊ���벶���ܣ���������������źŲ���
**********************************************************************/
/**
  * @brief      .
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * T0_Init_CAP();
  * @endcode
  * @warning:
*/

void T0_Init_CAP(void)
{
	

	TIM_ARPE_ENABLE;  // ���ڼ���Ԥװ������λ��TIM_ARR �Ĵ����л���
	TIMER0->TIM_CCMR1|=	CC2S_INPUT_IC2_To_TI2;  // ��׽ / �Ƚ� 2 ѡ��CC2 ͨ��������Ϊ���룬IC2 ӳ���� TI2 �ϣ�
	TIMER0->TIM_CCMR1|=	CC1S_INPUT_IC1_To_TI1;  // ��׽ / �Ƚ� 1 ѡ��CC1 ͨ��������Ϊ���룬IC1 ӳ���� TI1 �ϣ�
	TIMER0->TIM_CCMR2|=	CC3S_INPUT_IC3_To_TI3;  // ��׽ / �Ƚ� 3 ѡ��CC3 ͨ��������Ϊ���룬IC3 ӳ���� TI3 �ϣ�

	
	TIMER0->TIM_CCER_b.CC3P = 1;  // ��׽/�Ƚ�3������ԣ���·������ TI3FP1 �������غ��½���
	TIMER0->TIM_CCER_b.CC3NP = 1;
	TIMER0->TIM_CCER_b.CC2P = 1;  // ��׽/�Ƚ�2������ԣ���·������ TI2FP1 �������غ��½���
	TIMER0->TIM_CCER_b.CC2NP = 1;
	TIMER0->TIM_CCER_b.CC1P = 1;  // ��׽/�Ƚ�1������ԣ���·������ TI1FP1 �������غ��½���
	TIMER0->TIM_CCER_b.CC1NP = 1;

	
	TIMER0->TIM_CCER_b.CC1E = CC1E_ENABLE;  // ��׽/�Ƚ�1���ʹ��
	TIMER0->TIM_CCER_b.CC2E = CC2E_ENABLE;  // ��׽/�Ƚ�2���ʹ��
	TIMER0->TIM_CCER_b.CC3E = CC3E_ENABLE;  // ��׽/�Ƚ�3���ʹ��

	
//	TIMER0->TIM_DIER_b.UIE = UIE_ENABLE;	  // ʹ�ܸ����¼��ж�
	TIMER0->TIM_DIER_b.CC1IE = CC1IE_ENABLE;	// ��׽ / �Ƚ� 1 �ж�ʹ��
	TIMER0->TIM_DIER_b.CC2IE = CC2IE_ENABLE;	// ��׽ / �Ƚ� 2 �ж�ʹ��
	TIMER0->TIM_DIER_b.CC3IE = CC3IE_ENABLE;	// ��׽ / �Ƚ� 3 �ж�ʹ��


	TIMER0->TIM_ARR = 10000;			// �Լ������ڼĴ�����ֵ
	TIMER0->TIM_ISR|= CNT_CLR_ENABLE;			// ������������0ʹ��
	TIMER0->TIM_ISR|= CNT_CLR_SEL_CH1;			// ������������0ѡ��ͨ��1����ʱ��0
	CNT_ENABLE; 			// ʹ�ܼ����� 

}
/**
  * @brief      .
  * @param[in]  void : PRD,DB_CFG
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * T0_Init_PWM(uint32_t PRD,uint32_t DB_CFG)
  * @endcode
  * @warning:
*/

/***************************************************************************
			��TIMER0����ΪPWM�������
****************************************************************************/

void T0_Init_PWM(uint32_t PRD,uint32_t DB_CFG)
{

	TIMER0->TIM_CCMR1|= OC1M_PWM_MODE1;     // OC1M   CH1ѡ��PWMģʽ1
	TIMER0->TIM_CCMR1|= OC1PE_PRELOAD_ENABLE;     // OC1PE  ���� TIM_CCR1 �Ĵ�����Ԥװ�ع���
	TIM_ARPE_ENABLE;    // ���ڼ���Ԥװ������λ��TIM_ARR �Ĵ����л���
	
	     
	TIMER0->TIM_CCER_b.CC1E = CC1E_ENABLE;   // ��׽/�Ƚ�1���ʹ��
	TIMER0->TIM_CCER_b.CC1NE = CC1NE_ENABLE;  // ��׽/�Ƚ� 1 �������ʹ��
	TIMER0->TIM_CCER_b.CC1P = CC1P_OUTPUT_HIGH;   // ��׽/�Ƚ�1������ԣ�OC1 �ߵ�ƽ��Ч��
	TIMER0->TIM_CCER_b.CC1NP = CC1NP_OUTPUT_HIGH;  // ��׽/�Ƚ�1����������ԣ�OC1N �ߵ�ƽ��Ч��
	TIMER0->TIM_ARR = PRD;	       // PWM 10kHz
	TIMER0->TIM_BDTR_b.MOE = MOE_ENABLE;    // �����ʹ��
	TIMER0->TIM_BDTR_b.AOE = AOE_SW_SET;
	TIMER0->TIM_BDTR_b.OSSR = 0;   // ����ģʽ�¡��ر�״̬��ѡ��
	TIMER0->TIM_BDTR_b.DTG = DB_CFG;  // 196 �������� OC1�����غ���ʱ2us���������òο��Ĵ���˵��
	TIMER0->TIM_DTG1 = DB_CFG;				 // 196 �������� OC1N�½��غ���ʱ2us���������òο��Ĵ���˵��
	TIMER0->TIM_CCR1 = 1800;	     // ռ�ձ�����
	TIMER0->TIM_CR1_b.CMS = CMS_CENTER_MODE3;     // �������ģʽ 3
	EGR_CNT_UPDATE;		 // ���³�ʼ����������������һ�� ( �Ĵ��� ) �����¼�
	CNT_ENABLE;    // ʹ�ܼ�����

	
/*************************************************************************
			ɲ������
************************************************************************/

	
	
	TIMER0->TIM_BDTR_b.BKE = BKE_BRAKE_ENABLE;    // ɲ��ʹ��
	TIMER0->TIM_BDTR_b.BKP = BKP_BRAKE_POL_LOW;		 // ɲ������Ϊ�͵�ƽ��Ч
	TIMER0->TIM_BDTR_b.OSSI = 0;   // ����ģʽ�¡�����״̬��ѡ��
	TIMER0->TIM_CR2_b.OIS1 = OIS1_OC1_AFTER_DT_LOW;    // �������״̬ 1(OC1 ��� ) 
	TIMER0->TIM_CR2_b.OIS1N = OIS1N_OC1N_AFTER_DT_LOW;   // �������״̬ 1(OC1N ��� ) 

}
/**
  * @brief      .
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * T0_PWM_MEASURE();
  * @endcode
  * @warning:
*/

/**********************************************************************
			PWM����ģʽ
**********************************************************************/

void T0_PWM_MEASURE(void)
{
	
	TIM_ARPE_ENABLE;																				// Ԥװ��ʹ��
	TIMER0->TIM_ARR = 0xffff;
	
	TIMER0->TIM_CCMR1|=	CC1S_INPUT_IC1_To_TI1;							// CC1Sͨ��ӳ�䵽TI1
	TIMER0->TIM_CCMR1|= CC2S_INPUT_IC2_To_TI1;							// CC2Sͨ��ӳ�䵽TI2
	
	TIMER0->TIM_CCER_b.CC1P = 0;														// ����ѡ��������
	TIMER0->TIM_CCER_b.CC2P = 1;
	
	TIMER0->TIM_SMCR_b.TS = TS_TI1FP1;											// �����ź�ѡ��
	TIMER0->TIM_SMCR_b.SMS = SMS_RESET_MODE;								// ��ģʽѡ��λģʽ
	
	TIMER0->TIM_CCER_b.CC1E = CC1E_ENABLE;									// 1ͨ��ʹ��
	TIMER0->TIM_CCER_b.CC2E = CC2E_ENABLE;									// 2ͨ��ʹ��
	
	EGR_CNT_UPDATE;																					// ����
	CNT_ENABLE;																							// ����������
	
	
}

/**
  * @brief      .
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * T0_ENCODER_MODE();
  * @endcode
  * @warning:
*/

/*************************************************************************
			�������ӿ�ģʽ
*************************************************************************/

void T0_ENCODER_MODE()
{
	
	TIMER0->TIM_CCMR1|= CC2S_INPUT_IC2_To_TI2;  // ��׽ / �Ƚ� 2 ѡ��CC2 ͨ��������Ϊ���룬IC2 ӳ���� TI2 �ϣ�
	TIMER0->TIM_CCMR1|= CC1S_INPUT_IC1_To_TI1;  // ��׽ / �Ƚ� 1 ѡ��CC1 ͨ��������Ϊ���룬IC1 ӳ���� TI1 �ϣ�
//	TIMER0->TIM_CCMR2|= CC3S_INPUT_IC3_To_TI3;  // ��׽ / �Ƚ� 3 ѡ��CC3 ͨ��������Ϊ���룬IC3 ӳ���� TI3 �ϣ�
	TIMER0->TIM_CCER_b.CC1P = 0;
	TIMER0->TIM_CCER_b.CC2P = 0;
	
	TIMER0->TIM_SMCR_b.SMS = SMS_ENCODER_MODE3;					//��ģʽѡ�������ģʽ3
	
	TIMER0->TIM_ARR = 0xffff;
	EGR_CNT_UPDATE;
	CNT_ENABLE;
	
}

/**
  * @brief      .
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * TIM6_T0_Init();
  * @endcode
  * @warning:
*/


/**************************************************************************
			����TIM6ͨ�ö�ʱ��
***************************************************************************/

void TIM6_T0_Init()
{
	TIM6 -> COMPARE0 = 360000;		     // �����Ƚ�ֵ
	TIM6 -> CTC0_b.Freerun = 1;	     // timer��ʹ�ܺ�һֱ����
	TIM6 -> CTC0_b.COUNT0INT_EN = 1; // �ж�ʹ��λ���ߵ�ƽ��Ч
	TIM6 -> CTCSEL0 = 0x08;						 // ����Ƶ
	TIM6 -> CTC0_b.COUNTEN = 1;			 // ʹ�ܣ���ʼ����
}

/**
  * @brief      .
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * TIM6_T1_Init();
  * @endcode
  * @warning:
*/

void TIM6_T1_Init()
{
	TIM6->COMPARE1 = 5000;		     // �����Ƚ�ֵ
	TIM6->CTC1_b.Freerun = 1;	     // timer��ʹ�ܺ�һֱ����
	TIM6->CTC1_b.COUNT0INT_EN = 1; // �ж�ʹ��λ���ߵ�ƽ��Ч
	TIM6->CTCSEL1 = 0;						 // ����Ƶ
	TIM6->CTC1_b.COUNTEN = 1;			 // ʹ�ܣ���ʼ����
}

