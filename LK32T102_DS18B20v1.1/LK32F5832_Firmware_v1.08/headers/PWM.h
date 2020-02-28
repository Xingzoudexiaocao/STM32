#ifndef __PWM_H
#define __PWM_H

#include <SC32F5832.h>

#define PWM0_CTRMODE_UP	 			PWM0->TBCTL_b.CTRMODE = 0;			// ������ģʽ
#define PWM1_CTRMODE_UP	 			PWM1->TBCTL_b.CTRMODE = 0;			// ������ģʽ
#define PWM2_CTRMODE_UP	 			PWM2->TBCTL_b.CTRMODE = 0;			// ������ģʽ
#define PWM4_CTRMODE_UP	 			PWM4->TBCTL_b.CTRMODE = 0;			// ������ģʽ
#define PWM0_CTRMODE_DOWN	 		PWM0->TBCTL_b.CTRMODE = 1;			// ������ģʽ
#define PWM1_CTRMODE_DOWN	 		PWM1->TBCTL_b.CTRMODE = 1;			// ������ģʽ
#define PWM2_CTRMODE_DOWN	 		PWM2->TBCTL_b.CTRMODE = 1;			// ������ģʽ
#define PWM4_CTRMODE_DOWN	 		PWM4->TBCTL_b.CTRMODE = 1;			// ������ģʽ
#define PWM0_CTRMODE_UPDOWN	 	PWM0->TBCTL_b.CTRMODE = 2;			// ��������ģʽ
#define PWM1_CTRMODE_UPDOWN	 	PWM1->TBCTL_b.CTRMODE = 2;			// ��������ģʽ
#define PWM2_CTRMODE_UPDOWN	 	PWM2->TBCTL_b.CTRMODE = 2;			// ��������ģʽ
#define PWM4_CTRMODE_UPDOWN	 	PWM4->TBCTL_b.CTRMODE = 2;			// ��������ģʽ

#define PWM0_PHASE_ENABLE			PWM0->TBCTL_b.PHSEN = 1;				// ��λװ��ʹ��
#define PWM1_PHASE_ENABLE			PWM1->TBCTL_b.PHSEN = 1;				// ��λװ��ʹ��
#define PWM2_PHASE_ENABLE			PWM2->TBCTL_b.PHSEN = 1;				// ��λװ��ʹ��
#define PWM4_PHASE_ENABLE			PWM4->TBCTL_b.PHSEN = 1;				// ��λװ��ʹ��
#define PWM0_PHASE_DISABLE		PWM0->TBCTL_b.PHSEN = 0;				// ��λװ�ؽ�ֹ
#define PWM1_PHASE_DISABLE		PWM1->TBCTL_b.PHSEN = 0;				// ��λװ�ؽ�ֹ
#define PWM2_PHASE_DISABLE		PWM2->TBCTL_b.PHSEN = 0;				// ��λװ�ؽ�ֹ
#define PWM4_PHASE_DISABLE		PWM4->TBCTL_b.PHSEN = 0;				// ��λװ�ؽ�ֹ

#define PWM0_PRD_SHADOWON			PWM0->TBCTL_b.PRDLD = 0;				// ʹ��ӳ��Ĵ���
#define PWM1_PRD_SHADOWON			PWM1->TBCTL_b.PRDLD = 0;				// ʹ��ӳ��Ĵ���
#define PWM2_PRD_SHADOWON			PWM2->TBCTL_b.PRDLD = 0;				// ʹ��ӳ��Ĵ���
#define PWM4_PRD_SHADOWON			PWM4->TBCTL_b.PRDLD = 0;				// ʹ��ӳ��Ĵ���
#define PWM0_PRD_SHADOWOFF		PWM0->TBCTL_b.PRDLD = 1;				// ��ֹӳ��Ĵ���
#define PWM1_PRD_SHADOWOFF		PWM1->TBCTL_b.PRDLD = 1;				// ��ֹӳ��Ĵ���
#define PWM2_PRD_SHADOWOFF		PWM2->TBCTL_b.PRDLD = 1;				// ��ֹӳ��Ĵ���
#define PWM4_PRD_SHADOWOFF		PWM4->TBCTL_b.PRDLD = 1;				// ��ֹӳ��Ĵ���

#define SYNCOSEL_SYNC 				0 															// ͬ��Դѡ��SYNC
#define SYNCOSEL_CTR_ZERO			1																// ͬ��Դѡ��CTR=0
#define	SYNCOSEL_CTR_CMPB			2																// ͬ��Դѡ��CTR=CMPB
#define SYNCOSEL_DISABLE			3																// ����ͬ���ź�

#define SHADOWMODE_ON 				0																// ӳ��ģʽ
#define SHADOWMODE_OFF				1															  // ֱ��ģʽ

#define CMP_LOAD_ZERO					0																// CTR=0ʱ����
#define CMP_LOAD_PRD					1																// CTR=PRDʱ����
#define CMP_LOAD_ZERO_PRD			2																// CTR=0��CTR=PRDʱ����
#define CMP_FREEZE						3																// ����

#define AQ_CBD_NOACTION				0																// ������ģʽ�У�CTR=CMPBʱ���޶���
#define AQ_CBD_CLR						1																// ������ģʽ�У�CTR=CMPBʱ���õ�
#define AQ_CBD_SET						2																// ������ģʽ�У�CTR=CMPBʱ���ø�
#define AQ_CBD_TGL						3																// ������ģʽ�У�CTR=CMPBʱ����ת

#define AQ_CBU_NOACTION				0																// ������ģʽ�У�CTR=CMPBʱ���޶���
#define AQ_CBU_CLR						1																// ������ģʽ�У�CTR=CMPBʱ���õ�
#define AQ_CBU_SET						2																// ������ģʽ�У�CTR=CMPBʱ���ø�
#define AQ_CBU_TGL						3																// ������ģʽ�У�CTR=CMPBʱ����ת

#define AQ_CAD_NOACTION				0																// ������ģʽ�У�CTR=CMPAʱ���޶���
#define AQ_CAD_CLR						1																// ������ģʽ�У�CTR=CMPAʱ���õ�
#define AQ_CAD_SET						2																// ������ģʽ�У�CTR=CMPAʱ���ø�
#define AQ_CAD_TGL						3																// ������ģʽ�У�CTR=CMPAʱ����ת

#define AQ_CAU_NOACTION				0																// ������ģʽ�У�CTR=CMPAʱ���޶���
#define AQ_CAU_CLR						1																// ������ģʽ�У�CTR=CMPAʱ���õ�
#define AQ_CAU_SET						2																// ������ģʽ�У�CTR=CMPAʱ���ø�
#define AQ_CAU_TGL						3																// ������ģʽ�У�CTR=CMPAʱ����ת

#define AQ_PRU_NOACTION				0																// ��CTR=PRDʱ���޶���
#define AQ_PRU_CLR						1																// ��CTR=PRDʱ���õ�
#define AQ_PRU_SET						2																// ��CTR=PRDʱ���ø�
#define AQ_PRU_TGL						3																// ��CTR=PRDʱ����ת

#define AQ_ZRO_NOACTION				0																// ��CTR=PRDʱ���޶���
#define AQ_ZRO_CLR						1																// ��CTR=PRDʱ���õ�
#define AQ_ZRO_SET						2																// ��CTR=PRDʱ���ø�
#define AQ_ZRO_TGL						3																// ��CTR=PRDʱ���޶���

#define DB_INMODE_PWMA_BOTH_EDGE		0													// PWMxA�������غ��½����ӳٵ�����Դ
#define	DB_INMODE_PWMA_FE_PWMB_RE		1													// PWMxA�� �½��� PWMxB�������ص�����Դ
#define DB_INMODE_PWMA_RE_PWMB_FE		2													// PWMxB�� �½��� PWMxA�������ص�����Դ
#define	DB_INMODE_PWMB_BOTH_EDGE		3													// PWMxB�������غ��½����ӳٵ�����Դ

#define DB_OUTMODE_DISABLE					0													// ������������ֹ
#define	DB_OUTMODE_RE_DISABLE				1													// �������ӳٽ�ֹ
#define DB_OUTMODE_FE_DISABLE				2													// �½����ӳٽ�ֹ
#define	DB_OUTMODE_BOTH_ENABLE			3													// �������غ��½����ӳ���ȫʹ��

#define DB_POLSEL_AH					0																// ����Чģʽ
#define DB_POLSEL_ALC					1																// ����Ч����ģʽ
#define DB_POLSEL_AHC					2																// ����Ч����ģʽ
#define	DB_POLSEL_AL					3																// ����Чģʽ

#define ET_INTPRD_DISABLE			0																// �����ж��¼�������
#define ET_INTPRD_1						1																// �ڵ�һ���¼�����ʱ�ж�
#define ET_INTPRD_2						2																// �ڵڶ����¼�����ʱ�ж�
#define	ET_INTPRD_3						3																// �ڵ������¼�����ʱ�ж�

#define ET_INTSEL_CTR_ZERO		1																// ��CTR=0ʱ�����ж�
#define ET_INTSEL_CTR_PRD			2																// ��CTR=PRDʱ�����ж�
#define ET_INTSEL_CAU					4																// ��������ģʽ�У�CTR=CMPAʱ�����ж�
#define ET_INTSEL_CAD					5																// �ڼ�����ģʽ�У�CTR=CMPAʱ�����ж�
#define ET_INTSEL_CBU					6																// ��������ģʽ�У�CTR=CMPBʱ�����ж�
#define ET_INTSEL_CBD					7																// �ڼ�����ģʽ�У�CTR=CMPBʱ�����ж�

#define ET_INT_ENABLE					1																// �����ж�����
#define ET_INT_DISABLE				0																// ��ֹ�ж�����

#define ET_SOCPRD_DISABLE		0																	// ����SOC�¼�������
#define ET_SOCPRD_1					1																	// �ڵ�һ���¼�������SOC����
#define ET_SOCPRD_2					2																	// �ڵڶ����¼�������SOC����
#define ET_SOCPRD_3					3																	// �ڵ������¼�������SOC����

#define ET_SOCSEL_CTR_ZERO		1																// ��CTR=0ʱ����SOC����
#define ET_SOCSEL_CTR_PRD			2																// ��CTR=PRDʱ����SOC����
#define	ET_SOCSEL_CAU					4																// ��������ģʽ�У�CTR=CMPAʱ����SOC����
#define ET_SOCSEL_CAD					5																// �ڼ�����ģʽ�У�CTR=CMPAʱ����SOC����
#define	ET_SOCSEL_CBU					6																// ��������ģʽ�У�CTR=CMPBʱ����SOC����
#define	ET_SOCSEL_CBD					7																// �ڼ�����ģʽ�У�CTR=CMPBʱ����SOC����

#define ET_SOC_ENABLE					1																// ʹ��SOC�����ź�
#define ET_SOC_DISABLE				0																// ��ֹSOC�����ź�

#define ACCESS_ENABLE		SYSREG->ACCESS_EN = 0x05fa659a; 			// �ر�д����

#define TZ_OSHT_ENABLE				1																// ���ι��ϱ���ʹ��
#define	TZ_OSHT_DISABLE				0																// ���ι��ϱ�����ֹ
#define TZ_CBC_ENABLE					1																// ����ѭ�����ϱ���ʹ��
#define TZ_CBC_DISABLE				0																// ����ѭ�����ϱ�����ֹ

#define TZ_HIGH_R							0																// ����̬
#define	TZ_SET_HIGH						1																// �ø�
#define	TZ_SET_LOW						2																// �õ�
#define	TZ_NO_ACTION					3																// �޶���

#define PWM_START	ACCESS_ENABLE;SYSREG->PWM_CFG|= 0x000000ff;			// ͬ��������PWMͨ��


#endif
