#ifndef __CMP_H
#define __CMP_H

#include <SC32F5832.h>


/************************************************************
												比较器定义
************************************************************/

#define	C0PS_INPUT_SEL_OPA_OUTPUT						0;				// 比较器0输入选择OPA输出结果
#define C0PS_INPUT_SEL_PIN									1;				// 比较器0输入选择管脚输入

#define C0OPS_SEL_OP0O											0;				// 比较器0输入选择OPA0输出结果
#define C0OPS_SEL_OP1O											1;				// 比较器0输入选择OPA1输出结果
#define C0OPS_SEL_OP2O											2;				// 比较器0输入选择OPA2输出结果
#define C0OPS_SEL_OP3O											3;				// 比较器0输入选择OPA3输出结果

#define CMP_ENABLE													1;				// 比较器使能
#define CMP_DISABLE													0;				// 比较器禁止

#define	VRHS_SOURCE_SEL_VDD									0;				// 内部电阻分压阶梯电源选择VDD


#define REFEN_INTERN_REF_ENABLE							1;				// 内部参考电压使能
#define REFEN_INTERN_REF_DISABLE						0;				// 内部参考电压禁止

#define HYSEN_WITH_HYSTERESIS								1;				// 有迟滞
#define HYSEN_WITHOUT_HYSTERESIS						0;				// 无迟滞

#define C0NS_NEG_INPUT_SEL_CVREF0						0;				// 负端输入选择CVREF0
#define C0NS_NEG_INPUT_SEL_PIN							1;				// 负端输入选择外部管脚输入
#define C0NS_NEG_INPUT_SEL_VSS							3;				// 负端输入选择VSS

#define INTS_DISABLE												0;				// 中断类型选择：禁止
#define INTS_FE															1;				// 中断类型选择下降沿
#define INTS_RE															2;				// 中断类型选择上升沿
#define INTS_FE_RE													3;				// 中断类型选择上升沿和下降沿

#define INTM_INT_ENABLE											0;				// 不屏蔽中断
#define INTM_INT_DISABLE										1;				// 屏蔽中断

#define C1PS_INPUT_SEL_OPA_OUTPUT						0;				// 正端输入选择OPA输出
#define C1PS_INPUT_SEL_PIN									1;				// 正端输入选择管脚输入

#define C1NS_NEG_INPUT_SEL_CVREF0						0;				// 负端选择CVREF0
#define C1NS_NEG_INPUT_SEL_CP10N						1;				// 负端选择CP10N
#define C1NS_NEG_INPUT_SEL_CP11N						2;				// 负端选择CP11N
#define C1NS_NEG_INPUT_SEL_CP12N						3;				// 负端选择CP12N
#define C1NS_NEG_INPUT_SEL_VSS							4;				// 负端选择VSS
#define C1NS_NEG_INPUT_SEL_VCORE						6;				// 负端选择VCORE
#define C1NS_NEG_INPUT_SEL_SEPARATE					7;				// 负端分别接CP10N、CP11N、CP12N



#endif
