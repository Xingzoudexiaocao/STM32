#ifndef __CLK_H
#define __CLK_H


#define PLLSRC_RCH  0		//选择RCH16M作为时钟源
#define PLLSRC_OSC  1		//选择外部晶振作为时钟源

#define CHIPKEY_ENABLE CHIPCTL -> CHIP_KEY = 0x05fa659aul;

#define PLLDIV1	0		// PLL不分频
#define PLLDIV2	1		// PLL2分频
#define PLLDIV3 2		// PLL3分频
#define PLLDIV4 3		// PLL4分频
#define PLLDIV5 4		// PLL5分频
#define PLLDIV6 5		// PLL6分频
#define PLLDIV7 6		// PLL7分频
#define PLLDIV8 7		// PLL8分频
#define PLLDIV9 8		// PLL9分频
#define PLLDIV10 9		// PLL10分频
#define PLLDIV11 10		// PLL11分频
#define PLLDIV12 11		// PLL12分频
#define PLLDIV13 12		// PLL13分频
#define PLLDIV14 13		// PLL14分频
#define PLLDIV15 14		// PLL15分频
#define PLLDIV16 15		// PLL16分频

#define PLLMUL24 0		// PLL24倍频
#define PLLMUL28 1		// PLL28倍频
#define PLLMUL32 2		// PLL32倍频
#define PLLMUL36 3		// PLL36倍频

#define OSCGAIN1_4 0			// 外部接1-4MHz晶振
#define OSCGAIN4_8 1			// 外部接4-8MHz晶振
#define OSCGAIN8_16 2			// 外部接8-16MHz晶振
#define OSCGAIN16_32 3		// 外部接16-32MHz晶振

//外部晶振稳定时间选择

#define OSCSTB4MS 0			// 32k时钟计数2^7,约4ms
#define OSCSTB8MS 1			// 32k时钟计数2^8,8ms
#define OSCSTB16MS 2		// 32k时钟计数2^9,16ms
#define OSCSTB32MS 3		// 32k时钟计数2^10,32ms

#define OSCEN	 1					// 晶振使能
#define	OSCSTB	(1<<11)		// 外部晶振稳定标志
#define	RCHEN	(1<<12)			// rch使能；受highest_key控制
#define	RCHSTB	(1<<14)		// rch稳定标志
#define PLLEN	(1<<28)			// pll使能
#define PLLLOCK	(1<<30)		// pll锁定标志
#define OSCDEN (1<<1)     // 晶振检测使能	
#define OSCREN (1<<6)     // 外部晶振内置反馈电阻选择：有效
#define DCTEN (1<<2)   // 当检测到正在使用的时钟源不稳定或丢失，直接将时钟切换到到rch16m,使能
#define OSC_MISS_MASK (1<<18)	// 时钟不稳定中断屏蔽

#endif
