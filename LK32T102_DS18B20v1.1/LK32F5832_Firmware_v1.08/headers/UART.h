/*******************************************************************
	本文件定义了UART串口通讯的数据结构体以及各收、发函数
******************************************************************/

#ifndef _UART_H_
#define _UART_H_
#include <SC32F5832.h>
#include <DevInit.h>
#include "stdint.h"


#define UART_DEBUG  1
#define UART_SEND_BUF_SIZE  250
#define UART_REV_BUF_SIZE   100
#define UART_DATA_SIZE      50

typedef struct
{
	uint8_t SendBuf[UART_SEND_BUF_SIZE]; // 串口发送缓存
	uint8_t RevBuf[UART_REV_BUF_SIZE]; // 串口接收缓存
	
	uint8_t RevData[UART_DATA_SIZE];// 接收数据存放区

	uint16_t SBWriteIdx;// 发送缓存写入序号
	uint16_t SBReadIdx;// 发送缓存读取序号
	uint16_t UnSendCnt;// 未发送字节数

	uint8_t IntSendFlag;// 发送忙碌标志

	uint16_t RBWriteIdx;// 接收缓存写入序号
	uint16_t RBReadIdx;// 接收缓存读取序号
	uint16_t UnRevCnt;// 未读取字节数

	uint16_t RevStart;// 帧起始标志
	uint16_t RevLen;// 接收地址计数器
	uint8_t RevOK;// 一帧指令接收完毕标志
	uint8_t DataLen;// 数据长度

}UART_PARAM_s;


extern UART_PARAM_s Uart,Uart1;

extern void UartSentUint32ToASCII(uint32_t output);

extern void UartSendStart(void);
extern void UartSendByte(uint8_t);
extern void UartSendString(char*);
extern void ReadUartBuf(void);
extern void SendResponse(void);

extern void Uart1SendStart(void);
extern void Uart1SendByte(uint8_t);
extern void Uart1SendString(uint8_t *);
extern void ReadUart1Buf(void);
extern void Send1Response(void);

#endif
