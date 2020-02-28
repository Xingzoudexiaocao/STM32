/**
* @file          : ADC.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for ADC configuration.
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

/**********************************************************************
    ���ļ�չʾ��ADCģ��ĳ�ʼ����������������ģʽ��2��ͨ�����в���
**********************************************************************/

#include <SC32F5832.h>
#include <DevInit.h>

int ChSel[16]   = {14,15,0,1,0,0,0,0,0,0,0,0,0,0,0,0};               		// ����ADCͨ������
/*ͨ��ѡ���
		0h ADCINA0												
		1h ADCINA1											
		2h ADCINA2											
		3h ADCINA3												
		4h ADCINA4											
		5h ADCINA5												
		6h ADCINA6												
		7h ADCINA7											
		8h ADCINB0							
		9h ADCINB1										
		Ah ADCINB2								
		Bh ADCINB3											
		Ch ADCINB4											
		Dh ADCINB5												
		Eh ADCINB6												
		Fh ADCINB7	
*/
int ACQPS[16]   = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};   									// �����ͨ�����ڴ�С����,�������ִ���ʱ�䣬��СֵΪ9
int TrigSel[16] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};		       					// �����ͨ������Դ����
/*����Դѡ���
	00���������
		01h������
		02h������
		03h������
		04h������
		05h��PWM0_SOCA
		06h��PWM0_SOCB
		07h��PWM1_SOCA
		08h��PWM1_SOCB
		09h��PWM2_SOCA
		0Ah��PWM2_SOCB
		0Bh������
		0Ch������
		0Dh��PWM4_SOCA
		0Eh��PWM4_SOCB
		0Fh������
		10h������
		11h������
		12h������
		13h������
		14h������
		15h��ERU_EVENT0
		16h��ERU_EVENT1
		17h��ERU_EVENT2
		18h��ERU_EVENT3
*/

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
  * ADC_Init();
  * @endcode
  * @warning:
*/

void ADC_Init()
{
	
	ADC_RESET;										 // ADCģ�鸴λ
	ADC_ENABLE;										 // ADCģ��ʹ��
	
	ACCESS_ENABLE;
	ADC->ADCCTL1_b.ADCPD = 0;      // ADC�ϵ磬�ߵ�ƽ��Ч
	ACCESS_ENABLE;
	ADC->ADCCTL1_b.ADCSHPD = 0;    // ADC����ģ��ϵ磬�ߵ�ƽ��Ч
	ACCESS_ENABLE;
	ADC->ADCCTL1_b.AADCREFPD = 0;  // �ο�Դ�����·�ϵ���ƣ�����Ч��
	ACCESS_ENABLE;
	ADC->ADCCTL1_b.ADCCOREPD = 0;  // ADC����core�ϵ磬�ߵ�ƽ��Ч
	
	ACCESS_ENABLE;
	ADC->ADCCTL2_b.clkdiv = ADC_CLKDIV_3;     // ʱ�� 3��Ƶ�� 24MHz ��ΪADCģ��ʱ��
	ACCESS_ENABLE;
	ADC->ADCCTL2_b.smp_conv_delay = 3;  // �����Ϳ�ʼת��֮�����ʱ
	ACCESS_ENABLE;
	ADC->ADCCTL2_b.start_width = 3;     // ��ʼת����������
	
	ADC_NONOVERLAP;											// ������ת�����ص�
	ADC_MODE2;													// ����ģʽ��ǿ���趨
	ADC_VOL_SEL_50V;										// ������ѹѡ��5.0V
	
	ADC->ADCTRIM_b.meas_i = 0;          // ģ��ģ��͵�ѹѡ��
	ADC->ADCTRIM_b.ntrim = 0;           // NTrim�ο���ѹ
	ADC->ADCTRIM_b.itrim = 11;          // ƫ�õ���У׼λ  ��������Ϊ�������ã������޸ģ�
	
	ADC_INT_AT_EOC;											// ��ADC����������Ĵ�����ǰһ�����ڲ���INT����
	
	ADC_REF_INTERNAL;										// �ڲ��ⲿ�ο�Դѡ��ѡ���ڲ���϶�ο�Դ
	
	ACCESS_ENABLE;
	ADC->INTSEL1N2_b.INT1E = 1;         // ADCINT1�ж�ʹ��

	ACCESS_ENABLE;
	ADC->INTSEL1N2_b.INT1CONT = 1;      // ADCINT1����ģʽʹ�ܣ�ֻҪEOC����������Ϳ��Բ���ADCINTx����

	ACCESS_ENABLE;
	ADC->INTSEL1N2_b.INT1SEL = 0;       // ADCINT1Դѡ��EOC0��ΪADCINTx�Ĵ���Դ
	
	ADC_B6_SEL_PIN;											// B6ͨ��ѡ��ܽ�����
	ADC_B7_SEL_OPA2;										// B7ͨ��ѡ���˷�2�������Ϊ����
	
/******************************************************************************
												ADCͨ��ѡ��
*******************************************************************************/

	ACCESS_ENABLE;ADC->ADCSOC0CTL_b.CHSEL = ChSel[0];
	ACCESS_ENABLE;ADC->ADCSOC1CTL_b.CHSEL = ChSel[1];
	ACCESS_ENABLE;ADC->ADCSOC2CTL_b.CHSEL = ChSel[2];
	ACCESS_ENABLE;ADC->ADCSOC3CTL_b.CHSEL = ChSel[3];
	ACCESS_ENABLE;ADC->ADCSOC4CTL_b.CHSEL = ChSel[4];
	ACCESS_ENABLE;ADC->ADCSOC5CTL_b.CHSEL = ChSel[5];
	ACCESS_ENABLE;ADC->ADCSOC6CTL_b.CHSEL = ChSel[6];
	ACCESS_ENABLE;ADC->ADCSOC7CTL_b.CHSEL = ChSel[7];
	ACCESS_ENABLE;ADC->ADCSOC8CTL_b.CHSEL = ChSel[8];
	ACCESS_ENABLE;ADC->ADCSOC9CTL_b.CHSEL = ChSel[9];
	ACCESS_ENABLE;ADC->ADCSOC10CTL_b.CHSEL = ChSel[10];
	ACCESS_ENABLE;ADC->ADCSOC11CTL_b.CHSEL = ChSel[11];
	ACCESS_ENABLE;ADC->ADCSOC12CTL_b.CHSEL = ChSel[12];
	ACCESS_ENABLE;ADC->ADCSOC13CTL_b.CHSEL = ChSel[13];
	ACCESS_ENABLE;ADC->ADCSOC14CTL_b.CHSEL = ChSel[14];
	ACCESS_ENABLE;ADC->ADCSOC15CTL_b.CHSEL = ChSel[15];

/****************************************************************************
											 ADC����Դѡ��
*****************************************************************************/

	ACCESS_ENABLE;ADC->ADCSOC0CTL_b.TRIGSEL = TrigSel[0];
	ACCESS_ENABLE;ADC->ADCSOC1CTL_b.TRIGSEL = TrigSel[1];
	ACCESS_ENABLE;ADC->ADCSOC2CTL_b.TRIGSEL = TrigSel[2];
	ACCESS_ENABLE;ADC->ADCSOC3CTL_b.TRIGSEL = TrigSel[3];
	ACCESS_ENABLE;ADC->ADCSOC4CTL_b.TRIGSEL = TrigSel[4];
	ACCESS_ENABLE;ADC->ADCSOC5CTL_b.TRIGSEL = TrigSel[5];
	ACCESS_ENABLE;ADC->ADCSOC6CTL_b.TRIGSEL = TrigSel[6];
	ACCESS_ENABLE;ADC->ADCSOC7CTL_b.TRIGSEL = TrigSel[7];
	ACCESS_ENABLE;ADC->ADCSOC8CTL_b.TRIGSEL = TrigSel[8];
	ACCESS_ENABLE;ADC->ADCSOC9CTL_b.TRIGSEL = TrigSel[9];
	ACCESS_ENABLE;ADC->ADCSOC10CTL_b.TRIGSEL = TrigSel[10];
	ACCESS_ENABLE;ADC->ADCSOC11CTL_b.TRIGSEL = TrigSel[11];
	ACCESS_ENABLE;ADC->ADCSOC12CTL_b.TRIGSEL = TrigSel[12];
	ACCESS_ENABLE;ADC->ADCSOC13CTL_b.TRIGSEL = TrigSel[13];
	ACCESS_ENABLE;ADC->ADCSOC14CTL_b.TRIGSEL = TrigSel[14];
	ACCESS_ENABLE;ADC->ADCSOC15CTL_b.TRIGSEL = TrigSel[15];

/******************************************************************************
											 ADC���ڴ�Сѡ��
******************************************************************************/

	ACCESS_ENABLE;ADC->ADCSOC0CTL_b.ACQPS = ACQPS[0];
	ACCESS_ENABLE;ADC->ADCSOC1CTL_b.ACQPS = ACQPS[1];
	ACCESS_ENABLE;ADC->ADCSOC2CTL_b.ACQPS = ACQPS[2];
	ACCESS_ENABLE;ADC->ADCSOC3CTL_b.ACQPS = ACQPS[3];
	ACCESS_ENABLE;ADC->ADCSOC4CTL_b.ACQPS = ACQPS[4];
	ACCESS_ENABLE;ADC->ADCSOC5CTL_b.ACQPS = ACQPS[5];
	ACCESS_ENABLE;ADC->ADCSOC6CTL_b.ACQPS = ACQPS[6];
	ACCESS_ENABLE;ADC->ADCSOC7CTL_b.ACQPS = ACQPS[7];
	ACCESS_ENABLE;ADC->ADCSOC8CTL_b.ACQPS = ACQPS[8];
	ACCESS_ENABLE;ADC->ADCSOC9CTL_b.ACQPS = ACQPS[9];
	ACCESS_ENABLE;ADC->ADCSOC10CTL_b.ACQPS = ACQPS[10];
	ACCESS_ENABLE;ADC->ADCSOC11CTL_b.ACQPS = ACQPS[11];
	ACCESS_ENABLE;ADC->ADCSOC12CTL_b.ACQPS = ACQPS[12];
	ACCESS_ENABLE;ADC->ADCSOC13CTL_b.ACQPS = ACQPS[13];
	ACCESS_ENABLE;ADC->ADCSOC14CTL_b.ACQPS = ACQPS[14];
	ACCESS_ENABLE;ADC->ADCSOC15CTL_b.ACQPS = ACQPS[15];
	
}
