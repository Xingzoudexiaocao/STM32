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
	���ļ�չʾ��UART��ͨѶЭ���Լ���ʼ����������
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

	UART0 -> UARTCR_b.UARTEN = 1;     // UARTʹ��
	
	UART0 -> UARTIBRD = 39;	      // �����ʷ�Ƶ�ȵ���������
	
	UART0 -> UARTFBRD = 5;	      // �����ʷ�Ƶ�ȵ�С������
// �����У���PCLK01ʱ��Ϊ72Mhzʱ����Ӧ������Ϊ115200bps
//	UART0->UARTIBRD=468;
//	UART0->UARTFBRD=48; 	// ��Ӧ9600bps������

	UART0 -> UARTLCR_H = 0x60;  // ����żУ�飬8λ�ֳ���FIFO��ʹ�ܣ���ֹͣλ��no break

	UART0 -> UARTIMSC_b.Receive_IM = 0;  // �رս����ж�����(1)
	UART0 -> UARTIMSC_b.Transmit_IM = 0; // �رշ����ж�����(1)

	UART0 -> UARTDMACR_b.TxFIFO_en = 0; // TxFIFO��DMAʹ�ܣ��ߵ�ƽ��Ч(1)
	
	
}

UART_PARAM_s Uart;//����UART0�ṹ�����

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
 		ͨ���״ζ�UARTDR��ֵ�����������ж�
**************************************************************************/

void UartSendStart(void)
{
	if(Uart.IntSendFlag)// ����æµ��־ 
		return;
	
	if(Uart.UnSendCnt > 0)// δ�����ֽ���
	{
		if(Uart.IntSendFlag==0) 
			Uart.UnSendCnt--;// �粻��һ�������෢һ���ֽ�

		Uart.IntSendFlag = 1;// ����æµ��־
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
		�����͵�һ���ֽ����ݷ��뷢�ͻ���
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

//  �������ж��е���
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

// �����ַ��������뷢�ͻ�����
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
 	�����յ������ݣ��жϴ����Ƿ�Ϊ��Чָ����ǣ��������������
**************************************************************************/

void UartRevFunc(uint8_t rev)
{
	uint8_t revtmp;

	revtmp = rev;
	if(Uart.RevOK ==0)
	{
		if(Uart.RevStart==0) // ֡δ��ʼ
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
		else//   ֡�ѿ�ʼ
		{
			if(Uart.RevLen==0)  // �������½���
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
			else // ���ĸ��ֽڿ�ʼ����CMD
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
		��������
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

void ReadUartBuf(void)//��ȡ��������
{
	uint8_t i,revdat;
	
	for(i = 0; i < UART_REV_BUF_SIZE; i++)
	{
		if(Uart.UnRevCnt)//��δ��ȡ�ֽ���
		{
			Uart.UnRevCnt--;
			revdat = Uart.RevBuf[Uart.RBReadIdx];
			Uart.RBReadIdx++;// ���ջ����ȡ���
			
//			UartRevFunc(revdat);
			
		//	UartSendByte(revdat);

		UartRevFunc(revdat);//�ж��Ƿ�����Ч����
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
			UART0�ж��ӳ���
****************************************************************************/

void UART0_IRQHandler(void)
{
	uint32_t temp32;
	temp32 = UART0 -> UARTMIS;//�����ж�״̬�Ĵ���

	
	if(temp32 & (1 << 5))//���������ж�״̬TX
	{
		UART0 -> UARTICR = (1 << 5);//�����ж�����
		if(Uart.UnSendCnt > 0)//�з�������
		{
			Uart.UnSendCnt--;//δ�����ֽ���
      Uart.SBReadIdx++;//���ͻ����ȡ���	
			UART0 -> UARTDR = Uart.SendBuf[Uart.SBReadIdx];
			
			
			if(Uart.SBReadIdx >= UART_SEND_BUF_SIZE)//��������ֵ
			{
				Uart.SBReadIdx = 0;// ���ͻ����ȡ���
			}
		}
		else
		{
			Uart.SBWriteIdx = 0;// ���ͻ���д�����
			Uart.SBReadIdx = 0;// ���ͻ����ȡ���
			Uart.IntSendFlag = 0;// ����æµ��־
		}
	}
	
	if(temp32 &( 1 << 4 ))//���������ж�״̬RX
	{
		Uart.RevBuf[Uart.RBWriteIdx] = UART0 -> UARTDR;// ���ջ���д����ţ���ȡ����

		Uart.UnRevCnt++;// δ��ȡ�ֽ���
		Uart.RBWriteIdx++;// ���ջ���д�����
		if(Uart.RBWriteIdx >= UART_REV_BUF_SIZE)
		{
			Uart.RBWriteIdx = 0;
		}
	}
}
