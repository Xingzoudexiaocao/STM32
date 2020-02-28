/**
* @file          : Uart1.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for Uart1 configuration.
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
	本文件展示了UART的通讯协议以及初始化参数设置
******************************************************************************/


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
  * Uart1_Init();
  * @endcode
  * @warning:
*/

void Uart1_Init(void)
{

	UART1->UARTCR_b.UARTEN=1;     // UART使能
	UART1->UARTIBRD=39;	      // 波特率分频比的整数部分
	UART1->UARTFBRD=4;	      // 波特率分频比的小数部分
// 本例中，在PCLK01时钟为72Mhz时，对应波特率为115200bps
//	UART1->UARTIBRD=468;
//	UART1->UARTFBRD=48; 	// 对应9600bps波特率

	UART1->UARTLCR_H=0x60;  // 无奇偶校验，8位字长，FIFO不使能，无停止位，no break

	UART1->UARTIMSC_b.Receive_IM =1;  // 关闭接收中断屏蔽
	UART1->UARTIMSC_b.Transmit_IM =1; // 关闭发送中断屏蔽
	
	UART1->UARTDMACR_b.TxFIFO_en = 1; // TxFIFO的DMA使能，高电平有效。

}


UART_PARAM_s Uart1;

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
  * Uart1SendStart();
  * @endcode
  * @warning:
*/


/*************************************************************************
 		通过首次对UARTDR赋值，启动串口中断
**************************************************************************/

void Uart1SendStart(void)
{
	if(Uart1.IntSendFlag) return;
	
	if(Uart1.UnSendCnt > 0)
	{
		if(Uart1.IntSendFlag==0) Uart1.UnSendCnt--;

		Uart1.IntSendFlag = 1;
		UART1->UARTDR = Uart1.SendBuf[Uart1.SBReadIdx];
		
	}
	else
	{
		Uart1.SBWriteIdx = 0;
		Uart1.SBReadIdx = 0;
	}
}

/**
  * @brief      .
  * @param[in]  void : byte.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * Uart1SendByte(uint8_t byte);
  * @endcode
  * @warning:
*/

/***************************************************************************
		将发送的一个字节内容放入发送缓存
****************************************************************************/

void Uart1SendByte(uint8_t byte)
{
	Uart1.SendBuf[Uart1.SBWriteIdx] = byte;
	Uart1.UnSendCnt++;
	Uart1.SBWriteIdx++;
	if(Uart1.SBWriteIdx >= UART_SEND_BUF_SIZE)
	{
		Uart1.SBWriteIdx = 0;
	}
}

/**
  * @brief      .
  * @param[in]  void : str.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * Uart1SendString(uint8_t *str)
  * @endcode
  * @warning:
*/

/*************************************************************************
 			发送字符串，放入发送缓存区
**************************************************************************/

void Uart1SendString(uint8_t *str)
{
	while((*str) != '\0')
	{
		Uart1.SendBuf[Uart1.SBWriteIdx] = *str;
		str++;
		Uart1.UnSendCnt++;
		Uart1.SBWriteIdx++;
		if(Uart1.SBWriteIdx >= UART_SEND_BUF_SIZE)
		{
			Uart1.SBWriteIdx = 0;
		}
	}
}
/**
  * @brief      .
  * @param[in]  void : rev.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * Uart1RevFunc(uint8_t rev);
  * @endcode
  * @warning:
*/

/*************************************************************************
	根据收到的内容，判断处理是否为有效指令，若是，放入接收数据区
**************************************************************************/


void Uart1RevFunc(uint8_t rev)
{
	uint8_t revtmp;

	revtmp = rev;
	if(Uart1.RevOK ==0)
	{
		if(Uart1.RevStart==0)   // 帧未开始
		{
			if(Uart1.RevLen==0)
			{
				if(revtmp == 0xF0)
				{
					Uart1.RevData[Uart1.RevLen]= revtmp;
					Uart1.RevLen++;
					Uart1.RevStart=1;					
				}
				else
				{
					Uart1.RevStart=0;
					Uart1.RevLen=0;
					Uart1.RevOK=0;
				}
				
			}
			else
			{
				Uart1.RevStart=0;
				Uart1.RevLen=0;
				Uart1.RevOK=0;
			}
		}
		else         // 帧已开始
		{
			if(Uart1.RevLen==0)      // 错误，重新接收
			{
				Uart1.RevStart=0;
				Uart1.RevLen=0;
				Uart1.RevOK=0;
			}
			else if(Uart1.RevLen==1)
			{
			if(revtmp == 0xAA)
			{
				Uart1.RevData[Uart1.RevLen] = revtmp;
				Uart1.RevLen++;
			}
			else if(revtmp == 0xA5)
			{
				Uart1.RevData[Uart1.RevLen] = revtmp;
				Uart1.RevLen++;
			}
			else
			{
				Uart1.RevStart=0;
					Uart1.RevLen=0;
					Uart1.RevOK=0;
			}
		  }
			else if(Uart1.RevLen ==2)
			{
				Uart1.RevData[Uart1.RevLen] = revtmp;
				Uart1.DataLen = Uart1.RevData[2];
				Uart1.RevLen++;
				
				
			}
			else          // 第四个字节开始，即CMD
			{
				Uart1.RevData[Uart1.RevLen] = revtmp;
				Uart1.RevLen++;
				Uart1.DataLen--;
				if(Uart1.DataLen == 0)
				{

						Uart1.RevStart =0;
						Uart1.RevLen = 0;
						Uart1.RevOK = 1;

				}
			}
		}
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
  * Send1Response();
  * @endcode
  * @warning:
*/

/**********************************************************************
			返回数据
**********************************************************************/

void Send1Response(void)
{
	
	if(Uart1.RevOK == 1)
  {
		if(Uart1.RevData[1]==0xAA)
		{
		if((Uart1.RevData[3]==0x11)|(Uart1.RevData[3]==0x21))   // 收到指令为0x11或0x21
		{
		
			Uart1SendByte(Uart1.RevData[0]);
			Uart1SendByte(Uart1.RevData[1]);
			Uart1SendByte(Uart1.RevData[2]);
			Uart1SendByte(Uart1.RevData[3]);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(Uart1.RevData[Uart1.RevData[2]+2]);
		}
		else if(Uart1.RevData[3]==0x12)				//  收到指令为0x12
		{
			Uart1SendByte(Uart1.RevData[0]);
			Uart1SendByte(Uart1.RevData[1]);
			Uart1SendByte(Uart1.RevData[2]);
			Uart1SendByte(Uart1.RevData[3]);
				Uart1SendByte(0x55);
			Uart1SendByte(0x55);
				Uart1SendByte(0x55);
			Uart1SendByte(0x55);
			Uart1SendByte(Uart1.RevData[Uart1.RevData[2]+2]);			
		}
		else if(Uart1.RevData[3]==0x22)				// 收到指令为0x22
		{
			Uart1SendByte(Uart1.RevData[0]);
			Uart1SendByte(Uart1.RevData[1]);
			Uart1SendByte(Uart1.RevData[2]);
			Uart1SendByte(Uart1.RevData[3]);
				Uart1SendByte(0x33);
			Uart1SendByte(0x33);
				Uart1SendByte(0x33);
			Uart1SendByte(0x33);
			Uart1SendByte(Uart1.RevData[Uart1.RevData[2]+2]);	
		}
		else if(Uart1.RevData[3]==0x23)				// 收到指令为0x23
		{
			Uart1SendByte(Uart1.RevData[0]);
			Uart1SendByte(Uart1.RevData[1]);
			Uart1SendByte(Uart1.RevData[2]);
			Uart1SendByte(Uart1.RevData[3]);
				Uart1SendByte(0x44);
			Uart1SendByte(0x44);
				Uart1SendByte(0x44);
			Uart1SendByte(0x44);
				Uart1SendByte(0x44);
			Uart1SendByte(0x44);
			Uart1SendByte(Uart1.RevData[Uart1.RevData[2]+2]);	
		}
	}
		else if(Uart1.RevData[1] == 0xA5)
		{
		if((Uart1.RevData[3]==0x11)|(Uart1.RevData[3]==0x21))		// 收到指令为0x11或0x21
		{
			Uart1SendByte(Uart1.RevData[0]);
			Uart1SendByte(Uart1.RevData[1]);
			Uart1SendByte(Uart1.RevData[2]);
			Uart1SendByte(Uart1.RevData[3]);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
			Uart1SendByte(0xAA);
		}
		else if(Uart1.RevData[3]==0x12)			 // 收到指令为0x12
		{			
			Uart1SendByte(Uart1.RevData[0]);
			Uart1SendByte(Uart1.RevData[1]);
			Uart1SendByte(Uart1.RevData[2]);
			Uart1SendByte(Uart1.RevData[3]);
				Uart1SendByte(0x55);
			Uart1SendByte(0x55);
				Uart1SendByte(0x55);
			Uart1SendByte(0x55);
		}
		else if(Uart1.RevData[3]==0x22)					// 收到指令为0x22
		{
			Uart1SendByte(Uart1.RevData[0]);
			Uart1SendByte(Uart1.RevData[1]);
			Uart1SendByte(Uart1.RevData[2]);
			Uart1SendByte(Uart1.RevData[3]);
				Uart1SendByte(0x33);
			Uart1SendByte(0x33);
				Uart1SendByte(0x33);
			Uart1SendByte(0x33);
		}
		else if(Uart1.RevData[3]==0x23)					// 收到指令为0x23
		{
			Uart1SendByte(Uart1.RevData[0]);
			Uart1SendByte(Uart1.RevData[1]);
			Uart1SendByte(Uart1.RevData[2]);
			Uart1SendByte(Uart1.RevData[3]);
				Uart1SendByte(0x44);
			Uart1SendByte(0x44);
				Uart1SendByte(0x44);
			Uart1SendByte(0x44);
				Uart1SendByte(0x44);
			Uart1SendByte(0x44);
		}
	
	}
		Uart1.RevOK=0;
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
  * ReadUart1Buf(void);
  * @endcode
  * @warning:
*/

/****************************************************************
		读取接收缓存区中的内容
*****************************************************************/

void ReadUart1Buf(void)
{
	uint8_t i,revdat;
	
	for(i = 0;i < UART_REV_BUF_SIZE;i++)
	{
		if(Uart1.UnRevCnt)	//CoreRevBuf
		{
			Uart1.UnRevCnt--;
			revdat = Uart1.RevBuf[Uart1.RBReadIdx];
			Uart1.RBReadIdx++;

		Uart1RevFunc(revdat);
		}
		else
		{
			Uart1.RBWriteIdx = 0;
			Uart1.RBReadIdx = 0;
			
			break;
		}
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
  * UART1_IRQHandler();
  * @endcode
  * @warning:
*/

/***************************************************************************
			UART1中断子程序
****************************************************************************/

void UART1_IRQHandler(void)
{
	uint32_t temp32;
	temp32 = UART1->UARTMIS;		// 读取中断标志寄存器
	
	if(temp32&(1<<5))			// 判断是否为发送中断
	{
		UART1->UARTICR= (1<<5);		// 清除发送中断标志
		if(Uart1.UnSendCnt > 0)		
		{
			Uart1.UnSendCnt--;	
     	Uart1.SBReadIdx++;
			UART1->UARTDR = Uart1.SendBuf[Uart1.SBReadIdx];		// 从发送缓存发出数据
			
			
			if(Uart1.SBReadIdx >= UART_SEND_BUF_SIZE)
			{
				Uart1.SBReadIdx = 0;
			}
		}
		else
		{
			Uart1.SBWriteIdx = 0;
			Uart1.SBReadIdx = 0;
			Uart1.IntSendFlag = 0;
		}
	}
	
	if (temp32&(1<<4))					 	// 判断是否为接收中断
	{
		Uart1.RevBuf[Uart1.RBWriteIdx] = UART1->UARTDR;	 	// 将接收到的数据放入接收缓存区

		Uart1.UnRevCnt++;
		Uart1.RBWriteIdx++;
		if(Uart1.RBWriteIdx >= UART_REV_BUF_SIZE)
		{
			Uart1.RBWriteIdx = 0;
		}


	}
		
}
