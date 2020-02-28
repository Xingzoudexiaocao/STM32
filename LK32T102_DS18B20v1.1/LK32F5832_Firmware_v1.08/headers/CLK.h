#ifndef __CLK_H
#define __CLK_H


#define PLLSRC_RCH  0		//ѡ��RCH16M��Ϊʱ��Դ
#define PLLSRC_OSC  1		//ѡ���ⲿ������Ϊʱ��Դ

#define CHIPKEY_ENABLE CHIPCTL -> CHIP_KEY = 0x05fa659aul;

#define PLLDIV1	0		// PLL����Ƶ
#define PLLDIV2	1		// PLL2��Ƶ
#define PLLDIV3 2		// PLL3��Ƶ
#define PLLDIV4 3		// PLL4��Ƶ
#define PLLDIV5 4		// PLL5��Ƶ
#define PLLDIV6 5		// PLL6��Ƶ
#define PLLDIV7 6		// PLL7��Ƶ
#define PLLDIV8 7		// PLL8��Ƶ
#define PLLDIV9 8		// PLL9��Ƶ
#define PLLDIV10 9		// PLL10��Ƶ
#define PLLDIV11 10		// PLL11��Ƶ
#define PLLDIV12 11		// PLL12��Ƶ
#define PLLDIV13 12		// PLL13��Ƶ
#define PLLDIV14 13		// PLL14��Ƶ
#define PLLDIV15 14		// PLL15��Ƶ
#define PLLDIV16 15		// PLL16��Ƶ

#define PLLMUL24 0		// PLL24��Ƶ
#define PLLMUL28 1		// PLL28��Ƶ
#define PLLMUL32 2		// PLL32��Ƶ
#define PLLMUL36 3		// PLL36��Ƶ

#define OSCGAIN1_4 0			// �ⲿ��1-4MHz����
#define OSCGAIN4_8 1			// �ⲿ��4-8MHz����
#define OSCGAIN8_16 2			// �ⲿ��8-16MHz����
#define OSCGAIN16_32 3		// �ⲿ��16-32MHz����

//�ⲿ�����ȶ�ʱ��ѡ��

#define OSCSTB4MS 0			// 32kʱ�Ӽ���2^7,Լ4ms
#define OSCSTB8MS 1			// 32kʱ�Ӽ���2^8,8ms
#define OSCSTB16MS 2		// 32kʱ�Ӽ���2^9,16ms
#define OSCSTB32MS 3		// 32kʱ�Ӽ���2^10,32ms

#define OSCEN	 1					// ����ʹ��
#define	OSCSTB	(1<<11)		// �ⲿ�����ȶ���־
#define	RCHEN	(1<<12)			// rchʹ�ܣ���highest_key����
#define	RCHSTB	(1<<14)		// rch�ȶ���־
#define PLLEN	(1<<28)			// pllʹ��
#define PLLLOCK	(1<<30)		// pll������־
#define OSCDEN (1<<1)     // ������ʹ��	
#define OSCREN (1<<6)     // �ⲿ�������÷�������ѡ����Ч
#define DCTEN (1<<2)   // ����⵽����ʹ�õ�ʱ��Դ���ȶ���ʧ��ֱ�ӽ�ʱ���л�����rch16m,ʹ��
#define OSC_MISS_MASK (1<<18)	// ʱ�Ӳ��ȶ��ж�����

#endif
