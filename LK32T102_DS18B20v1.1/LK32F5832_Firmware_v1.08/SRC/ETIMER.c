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
本文件以三通道输入捕获功能和单通道PWM输出为例，展示了TIMER0的初始化配置过程。
**********************************************************************/

#include <SC32F5832.h>
#include <DevInit.h>


/**********************************************************************
				将TIMER0配置为输入捕获功能，可用于三相霍尔信号捕获
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
	

	TIM_ARPE_ENABLE;  // 周期计数预装载允许位：TIM_ARR 寄存器有缓冲
	TIMER0->TIM_CCMR1|=	CC2S_INPUT_IC2_To_TI2;  // 捕捉 / 比较 2 选择：CC2 通道被配置为输入，IC2 映射在 TI2 上；
	TIMER0->TIM_CCMR1|=	CC1S_INPUT_IC1_To_TI1;  // 捕捉 / 比较 1 选择：CC1 通道被配置为输入，IC1 映射在 TI1 上；
	TIMER0->TIM_CCMR2|=	CC3S_INPUT_IC3_To_TI3;  // 捕捉 / 比较 3 选择：CC3 通道被配置为输入，IC3 映射在 TI3 上；

	
	TIMER0->TIM_CCER_b.CC3P = 1;  // 捕捉/比较3输出极性：电路作用于 TI3FP1 的上升沿和下降沿
	TIMER0->TIM_CCER_b.CC3NP = 1;
	TIMER0->TIM_CCER_b.CC2P = 1;  // 捕捉/比较2输出极性：电路作用于 TI2FP1 的上升沿和下降沿
	TIMER0->TIM_CCER_b.CC2NP = 1;
	TIMER0->TIM_CCER_b.CC1P = 1;  // 捕捉/比较1输出极性：电路作用于 TI1FP1 的上升沿和下降沿
	TIMER0->TIM_CCER_b.CC1NP = 1;

	
	TIMER0->TIM_CCER_b.CC1E = CC1E_ENABLE;  // 捕捉/比较1输出使能
	TIMER0->TIM_CCER_b.CC2E = CC2E_ENABLE;  // 捕捉/比较2输出使能
	TIMER0->TIM_CCER_b.CC3E = CC3E_ENABLE;  // 捕捉/比较3输出使能

	
//	TIMER0->TIM_DIER_b.UIE = UIE_ENABLE;	  // 使能更新事件中断
	TIMER0->TIM_DIER_b.CC1IE = CC1IE_ENABLE;	// 捕捉 / 比较 1 中断使能
	TIMER0->TIM_DIER_b.CC2IE = CC2IE_ENABLE;	// 捕捉 / 比较 2 中断使能
	TIMER0->TIM_DIER_b.CC3IE = CC3IE_ENABLE;	// 捕捉 / 比较 3 中断使能


	TIMER0->TIM_ARR = 10000;			// 对计数周期寄存器赋值
	TIMER0->TIM_ISR|= CNT_CLR_ENABLE;			// 计数器捕获清0使能
	TIMER0->TIM_ISR|= CNT_CLR_SEL_CH1;			// 计数器捕获清0选择：通道1捕获时清0
	CNT_ENABLE; 			// 使能计数器 

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
			将TIMER0配置为PWM输出功能
****************************************************************************/

void T0_Init_PWM(uint32_t PRD,uint32_t DB_CFG)
{

	TIMER0->TIM_CCMR1|= OC1M_PWM_MODE1;     // OC1M   CH1选择PWM模式1
	TIMER0->TIM_CCMR1|= OC1PE_PRELOAD_ENABLE;     // OC1PE  开启 TIM_CCR1 寄存器的预装载功能
	TIM_ARPE_ENABLE;    // 周期计数预装载允许位：TIM_ARR 寄存器有缓冲
	
	     
	TIMER0->TIM_CCER_b.CC1E = CC1E_ENABLE;   // 捕捉/比较1输出使能
	TIMER0->TIM_CCER_b.CC1NE = CC1NE_ENABLE;  // 捕捉/比较 1 互补输出使能
	TIMER0->TIM_CCER_b.CC1P = CC1P_OUTPUT_HIGH;   // 捕捉/比较1输出极性：OC1 高电平有效；
	TIMER0->TIM_CCER_b.CC1NP = CC1NP_OUTPUT_HIGH;  // 捕捉/比较1互补输出极性：OC1N 高电平有效；
	TIMER0->TIM_ARR = PRD;	       // PWM 10kHz
	TIMER0->TIM_BDTR_b.MOE = MOE_ENABLE;    // 主输出使能
	TIMER0->TIM_BDTR_b.AOE = AOE_SW_SET;
	TIMER0->TIM_BDTR_b.OSSR = 0;   // 运行模式下“关闭状态”选择
	TIMER0->TIM_BDTR_b.DTG = DB_CFG;  // 196 死区设置 OC1上升沿后延时2us，具体设置参考寄存器说明
	TIMER0->TIM_DTG1 = DB_CFG;				 // 196 死区设置 OC1N下降沿后延时2us，具体设置参考寄存器说明
	TIMER0->TIM_CCR1 = 1800;	     // 占空比设置
	TIMER0->TIM_CR1_b.CMS = CMS_CENTER_MODE3;     // 中央对齐模式 3
	EGR_CNT_UPDATE;		 // 重新初始化计数器，并产生一个 ( 寄存器 ) 更新事件
	CNT_ENABLE;    // 使能计数器

	
/*************************************************************************
			刹车输入
************************************************************************/

	
	
	TIMER0->TIM_BDTR_b.BKE = BKE_BRAKE_ENABLE;    // 刹车使能
	TIMER0->TIM_BDTR_b.BKP = BKP_BRAKE_POL_LOW;		 // 刹车极性为低电平有效
	TIMER0->TIM_BDTR_b.OSSI = 0;   // 运行模式下“空闲状态”选择
	TIMER0->TIM_CR2_b.OIS1 = OIS1_OC1_AFTER_DT_LOW;    // 输出空闲状态 1(OC1 输出 ) 
	TIMER0->TIM_CR2_b.OIS1N = OIS1N_OC1N_AFTER_DT_LOW;   // 输出空闲状态 1(OC1N 输出 ) 

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
			PWM输入模式
**********************************************************************/

void T0_PWM_MEASURE(void)
{
	
	TIM_ARPE_ENABLE;																				// 预装载使能
	TIMER0->TIM_ARR = 0xffff;
	
	TIMER0->TIM_CCMR1|=	CC1S_INPUT_IC1_To_TI1;							// CC1S通道映射到TI1
	TIMER0->TIM_CCMR1|= CC2S_INPUT_IC2_To_TI1;							// CC2S通道映射到TI2
	
	TIMER0->TIM_CCER_b.CC1P = 0;														// 极性选择上升沿
	TIMER0->TIM_CCER_b.CC2P = 1;
	
	TIMER0->TIM_SMCR_b.TS = TS_TI1FP1;											// 触发信号选择
	TIMER0->TIM_SMCR_b.SMS = SMS_RESET_MODE;								// 从模式选择复位模式
	
	TIMER0->TIM_CCER_b.CC1E = CC1E_ENABLE;									// 1通道使能
	TIMER0->TIM_CCER_b.CC2E = CC2E_ENABLE;									// 2通道使能
	
	EGR_CNT_UPDATE;																					// 更新
	CNT_ENABLE;																							// 启动计数器
	
	
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
			编码器接口模式
*************************************************************************/

void T0_ENCODER_MODE()
{
	
	TIMER0->TIM_CCMR1|= CC2S_INPUT_IC2_To_TI2;  // 捕捉 / 比较 2 选择：CC2 通道被配置为输入，IC2 映射在 TI2 上；
	TIMER0->TIM_CCMR1|= CC1S_INPUT_IC1_To_TI1;  // 捕捉 / 比较 1 选择：CC1 通道被配置为输入，IC1 映射在 TI1 上；
//	TIMER0->TIM_CCMR2|= CC3S_INPUT_IC3_To_TI3;  // 捕捉 / 比较 3 选择：CC3 通道被配置为输入，IC3 映射在 TI3 上；
	TIMER0->TIM_CCER_b.CC1P = 0;
	TIMER0->TIM_CCER_b.CC2P = 0;
	
	TIMER0->TIM_SMCR_b.SMS = SMS_ENCODER_MODE3;					//从模式选择编码器模式3
	
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
			配置TIM6通用定时器
***************************************************************************/

void TIM6_T0_Init()
{
	TIM6 -> COMPARE0 = 360000;		     // 计数比较值
	TIM6 -> CTC0_b.Freerun = 1;	     // timer在使能后一直计数
	TIM6 -> CTC0_b.COUNT0INT_EN = 1; // 中断使能位，高电平有效
	TIM6 -> CTCSEL0 = 0x08;						 // 不分频
	TIM6 -> CTC0_b.COUNTEN = 1;			 // 使能，开始计数
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
	TIM6->COMPARE1 = 5000;		     // 计数比较值
	TIM6->CTC1_b.Freerun = 1;	     // timer在使能后一直计数
	TIM6->CTC1_b.COUNT0INT_EN = 1; // 中断使能位，高电平有效
	TIM6->CTCSEL1 = 0;						 // 不分频
	TIM6->CTC1_b.COUNTEN = 1;			 // 使能，开始计数
}

