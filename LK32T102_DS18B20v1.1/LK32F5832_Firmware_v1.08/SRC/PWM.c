/**
* @file          : PWM.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for PWM module configuration.
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

/*************************************************************************
���ļ�չʾ��PWMģ������÷�������ֱ��Ӧ�������ű۵��������SVPWM
**************************************************************************/
#include <SC32F5832.h>
#include <DevInit.h>

/**
  * @brief      .
  * @param[in]  void : Period,DB
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * PWM_CFG(uint32_t Period,uint32_t DB)
  * @endcode
  * @warning:
*/

/************************************************************************
				��ʼ��PWM0-2�����ò���Ϊ��PWM�����ڼ���ֵ����������ֵ
************************************************************************/
void PWM_CFG(uint32_t Period,uint32_t DB)
{	
	
/**************************************************************************
							PWM0
***************************************************************************/	
	PWM0->TBPRD = Period; //Period = 4000TBCLK counts
	PWM0->TBPHS = 0; //Set Phase register to zero
	
	PWM0->TBCTL = 0;
	PWM0_CTRMODE_UPDOWN;	 // �����ݼ�����ģʽ
	PWM0_PHASE_DISABLE;	 	// ��ֹ��ʱ���׼��λ�Ĵ�����TBPHS�����ص�ʱ���׼��������TBCTR��
	PWM0_PRD_SHADOWON;		// ���ڼĴ�����TBPRD����ʱ���׼��������TBCTR���������ʱ�����ӳ��Ĵ�����װ�ء���TBPRD�Ĵ����Ķ���д������ӳ��Ĵ����С�
	PWM0->TBCTL_b.SYNCOSEL = SYNCOSEL_CTR_ZERO; // ͬ�����ѡ��ʱ���׼����������0��ΪPWMxSYNCO�źŵ�Դ
	
	PWM0->CMPCTL_b.SHDWAMODE = SHADOWMODE_ON; // ӳ��ģʽ����Ϊ˫������������е�д����ͨ��CPU����ӳ��Ĵ�����
	PWM0->CMPCTL_b.SHDWBMODE = SHADOWMODE_ON; // ӳ��ģʽ����Ϊ˫������������е�д����ͨ��CPU����ӳ��Ĵ�����
	PWM0->CMPCTL_b.LOADBMODE = CMP_LOAD_ZERO; // ӳ��Ĵ���װ��ģʽѡ�񣺵�CTR=0ʱ����
	PWM0->CMPCTL_b.LOADAMODE = CMP_LOAD_ZERO; // ӳ��Ĵ���װ��ģʽѡ�񣺵�CTR=0ʱ����
	
	PWM0->AQCTLA_b.CAU = AQ_CAU_CLR;					  // ��������������CMPA�Ĵ������Ҽ�������ʱ�����������ʹPWMxA�����
	PWM0->AQCTLA_b.CAD = AQ_CAD_SET; 						// ��������������CMPA�Ĵ������Ҽ����ݼ�ʱ��������λ��ʹPWMxA�����
	
	PWM0->AQCTLB_b.CAU = AQ_CAU_SET;					  // ��������������CMPB�Ĵ������Ҽ�������ʱ��������λ��ʹPWMxB�����
	PWM0->AQCTLB_b.CAD = AQ_CAD_CLR; 						// ��������������CMPB�Ĵ������Ҽ����ݼ�ʱ�����������ʹPWMxB�����
	
	PWM0->DBCTL_b.IN_MODE = DB_INMODE_PWMB_BOTH_EDGE;   // PWMxBIN��Ϊ�����غ��½����ӳٵ�����Դ
	PWM0->DBCTL_b.OUT_MODE = DB_OUTMODE_BOTH_ENABLE; 	  // ��������PWMXA������������ӳٺ�PWMxB������½����ӳ���ȫʹ�ܡ�
	PWM0->DBCTL_b.POLSEL = DB_POLSEL_AHC; 						  // ����Ч������AHC��ģʽ��PWMxB����
	
	PWM0->DBFED = DB; // �½�������
	PWM0->DBRED = DB; // ����������
/******************************************************************************
							PWM1
*******************************************************************************/	
	PWM1->TBPRD = Period; // Period = 4000 TBCLK counts
	PWM1->TBPHS = 0; // Set Phase register to zero

	PWM1->TBCTL = 0;
	PWM1_CTRMODE_UPDOWN;		 	// Symmetrical mode CTRMODE
	PWM1_PHASE_ENABLE; 			// Slave module PHSEN
	PWM1_PRD_SHADOWON;				 // TB_SHADOW
	PWM1->TBCTL_b.SYNCOSEL = SYNCOSEL_SYNC; // sync flow-through  SYNCOSEL
	
	PWM1->CMPCTL_b.SHDWAMODE = SHADOWMODE_ON;	// CC_SHADOW
	PWM1->CMPCTL_b.SHDWBMODE = SHADOWMODE_ON;	// CC_SHADOW
	PWM1->CMPCTL_b.LOADAMODE = CMP_LOAD_ZERO; // load on CTR=Zero
	PWM1->CMPCTL_b.LOADBMODE = CMP_LOAD_ZERO; // load on CTR=Zero
	
	PWM1->AQCTLA_b.CAU = AQ_CAU_CLR;					  // ��������������CMPA�Ĵ������Ҽ�������ʱ�����������ʹPWMxA�����
	PWM1->AQCTLA_b.CAD = AQ_CAD_SET; 						// ��������������CMPA�Ĵ������Ҽ����ݼ�ʱ��������λ��ʹPWMxA�����
	
	PWM1->AQCTLB_b.CAU = AQ_CAU_SET;					  // ��������������CMPB�Ĵ������Ҽ�������ʱ��������λ��ʹPWMxB�����
	PWM1->AQCTLB_b.CAD = AQ_CAD_CLR; 						// ��������������CMPB�Ĵ������Ҽ����ݼ�ʱ�����������ʹPWMxB�����
	
	PWM1->DBCTL_b.IN_MODE = DB_INMODE_PWMB_BOTH_EDGE;   // PWMxBIN��Ϊ�����غ��½����ӳٵ�����Դ
	PWM1->DBCTL_b.OUT_MODE = DB_OUTMODE_BOTH_ENABLE; 	  // ��������PWMXA������������ӳٺ�PWMxB������½����ӳ���ȫʹ�ܡ�
	PWM1->DBCTL_b.POLSEL = DB_POLSEL_AHC; 						  // ����Ч������AHC��ģʽ��PWMxB����
	
	PWM1->DBFED = DB; // �½�������
	PWM1->DBRED = DB; // ����������
/*****************************************************************************
							PWM2
*****************************************************************************/	
	PWM2->TBPRD = Period; //Symmetrical mode CTRMODE
	PWM2->TBPHS = 0; //Set Phase register to zero
		
	PWM2->TBCTL = 0;
	PWM2_CTRMODE_UPDOWN; 		//Symmetrical mode CTRMODE
	PWM2_PHASE_ENABLE;		 	// SLave module PHSEN
	PWM2_PRD_SHADOWON;	 // TB_SHADOW
	PWM2->TBCTL_b.SYNCOSEL = SYNCOSEL_SYNC; //sync flow-through SYNCOSEL
	
	PWM2->CMPCTL_b.SHDWAMODE = SHADOWMODE_ON; 	// CC_SHADOW
	PWM2->CMPCTL_b.SHDWBMODE = SHADOWMODE_ON; 	// CC_SHADOW
	PWM2->CMPCTL_b.LOADAMODE = CMP_LOAD_ZERO; 	// load on CTR=Zero
	PWM2->CMPCTL_b.LOADBMODE = CMP_LOAD_ZERO; 	// load on CTR=Zero
	
	PWM2->AQCTLA_b.CAU = AQ_CAU_CLR;					  // ��������������CMPA�Ĵ������Ҽ�������ʱ�����������ʹPWMxA�����
	PWM2->AQCTLA_b.CAD = AQ_CAD_SET; 						// ��������������CMPA�Ĵ������Ҽ����ݼ�ʱ��������λ��ʹPWMxA�����
	
	PWM2->AQCTLB_b.CAU = AQ_CAU_SET;					  // ��������������CMPB�Ĵ������Ҽ�������ʱ��������λ��ʹPWMxB�����
	PWM2->AQCTLB_b.CAD = AQ_CAD_CLR; 						// ��������������CMPB�Ĵ������Ҽ����ݼ�ʱ�����������ʹPWMxB�����
	
	PWM2->DBCTL_b.IN_MODE = DB_INMODE_PWMB_BOTH_EDGE;   // PWMxBIN��Ϊ�����غ��½����ӳٵ�����Դ
	PWM2->DBCTL_b.OUT_MODE = DB_OUTMODE_BOTH_ENABLE; 	  // ��������PWMXA������������ӳٺ�PWMxB������½����ӳ���ȫʹ�ܡ�
	PWM2->DBCTL_b.POLSEL = DB_POLSEL_AHC; 						  // ����Ч������AHC��ģʽ��PWMxB����
	
	PWM2->DBFED = DB; // �½�������
	PWM2->DBRED = DB; // ����������
/******************************************************************
							����PWM�жϴ����ź���ADC������ʼ�ź�
******************************************************************/	
	PWM0->ETPS_b.INTPRD = ET_INTPRD_1; // PWM�ж�����ѡ���ڵ�һ��ETPS[INTCNT]=0,1�¼�����ʱ�жϣ���һ���¼���
	
	PWM0->ETSEL_b.INTESEL = ET_INTSEL_CTR_ZERO; // PWM�жϴ����¼�ѡ�񣺵�ʱ���׼����������0��TBCTR=0x0000��ʱ�����ж�
	PWM0->ETSEL_b.INTEN = ET_INT_ENABLE; // ʹ��PWM�ж����ɣ�


	PWM0->ETPS_b.SOCAPRD = ET_SOCPRD_1; // �ڵ�һ���¼�������PWMxSOCA����
	PWM0->ETSEL_b.SOCASEL = ET_SOCSEL_CTR_PRD; // ��ʱ���׼�������������ڣ�����PWMxSOCA����
	PWM0->ETSEL_b.SOCAEN = ET_SOC_ENABLE;  // ʹ��ADC��ʼת��A��PWMxSOCA������
	PWM0->ETSEL_b.SOCBSEL = ET_SOCSEL_CTR_PRD;  // ��ʱ���׼�������������ڣ�����PWMxSOCA����
	PWM0->ETSEL_b.SOCBEN = ET_SOC_ENABLE;  // ʹ��ADC��ʼת��B��PWMxSOCB������
	
/*******************************************************************
							����PWM��ɲ�����ܣ������ڹ��ϱ���
********************************************************************/
	ACCESS_ENABLE;
	SYSREG->PWM_CFG = 0x00000000;     // CP0�����ΪTZ3����,���ڹ�������
	ACCESS_ENABLE;
	PWM0->TZSEL_b.OSHT3 = TZ_OSHT_ENABLE;				
	ACCESS_ENABLE;
	PWM1->TZSEL_b.OSHT3 = TZ_OSHT_ENABLE;				
	ACCESS_ENABLE;
	PWM2->TZSEL_b.OSHT3 = TZ_OSHT_ENABLE;  // ʹ��TZ3��ΪPWMģ��ĵ��ι���Դ
	ACCESS_ENABLE;
	PWM0->TZCTL_b.TZA = TZ_NO_ACTION;  // ��PWMxA�õ� 
	ACCESS_ENABLE;
	PWM0->TZCTL_b.TZB = TZ_NO_ACTION;  // ��PWMxB�õ�
	ACCESS_ENABLE;
	PWM1->TZCTL_b.TZA = TZ_NO_ACTION;  // ��PWMxA�õ� 
	ACCESS_ENABLE;
	PWM1->TZCTL_b.TZB = TZ_NO_ACTION;  // ��PWMxB�õ� 
	ACCESS_ENABLE;
	PWM2->TZCTL_b.TZA = TZ_NO_ACTION;  // ��PWMxA�õ� 
	ACCESS_ENABLE;
	PWM2->TZCTL_b.TZB = TZ_NO_ACTION;  // ��PWMxB�õ� 
	
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
  * PWM_Init();
  * @endcode
  * @warning:
*/
/********************************************************************
					����PWM�����ڼ���ֵ����������ֵ��ռ�ձȲ�ͬ������������
*********************************************************************/
void PWM_Init()
{
	PWM_CFG(3600,72);    // 72MHz�£�10kHzPWM��1us����
	PWM0->CMPA = 500;
	PWM1->CMPA = 1000;
	PWM2->CMPA = 1500;
	PWM_START;
	
}
