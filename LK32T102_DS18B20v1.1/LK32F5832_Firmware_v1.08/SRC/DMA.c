/**
* @file          : DMA.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for DMA configuration.
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

/***************************************************************
			���ļ�չʾ��ʵ��DMA�����ʵ��
****************************************************************/
#include <SC32F5832.h>
#include <DevInit.h>

uint32_t ADCRESULT[16];
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
  * DMA_UART_INIT();
  * @endcode
  * @warning:
*/


void DMA_UART_INIT(void)
{
	UART0->UARTCR |=UART0_UARTCR_UARTEN_Msk;				// UART ʹ��
	UART0->UARTIBRD=39;
	UART0->UARTFBRD=4;															// �����У���PCLK01ʱ��Ϊ72Mhzʱ����Ӧ������Ϊ115200bps
	UART0->UARTLCR_H = 0x60;												// ����żУ�飬8λ�ֳ���FIFO��ʹ�ܣ���ֹͣλ��no break
	UART0->UARTDMACR = 0x3;													// TXFIFO��RXFIFO��DMAʹ��
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
  * DMA_CH0_UART0TX();
  * @endcode
  * @warning:
*/

/*************************************************
				��UART���ڷ���DMA��������
**************************************************/

void DMA_CH0_UART0TX(void)
{


		DMA_DATA->SOURCE = (uint32_t *)0x20000900ul;		// ���ʹ洢��������Դ���׵�ַ���û������ж��壬����Ϊ���Ե�ַ��
		DMA_DATA->DESTIN = (uint32_t *)0x40090000ul;		// �������ݼĴ���UARTDR��Ӳ����ַ
		DMA_DATA->CTL=0xc00001f1;												// Ŀ���ַ��������Դ��ַ����Ϊ�ֽڣ��������ݴ�СΪ�ֽڣ�ÿ�����DMA���ٲã�32�δ��䣬��������

		
		DMA->BASE_PTR=0x20000100;
		DMA->CTRL0 =0x00800001;											// ����1�����Σ�ʹ������0��uart0 tx DMA����ʹ��
		DMA->CFG=0x01;
  	while((DMA->DONE&0x01)==0x00ul);
//		DMA->DONE=0x1;														// �����ɱ�־
		DMA->CFG_ERR=0x1;														// ������ô����־
		DMA->BUS_ERR =0x1;													// ������ߴ����־

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
  * DMA_CH1_UART0RX();
  * @endcode
  * @warning:
*/

/***************************************************
						��UART���ڽ���DMA��������
***************************************************/
void DMA_CH1_UART0RX(void)
{


		DMA_DATA1->SOURCE = (uint32_t *)0x40090000ul;		// �������ݼĴ���UARTDR��Ӳ����ַ
		DMA_DATA1->DESTIN = (uint32_t *)0x20000900ul;		// ���մ洢����Ŀ�ģ��׵�ַ���û������ж��壬����Ϊ���Ե�ַ��
		DMA_DATA1->CTL=0x300001f1;											// Դ��ַ��������Ŀ���ַ����Ϊ�ֽڣ��������ݴ�СΪ�ֽڣ�ÿ�����DMA���ٲã�32�δ��䣬��������

		
		DMA->BASE_PTR=0x20000100;
		DMA->CTRL1 =0x00000101;											// ����1�����Σ�ʹ������0��uart0 rx DMA����ʹ��
		DMA->CFG=0x01;
		while((DMA->DONE&0x02)==0x00ul);
//		DMA->DONE=0x2;														// �����ɱ�־
		DMA->CFG_ERR=0x2;														// ������ô����־
		DMA->BUS_ERR =0x2;													// ������ߴ����־
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
  * DMA_CH0_ADC();
  * @endcode
  * @warning:
*/
/***************************************************
						ͨ��DMA��ADC����Ĵ�����ȡ����ֵ
***************************************************/
void DMA_CH0_ADC(void)
{
	 DMA_DATA->SOURCE = (uint32_t *)0x400A8200ul;
	 DMA_DATA->DESTIN = ADCRESULT;
	 DMA_DATA->CTL=0xa8000031;
	 
	 DMA->BASE_PTR=0x20000100;
	 DMA->CTRL0 =0x00800001;
	 DMA->CFG=0x01;
	 while((DMA->DONE&0x01)==0x00ul);
	 DMA->DONE=0x1;
	 DMA->CFG_ERR=0x1;	
	 DMA->BUS_ERR =0x1;	
}
