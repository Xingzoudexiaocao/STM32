/**
* @file          : CMP.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for CMP configuration.
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
/***************************************************************************
							本文件展示了比较器的初始化设置
****************************************************************************/

#include <SC32F5832.h>
#include <DevInit.h>

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
  * CMP0_Init();
  * @endcode
  * @warning:
*/

/******************************************************************************
		比较器CMP0初始化
******************************************************************************/

void CMP0_Init()
{
	 
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0PS = C0PS_INPUT_SEL_OPA_OUTPUT;	    // 正端选择运放输出
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0OPS = C0OPS_SEL_OP0O;								//	选择OPA0的输出作为正端输入
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0EN = CMP_ENABLE;	     							// 比较器0使能
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0RDS = 16;	     // 参考电压参数,在VRRH=1，VRRL=1时，对应16/32*VS=2.5V
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0VRRL = 1;	     // 参考电压内部分压阶梯调整位（低位）
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0VRRH = 1;	     // 参考电压内部分压阶梯调整位（高位）
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0VRHS = VRHS_SOURCE_SEL_VDD;          // 分压阶梯电源选择VDD
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0REFEN = REFEN_INTERN_REF_ENABLE; 	     // 内部参考电压使能
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0HYSEN = HYSEN_WITHOUT_HYSTERESIS;          // 没有迟滞
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0NS = C0NS_NEG_INPUT_SEL_CVREF0;	      // 负端输入选择位，选择CVREF0
	 
	 
	 ACCESS_ENABLE;
	 ACMP->CP0CFG_b.C0INTS = INTS_RE;	      // 中断类型选择上升沿
	 ACCESS_ENABLE;
	 ACMP->CP0CFG_b.C0INTM = INTM_INT_ENABLE;            // 不屏蔽中断
	 
	 ACCESS_ENABLE;
	 ACMP->CP0CFG_b.C0DFILT = 3;   // 窗口设置为3个周期，对应1us
	 ACCESS_ENABLE;
	 ACMP->CP0CFG|=(1<<19);				 // 关闭32预分频
	 ACCESS_ENABLE;
	 ACMP->CP0CFG_b.C0CLKD = 23;   // 24分频
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0AFILT = 0;   // 关闭模拟滤波
	 
		
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
  * CP10_Init();
  * @endcode
  * @warning:
*/

/****************************************************************************
		比较器CP10初始化
****************************************************************************/

void CP10_Init()
{

	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C10PS = C1PS_INPUT_SEL_PIN;	     // 正端选择外部管脚输入
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C10EN = CMP_ENABLE;	     // 比较器10使能
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1RDS = 8;	     // 参考电压参数，在VRRH=0，VRRL=1时，对应8/24*VS=1.667V
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRL = 1;	     // 参考电压内部分压阶梯调整位（低位）
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRH = 0;	     // 参考电压内部分压阶梯调整位（高位）
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRHS = VRHS_SOURCE_SEL_VDD;          // 分压阶梯电源选择VDD
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1REFEN = REFEN_INTERN_REF_ENABLE; 	     // 内部参考电压使能
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1HYSEN = HYSEN_WITHOUT_HYSTERESIS;          // 没有迟滞
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1NS = C1NS_NEG_INPUT_SEL_CVREF0;	      // 负端输入选择位，选择CVREF0
	 
	 
	 ACCESS_ENABLE;
	 ACMP->CP10CFG_b.C10INTS = INTS_FE_RE;	      // 中断类型选择双沿
	 ACCESS_ENABLE;
	 ACMP->CP10CFG_b.C10INTM = INTM_INT_ENABLE;            // 不屏蔽中断
		
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
  * CP11_Init();
  * @endcode
  * @warning:
*/

 /*******************************************************************************
		比较器CP11初始化
*******************************************************************************/
  
void CP11_Init()
{

	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C11PS = C1PS_INPUT_SEL_PIN;	     // 正端选择外部管脚输入
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C11EN = CMP_ENABLE;	     // 比较器11使能
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1RDS = 8;	     // 参考电压参数，在VRRH=0，VRRL=1时，对应8/24*VS=1.667V
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRL = 1;	     // 参考电压内部分压阶梯调整位（低位）
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRH = 0;	     // 参考电压内部分压阶梯调整位（高位）
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRHS = VRHS_SOURCE_SEL_VDD;          // 分压阶梯电源选择VDD
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1REFEN = REFEN_INTERN_REF_ENABLE; 	     // 内部参考电压使能
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1HYSEN = HYSEN_WITHOUT_HYSTERESIS;          // 没有迟滞
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1NS = C1NS_NEG_INPUT_SEL_CVREF0;	      // 负端输入选择位，选择CVREF0
	 
	 
	 ACCESS_ENABLE;
	 ACMP->CP11CFG_b.C11INTS = INTS_FE_RE;	      // 中断类型选择双沿
	 ACCESS_ENABLE;
	 ACMP->CP11CFG_b.C11INTM = INTM_INT_ENABLE;            // 不屏蔽中断
		
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
  * CP12_Init();
  * @endcode
  * @warning:
*/


/*****************************************************************************
		比较器CP12初始化
*******************************************************************************/
 
void CP12_Init()
{
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C12PS = C1PS_INPUT_SEL_PIN;	     // 正端选择外部管脚输入
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C12EN = CMP_ENABLE;	     // 比较器12使能
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1RDS = 8;	     // 参考电压参数，在VRRH=0，VRRL=1时，对应8/24*VS=1.667V
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRL = 1;	     // 参考电压内部分压阶梯调整位（低位）
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRH = 0;	     // 参考电压内部分压阶梯调整位（高位）
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRHS = VRHS_SOURCE_SEL_VDD;          // 分压阶梯电源选择VDD
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1REFEN = REFEN_INTERN_REF_ENABLE; 	     // 内部参考电压使能
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1HYSEN = HYSEN_WITHOUT_HYSTERESIS;          // 没有迟滞
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1NS = C1NS_NEG_INPUT_SEL_CVREF0;	      // 负端输入选择位，选择CVREF0
	 
	 
	 ACCESS_ENABLE;
	 ACMP->CP12CFG_b.C12INTS = INTS_FE_RE;	      // 中断类型选择双沿
	 ACCESS_ENABLE;
	 ACMP->CP12CFG_b.C12INTM = INTM_INT_ENABLE;            // 不屏蔽中断
		
}

