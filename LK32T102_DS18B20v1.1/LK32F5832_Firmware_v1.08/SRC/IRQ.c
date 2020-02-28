/**
* @file          : IRQ.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for IRQ configuration.
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

/*********************************************************************
	���ļ�չʾ���жϵĳ�ʼ���Լ��򿪺͹ر��ж�
********************************************************************/

#include <SC32F5832.h>


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
  * IRQ_Init();
  * @endcode
  * @warning:
*/

/********************************************************************
				�жϳ�ʼ���������ж����ȼ���0Ϊ���
********************************************************************/

void IRQ_Init()
{
//	NVIC_ClearPendingIRQ(SysTick_IRQn);   //ϵͳ�δ�ʱ���ж����
//  NVIC_SetPriority(SysTick_IRQn,3); 		//ϵͳ�δ�ʱ�����ȼ�����

	
	NVIC_ClearPendingIRQ(PWM0_IRQn);
	NVIC_SetPriority(PWM0_IRQn,1);

	
	NVIC_ClearPendingIRQ(TIMER0_IRQn);		
  NVIC_SetPriority(TIMER0_IRQn,0); 			
	
	NVIC_ClearPendingIRQ(ADC_IRQn);		
  NVIC_SetPriority(ADC_IRQn,1); 
 
	
	NVIC_ClearPendingIRQ(TIM6_T0_IRQn);
  NVIC_SetPriority(TIM6_T0_IRQn,2); 

	NVIC_ClearPendingIRQ(TIM6_T1_IRQn);
	NVIC_SetPriority(TIM6_T1_IRQn,2); 
	
	NVIC_ClearPendingIRQ(UART0_IRQn);//���UART0�ж�
	NVIC_SetPriority(UART0_IRQn,3);

	
	NVIC_ClearPendingIRQ(UART1_IRQn);
	NVIC_SetPriority(UART1_IRQn,3);
	
	NVIC_ClearPendingIRQ(ACMP_OPA_IRQn);
	NVIC_SetPriority(ACMP_OPA_IRQn,0);
	
	NVIC_ClearPendingIRQ(PA_IRQn);
	NVIC_SetPriority(PA_IRQn,0);
	
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
  * IRQ_Enable();
  * @endcode
  * @warning:
*/

/*******************************************************************
				���ж�
********************************************************************/

void IRQ_Enable()
{
	
	//NVIC_EnableIRQ(SysTick_IRQn);	//ϵͳ�δ�ʱ���ж�����
	
	NVIC_EnableIRQ(PWM0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);	
	NVIC_EnableIRQ(ADC_IRQn);	
	
	NVIC_EnableIRQ(TIM6_T0_IRQn);
	
	NVIC_EnableIRQ(TIM6_T1_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);//����UART0�ж�
	
	NVIC_EnableIRQ(PA_IRQn);
	NVIC_EnableIRQ(PB_IRQn);
	NVIC_EnableIRQ(PC_IRQn);
//	NVIC_EnableIRQ(UART1_IRQn);
//	NVIC_EnableIRQ(ACMP_OPA_IRQn);
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
  * IRQ_Disable();
  * @endcode
  * @warning:
*/

/*******************************************************************
				�ر��ж�
********************************************************************/

void IRQ_Disable()
{
	NVIC_DisableIRQ(SysTick_IRQn);
	NVIC_DisableIRQ(PWM0_IRQn);
	NVIC_DisableIRQ(TIMER0_IRQn);
	NVIC_DisableIRQ(ADC_IRQn);
	NVIC_DisableIRQ(TIM6_T0_IRQn);
	NVIC_DisableIRQ(TIM6_T1_IRQn);
	NVIC_DisableIRQ(UART0_IRQn);
	NVIC_DisableIRQ(UART1_IRQn);
	NVIC_DisableIRQ(ACMP_OPA_IRQn);
	
	NVIC_DisableIRQ(PA_IRQn);
	NVIC_DisableIRQ(PB_IRQn);
	NVIC_DisableIRQ(PC_IRQn);
	
}
