#ifndef __OPA_H
#define __OPA_H

#include <SC32F5832.h>

/********************************************************
			�˷Ŷ���
**********************************************************/

//#define ACCESS_ENABLE  SYSREG->ACCESS_EN = 0x05fa659A;
#define OPA_ENABLE								1;				// �˷�ʹ��
#define OPA_DISABLE 							0;				// �˷Ž�ֹ
#define OPA_FEEDBACK_LOOP_ENABLE	1;				// �˷ŷ�����·ʹ��
#define OPA_FEEDBACK_LOOP_DISABLE 0;				// �˷ŷ�����·��ֹ
#define OPA_OUTPUT_To_PIN_ENABLE  1;				// �˷Ž��������ܽ�ʹ��
#define OPA_OUTPUT_To_PIN_DISABLE 0;				// �˷Ž��������ܽŽ�ֹ
#define OP0GS_1x									0;				// OPA0�Ŵ�����Ϊ1
#define OP0GS_4x									1;				// OPA0�Ŵ�����Ϊ4
#define OP0GS_8x									2;				// OPA0�Ŵ�����Ϊ8
#define OP0GS_9x									3;				// OPA0�Ŵ�����Ϊ9
#define OP0GS_10x									4;				// OPA0�Ŵ�����Ϊ10
#define OP0GS_11x									5;				// OPA0�Ŵ�����Ϊ11
#define OP0GS_16x									6;				// OPA0�Ŵ�����Ϊ16
#define OP0GS_32x									7;				// OPA0�Ŵ�����Ϊ32
#define OPA0_NEG_To_GND_ENABLE		1;				// OPA0����˽ӵ�ʹ��
#define OPA0_NEG_To_GND_DISABLE		0;				// OPA0����˽ӵؽ�ֹ
#define OP1GS_1x									0;				// OPA1/2/3�Ŵ�����Ϊ1
#define OP1GS_2x									1;				// OPA1/2/3�Ŵ�����Ϊ2
#define OP1GS_3x									2;				// OPA1/2/3�Ŵ�����Ϊ3
#define OP1GS_4x									3;				// OPA1/2/3�Ŵ�����Ϊ4
#define OP1GS_5x									4;				// OPA1/2/3�Ŵ�����Ϊ5
#define OP1GS_6x									5;				// OPA1/2/3�Ŵ�����Ϊ6
#define OP1GS_8x									6;				// OPA1/2/3�Ŵ�����Ϊ8
#define OP1GS_12x									7;				// OPA1/2/3�Ŵ�����Ϊ12
#define OP1NRS_RES_ENABLE					0;				// OPA1/2/3����˵���ʹ��
#define OP1NRS_RES_SHORT					1;				// OPA1/2/3����˵���̽�

#endif
