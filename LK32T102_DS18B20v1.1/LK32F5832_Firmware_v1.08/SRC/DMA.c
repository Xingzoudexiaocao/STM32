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
			本文件展示了实现DMA传输的实例
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
	UART0->UARTCR |=UART0_UARTCR_UARTEN_Msk;				// UART 使能
	UART0->UARTIBRD=39;
	UART0->UARTFBRD=4;															// 本例中，在PCLK01时钟为72Mhz时，对应波特率为115200bps
	UART0->UARTLCR_H = 0x60;												// 无奇偶校验，8位字长，FIFO不使能，无停止位，no break
	UART0->UARTDMACR = 0x3;													// TXFIFO、RXFIFO的DMA使能
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
				向UART串口发送DMA传输数据
**************************************************/

void DMA_CH0_UART0TX(void)
{


		DMA_DATA->SOURCE = (uint32_t *)0x20000900ul;		// 发送存储区（数据源）首地址（用户可自行定义，无需为绝对地址）
		DMA_DATA->DESTIN = (uint32_t *)0x40090000ul;		// 串口数据寄存器UARTDR的硬件地址
		DMA_DATA->CTL=0xc00001f1;												// 目标地址无增量，源地址增量为字节，传输数据大小为字节，每次完成DMA后仲裁，32次传输，基本周期

		
		DMA->BASE_PTR=0x20000100;
		DMA->CTRL0 =0x00800001;											// 请求1被屏蔽，使用请求0，uart0 tx DMA请求使能
		DMA->CFG=0x01;
  	while((DMA->DONE&0x01)==0x00ul);
//		DMA->DONE=0x1;														// 清除完成标志
		DMA->CFG_ERR=0x1;														// 清除配置错误标志
		DMA->BUS_ERR =0x1;													// 清除总线错误标志

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
						从UART串口接收DMA传输数据
***************************************************/
void DMA_CH1_UART0RX(void)
{


		DMA_DATA1->SOURCE = (uint32_t *)0x40090000ul;		// 串口数据寄存器UARTDR的硬件地址
		DMA_DATA1->DESTIN = (uint32_t *)0x20000900ul;		// 接收存储区（目的）首地址（用户可自行定义，无需为绝对地址）
		DMA_DATA1->CTL=0x300001f1;											// 源地址无增量，目标地址增量为字节，传输数据大小为字节，每次完成DMA后仲裁，32次传输，基本周期

		
		DMA->BASE_PTR=0x20000100;
		DMA->CTRL1 =0x00000101;											// 请求1被屏蔽，使用请求0，uart0 rx DMA请求使能
		DMA->CFG=0x01;
		while((DMA->DONE&0x02)==0x00ul);
//		DMA->DONE=0x2;														// 清除完成标志
		DMA->CFG_ERR=0x2;														// 清除配置错误标志
		DMA->BUS_ERR =0x2;													// 清除总线错误标志
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
						通过DMA从ADC结果寄存器提取采样值
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
