#ifndef __ADC_H
#define __ADC_H

#include <SC32F5832.h>
/**********************************************************************
			ADC模块时钟分频
**********************************************************************/

#define ADC_CLKDIV_2				0								// 2分频
#define ADC_CLKDIV_3				1								// 3分频
#define ADC_CLKDIV_4				2								// 4分频
#define ADC_CLKDIV_5				3								// 5分频
#define ADC_CLKDIV_6				4								// 6分频
#define ADC_CLKDIV_8				5								// 8分频
#define ADC_CLKDIV_10				6								// 10分频
#define ADC_CLKDIV_12				7								// 12分频
#define ADC_CLKDIV_14				8								// 14分频
#define ADC_CLKDIV_16				9								// 16分频
#define ADC_CLKDIV_18				10							// 18分频
#define ADC_CLKDIV_20				11							// 20分频
#define ADC_CLKDIV_26				12							// 26分频
#define ADC_CLKDIV_32				13							// 32分频
#define ADC_CLKDIV_64				14							// 64分频

#define ACCESS_ENABLE SYSREG->ACCESS_EN = 0x05fa659a;										// 关闭写保护
#define ADC_RESET 	ACCESS_ENABLE;ADC->ADCCTL1_b.RESET = 1; 						// ADC模块重启
#define ADC_ENABLE 	ACCESS_ENABLE;ADC->ADCCTL1_b.ADCENABLE = 1;   			// ADC模块使能
#define ADC_DISABLE ACCESS_ENABLE;ADC->ADCCTL1_b.ADCENABLE = 0;					// ADC模块禁止
#define ADC_NONOVERLAP ACCESS_ENABLE;ADC->ADCCTL2|=(1<<1);							// 采样与转换不重叠
#define ADC_OVERLAP  ACCESS_ENABLE;ADC->ADCCTL2&=~(1<<1);								// 采样与转换重叠
#define ADC_MODE2		ADC->ADCTRIM_b.mode2 = 1;														// ADC模式2
#define ADC_VOL_SEL_50V	ADC->ADCTRIM_b.vol_sel = 1;											// 内部电压参考选择5.0V
#define ADC_VOL_SEL_33V ADC->ADCTRIM_b.vol_sel = 0;											// 内部电压参考选择3.3V
#define ADC_INT_AT_EOC 	ACCESS_ENABLE;ADC->ADCCTL1_b.INTPULSEPOS = 1;		// EOC脉冲产生于放入结果寄存器前的一个周期
#define ADC_INT_AT_SOC	ACCESS_ENABLE;ADC->ADCCTL1_b.INTPULSEPOS = 0;		// EOC脉冲产生于转换开始时
#define ADC_REF_INTERNAL		ACCESS_ENABLE;ADC->ADCCTL1_b.ADCREFSEL = 0; // ADC使用内部参考电压
#define ADC_REF_EXT_VREF		ACCESS_ENABLE;ADC->ADCCTL1_b.ADCREFSEL = 1; // ADC使用外部参考电压
#define ADC_B7_SEL_OPA2			ACCESS_ENABLE;ADC->ADCCTL1_b.INB7_SEL = 1;	// ADCB7通道采集OPA2结果输出
#define ADC_B7_SEL_PIN 			ACCESS_ENABLE;ADC->ADCCTL1_b.INB7_SEL = 0;	// ADCB7通道采集管脚输入
#define ADC_B6_SEL_OPA1 		ACCESS_ENABLE;ADC->ADCCTL1_b.INB6_SEL = 1;	// ADCB6通道采集OPA1结果输出
#define ADC_B6_SEL_PIN			ACCESS_ENABLE;ADC->ADCCTL1_b.INB6_SEL = 0;	// ADCB6通道采集管脚输入
#define ADC_A7_SEL_OPA3			ACCESS_ENABLE;ADC->ADCCTL1_b.INA7_SEL = 1;	// ADCA7通道采集OPA3结果输出
#define ADC_A7_SEL_PIN			ACCESS_ENABLE;ADC->ADCCTL1_b.INA7_SEL = 0;	// ADCA7通道采集管脚输入
#define ADC_A6_SEL_OPA0			ACCESS_ENABLE;ADC->ADCCTL1_b.INA6_SEL = 1;	// ADCA6通道采集OPA0结果输出
#define ADC_A6_SEL_PIN			ACCESS_ENABLE;ADC->ADCCTL1_b.INA6_SEL = 0;	// ADCA6通道采集管脚输入


#endif
