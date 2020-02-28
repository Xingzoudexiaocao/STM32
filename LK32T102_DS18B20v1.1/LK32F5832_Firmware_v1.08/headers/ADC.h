#ifndef __ADC_H
#define __ADC_H

#include <SC32F5832.h>
/**********************************************************************
			ADCģ��ʱ�ӷ�Ƶ
**********************************************************************/

#define ADC_CLKDIV_2				0								// 2��Ƶ
#define ADC_CLKDIV_3				1								// 3��Ƶ
#define ADC_CLKDIV_4				2								// 4��Ƶ
#define ADC_CLKDIV_5				3								// 5��Ƶ
#define ADC_CLKDIV_6				4								// 6��Ƶ
#define ADC_CLKDIV_8				5								// 8��Ƶ
#define ADC_CLKDIV_10				6								// 10��Ƶ
#define ADC_CLKDIV_12				7								// 12��Ƶ
#define ADC_CLKDIV_14				8								// 14��Ƶ
#define ADC_CLKDIV_16				9								// 16��Ƶ
#define ADC_CLKDIV_18				10							// 18��Ƶ
#define ADC_CLKDIV_20				11							// 20��Ƶ
#define ADC_CLKDIV_26				12							// 26��Ƶ
#define ADC_CLKDIV_32				13							// 32��Ƶ
#define ADC_CLKDIV_64				14							// 64��Ƶ

#define ACCESS_ENABLE SYSREG->ACCESS_EN = 0x05fa659a;										// �ر�д����
#define ADC_RESET 	ACCESS_ENABLE;ADC->ADCCTL1_b.RESET = 1; 						// ADCģ������
#define ADC_ENABLE 	ACCESS_ENABLE;ADC->ADCCTL1_b.ADCENABLE = 1;   			// ADCģ��ʹ��
#define ADC_DISABLE ACCESS_ENABLE;ADC->ADCCTL1_b.ADCENABLE = 0;					// ADCģ���ֹ
#define ADC_NONOVERLAP ACCESS_ENABLE;ADC->ADCCTL2|=(1<<1);							// ������ת�����ص�
#define ADC_OVERLAP  ACCESS_ENABLE;ADC->ADCCTL2&=~(1<<1);								// ������ת���ص�
#define ADC_MODE2		ADC->ADCTRIM_b.mode2 = 1;														// ADCģʽ2
#define ADC_VOL_SEL_50V	ADC->ADCTRIM_b.vol_sel = 1;											// �ڲ���ѹ�ο�ѡ��5.0V
#define ADC_VOL_SEL_33V ADC->ADCTRIM_b.vol_sel = 0;											// �ڲ���ѹ�ο�ѡ��3.3V
#define ADC_INT_AT_EOC 	ACCESS_ENABLE;ADC->ADCCTL1_b.INTPULSEPOS = 1;		// EOC��������ڷ������Ĵ���ǰ��һ������
#define ADC_INT_AT_SOC	ACCESS_ENABLE;ADC->ADCCTL1_b.INTPULSEPOS = 0;		// EOC���������ת����ʼʱ
#define ADC_REF_INTERNAL		ACCESS_ENABLE;ADC->ADCCTL1_b.ADCREFSEL = 0; // ADCʹ���ڲ��ο���ѹ
#define ADC_REF_EXT_VREF		ACCESS_ENABLE;ADC->ADCCTL1_b.ADCREFSEL = 1; // ADCʹ���ⲿ�ο���ѹ
#define ADC_B7_SEL_OPA2			ACCESS_ENABLE;ADC->ADCCTL1_b.INB7_SEL = 1;	// ADCB7ͨ���ɼ�OPA2������
#define ADC_B7_SEL_PIN 			ACCESS_ENABLE;ADC->ADCCTL1_b.INB7_SEL = 0;	// ADCB7ͨ���ɼ��ܽ�����
#define ADC_B6_SEL_OPA1 		ACCESS_ENABLE;ADC->ADCCTL1_b.INB6_SEL = 1;	// ADCB6ͨ���ɼ�OPA1������
#define ADC_B6_SEL_PIN			ACCESS_ENABLE;ADC->ADCCTL1_b.INB6_SEL = 0;	// ADCB6ͨ���ɼ��ܽ�����
#define ADC_A7_SEL_OPA3			ACCESS_ENABLE;ADC->ADCCTL1_b.INA7_SEL = 1;	// ADCA7ͨ���ɼ�OPA3������
#define ADC_A7_SEL_PIN			ACCESS_ENABLE;ADC->ADCCTL1_b.INA7_SEL = 0;	// ADCA7ͨ���ɼ��ܽ�����
#define ADC_A6_SEL_OPA0			ACCESS_ENABLE;ADC->ADCCTL1_b.INA6_SEL = 1;	// ADCA6ͨ���ɼ�OPA0������
#define ADC_A6_SEL_PIN			ACCESS_ENABLE;ADC->ADCCTL1_b.INA6_SEL = 0;	// ADCA6ͨ���ɼ��ܽ�����


#endif
