/**
* @file          : CLK.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for CLK configuration.
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
   本文件展示了时钟系统的配置过程，使用SC32F5832芯片的最高工作频率72MHz
*************************************************************************/

#include <SC32F5832.h>
#include <DevInit.h>

/**
  * @brief      .
  * @param[in]  void : pllsrc,plldiv,pllmul
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * PLLSET(uint8_t pllsrc,uint8_t plldiv,uint8_t pllmul)
  * @endcode
  * @warning:
*/


/*************************************************************************
								设置PLL的时钟源、分频和倍频系数
*************************************************************************/

void PLLSET(uint8_t pllsrc,uint8_t plldiv,uint8_t pllmul)
{
	uint32_t temp;
	temp = CHIPCTL->CLKCFG0&=0xfffff30e;
	temp|=pllsrc|(plldiv<<4)|(pllmul<<10);  // 选择RCH16M，倍频，分频
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCFG0 = temp;
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
  * OPENPLL();
  * @endcode
  * @warning:
*/

/*************************************************************************
								启动PLL时钟
****************************************************************************/
void OPENPLL(void)
{
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCTRL|=PLLEN;							 // pll使能
	while((CHIPCTL->CLKCTRL&PLLLOCK)==0);  // 等待PLL锁定
}
/**
  * @brief      .
  * @param[in]  void : oscgain,oscsts
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * OSCSET(uint8_t oscgain,uint8_t oscsts)
  * @endcode
  * @warning:
*/
/*************************************************************************
								设置外部晶振的稳定时间，选择晶振的增益
*************************************************************************/

void OSCSET(uint8_t oscgain,uint8_t oscsts)
{
	uint32_t temp;
	temp=CHIPCTL->CLKCTRL&=0xfffffccf;
	temp|=(oscgain<<4)|(oscsts<<8);     //外部晶振稳定时间选择，外接晶振增益选择
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCTRL=temp;
}
/**
  * @brief      .
  * @param[in]  void : oscgain,oscsts
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * OPENOSC();
  * @endcode
  * @warning:
*/
/****************************************************************************
								启动外部晶振
****************************************************************************/

void OPENOSC(void)
{
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCTRL|=OSCEN;						// 晶振使能
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCTRL|=OSCDEN;						// 晶振检测使能
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCTRL|=OSCREN;						// 外部晶振内置反馈电阻选择：有效
	CHIPKEY_ENABLE;
	CHIPCTL->POWER_CTRL|=DCTEN;					// 系统时钟检测使能：当检测到正在使用的时钟源不稳定或丢失，直接将时钟切换到到rch16m

	while(CHIPCTL->CLKCTRL&(1<<2));					// 检测外部晶振停振标志位
	while((CHIPCTL->CLKCTRL&OSCSTB)==0);    // 外部晶振稳定标志
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
  * SetPll();
  * @endcode
  * @warning:
*/
/***********************************************************
									设置PLL时钟（PLL最高144MHz）
***********************************************************/

void SetPll(void)
{		
	
//	OSCSET(OSCGAIN4_8,OSCSTB32MS);
//	OPENOSC();
	CHIPKEY_ENABLE;
	CHIPCTL->POWER_CTRL_b.MVRSEL = 1;       //  内核电压提高为1.7V
	
	PLLSET(PLLSRC_RCH,PLLDIV4,PLLMUL36);		//  16/4*36 = 144   PLL 144MHz	时钟源选择内部RCH16M
//	PLLSET(PLLSRC_OSC,PLLDIV1,PLLMUL36);  //   4/1*36 = 144   PLL 144Mhz	时钟源选择4MHz外部晶振
	OPENPLL();
	
	CHIPKEY_ENABLE;
	CHIPCTL->STATUS0 = 0xa05fccccul;				// 清除寄存器中所有事件
	CHIPKEY_ENABLE;
	CHIPCTL->INTMASK&=~OSC_MISS_MASK;				// 使能时钟不稳定中断
	
/*************************************************************************
								设置HDIV时钟
*************************************************************************/
	
	CHIPKEY_ENABLE;
	CHIPCTL -> CLKCFG2 = 0;
	CHIPKEY_ENABLE;
	CHIPCTL -> CLKCFG2_b.HDIV = 1;	// (1)2分频  72MHz

/************************************************************************
								设置MTDIV时钟
************************************************************************/

	CHIPKEY_ENABLE;
//	CHIPCTL->CLKCFG2_b.MTDIV = 0;	// 不分频
	CHIPCTL->CLKCFG2_b.MTDIV = 1;	  //(1) 2分频  72MHz
//	CHIPCTL->CLKCFG2_b.MTDIV = 2;	// 3分频

//	IAP->CFG = ((1<<4)|(1<<2)|(2<<0));
/**********************************************************************
								调试时钟输出时使用
**********************************************************************/	

//	GPIO_AF_SEL(DIGITAL,PB,2,5);			// PB2选择XCLKOUT复用功能
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCFG0_b.XCLKSEL = 8;	 	// clkout选择sysclk
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCFG0_b.XCLKDIV = 4;  		// clkout 16分频
/**********************************************************************
								系统时钟切换到PLL时钟
**********************************************************************/ 
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCFG1_b.SYSCLKSEL = 2;  	// SYSCLK = PLLCLK 
	while(CHIPCTL->CLKCFG1_b.SYSCLKLOCK==0);   // 等待pll锁定
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
  * SetSysTick();
  * @endcode
  * @warning:
*/
/**********************************************************************
									设置SYSTICK时钟
**********************************************************************/

void SetSysTick(void)
{
	CHIPKEY_ENABLE;
	CHIPCTL -> CLKCFG1_b.SYSTICKSEL = 2;// systick时钟源选择rch16M的16分频

	SysTick -> LOAD = 999;	// 1Mhz下为1ms
	SysTick -> VAL = 0x00ul;
	SysTick -> CTRL = 0x03ul;   
}
