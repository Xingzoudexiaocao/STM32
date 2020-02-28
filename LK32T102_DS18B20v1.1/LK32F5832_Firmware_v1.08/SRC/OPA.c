/**
* @file          : OPA.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for OPA configuration.
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
							���ļ�չʾ���˷ŵĳ�ʼ������
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
  * OPA0_Init();
  * @endcode
  * @warning:
*/


/***************************************************************************
		�˷�OPA0��ʼ��
***************************************************************************/

void OPA0_Init()
{
	 
	 ACCESS_ENABLE;
	 ACMP->OP0CON_b.OP0EN = OPA_ENABLE;	      					// �˷�ʹ��
	 ACCESS_ENABLE;
	 ACMP->OP0CON_b.OP0NS = OPA_FEEDBACK_LOOP_ENABLE;	  // ��������˷���ͨ·ʹ��/��ֹ
	 ACCESS_ENABLE;
	 ACMP->OP0CON_b.OP0OE = OPA_OUTPUT_To_PIN_ENABLE;		// OPA_OUTPUT_To_PIN_DISABLE;	   // ������˿�ʹ��/��ֹ
	 ACCESS_ENABLE;
	 ACMP->OP0CON_b.OP0GS = OP0GS_4x;      							// 4x	
	 ACCESS_ENABLE;
	 ACMP->OP0CON_b.OP0NGD = OPA0_NEG_To_GND_ENABLE;		// ����˽ӵ�ʹ��/��ֹ
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
  * OPA1_Init();
  * @endcode
  * @warning:
*/


/*****************************************************************************
		�˷�OPA1��ʼ��
*****************************************************************************/

void OPA1_Init()
{
	 
	 ACCESS_ENABLE;
	 ACMP->OP1CON_b.OP1EN = OPA_ENABLE;									// �˷�ʹ��
	 ACCESS_ENABLE;
	 ACMP->OP1CON_b.OP1PS = 0;													// �ر�����ƫ�õ�Դ
	 ACCESS_ENABLE;
	 ACMP->OP1CON_b.OP1NS = OPA_FEEDBACK_LOOP_ENABLE;		// ��������˷���ͨ·ʹ��/��ֹ
	 ACCESS_ENABLE;
	 ACMP->OP1CON_b.OP1OE = OPA_OUTPUT_To_PIN_ENABLE; 	// ������˿�ʹ��/��ֹ
	 ACCESS_ENABLE;
	 ACMP->OP1CON_b.OP1GS = OP1GS_5x;          					// ���汶�� 5x
	 ACCESS_ENABLE;
	 ACMP->OP1CON_b.OP1PRS = OP1NRS_RES_SHORT; 					// ��������˵���ѡ��0ŷ
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
  * OPA2_Init();
  * @endcode
  * @warning:
*/

 /****************************************************************************
		�˷�OPA2��ʼ��
****************************************************************************/

void OPA2_Init()
{
	 
	 ACCESS_ENABLE;
	 ACMP->OP2CON_b.OP2EN = OPA_ENABLE;									// �˷�ʹ��
	 ACCESS_ENABLE;
	 ACMP->OP2CON_b.OP2PS = 0;													// �ر�����ƫ�õ�Դ
	 ACCESS_ENABLE;
	 ACMP->OP2CON_b.OP2NS = OPA_FEEDBACK_LOOP_ENABLE;	  // ��������˷���ͨ·ʹ��
	 ACCESS_ENABLE;
	 ACMP->OP2CON_b.OP2OE = OPA_OUTPUT_To_PIN_ENABLE;		// ������˿�ʹ��
	 ACCESS_ENABLE;
	 ACMP->OP2CON_b.OP2GS = OP1GS_5x;          					// ���汶�� 5x
	 ACCESS_ENABLE;
	 ACMP->OP2CON_b.OP2PRS = OP1NRS_RES_SHORT;					// ��������˵���ѡ��0ŷ
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
  * OPA3_Init();
  * @endcode
  * @warning:
*/

 /*****************************************************************************
		�˷�OPA3��ʼ��
*****************************************************************************/

void OPA3_Init()
{

	 ACCESS_ENABLE;
	 ACMP->OP3CON_b.OP3EN = OPA_ENABLE;									// �˷�ʹ��
	 ACCESS_ENABLE;
	 ACMP->OP3CON_b.OP3PS = 0;													// �ر�����ƫ�õ�Դ
	 ACCESS_ENABLE;
	 ACMP->OP3CON_b.OP3NS = OPA_FEEDBACK_LOOP_ENABLE;	  // ��������˷���ͨ·ʹ��/��ֹ
	 ACCESS_ENABLE;
	 ACMP->OP3CON_b.OP3OE = OPA_OUTPUT_To_PIN_ENABLE;		// ������˿�ʹ��/��ֹ
	 ACCESS_ENABLE;
	 ACMP->OP3CON_b.OP3GS = OP1GS_5x;          					// ���汶�� 5x
	 ACCESS_ENABLE;
	 ACMP->OP3CON_b.OP3PRS = OP1NRS_RES_SHORT;					// ��������˵���ѡ��0ŷ
}
