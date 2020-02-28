#ifndef __OPA_H
#define __OPA_H

#include <SC32F5832.h>

/********************************************************
			运放定义
**********************************************************/

//#define ACCESS_ENABLE  SYSREG->ACCESS_EN = 0x05fa659A;
#define OPA_ENABLE								1;				// 运放使能
#define OPA_DISABLE 							0;				// 运放禁止
#define OPA_FEEDBACK_LOOP_ENABLE	1;				// 运放反馈环路使能
#define OPA_FEEDBACK_LOOP_DISABLE 0;				// 运放反馈环路禁止
#define OPA_OUTPUT_To_PIN_ENABLE  1;				// 运放结果输出到管脚使能
#define OPA_OUTPUT_To_PIN_DISABLE 0;				// 运放结果输出到管脚禁止
#define OP0GS_1x									0;				// OPA0放大倍数设为1
#define OP0GS_4x									1;				// OPA0放大倍数设为4
#define OP0GS_8x									2;				// OPA0放大倍数设为8
#define OP0GS_9x									3;				// OPA0放大倍数设为9
#define OP0GS_10x									4;				// OPA0放大倍数设为10
#define OP0GS_11x									5;				// OPA0放大倍数设为11
#define OP0GS_16x									6;				// OPA0放大倍数设为16
#define OP0GS_32x									7;				// OPA0放大倍数设为32
#define OPA0_NEG_To_GND_ENABLE		1;				// OPA0反相端接地使能
#define OPA0_NEG_To_GND_DISABLE		0;				// OPA0反相端接地禁止
#define OP1GS_1x									0;				// OPA1/2/3放大倍数设为1
#define OP1GS_2x									1;				// OPA1/2/3放大倍数设为2
#define OP1GS_3x									2;				// OPA1/2/3放大倍数设为3
#define OP1GS_4x									3;				// OPA1/2/3放大倍数设为4
#define OP1GS_5x									4;				// OPA1/2/3放大倍数设为5
#define OP1GS_6x									5;				// OPA1/2/3放大倍数设为6
#define OP1GS_8x									6;				// OPA1/2/3放大倍数设为8
#define OP1GS_12x									7;				// OPA1/2/3放大倍数设为12
#define OP1NRS_RES_ENABLE					0;				// OPA1/2/3反相端电阻使能
#define OP1NRS_RES_SHORT					1;				// OPA1/2/3反相端电阻短接

#endif
