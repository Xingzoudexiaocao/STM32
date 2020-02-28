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
本文件展示了PWM模块的配置方法，可直接应用于下桥臂电阻采样的SVPWM
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
				初始化PWM0-2，设置参数为：PWM半周期计数值、死区计数值
************************************************************************/
void PWM_CFG(uint32_t Period,uint32_t DB)
{	
	
/**************************************************************************
							PWM0
***************************************************************************/	
	PWM0->TBPRD = Period; //Period = 4000TBCLK counts
	PWM0->TBPHS = 0; //Set Phase register to zero
	
	PWM0->TBCTL = 0;
	PWM0_CTRMODE_UPDOWN;	 // 递增递减计数模式
	PWM0_PHASE_DISABLE;	 	// 禁止从时间基准相位寄存器（TBPHS）加载到时间基准计数器（TBCTR）
	PWM0_PRD_SHADOWON;		// 周期寄存器（TBPRD）在时间基准计数器（TBCTR）等于零的时候从其映射寄存器中装载。对TBPRD寄存器的读和写都进入映射寄存器中。
	PWM0->TBCTL_b.SYNCOSEL = SYNCOSEL_CTR_ZERO; // 同步输出选择，时间基准计数器等于0作为PWMxSYNCO信号的源
	
	PWM0->CMPCTL_b.SHDWAMODE = SHADOWMODE_ON; // 映射模式。作为双缓冲操作，所有的写操作通过CPU访问映射寄存器。
	PWM0->CMPCTL_b.SHDWBMODE = SHADOWMODE_ON; // 映射模式。作为双缓冲操作，所有的写操作通过CPU访问映射寄存器。
	PWM0->CMPCTL_b.LOADBMODE = CMP_LOAD_ZERO; // 映射寄存器装载模式选择：当CTR=0时加载
	PWM0->CMPCTL_b.LOADAMODE = CMP_LOAD_ZERO; // 映射寄存器装载模式选择：当CTR=0时加载
	
	PWM0->AQCTLA_b.CAU = AQ_CAU_CLR;					  // 当计数器等于主CMPA寄存器并且计数递增时动作：清除：使PWMxA输出低
	PWM0->AQCTLA_b.CAD = AQ_CAD_SET; 						// 当计数器等于主CMPA寄存器并且计数递减时动作：置位：使PWMxA输出高
	
	PWM0->AQCTLB_b.CAU = AQ_CAU_SET;					  // 当计数器等于主CMPB寄存器并且计数递增时动作：置位：使PWMxB输出高
	PWM0->AQCTLB_b.CAD = AQ_CAD_CLR; 						// 当计数器等于主CMPB寄存器并且计数递减时动作：清除：使PWMxB输出低
	
	PWM0->DBCTL_b.IN_MODE = DB_INMODE_PWMB_BOTH_EDGE;   // PWMxBIN作为上升沿和下降沿延迟的输入源
	PWM0->DBCTL_b.OUT_MODE = DB_OUTMODE_BOTH_ENABLE; 	  // 死区对于PWMXA输入的上升沿延迟和PWMxB输出的下降沿延迟完全使能。
	PWM0->DBCTL_b.POLSEL = DB_POLSEL_AHC; 						  // 高有效互补（AHC）模式。PWMxB反相
	
	PWM0->DBFED = DB; // 下降沿死区
	PWM0->DBRED = DB; // 上升沿死区
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
	
	PWM1->AQCTLA_b.CAU = AQ_CAU_CLR;					  // 当计数器等于主CMPA寄存器并且计数递增时动作：清除：使PWMxA输出低
	PWM1->AQCTLA_b.CAD = AQ_CAD_SET; 						// 当计数器等于主CMPA寄存器并且计数递减时动作：置位：使PWMxA输出高
	
	PWM1->AQCTLB_b.CAU = AQ_CAU_SET;					  // 当计数器等于主CMPB寄存器并且计数递增时动作：置位：使PWMxB输出高
	PWM1->AQCTLB_b.CAD = AQ_CAD_CLR; 						// 当计数器等于主CMPB寄存器并且计数递减时动作：清除：使PWMxB输出低
	
	PWM1->DBCTL_b.IN_MODE = DB_INMODE_PWMB_BOTH_EDGE;   // PWMxBIN作为上升沿和下降沿延迟的输入源
	PWM1->DBCTL_b.OUT_MODE = DB_OUTMODE_BOTH_ENABLE; 	  // 死区对于PWMXA输入的上升沿延迟和PWMxB输出的下降沿延迟完全使能。
	PWM1->DBCTL_b.POLSEL = DB_POLSEL_AHC; 						  // 高有效互补（AHC）模式。PWMxB反相
	
	PWM1->DBFED = DB; // 下降沿死区
	PWM1->DBRED = DB; // 上升沿死区
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
	
	PWM2->AQCTLA_b.CAU = AQ_CAU_CLR;					  // 当计数器等于主CMPA寄存器并且计数递增时动作：清除：使PWMxA输出低
	PWM2->AQCTLA_b.CAD = AQ_CAD_SET; 						// 当计数器等于主CMPA寄存器并且计数递减时动作：置位：使PWMxA输出高
	
	PWM2->AQCTLB_b.CAU = AQ_CAU_SET;					  // 当计数器等于主CMPB寄存器并且计数递增时动作：置位：使PWMxB输出高
	PWM2->AQCTLB_b.CAD = AQ_CAD_CLR; 						// 当计数器等于主CMPB寄存器并且计数递减时动作：清除：使PWMxB输出低
	
	PWM2->DBCTL_b.IN_MODE = DB_INMODE_PWMB_BOTH_EDGE;   // PWMxBIN作为上升沿和下降沿延迟的输入源
	PWM2->DBCTL_b.OUT_MODE = DB_OUTMODE_BOTH_ENABLE; 	  // 死区对于PWMXA输入的上升沿延迟和PWMxB输出的下降沿延迟完全使能。
	PWM2->DBCTL_b.POLSEL = DB_POLSEL_AHC; 						  // 高有效互补（AHC）模式。PWMxB反相
	
	PWM2->DBFED = DB; // 下降沿死区
	PWM2->DBRED = DB; // 上升沿死区
/******************************************************************
							设置PWM中断触发信号与ADC采样开始信号
******************************************************************/	
	PWM0->ETPS_b.INTPRD = ET_INTPRD_1; // PWM中断周期选择：在第一个ETPS[INTCNT]=0,1事件发生时中断（第一个事件）
	
	PWM0->ETSEL_b.INTESEL = ET_INTSEL_CTR_ZERO; // PWM中断触发事件选择：当时间基准计数器等于0（TBCTR=0x0000）时产生中断
	PWM0->ETSEL_b.INTEN = ET_INT_ENABLE; // 使能PWM中断生成；


	PWM0->ETPS_b.SOCAPRD = ET_SOCPRD_1; // 在第一个事件上生成PWMxSOCA脉冲
	PWM0->ETSEL_b.SOCASEL = ET_SOCSEL_CTR_PRD; // 当时间基准计数器等于周期，生成PWMxSOCA脉冲
	PWM0->ETSEL_b.SOCAEN = ET_SOC_ENABLE;  // 使能ADC开始转换A（PWMxSOCA）脉冲
	PWM0->ETSEL_b.SOCBSEL = ET_SOCSEL_CTR_PRD;  // 当时间基准计数器等于周期，生成PWMxSOCA脉冲
	PWM0->ETSEL_b.SOCBEN = ET_SOC_ENABLE;  // 使能ADC开始转换B（PWMxSOCB）脉冲
	
/*******************************************************************
							配置PWM的刹车功能，可用于故障保护
********************************************************************/
	ACCESS_ENABLE;
	SYSREG->PWM_CFG = 0x00000000;     // CP0输出作为TZ3输入,用于过流保护
	ACCESS_ENABLE;
	PWM0->TZSEL_b.OSHT3 = TZ_OSHT_ENABLE;				
	ACCESS_ENABLE;
	PWM1->TZSEL_b.OSHT3 = TZ_OSHT_ENABLE;				
	ACCESS_ENABLE;
	PWM2->TZSEL_b.OSHT3 = TZ_OSHT_ENABLE;  // 使能TZ3作为PWM模块的单次故障源
	ACCESS_ENABLE;
	PWM0->TZCTL_b.TZA = TZ_NO_ACTION;  // 将PWMxA置低 
	ACCESS_ENABLE;
	PWM0->TZCTL_b.TZB = TZ_NO_ACTION;  // 将PWMxB置低
	ACCESS_ENABLE;
	PWM1->TZCTL_b.TZA = TZ_NO_ACTION;  // 将PWMxA置低 
	ACCESS_ENABLE;
	PWM1->TZCTL_b.TZB = TZ_NO_ACTION;  // 将PWMxB置低 
	ACCESS_ENABLE;
	PWM2->TZCTL_b.TZA = TZ_NO_ACTION;  // 将PWMxA置低 
	ACCESS_ENABLE;
	PWM2->TZCTL_b.TZB = TZ_NO_ACTION;  // 将PWMxB置低 
	
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
					给定PWM的周期计数值，死区周期值，占空比并同步启动计数器
*********************************************************************/
void PWM_Init()
{
	PWM_CFG(3600,72);    // 72MHz下，10kHzPWM，1us死区
	PWM0->CMPA = 500;
	PWM1->CMPA = 1000;
	PWM2->CMPA = 1500;
	PWM_START;
	
}
