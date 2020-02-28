#ifndef __ETIMER_H
#define __ETIMER_H

#define	TIM_ARPE_ENABLE 		TIMER0->TIM_CR1_b.ARPE=1;					// Ԥװ��ʹ��
#define TIM_ARPE_DISABLE		TIMER0->TIM_CR1_b.ARPE=0;					// Ԥװ�ؽ�ֹ
	
#define CC1S_OUTPUT						(0<<0);													// CC1Sͨ����Ϊ���
#define CC1S_INPUT_IC1_To_TI1	(1<<0);													// CC1Sͨ����Ϊ���벢ӳ�䵽TI1
#define CC1S_INPUT_IC1_To_TI2	(2<<0);													// CC1Sͨ����Ϊ���벢ӳ�䵽TI2
#define CC1S_INPUT_IC1_To_TRC	(3<<0);													// CC1Sͨ����Ϊ���벢ӳ�䵽TRC
#define CC2S_OUTPUT						(0<<8);													// CC2Sͨ����Ϊ���
#define CC2S_INPUT_IC2_To_TI2 (1<<8);													// CC2Sͨ����Ϊ���벢ӳ�䵽TI2
#define CC2S_INPUT_IC2_To_TI1	(2<<8);													// CC2Sͨ����Ϊ���벢ӳ�䵽TI1
#define	CC2S_INPUT_IC2_To_TRC	(3<<8);													// CC2Sͨ����Ϊ���벢ӳ�䵽TRC
#define CC3S_OUTPUT						(0<<0);													// CC3Sͨ����Ϊ���
#define	CC3S_INPUT_IC3_To_TI3	(1<<0);													// CC3Sͨ����Ϊ���벢ӳ�䵽TI3
#define	CC3S_INPUT_IC3_To_TI4	(2<<0);													// CC3Sͨ����Ϊ���벢ӳ�䵽TI4
#define	CC3S_INPUT_IC3_To_TRC	(3<<0);													// CC3Sͨ����Ϊ���벢ӳ�䵽TRC
#define CC4S_OUTPUT						(0<<8);													// CC4Sͨ����Ϊ���
#define	CC4S_INPUT_IC4_To_TI4	(1<<8);													// CC4Sͨ����Ϊ���벢ӳ�䵽TI4
#define CC4S_INPUT_IC4_To_TI3	(2<<8);													// CC4Sͨ����Ϊ���벢ӳ�䵽TI3
#define	CC4S_INPUT_IC4_To_TRC	(3<<8);													// CC4Sͨ����Ϊ���벢ӳ�䵽TRC

#define CC1E_ENABLE						1;															// CC1ͨ��ʹ��
#define CC1E_DISABLE					0;															// CC1ͨ����ֹ
#define	CC1NE_ENABLE					1;															// CC1Nͨ��ʹ��
#define	CC1NE_DISABLE					0;															// CC1Nͨ����ֹ
#define	CC2E_ENABLE						1;															// CC2ͨ��ʹ��
#define CC2E_DISABLE					0;															// CC2ͨ����ֹ
#define	CC2NE_ENABLE					1;															// CC2Nͨ��ʹ��
#define	CC2NE_DISABLE					0;															// CC2Nͨ����ֹ
#define	CC3E_ENABLE						1;															// CC3ͨ��ʹ��
#define	CC3E_DISABLE					0;															// CC3ͨ����ֹ
#define	CC3NE_ENABLE					1;															// CC3Nͨ��ʹ��
#define	CC3NE_DISABLE					0;															// CC3Nͨ����ֹ
#define	CC4E_ENABLE						1;															// CC4ͨ��ʹ��
#define CC4E_DISABLE					0;															// CC4ͨ����ֹ

#define OC1M_FREEZE						(0<<4);													// �Ƚ����ģʽ1ѡ�񣺶���
#define	OC1M_MATCH_HIGH				(1<<4);													// �Ƚ����ģʽ1ѡ��ƥ��ʱ��Ϊ��Ч��ƽ
#define OC1M_MATCH_LOW				(2<<4);													// �Ƚ����ģʽ1ѡ��ƥ��ʱ��Ϊ��Ч��ƽ
#define OC1M_MATCH_TOGGLE			(3<<4);													// �Ƚ����ģʽ1ѡ��ƥ��ʱ��ת��ƽ
#define OC1M_FORCE_LOW				(4<<4);													// �Ƚ����ģʽ1ѡ��ǿ��Ϊ��Ч��ƽ
#define	OC1M_FORCE_HIGH				(5<<4);													// �Ƚ����ģʽ1ѡ��ǿ��Ϊ��Ч��ƽ
#define	OC1M_PWM_MODE1				(6<<4);													// �Ƚ����ģʽ1ѡ��PWMģʽ1
#define OC1M_PWM_MODE2				(7<<4);													// �Ƚ����ģʽ1ѡ��PWMģʽ2
#define OC2M_FREEZE						(0<<12);												// �Ƚ����ģʽ2ѡ�񣺶���
#define	OC2M_MATCH_HIGH				(1<<12);												// �Ƚ����ģʽ2ѡ��ƥ��ʱ��Ϊ��Ч��ƽ
#define OC2M_MATCH_LOW				(2<<12);												// �Ƚ����ģʽ2ѡ��ƥ��ʱ��Ϊ��Ч��ƽ
#define OC2M_MATCH_TOGGLE			(3<<12);												// �Ƚ����ģʽ2ѡ��ƥ��ʱ��ת��ƽ
#define OC2M_FORCE_LOW				(4<<12);												// �Ƚ����ģʽ2ѡ��ǿ��Ϊ��Ч��ƽ
#define	OC2M_FORCE_HIGH				(5<<12);												// �Ƚ����ģʽ2ѡ��ǿ��Ϊ��Ч��ƽ	
#define	OC2M_PWM_MODE1				(6<<12);												// �Ƚ����ģʽ2ѡ��PWMģʽ1
#define OC2M_PWM_MODE2				(7<<12);												// �Ƚ����ģʽ2ѡ��PWMģʽ2
#define OC3M_FREEZE						(0<<4);													// �Ƚ����ģʽ3ѡ�񣺶���
#define	OC3M_MATCH_HIGH				(1<<4);													// �Ƚ����ģʽ3ѡ��ƥ��ʱ��Ϊ��Ч��ƽ
#define OC3M_MATCH_LOW				(2<<4);													// �Ƚ����ģʽ3ѡ��ƥ��ʱ��Ϊ��Ч��ƽ
#define OC3M_MATCH_TOGGLE			(3<<4);													// �Ƚ����ģʽ3ѡ��ƥ��ʱ��ת��ƽ
#define OC3M_FORCE_LOW				(4<<4);													// �Ƚ����ģʽ3ѡ��ǿ��Ϊ��Ч��ƽ
#define	OC3M_FORCE_HIGH				(5<<4);													// �Ƚ����ģʽ3ѡ��ǿ��Ϊ��Ч��ƽ	
#define	OC3M_PWM_MODE1				(6<<4);													// �Ƚ����ģʽ3ѡ��PWMģʽ1
#define OC3M_PWM_MODE2				(7<<4);													// �Ƚ����ģʽ3ѡ��PWMģʽ2
#define OC4M_FREEZE						(0<<12);												// �Ƚ����ģʽ4ѡ�񣺶���
#define	OC4M_MATCH_HIGH				(1<<12);												// �Ƚ����ģʽ4ѡ��ƥ��ʱ��Ϊ��Ч��ƽ
#define OC4M_MATCH_LOW				(2<<12);												// �Ƚ����ģʽ4ѡ��ƥ��ʱ��Ϊ��Ч��ƽ
#define OC4M_MATCH_TOGGLE			(3<<12);												// �Ƚ����ģʽ4ѡ��ƥ��ʱ��ת��ƽ
#define OC4M_FORCE_LOW				(4<<12);												// �Ƚ����ģʽ4ѡ��ǿ��Ϊ��Ч��ƽ
#define	OC4M_FORCE_HIGH				(5<<12);												// �Ƚ����ģʽ4ѡ��ǿ��Ϊ��Ч��ƽ	
#define	OC4M_PWM_MODE1				(6<<12);												// �Ƚ����ģʽ4ѡ��PWMģʽ1
#define OC4M_PWM_MODE2				(7<<12);												// �Ƚ����ģʽ4ѡ��PWMģʽ2

#define OC1PE_PRELOAD_ENABLE	(1<<3);													// Ԥװ��ʹ��
#define OC1PE_PRELOAD_DISABLE	(0<<3);													// Ԥװ�ؽ�ֹ
#define OC2PE_PRELOAD_ENABLE	(1<<11);												// Ԥװ��ʹ��
#define	OC2PE_PRELOAD_DISABLE	(0<<11);												// Ԥװ�ؽ�ֹ
#define OC3PE_PRELOAD_ENABLE	(1<<3);													// Ԥװ��ʹ��
#define OC3PE_PRELOAD_DISABLE	(0<<3);													// Ԥװ�ؽ�ֹ
#define OC4PE_PRELOAD_ENABLE	(1<<11);												// Ԥװ��ʹ��
#define	OC4PE_PRELOAD_DISABLE	(0<<11);												// Ԥװ�ؽ�ֹ
/*****************************************************
						������������ܼ�������
******************************************************/
#define	CC1P_OUTPUT_HIGH			0;															// �ߵ�ƽ��Ч
#define CC1P_OUTPUT_LOW				1;															// �͵�ƽ��Ч
#define	CC1NP_OUTPUT_HIGH			0;															// �ߵ�ƽ��Ч
#define	CC1NP_OUTPUT_LOW			1;															// �͵�ƽ��Ч
#define	CC2P_OUTPUT_HIGH			0;															// �ߵ�ƽ��Ч
#define CC2P_OUTPUT_LOW				1;															// �͵�ƽ��Ч
#define	CC2NP_OUTPUT_HIGH			0;															// �ߵ�ƽ��Ч
#define	CC2NP_OUTPUT_LOW			1;															// �͵�ƽ��Ч
#define	CC3P_OUTPUT_HIGH			0;															// �ߵ�ƽ��Ч
#define CC3P_OUTPUT_LOW				1;															// �͵�ƽ��Ч
#define	CC3NP_OUTPUT_HIGH			0;															// �ߵ�ƽ��Ч
#define	CC3NP_OUTPUT_LOW			1;															// �͵�ƽ��Ч
#define	CC4P_OUTPUT_HIGH			0;															// �ߵ�ƽ��Ч
#define CC4P_OUTPUT_LOW				1;															// �͵�ƽ��Ч

#define CC1IE_ENABLE					1;															// ��׽/�Ƚ�1�ж�ʹ��
#define CC1IE_DISABLE					0;															// ��׽/�Ƚ�1�жϽ�ֹ
#define	CC2IE_ENABLE					1;															// ��׽/�Ƚ�2�ж�ʹ��
#define	CC2IE_DISABLE					0;															// ��׽/�Ƚ�2�жϽ�ֹ
#define	CC3IE_ENABLE					1;															// ��׽/�Ƚ�3�ж�ʹ��
#define	CC3IE_DISABLE					0;															// ��׽/�Ƚ�3�жϽ�ֹ
#define	CC4IE_ENABLE					1;															// ��׽/�Ƚ�4�ж�ʹ��
#define	CC4IE_DISABLE					0;															// ��׽/�Ƚ�4�жϽ�ֹ
#define	UIE_ENABLE						1;															// �����ж�ʹ��
#define	UIE_DISABLE						0;															// �����жϽ�ֹ
#define	COMIE_ENABLE					1;															// COM�ж�ʹ��
#define	COMIE_DISABLE					0;															// COM�жϽ�ֹ
#define	TIE_ENBALE						1;															// �����ж�ʹ��
#define	TIE_DISABLE						0;															// �����жϽ�ֹ
#define	BIE_ENABLE						1;															// ɲ���ж�ʹ��
#define BIE_DISABLE						0;															// ɲ���жϽ�ֹ

#define MOE_ENABLE						1;															// �����ʹ��
#define MOE_DISABLE						0;															// �������ֹ
#define	AOE_AUTO_SET					1;															// �Զ����ʹ��
#define	AOE_SW_SET						0;															// �Զ������ֹ


#define CNT_CLR_ENABLE				(1<<17);												// ��������������ʹ��
#define CNT_CLR_DISABLE				(0<<17);												// ���������������ֹ

#define CNT_CLR_SEL_CH1				(0<<15);												// ͨ��1��������
#define	CNT_CLR_SEL_CH2				(1<<15);												// ͨ��2��������
#define	CNT_CLR_SEL_CH3				(2<<15);												// ͨ��3��������
#define	CNT_CLR_SEL_CH4				(3<<15);												// ͨ��4��������

#define CNT_ENABLE		TIMER0->TIM_CR1_b.CEN=1;								// ������ʹ��
#define CNT_DISABLE		TIMER0->TIM_CR1_b.CEN=0;								// ����������

#define	CMS_EDGE_ALIGN				0;															// ���ض���ģʽ
#define CMS_CENTER_MODE1			1;															// �������ģʽ1
#define CMS_CENTER_MODE2			2;															// �������ģʽ2
#define CMS_CENTER_MODE3			3;															// �������ģʽ3

#define	BKE_BRAKE_ENABLE			1;															// ɲ��ʹ��
#define	BKE_BRAKE_DISABLE			0;															// ɲ����ֹ
#define	BKP_BRAKE_POL_HIGH		1;															// ɲ������ߵ�ƽ��Ч
#define BKP_BRAKE_POL_LOW			0;															// ɲ������͵�ƽ��Ч

#define OIS1_OC1_AFTER_DT_LOW			0;													// �������õ�
#define OIS1_OC1_AFTER_DT_HIGH		1;													// �������ø�
#define	OIS1N_OC1N_AFTER_DT_LOW		0;													// �������õ�
#define OIS1N_OC1N_AFTER_DT_HIGH	1;													// �������ø�
#define OIS2_OC1_AFTER_DT_LOW			0;													// �������õ�
#define OIS2_OC1_AFTER_DT_HIGH		1;													// �������ø�
#define	OIS2N_OC1N_AFTER_DT_LOW		0;													// �������õ�
#define OIS2N_OC1N_AFTER_DT_HIGH	1;													// �������ø�
#define OIS3_OC1_AFTER_DT_LOW			0;													// �������õ�
#define OIS3_OC1_AFTER_DT_HIGH		1;													// �������ø�
#define	OIS3N_OC1N_AFTER_DT_LOW		0;													// �������õ�
#define OIS3N_OC1N_AFTER_DT_HIGH	1;													// �������ø�
#define OIS4_OC1_AFTER_DT_LOW			0;													// �������õ�
#define OIS4_OC1_AFTER_DT_HIGH		1;													// �������ø�

#define TS_ITR0										0;													// ����Դѡ��ITR0
#define TS_ITR1										1;													// ����Դѡ��ITR1
#define	TS_ITR2										2;													// ����Դѡ��ITR2
#define TS_ITR3										3;													// ����Դѡ��ITR3
#define TS_TI1F_ED								4;													// ����Դѡ��TI1F_ED
#define TS_TI1FP1									5;													// ����Դѡ��TI1FP1
#define	TS_TI2FP2									6;													// ����Դѡ��TI2FP2
#define TS_ETRF										7;													// ����Դѡ��ETRF

#define SMS_SLAVE_MODE_DISABLE		0;													// ��ģʽ��ֹ
#define SMS_ENCODER_MODE1					1;													// ��ģʽѡ�������ģʽ1
#define SMS_ENCODER_MODE2					2;													// ��ģʽѡ�������ģʽ2
#define SMS_ENCODER_MODE3					3;													// ��ģʽѡ�������ģʽ3
#define SMS_RESET_MODE						4;													// ��ģʽѡ��λģʽ
#define SMS_GATE_CONTROL					5;													// ��ģʽѡ���ſ�ģʽ
#define SMS_TRIG_MODE							6;													// ��ģʽѡ�񴥷�ģʽ								
#define SMS_EXT_CLK_MODE1					7;													// ��ģʽѡ���ⲿʱ��ģʽ

#define EGR_CNT_UPDATE	TIMER0->TIM_EGR_b.UG = 1;							// ���������¼�


#endif
