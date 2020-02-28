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
    本文件展示了ADC模块的初始化，采用连续采样模式对2个通道进行采样
**********************************************************************/

#include <SC32F5832.h>
#include <DevInit.h>

int ChSel[16]   = {14,15,0,1,0,0,0,0,0,0,0,0,0,0,0,0};               		// 定义ADC通道数组
/*通道选择表
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
int ACQPS[16]   = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};   									// 定义各通道窗口大小数组,采样保持窗口时间，最小值为9
int TrigSel[16] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};		       					// 定义各通道触发源数组
/*触发源选择表
	00：软件触发
		01h：保留
		02h：保留
		03h：保留
		04h：保留
		05h：PWM0_SOCA
		06h：PWM0_SOCB
		07h：PWM1_SOCA
		08h：PWM1_SOCB
		09h：PWM2_SOCA
		0Ah：PWM2_SOCB
		0Bh：保留
		0Ch：保留
		0Dh：PWM4_SOCA
		0Eh：PWM4_SOCB
		0Fh：保留
		10h：保留
		11h：保留
		12h：保留
		13h：保留
		14h：保留
		15h：ERU_EVENT0
		16h：ERU_EVENT1
		17h：ERU_EVENT2
		18h：ERU_EVENT3
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
	
	ADC_RESET;										 // ADC模块复位
	ADC_ENABLE;										 // ADC模块使能
	
	ACCESS_ENABLE;
	ADC->ADCCTL1_b.ADCPD = 0;      // ADC断电，高电平有效
	ACCESS_ENABLE;
	ADC->ADCCTL1_b.ADCSHPD = 0;    // ADC采样模块断电，高电平有效
	ACCESS_ENABLE;
	ADC->ADCCTL1_b.AADCREFPD = 0;  // 参考源缓冲电路断电控制（高有效）
	ACCESS_ENABLE;
	ADC->ADCCTL1_b.ADCCOREPD = 0;  // ADC数字core断电，高电平有效
	
	ACCESS_ENABLE;
	ADC->ADCCTL2_b.clkdiv = ADC_CLKDIV_3;     // 时钟 3分频后 24MHz 作为ADC模块时钟
	ACCESS_ENABLE;
	ADC->ADCCTL2_b.smp_conv_delay = 3;  // 采样和开始转换之间的延时
	ACCESS_ENABLE;
	ADC->ADCCTL2_b.start_width = 3;     // 开始转换的脉冲宽度
	
	ADC_NONOVERLAP;											// 采样与转换不重叠
	ADC_MODE2;													// 工作模式，强制设定
	ADC_VOL_SEL_50V;										// 工作电压选择5.0V
	
	ADC->ADCTRIM_b.meas_i = 0;          // 模拟模块低电压选择
	ADC->ADCTRIM_b.ntrim = 0;           // NTrim参考电压
	ADC->ADCTRIM_b.itrim = 11;          // 偏置电流校准位  （本参数为出厂设置，请勿修改）
	
	ADC_INT_AT_EOC;											// 在ADC结果存入结果寄存器的前一个周期产生INT脉冲
	
	ADC_REF_INTERNAL;										// 内部外部参考源选择，选择内部带隙参考源
	
	ACCESS_ENABLE;
	ADC->INTSEL1N2_b.INT1E = 1;         // ADCINT1中断使能

	ACCESS_ENABLE;
	ADC->INTSEL1N2_b.INT1CONT = 1;      // ADCINT1连续模式使能：只要EOC脉冲产生，就可以产生ADCINTx脉冲

	ACCESS_ENABLE;
	ADC->INTSEL1N2_b.INT1SEL = 0;       // ADCINT1源选择：EOC0作为ADCINTx的触发源
	
	ADC_B6_SEL_PIN;											// B6通道选择管脚输入
	ADC_B7_SEL_OPA2;										// B7通道选择运放2的输出作为输入
	
/******************************************************************************
												ADC通道选择
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
											 ADC触发源选择
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
											 ADC窗口大小选择
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
