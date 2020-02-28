#ifndef __CMP_H
#define __CMP_H

#include <SC32F5832.h>


/************************************************************
												�Ƚ�������
************************************************************/

#define	C0PS_INPUT_SEL_OPA_OUTPUT						0;				// �Ƚ���0����ѡ��OPA������
#define C0PS_INPUT_SEL_PIN									1;				// �Ƚ���0����ѡ��ܽ�����

#define C0OPS_SEL_OP0O											0;				// �Ƚ���0����ѡ��OPA0������
#define C0OPS_SEL_OP1O											1;				// �Ƚ���0����ѡ��OPA1������
#define C0OPS_SEL_OP2O											2;				// �Ƚ���0����ѡ��OPA2������
#define C0OPS_SEL_OP3O											3;				// �Ƚ���0����ѡ��OPA3������

#define CMP_ENABLE													1;				// �Ƚ���ʹ��
#define CMP_DISABLE													0;				// �Ƚ�����ֹ

#define	VRHS_SOURCE_SEL_VDD									0;				// �ڲ������ѹ���ݵ�Դѡ��VDD


#define REFEN_INTERN_REF_ENABLE							1;				// �ڲ��ο���ѹʹ��
#define REFEN_INTERN_REF_DISABLE						0;				// �ڲ��ο���ѹ��ֹ

#define HYSEN_WITH_HYSTERESIS								1;				// �г���
#define HYSEN_WITHOUT_HYSTERESIS						0;				// �޳���

#define C0NS_NEG_INPUT_SEL_CVREF0						0;				// ��������ѡ��CVREF0
#define C0NS_NEG_INPUT_SEL_PIN							1;				// ��������ѡ���ⲿ�ܽ�����
#define C0NS_NEG_INPUT_SEL_VSS							3;				// ��������ѡ��VSS

#define INTS_DISABLE												0;				// �ж�����ѡ�񣺽�ֹ
#define INTS_FE															1;				// �ж�����ѡ���½���
#define INTS_RE															2;				// �ж�����ѡ��������
#define INTS_FE_RE													3;				// �ж�����ѡ�������غ��½���

#define INTM_INT_ENABLE											0;				// �������ж�
#define INTM_INT_DISABLE										1;				// �����ж�

#define C1PS_INPUT_SEL_OPA_OUTPUT						0;				// ��������ѡ��OPA���
#define C1PS_INPUT_SEL_PIN									1;				// ��������ѡ��ܽ�����

#define C1NS_NEG_INPUT_SEL_CVREF0						0;				// ����ѡ��CVREF0
#define C1NS_NEG_INPUT_SEL_CP10N						1;				// ����ѡ��CP10N
#define C1NS_NEG_INPUT_SEL_CP11N						2;				// ����ѡ��CP11N
#define C1NS_NEG_INPUT_SEL_CP12N						3;				// ����ѡ��CP12N
#define C1NS_NEG_INPUT_SEL_VSS							4;				// ����ѡ��VSS
#define C1NS_NEG_INPUT_SEL_VCORE						6;				// ����ѡ��VCORE
#define C1NS_NEG_INPUT_SEL_SEPARATE					7;				// ���˷ֱ��CP10N��CP11N��CP12N



#endif
