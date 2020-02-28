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
   ���ļ�չʾ��ʱ��ϵͳ�����ù��̣�ʹ��SC32F5832оƬ����߹���Ƶ��72MHz
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
								����PLL��ʱ��Դ����Ƶ�ͱ�Ƶϵ��
*************************************************************************/

void PLLSET(uint8_t pllsrc,uint8_t plldiv,uint8_t pllmul)
{
	uint32_t temp;
	temp = CHIPCTL->CLKCFG0&=0xfffff30e;
	temp|=pllsrc|(plldiv<<4)|(pllmul<<10);  // ѡ��RCH16M����Ƶ����Ƶ
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
								����PLLʱ��
****************************************************************************/
void OPENPLL(void)
{
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCTRL|=PLLEN;							 // pllʹ��
	while((CHIPCTL->CLKCTRL&PLLLOCK)==0);  // �ȴ�PLL����
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
								�����ⲿ������ȶ�ʱ�䣬ѡ���������
*************************************************************************/

void OSCSET(uint8_t oscgain,uint8_t oscsts)
{
	uint32_t temp;
	temp=CHIPCTL->CLKCTRL&=0xfffffccf;
	temp|=(oscgain<<4)|(oscsts<<8);     //�ⲿ�����ȶ�ʱ��ѡ����Ӿ�������ѡ��
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
								�����ⲿ����
****************************************************************************/

void OPENOSC(void)
{
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCTRL|=OSCEN;						// ����ʹ��
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCTRL|=OSCDEN;						// ������ʹ��
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCTRL|=OSCREN;						// �ⲿ�������÷�������ѡ����Ч
	CHIPKEY_ENABLE;
	CHIPCTL->POWER_CTRL|=DCTEN;					// ϵͳʱ�Ӽ��ʹ�ܣ�����⵽����ʹ�õ�ʱ��Դ���ȶ���ʧ��ֱ�ӽ�ʱ���л�����rch16m

	while(CHIPCTL->CLKCTRL&(1<<2));					// ����ⲿ����ͣ���־λ
	while((CHIPCTL->CLKCTRL&OSCSTB)==0);    // �ⲿ�����ȶ���־
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
									����PLLʱ�ӣ�PLL���144MHz��
***********************************************************/

void SetPll(void)
{		
	
//	OSCSET(OSCGAIN4_8,OSCSTB32MS);
//	OPENOSC();
	CHIPKEY_ENABLE;
	CHIPCTL->POWER_CTRL_b.MVRSEL = 1;       //  �ں˵�ѹ���Ϊ1.7V
	
	PLLSET(PLLSRC_RCH,PLLDIV4,PLLMUL36);		//  16/4*36 = 144   PLL 144MHz	ʱ��Դѡ���ڲ�RCH16M
//	PLLSET(PLLSRC_OSC,PLLDIV1,PLLMUL36);  //   4/1*36 = 144   PLL 144Mhz	ʱ��Դѡ��4MHz�ⲿ����
	OPENPLL();
	
	CHIPKEY_ENABLE;
	CHIPCTL->STATUS0 = 0xa05fccccul;				// ����Ĵ����������¼�
	CHIPKEY_ENABLE;
	CHIPCTL->INTMASK&=~OSC_MISS_MASK;				// ʹ��ʱ�Ӳ��ȶ��ж�
	
/*************************************************************************
								����HDIVʱ��
*************************************************************************/
	
	CHIPKEY_ENABLE;
	CHIPCTL -> CLKCFG2 = 0;
	CHIPKEY_ENABLE;
	CHIPCTL -> CLKCFG2_b.HDIV = 1;	// (1)2��Ƶ  72MHz

/************************************************************************
								����MTDIVʱ��
************************************************************************/

	CHIPKEY_ENABLE;
//	CHIPCTL->CLKCFG2_b.MTDIV = 0;	// ����Ƶ
	CHIPCTL->CLKCFG2_b.MTDIV = 1;	  //(1) 2��Ƶ  72MHz
//	CHIPCTL->CLKCFG2_b.MTDIV = 2;	// 3��Ƶ

//	IAP->CFG = ((1<<4)|(1<<2)|(2<<0));
/**********************************************************************
								����ʱ�����ʱʹ��
**********************************************************************/	

//	GPIO_AF_SEL(DIGITAL,PB,2,5);			// PB2ѡ��XCLKOUT���ù���
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCFG0_b.XCLKSEL = 8;	 	// clkoutѡ��sysclk
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCFG0_b.XCLKDIV = 4;  		// clkout 16��Ƶ
/**********************************************************************
								ϵͳʱ���л���PLLʱ��
**********************************************************************/ 
	CHIPKEY_ENABLE;
	CHIPCTL->CLKCFG1_b.SYSCLKSEL = 2;  	// SYSCLK = PLLCLK 
	while(CHIPCTL->CLKCFG1_b.SYSCLKLOCK==0);   // �ȴ�pll����
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
									����SYSTICKʱ��
**********************************************************************/

void SetSysTick(void)
{
	CHIPKEY_ENABLE;
	CHIPCTL -> CLKCFG1_b.SYSTICKSEL = 2;// systickʱ��Դѡ��rch16M��16��Ƶ

	SysTick -> LOAD = 999;	// 1Mhz��Ϊ1ms
	SysTick -> VAL = 0x00ul;
	SysTick -> CTRL = 0x03ul;   
}
