/**
* @file          : GPIO.c
* @author        : Motor Lab 
* @date          : 21/03/2018
* @brief         : This file is for GPIO configuration.
* @version       : Ver. 1.01

* H/W Platform   : SL_FOC FOR MOTOR CONTROL

*------------------------------------------------------------------------------
 
* Compiler info  : Keil v5.20
 
*------------------------------------------------------------------------------
 
* Note: In this software, the function is used in motor control.

*------------------------------------------------------------------------------

*  History:  

*              17/11/2017 ver. 1.00 Motor Lab


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

/****************************************************************************
			本文件展示了GPIO的复用功能选择
*****************************************************************************/

#include <SC32F5832.h>
#include <DevInit.h>

/**
  * @brief      .
  * @param[in]  void : AD,PA_GPIOx,gpiopin,fun_num
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * GPIO_AF_SEL(uint8_t AD,PA_Type* GPIOx,uint8_t gpiopin,uint8_t fun_num)
  * @endcode
  * @warning:
*/

void GPIO_AF_SEL(uint8_t AD,PA_Type* GPIOx,uint8_t gpiopin,uint8_t fun_num)
{
	uint32_t tmp;
	
	switch (gpiopin)
	{
		case 0x00:
			tmp=GPIOx->CFG0 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG0 =tmp|fun_num|AD;
			break;
		
		case 0x01:
			tmp=GPIOx->CFG1 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG1 =tmp|fun_num|AD;
			break;
		
		case 0x02:
			tmp=GPIOx->CFG2 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG2 =tmp|fun_num|AD;
			break;
		
		case 0x03:
			tmp=GPIOx->CFG3 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG3 =tmp|fun_num|AD;
			break;
		
		case 0x04:
			tmp=GPIOx->CFG4 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG4 =tmp|fun_num|AD;
			break;
		
		case 0x05:
			tmp=GPIOx->CFG5 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG5 =tmp|fun_num|AD;
			break;
		
		case 0x06:
			tmp=GPIOx->CFG6 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG6 =tmp|fun_num|AD;
			break;
		
		case 0x07:
			tmp=GPIOx->CFG7 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG7 =tmp|fun_num|AD;
			break;
		
		case 0x08:
			tmp=GPIOx->CFG8 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG8 =tmp|fun_num|AD;
			break;
		
		case 0x09:
			tmp=GPIOx->CFG9 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG9 =tmp|fun_num|AD;
			break;
		
		case 0x0a:
			tmp=GPIOx->CFG10 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG10 =tmp|fun_num|AD;
			break;
		
		case 0x0b:
			tmp=GPIOx->CFG11 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG11 =tmp|fun_num|AD;
			break;
		
		case 0x0c:
			tmp=GPIOx->CFG12 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG12 =tmp|fun_num|AD;
			break;
		
		case 0x0d:
			tmp=GPIOx->CFG13 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG13 =tmp|fun_num|AD;
			break;
		
		case 0x0e:
			tmp=GPIOx->CFG14 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG14 =tmp|fun_num|AD;
			break;
		
		case 0x0f:
			tmp=GPIOx->CFG15 &=0xffffffe8ul;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG15 =tmp|fun_num|AD;
			break;
		
		default:
			break;
	}
}
/**
  * @brief      .
  * @param[in]  void : OD,PA_GPIOx,gpiopin
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * GPIO_OD_SEL(uint8_t OD,PA_Type* GPIOx,uint8_t gpiopin)
  * @endcode
  * @warning:
*/

/*****************************************************************************************
																	开漏模式使能/禁止
*****************************************************************************************/
void GPIO_OD_SEL(uint8_t OD,PA_Type* GPIOx,uint8_t gpiopin)
{
	uint32_t tmp;
	
	switch (gpiopin)
	{
		case 0x00:
			tmp=GPIOx->CFG0 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG0 =tmp|OD;
			break;
		
		case 0x01:
			tmp=GPIOx->CFG1 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG1 =tmp|OD;
			break;
		
		case 0x02:
			tmp=GPIOx->CFG2 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG2 =tmp|OD;
			break;
		
		case 0x03:
			tmp=GPIOx->CFG3 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG3 =tmp|OD;
			break;
		
		case 0x04:
			tmp=GPIOx->CFG4 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG4 =tmp|OD;
			break;
		
		case 0x05:
			tmp=GPIOx->CFG5 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG5 =tmp|OD;
			break;
		
		case 0x06:
			tmp=GPIOx->CFG6 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG6 =tmp|OD;
			break;
		
		case 0x07:
			tmp=GPIOx->CFG7 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG7 =tmp|OD;
			break;
		
		case 0x08:
			tmp=GPIOx->CFG8 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG8 =tmp|OD;
			break;
		
		case 0x09:
			tmp=GPIOx->CFG9 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG9 =tmp|OD;
			break;
		
		case 0x0a:
			tmp=GPIOx->CFG10 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG10 =tmp|OD;
			break;
		
		case 0x0b:
			tmp=GPIOx->CFG11 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG11 =tmp|OD;
			break;
		
		case 0x0c:
			tmp=GPIOx->CFG12 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG12 =tmp|OD;
			break;
		
		case 0x0d:
			tmp=GPIOx->CFG13 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG13 =tmp|OD;
			break;
		
		case 0x0e:
			tmp=GPIOx->CFG14 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG14 =tmp|OD;
			break;
		
		case 0x0f:
			tmp=GPIOx->CFG15 &=0xffffdffful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG15 =tmp|OD;
			break;
		
		default:
			break;
	}
}
/**
  * @brief      .
  * @param[in]  void : DRV,PA_GPIOx,gpiopin
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * GPIO_DRV_SEL(uint8_t DRV,PA_Type* GPIOx,uint8_t gpiopin)
  * @endcode
  * @warning:
*/

/**********************************************************************************
															高/低驱动模式选择
**********************************************************************************/
void GPIO_DRV_SEL(uint8_t DRV,PA_Type* GPIOx,uint8_t gpiopin)
{
	uint32_t tmp;
	
	switch (gpiopin)
	{
		case 0x00:
			tmp=GPIOx->CFG0 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG0 =tmp|DRV;
			break;
		
		case 0x01:
			tmp=GPIOx->CFG1 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG1 =tmp|DRV;
			break;
		
		case 0x02:
			tmp=GPIOx->CFG2 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG2 =tmp|DRV;
			break;
		
		case 0x03:
			tmp=GPIOx->CFG3 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG3 =tmp|DRV;
			break;
		
		case 0x04:
			tmp=GPIOx->CFG4 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG4 =tmp|DRV;
			break;
		
		case 0x05:
			tmp=GPIOx->CFG5 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG5 =tmp|DRV;
			break;
		
		case 0x06:
			tmp=GPIOx->CFG6 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG6 =tmp|DRV;
			break;
		
		case 0x07:
			tmp=GPIOx->CFG7 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG7 =tmp|DRV;
			break;
		
		case 0x08:
			tmp=GPIOx->CFG8 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG8 =tmp|DRV;
			break;
		
		case 0x09:
			tmp=GPIOx->CFG9 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG9 =tmp|DRV;
			break;
		
		case 0x0a:
			tmp=GPIOx->CFG10 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG10 =tmp|DRV;
			break;
		
		case 0x0b:
			tmp=GPIOx->CFG11 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG11 =tmp|DRV;
			break;
		
		case 0x0c:
			tmp=GPIOx->CFG12 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG12 =tmp|DRV;
			break;
		
		case 0x0d:
			tmp=GPIOx->CFG13 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG13 =tmp|DRV;
			break;
		
		case 0x0e:
			tmp=GPIOx->CFG14 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG14 =tmp|DRV;
			break;
		
		case 0x0f:
			tmp=GPIOx->CFG15 &=0xfffffbfful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG15 =tmp|DRV;
			break;
		
		default:
			break;
	}
}
/**
  * @brief      .
  * @param[in]  void : PUPD,PA_GPIOx,gpiopin
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * GPIO_PUPD_SEL(uint8_t PUPD,PA_Type* GPIOx,uint8_t gpiopin)
  * @endcode
  * @warning:
*/

/**********************************************************************************
															上/下拉选择
**********************************************************************************/

void GPIO_PUPD_SEL(uint8_t PUPD,PA_Type* GPIOx,uint8_t gpiopin)
{
	uint32_t tmp;
	
	switch (gpiopin)
	{
		case 0x00:
			tmp=GPIOx->CFG0 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG0 =tmp|PUPD;
			break;
		
		case 0x01:
			tmp=GPIOx->CFG1 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG1 =tmp|PUPD;
			break;
		
		case 0x02:
			tmp=GPIOx->CFG2 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG2 =tmp|PUPD;
			break;
		
		case 0x03:
			tmp=GPIOx->CFG3 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG3 =tmp|PUPD;
			break;
		
		case 0x04:
			tmp=GPIOx->CFG4 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG4 =tmp|PUPD;
			break;
		
		case 0x05:
			tmp=GPIOx->CFG5 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG5 =tmp|PUPD;
			break;
		
		case 0x06:
			tmp=GPIOx->CFG6 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG6 =tmp|PUPD;
			break;
		
		case 0x07:
			tmp=GPIOx->CFG7 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG7 =tmp|PUPD;
			break;
		
		case 0x08:
			tmp=GPIOx->CFG8 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG8 =tmp|PUPD;
			break;
		
		case 0x09:
			tmp=GPIOx->CFG9 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG9 =tmp|PUPD;
			break;
		
		case 0x0a:
			tmp=GPIOx->CFG10 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG10 =tmp|PUPD;
			break;
		
		case 0x0b:
			tmp=GPIOx->CFG11 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG11 =tmp|PUPD;
			break;
		
		case 0x0c:
			tmp=GPIOx->CFG12 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG12 =tmp|PUPD;
			break;
		
		case 0x0d:
			tmp=GPIOx->CFG13 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG13 =tmp|PUPD;
			break;
		
		case 0x0e:
			tmp=GPIOx->CFG14 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG14 =tmp|PUPD;
			break;
		
		case 0x0f:
			tmp=GPIOx->CFG15 &=0xffffff3ful;
			SYSREG->ACCESS_EN=0x05fa659aul;
			GPIOx->CFG15 =tmp|PUPD;
			break;
		
		default:
			break;
	}
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
  * GPIO_Init();
  * @endcode
  * @warning:
*/

/***************************************************************************************
										复用管脚功能选择初始化列表
****************************************************************************************/
void GPIO_Init()
{
	
//		GPIO_AF_SEL(DIGITAL,PA,8,2);       // PWM1A
//		GPIO_AF_SEL(DIGITAL,PA,9,2);			 // PWM2B
//		GPIO_AF_SEL(DIGITAL,PA,10,2);		   // PWM2A
//	  GPIO_AF_SEL(DIGITAL,PB,13,2);			 // PWM0B
//		GPIO_AF_SEL(DIGITAL,PB,14,2);			 // PWM0A
//		GPIO_AF_SEL(DIGITAL,PB,15,2);			 // PWM1B
//	
//		GPIO_AF_SEL(DIGITAL,PA,11,7);			 // TIM_CH1
//		GPIO_AF_SEL(DIGITAL,PA,12,7);			 // TIM_CH1N
//		GPIO_AF_SEL(DIGITAL,PB,12,4);			 // TIM_BKIN
//	
//		GPIO_AF_SEL(DIGITAL,PB,2,5);			 // PB2选择XCLKOUT复用功能
//	
//		GPIO_AF_SEL(ANALOGY,PB,11,0);			 // ADCB6
//		GPIO_AF_SEL(ANALOGY,PC,13,0);			 // ADCB7
//	
//		GPIO_AF_SEL(ANALOGY,PA,0,0);			 // OPA0P
//	
//		GPIO_AF_SEL(ANALOGY,PB,0,0);			 // OPA2P
//	
//		GPIO_AF_SEL(DIGITAL,PB,8,5);			 // TIM_CH2	
//		GPIO_AF_SEL(DIGITAL,PB,9,5);			 // TIM_CH2N
//		GPIO_AF_SEL(DIGITAL,PC,0,1);			 // TIM_CH3
//		GPIO_AF_SEL(DIGITAL,PB,1,6);			 // TIM_CH3N
//		
//		GPIO_AF_SEL(DIGITAL,PC,6,3);   	 // PC6选择UART0_TX功能
//		GPIO_AF_SEL(DIGITAL,PA,15,3);  		 // PA15选择UART0_RX功能

		GPIO_AF_SEL(DIGITAL,PA,0,0);
		GPIO_AF_SEL(DIGITAL,PA,1,0);
		GPIO_AF_SEL(DIGITAL,PA,2,0);
	  GPIO_AF_SEL(DIGITAL,PA,3,0);
		GPIO_AF_SEL(DIGITAL,PA,4,0);
		GPIO_AF_SEL(DIGITAL,PA,5,0);
		GPIO_AF_SEL(DIGITAL,PA,6,0);
		GPIO_AF_SEL(DIGITAL,PA,7,0);
		GPIO_AF_SEL(DIGITAL,PA,8,0);
		GPIO_AF_SEL(DIGITAL,PA,9,0);
		GPIO_AF_SEL(DIGITAL,PA,10,0);
		
		GPIO_PUPD_SEL(PUPD_PD, PB, 0 );
		GPIO_PUPD_SEL(PUPD_PD, PB, 1 );
		GPIO_PUPD_SEL(PUPD_PD, PB, 2 );
		GPIO_PUPD_SEL(PUPD_PD, PB, 3 );
		GPIO_PUPD_SEL(PUPD_PD, PB, 4 );
		GPIO_PUPD_SEL(PUPD_PD, PB, 5 );
		GPIO_PUPD_SEL(PUPD_PD, PB, 6 );
		GPIO_PUPD_SEL(PUPD_PD, PB, 7 );
		GPIO_PUPD_SEL(PUPD_PU, PB, 8 );
		GPIO_PUPD_SEL(PUPD_PU, PB, 9 );
		GPIO_PUPD_SEL(PUPD_PU, PB, 10 );

//		GPIO_AF_SEL(DIGITAL, PA, 2, 1);   	 // PA2选择UART0_TX功能
//		GPIO_AF_SEL(DIGITAL, PA, 3, 1);  		 // PA3选择UART0_RX功能
		
		//PB0 - PB7 -> LED1 - LED8
		GPIO_AF_SEL(DIGITAL, PB, 0, 0);       // LED1 - D9
		GPIO_AF_SEL(DIGITAL, PB, 1, 0);       // LED2 - D10
		GPIO_AF_SEL(DIGITAL, PB, 2, 0);       // LED3 - D11
		GPIO_AF_SEL(DIGITAL, PB, 3, 0);       // LED4 - D12
		GPIO_AF_SEL(DIGITAL, PB, 4, 0);       // LED5 - D13
		GPIO_AF_SEL(DIGITAL, PB, 5, 0);       // LED6 - D14
		GPIO_AF_SEL(DIGITAL, PB, 6, 0);       // LED7 - D15
		GPIO_AF_SEL(DIGITAL, PB, 7, 0);       // LED8 - D16
		
		//PB8 - PB15 -> 矩阵键盘
		GPIO_AF_SEL(DIGITAL, PB, 8, 0);       // LED1 - D9
		GPIO_AF_SEL(DIGITAL, PB, 9, 0);       // LED2 - D10
		GPIO_AF_SEL(DIGITAL, PB, 10, 0);      // LED3 - D11
		GPIO_AF_SEL(DIGITAL, PB, 11, 0);      // LED4 - D12
		GPIO_AF_SEL(DIGITAL, PB, 12, 0);      // LED5 - D13
		GPIO_AF_SEL(DIGITAL, PB, 13, 0);      // LED6 - D14
		GPIO_AF_SEL(DIGITAL, PB, 14, 0);      // LED7 - D15
		GPIO_AF_SEL(DIGITAL, PB, 15, 0);      // LED8 - D16
		
		//按键 PA0 -> SB1 PA1 -> SB2 PA10 -> SB3 PA11 -> SB4
		GPIO_AF_SEL(DIGITAL, PA, 0, 0);       // 按键1 - SB1
		GPIO_AF_SEL(DIGITAL, PA, 1, 0);       // 按键2 - SB2
		GPIO_AF_SEL(DIGITAL, PA, 10, 0);      // 按键3 - SB3
		GPIO_AF_SEL(DIGITAL, PA, 11, 0);      // 按键4 - SB4
		
		//按键端口配置 浮空
		GPIO_PUPD_SEL(PUPD_NULL, PA, 0 );
		GPIO_PUPD_SEL(PUPD_NULL, PA, 1 );
		GPIO_PUPD_SEL(PUPD_NULL, PA, 10 );
		GPIO_PUPD_SEL(PUPD_NULL, PA, 11 );
		
		//矩阵键盘端口配置 浮空
		GPIO_PUPD_SEL(PUPD_NULL, PB, 8 );
		GPIO_PUPD_SEL(PUPD_NULL, PB, 9 );
		GPIO_PUPD_SEL(PUPD_NULL, PB, 10 );
		GPIO_PUPD_SEL(PUPD_NULL, PB, 11 );
		
//		//蜂鸣器 -> PA12 
//		GPIO_AF_SEL(DIGITAL, PA, 12, 0);       //蜂鸣器 - PA12
		
	
//		GPIO_AF_SEL(DIGITAL,PB,6,3);			 // PB6选择UART1_TX功能
//		GPIO_AF_SEL(DIGITAL,PB,7,3);			 // PB7选择UART1_RX功能
		
	
}
