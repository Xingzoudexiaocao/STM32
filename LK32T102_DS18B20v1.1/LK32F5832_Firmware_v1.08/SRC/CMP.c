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
							���ļ�չʾ�˱Ƚ����ĳ�ʼ������
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
		�Ƚ���CMP0��ʼ��
******************************************************************************/

void CMP0_Init()
{
	 
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0PS = C0PS_INPUT_SEL_OPA_OUTPUT;	    // ����ѡ���˷����
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0OPS = C0OPS_SEL_OP0O;								//	ѡ��OPA0�������Ϊ��������
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0EN = CMP_ENABLE;	     							// �Ƚ���0ʹ��
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0RDS = 16;	     // �ο���ѹ����,��VRRH=1��VRRL=1ʱ����Ӧ16/32*VS=2.5V
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0VRRL = 1;	     // �ο���ѹ�ڲ���ѹ���ݵ���λ����λ��
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0VRRH = 1;	     // �ο���ѹ�ڲ���ѹ���ݵ���λ����λ��
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0VRHS = VRHS_SOURCE_SEL_VDD;          // ��ѹ���ݵ�Դѡ��VDD
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0REFEN = REFEN_INTERN_REF_ENABLE; 	     // �ڲ��ο���ѹʹ��
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0HYSEN = HYSEN_WITHOUT_HYSTERESIS;          // û�г���
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0NS = C0NS_NEG_INPUT_SEL_CVREF0;	      // ��������ѡ��λ��ѡ��CVREF0
	 
	 
	 ACCESS_ENABLE;
	 ACMP->CP0CFG_b.C0INTS = INTS_RE;	      // �ж�����ѡ��������
	 ACCESS_ENABLE;
	 ACMP->CP0CFG_b.C0INTM = INTM_INT_ENABLE;            // �������ж�
	 
	 ACCESS_ENABLE;
	 ACMP->CP0CFG_b.C0DFILT = 3;   // ��������Ϊ3�����ڣ���Ӧ1us
	 ACCESS_ENABLE;
	 ACMP->CP0CFG|=(1<<19);				 // �ر�32Ԥ��Ƶ
	 ACCESS_ENABLE;
	 ACMP->CP0CFG_b.C0CLKD = 23;   // 24��Ƶ
	 ACCESS_ENABLE;
	 ACMP->CP0CON_b.C0AFILT = 0;   // �ر�ģ���˲�
	 
		
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
		�Ƚ���CP10��ʼ��
****************************************************************************/

void CP10_Init()
{

	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C10PS = C1PS_INPUT_SEL_PIN;	     // ����ѡ���ⲿ�ܽ�����
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C10EN = CMP_ENABLE;	     // �Ƚ���10ʹ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1RDS = 8;	     // �ο���ѹ��������VRRH=0��VRRL=1ʱ����Ӧ8/24*VS=1.667V
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRL = 1;	     // �ο���ѹ�ڲ���ѹ���ݵ���λ����λ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRH = 0;	     // �ο���ѹ�ڲ���ѹ���ݵ���λ����λ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRHS = VRHS_SOURCE_SEL_VDD;          // ��ѹ���ݵ�Դѡ��VDD
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1REFEN = REFEN_INTERN_REF_ENABLE; 	     // �ڲ��ο���ѹʹ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1HYSEN = HYSEN_WITHOUT_HYSTERESIS;          // û�г���
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1NS = C1NS_NEG_INPUT_SEL_CVREF0;	      // ��������ѡ��λ��ѡ��CVREF0
	 
	 
	 ACCESS_ENABLE;
	 ACMP->CP10CFG_b.C10INTS = INTS_FE_RE;	      // �ж�����ѡ��˫��
	 ACCESS_ENABLE;
	 ACMP->CP10CFG_b.C10INTM = INTM_INT_ENABLE;            // �������ж�
		
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
		�Ƚ���CP11��ʼ��
*******************************************************************************/
  
void CP11_Init()
{

	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C11PS = C1PS_INPUT_SEL_PIN;	     // ����ѡ���ⲿ�ܽ�����
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C11EN = CMP_ENABLE;	     // �Ƚ���11ʹ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1RDS = 8;	     // �ο���ѹ��������VRRH=0��VRRL=1ʱ����Ӧ8/24*VS=1.667V
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRL = 1;	     // �ο���ѹ�ڲ���ѹ���ݵ���λ����λ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRH = 0;	     // �ο���ѹ�ڲ���ѹ���ݵ���λ����λ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRHS = VRHS_SOURCE_SEL_VDD;          // ��ѹ���ݵ�Դѡ��VDD
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1REFEN = REFEN_INTERN_REF_ENABLE; 	     // �ڲ��ο���ѹʹ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1HYSEN = HYSEN_WITHOUT_HYSTERESIS;          // û�г���
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1NS = C1NS_NEG_INPUT_SEL_CVREF0;	      // ��������ѡ��λ��ѡ��CVREF0
	 
	 
	 ACCESS_ENABLE;
	 ACMP->CP11CFG_b.C11INTS = INTS_FE_RE;	      // �ж�����ѡ��˫��
	 ACCESS_ENABLE;
	 ACMP->CP11CFG_b.C11INTM = INTM_INT_ENABLE;            // �������ж�
		
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
		�Ƚ���CP12��ʼ��
*******************************************************************************/
 
void CP12_Init()
{
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C12PS = C1PS_INPUT_SEL_PIN;	     // ����ѡ���ⲿ�ܽ�����
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C12EN = CMP_ENABLE;	     // �Ƚ���12ʹ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1RDS = 8;	     // �ο���ѹ��������VRRH=0��VRRL=1ʱ����Ӧ8/24*VS=1.667V
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRL = 1;	     // �ο���ѹ�ڲ���ѹ���ݵ���λ����λ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRRH = 0;	     // �ο���ѹ�ڲ���ѹ���ݵ���λ����λ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1VRHS = VRHS_SOURCE_SEL_VDD;          // ��ѹ���ݵ�Դѡ��VDD
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1REFEN = REFEN_INTERN_REF_ENABLE; 	     // �ڲ��ο���ѹʹ��
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1HYSEN = HYSEN_WITHOUT_HYSTERESIS;          // û�г���
	 ACCESS_ENABLE;
	 ACMP->CP1CON_b.C1NS = C1NS_NEG_INPUT_SEL_CVREF0;	      // ��������ѡ��λ��ѡ��CVREF0
	 
	 
	 ACCESS_ENABLE;
	 ACMP->CP12CFG_b.C12INTS = INTS_FE_RE;	      // �ж�����ѡ��˫��
	 ACCESS_ENABLE;
	 ACMP->CP12CFG_b.C12INTM = INTM_INT_ENABLE;            // �������ж�
		
}

