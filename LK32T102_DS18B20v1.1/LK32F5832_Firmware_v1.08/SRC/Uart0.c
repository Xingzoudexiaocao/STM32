/**
* @file          : Uart0.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for Uart0 configuration.
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

#include "SC32F5832.h"
#include "DevInit.h"
#include "UART.h"

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
  * Uart0_Init();
  * @endcode
  * @warning:
*/

void Uart0_Init(void)
{

	UART0 -> UARTCR_b.UARTEN = 1;     // UART使能
	
	UART0 -> UARTIBRD = 39;	      // 波特率分频比的整数部分
	
	UART0 -> UARTFBRD = 5;	      // 波特率分频比的小数部分
// 本例中，在PCLK01时钟为72Mhz时，对应波特率为115200bps
//	UART0->UARTIBRD=468;
//	UART0->UARTFBRD=48; 	// 对应9600bps波特率

	UART0 -> UARTLCR_H = 0x60;  // 无奇偶校验，8位字长，FIFO不使能，无停止位，no break

	UART0 -> UARTIMSC_b.Receive_IM = 0;  // 关闭接收中断屏蔽(1)
	UART0 -> UARTIMSC_b.Transmit_IM = 0; // 关闭发送中断屏蔽(1)

	UART0 -> UARTDMACR_b.TxFIFO_en = 0; // TxFIFO的DMA使能，高电平有效(1)
	
	
}

UART_PARAM_s Uart;//定义UART0结构体变量

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
  * UartSendStart();
  * @endcode
  * @warning:
*/

/*************************************************************************
 		通过首次对UARTDR赋值，启动串口中断
**************************************************************************/

void UartSendStart(void)
{
	if(Uart.IntSendFlag)// 发送忙碌标志 
		return;
	
	if(Uart.UnSendCnt > 0)// 未发送字节数
	{
		if(Uart.IntSendFlag==0) 
			Uart.UnSendCnt--;// 如不减一，结果会多发一个字节

		Uart.IntSendFlag = 1;// 发送忙碌标志
		UART0 -> UARTDR = Uart.SendBuf[Uart.SBReadIdx];		
	}
	else
	{
		Uart.SBWriteIdx = 0;
		Uart.SBReadIdx = 0;
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
  * UartSendByte(uint8_t	byte);
  * @endcode
  * @warning:
*/

/***************************************************************************
		将发送的一个字节内容放入发送缓存
****************************************************************************/

void UartSendByte(uint8_t	byte)
{
	Uart.SendBuf[Uart.SBWriteIdx] = byte;
	Uart.UnSendCnt++;
	Uart.SBWriteIdx++;
	if(Uart.SBWriteIdx >= UART_SEND_BUF_SIZE)
	{
		Uart.SBWriteIdx = 0;
	}
}
/**
  * @brief      .
  * @param[in]  void : output.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * UartSentUint32ToASCII(uint32_t output);
  * @endcode
  * @warning:
*/

//  不能在中断中调用
void UartSentUint32ToASCII(uint32_t output)
{
	uint8_t digit = 0;
				while (output >= 1000000000) { output -= 1000000000; digit++; } UartSendByte(digit + 0x30); digit = 0;
				while (output >=  100000000) { output -= 100000000; digit++; } UartSendByte(digit + 0x30); digit = 0;
				while (output >=   10000000) { output -= 10000000; digit++; } UartSendByte(digit + 0x30); digit = 0;
				while (output >=    1000000) { output -= 1000000; digit++; } UartSendByte(digit + 0x30); digit = 0;
				while (output >=     100000) { output -= 100000; digit++; } UartSendByte(digit + 0x30); digit = 0;
				while (output >=      10000) { output -= 10000; digit++; } UartSendByte(digit + 0x30); digit = 0;
        while (output >=       1000) { output -=  1000; digit++; } UartSendByte(digit + 0x30); digit = 0;
        while (output >=        100) { output -=   100; digit++; } UartSendByte(digit + 0x30); digit = 0;
        while (output >=         10) { output -=    10; digit++; } UartSendByte(digit + 0x30); digit = 0;
        while (output >=          1) { output -=     1; digit++; } UartSendByte(digit + 0x30);
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
  * UartSendString(uint8_t *str);
  * @endcode
  * @warning:
*/

// 发送字符串，放入发送缓存区
void UartSendString(char*str)
{
	while((*str) != '\0')
	{
		Uart.SendBuf[Uart.SBWriteIdx] = *str;
		str++;
		Uart.UnSendCnt++;
		Uart.SBWriteIdx++;
		if(Uart.SBWriteIdx >= UART_SEND_BUF_SIZE)
		{
			Uart.SBWriteIdx = 0;
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
  * UartRevFunc(uint8_t rev);
  * @endcode
  * @warning:
*/

/*************************************************************************
 	根据收到的内容，判断处理是否为有效指令，若是，放入接收数据区
**************************************************************************/

void UartRevFunc(uint8_t rev)
{
	uint8_t revtmp;

	revtmp = rev;
	if(Uart.RevOK ==0)
	{
		if(Uart.RevStart==0) // 帧未开始
		{
			if(Uart.RevLen==0)
			{
				if(revtmp == 0xF0)
				{
					Uart.RevData[Uart.RevLen]= revtmp;
					Uart.RevLen++;
					Uart.RevStart=1;					
				}
				else
				{
					Uart.RevStart=0;
					Uart.RevLen=0;
					Uart.RevOK=0;
				}
				
			}
			else
			{
				Uart.RevStart=0;
				Uart.RevLen=0;
				Uart.RevOK=0;
			}
		}
		else//   帧已开始
		{
			if(Uart.RevLen==0)  // 错误，重新接收
			{
				Uart.RevStart=0;
				Uart.RevLen=0;
				Uart.RevOK=0;
			}
			else if(Uart.RevLen==1)
			{
			if(revtmp == 0xAA)
			{
				Uart.RevData[Uart.RevLen] = revtmp;
				Uart.RevLen++;
			}
			else if(revtmp == 0xA5)
			{
				Uart.RevData[Uart.RevLen] = revtmp;
				Uart.RevLen++;
			}
			else
			{
				Uart.RevStart=0;
					Uart.RevLen=0;
					Uart.RevOK=0;
			}
		  }
			else if(Uart.RevLen ==2)
			{
				Uart.RevData[Uart.RevLen] = revtmp;
				Uart.DataLen = Uart.RevData[2];
				Uart.RevLen++;
				
				
			}
			else // 第四个字节开始，即CMD
			{
				Uart.RevData[Uart.RevLen] = revtmp;
				Uart.RevLen++;
				Uart.DataLen--;
				if(Uart.DataLen == 0)
				{
//					if(Uart.RevData[1] == 0xAA)
//					{
//					Uart.RevData[Uart.RevLen]= revtmp;
						Uart.RevStart =0;
						Uart.RevLen = 0;
						Uart.RevOK = 1;
//					}
//					else if(Uart.RevData[1] == 0xA5)
//					{
//						Uart.RevStart	= 0;
//						Uart.RevLen = 0;
//						Uart.RevOK = 1;
//					}
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
  * SendResponse();
  * @endcode
  * @warning:
*/

/**********************************************************************
		返回数据
**********************************************************************/

void SendResponse(void)
{
	
	if(Uart.RevOK == 1)
  {
		if(Uart.RevData[1]==0xAA)
		{
		if((Uart.RevData[3]==0x11)|(Uart.RevData[3]==0x21))
		{
			UartSendByte(Uart.RevData[0]);
			UartSendByte(Uart.RevData[1]);
			UartSendByte(Uart.RevData[2]);
			UartSendByte(Uart.RevData[3]);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(Uart.RevData[Uart.RevData[2]+2]);
		}
		else if(Uart.RevData[3]==0x12)
		{
			UartSendByte(Uart.RevData[0]);
			UartSendByte(Uart.RevData[1]);
			UartSendByte(Uart.RevData[2]);
			UartSendByte(Uart.RevData[3]);
				UartSendByte(0x55);
			UartSendByte(0x55);
				UartSendByte(0x55);
			UartSendByte(0x55);
			UartSendByte(Uart.RevData[Uart.RevData[2]+2]);			
		}
		else if(Uart.RevData[3]==0x22)
		{
			UartSendByte(Uart.RevData[0]);
			UartSendByte(Uart.RevData[1]);
			UartSendByte(Uart.RevData[2]);
			UartSendByte(Uart.RevData[3]);
				UartSendByte(0x33);
			UartSendByte(0x33);
				UartSendByte(0x33);
			UartSendByte(0x33);
			UartSendByte(Uart.RevData[Uart.RevData[2]+2]);	
		}
		else if(Uart.RevData[3]==0x23)
		{
			UartSendByte(Uart.RevData[0]);
			UartSendByte(Uart.RevData[1]);
			UartSendByte(Uart.RevData[2]);
			UartSendByte(Uart.RevData[3]);
				UartSendByte(0x44);
			UartSendByte(0x44);
				UartSendByte(0x44);
			UartSendByte(0x44);
				UartSendByte(0x44);
			UartSendByte(0x44);
			UartSendByte(Uart.RevData[Uart.RevData[2]+2]);	
		}
	}
		else if(Uart.RevData[1] == 0xA5)
		{
		if((Uart.RevData[3]==0x11)|(Uart.RevData[3]==0x21))
		{
			UartSendByte(Uart.RevData[0]);
			UartSendByte(Uart.RevData[1]);
			UartSendByte(Uart.RevData[2]);
			UartSendByte(Uart.RevData[3]);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
			UartSendByte(0xAA);
		}
		else if(Uart.RevData[3]==0x12)
		{
			UartSendByte(Uart.RevData[0]);
			UartSendByte(Uart.RevData[1]);
			UartSendByte(Uart.RevData[2]);
			UartSendByte(Uart.RevData[3]);
				UartSendByte(0x55);
			UartSendByte(0x55);
				UartSendByte(0x55);
			UartSendByte(0x55);
		}
		else if(Uart.RevData[3]==0x22)
		{
			UartSendByte(Uart.RevData[0]);
			UartSendByte(Uart.RevData[1]);
			UartSendByte(Uart.RevData[2]);
			UartSendByte(Uart.RevData[3]);
				UartSendByte(0x33);
			UartSendByte(0x33);
				UartSendByte(0x33);
			UartSendByte(0x33);
		}
		else if(Uart.RevData[3]==0x23)
		{
			UartSendByte(Uart.RevData[0]);
			UartSendByte(Uart.RevData[1]);
			UartSendByte(Uart.RevData[2]);
			UartSendByte(Uart.RevData[3]);
				UartSendByte(0x44);
			UartSendByte(0x44);
				UartSendByte(0x44);
			UartSendByte(0x44);
				UartSendByte(0x44);
			UartSendByte(0x44);
		}
	
	}
		Uart.RevOK=0;
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
  * ReadUartBuf();
  * @endcode
  * @warning:
*/

void ReadUartBuf(void)//读取串口数据
{
	uint8_t i,revdat;
	
	for(i = 0; i < UART_REV_BUF_SIZE; i++)
	{
		if(Uart.UnRevCnt)//有未读取字节数
		{
			Uart.UnRevCnt--;
			revdat = Uart.RevBuf[Uart.RBReadIdx];
			Uart.RBReadIdx++;// 接收缓存读取序号
			
//			UartRevFunc(revdat);
			
		//	UartSendByte(revdat);

		UartRevFunc(revdat);//判断是否是有效命令
		}
		else
		{
			Uart.RBWriteIdx = 0;
			Uart.RBReadIdx = 0;
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
  * UART0_IRQHandler();
  * @endcode
  * @warning:
*/

/****************************************************************************
			UART0中断子程序
****************************************************************************/

void UART0_IRQHandler(void)
{
	uint32_t temp32;
	temp32 = UART0 -> UARTMIS;//屏蔽中断状态寄存器

	
	if(temp32 & (1 << 5))//发送屏蔽中断状态TX
	{
		UART0 -> UARTICR = (1 << 5);//发送中断清零
		if(Uart.UnSendCnt > 0)//有发送数据
		{
			Uart.UnSendCnt--;//未发送字节数
      Uart.SBReadIdx++;//发送缓存读取序号	
			UART0 -> UARTDR = Uart.SendBuf[Uart.SBReadIdx];
			
			
			if(Uart.SBReadIdx >= UART_SEND_BUF_SIZE)//超过上限值
			{
				Uart.SBReadIdx = 0;// 发送缓存读取序号
			}
		}
		else
		{
			Uart.SBWriteIdx = 0;// 发送缓存写入序号
			Uart.SBReadIdx = 0;// 发送缓存读取序号
			Uart.IntSendFlag = 0;// 发送忙碌标志
		}
	}
	
	if(temp32 &( 1 << 4 ))//接收屏蔽中断状态RX
	{
		Uart.RevBuf[Uart.RBWriteIdx] = UART0 -> UARTDR;// 接收缓存写入序号，读取数据

		Uart.UnRevCnt++;// 未读取字节数
		Uart.RBWriteIdx++;// 接收缓存写入序号
		if(Uart.RBWriteIdx >= UART_REV_BUF_SIZE)
		{
			Uart.RBWriteIdx = 0;
		}
	}
}
