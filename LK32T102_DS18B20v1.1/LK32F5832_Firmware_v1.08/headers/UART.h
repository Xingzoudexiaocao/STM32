/*******************************************************************
	���ļ�������UART����ͨѶ�����ݽṹ���Լ����ա�������
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
	uint8_t SendBuf[UART_SEND_BUF_SIZE]; // ���ڷ��ͻ���
	uint8_t RevBuf[UART_REV_BUF_SIZE]; // ���ڽ��ջ���
	
	uint8_t RevData[UART_DATA_SIZE];// �������ݴ����

	uint16_t SBWriteIdx;// ���ͻ���д�����
	uint16_t SBReadIdx;// ���ͻ����ȡ���
	uint16_t UnSendCnt;// δ�����ֽ���

	uint8_t IntSendFlag;// ����æµ��־

	uint16_t RBWriteIdx;// ���ջ���д�����
	uint16_t RBReadIdx;// ���ջ����ȡ���
	uint16_t UnRevCnt;// δ��ȡ�ֽ���

	uint16_t RevStart;// ֡��ʼ��־
	uint16_t RevLen;// ���յ�ַ������
	uint8_t RevOK;// һָ֡�������ϱ�־
	uint8_t DataLen;// ���ݳ���

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
