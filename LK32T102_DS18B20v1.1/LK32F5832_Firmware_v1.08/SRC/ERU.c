/**
* @file          : ERU.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is for ERU configuration.
* @version       : Ver. 1.00

* H/W Platform   : SL_FOC FOR MOTOR CONTROL

*------------------------------------------------------------------------------
 
* Compiler info  : Keil v5.20
 
*------------------------------------------------------------------------------
 
* Note: In this software, the function is used in motor control.

*------------------------------------------------------------------------------

*  History:  

*              mm/dd/yyyy ver. x.y.z author

*              mm1/dd1/yyyy1 ver. x.y.z author1

*------------------------------------------------------------------------------
* @attention
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, SLMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* THIS SOURCE CODE IS PROTECTED BY A LICENSE.
* FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
* IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.

* <h2><center>&copy; COPYRIGHT 2017 SLMicroelectronics</center></h2>
*******************************************************************************
*/

/***********************************************************************************
			ERU模块可以连接MCU内部和外部的输入输出。
本例程中，三个模拟比较器将三路捕获信号滤波，其输出结果通过ERU连接至TIMER0，实现捕获功能
*************************************************************************************/

#include "stdint.h"
#include "SC32F5832.h"
#include "DevInit.h"

/***********************************************************************************
			 比较器初始化配置
***********************************************************************************/

void CP1_Init()
{
	GPIO_AF_SEL(ANALOGY,PB,6,0);	   	   // 选择正端输入管脚
	GPIO_AF_SEL(ANALOGY,PB,8,0);
	GPIO_AF_SEL(ANALOGY,PC,0,0);

	
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C12AFILT = 0;        // 滤波使能
  	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C12PS = 1;	    			// 外部管脚输入
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C12EN = 1;           // 比较器使能
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C11AFILT = 0;        // 滤波使能
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C11PS = 1;           // 外部管脚输入
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C11EN = 1;	    			// 比较器使能
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C10AFILT = 0;	   	  // 滤波使能
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C10PS = 1;	    			// 外部管脚输入
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C10EN = 1;  	    		// 比较器使能
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1RDS = 15;          // 设定比较值  
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1VRRH = 0;	    		// 高位
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1VRRL = 0;	    		// 低位
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1VRHS = 0;	    		// VDD
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1REFEN = 1;         // 内部参考电压使能
	SYSREG->ACCESS_EN = 0x05fa659A;
// CP10 CFG
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP10CFG_b.C10DFILT = 0;       // 滤波时钟周期个数，最大1023
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP10CFG_b.C10CLKD = 0;        // 2分频
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP10CFG_b.C10INTS = 3;	    	// 双沿
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP10CFG_b.C10INTM = 0;	    	// 不屏蔽中断
// CP11 CFG
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP11CFG_b.C11DFILT = 0;
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP11CFG_b.C11CLKD = 0; 
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP11CFG_b.C11INTS = 3;
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP11CFG_b.C11INTM = 0;
// CP12 CFG
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP12CFG_b.C12DFILT = 0;
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP12CFG_b.C12CLKD = 0; 
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP12CFG_b.C12INTS = 3;
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP12CFG_b.C12INTM = 0;
}

/*************************************************************************************
				ERU模块的配置
*************************************************************************************/

void ERU_Init()
{	
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXISEL|= ((7<<24)|(7<<16)|(7<<8));	 // 选择ERU_1A7输入；选择ERU_2A7输入；选择ERU_3A7输入；

	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXICON3|=((0<<16)|(1<<2)|(1<<1));   // ETL3状态标志的重建电平检测；上升沿被视为边沿事件；直接输出A
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXICON2|=((0<<16)|(1<<2)|(1<<1));	 // ETL2状态标志的重建电平检测；上升沿被视为边沿事件；直接输出A
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXICON1|=((0<<16)|(1<<2)|(1<<1));   // ETL1状态标志的重建电平检测；上升沿被视为边沿事件；直接输出A

	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXOCON2|=((1<<19)|(1<<2));          // 标志 ERUINCTRL3.FL参与模式检测；事件检测被使能
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXOCON1|=((1<<18)|(1<<2));					 // 标志 ERUINCTRL2.FL参与模式检测；事件检测被使能
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXOCON0|=((1<<17)|(1<<2));		 			 // 标志 ERUINCTRL1.FL参与模式检测；事件检测被使能
}

/*********************************************************************************
			TIMER0的输入捕获配置
*********************************************************************************/

void TIMER_INIT()
{
	TIMER0->TIM_PSC= 0;	              // 预分频
	TIMER0->TIM_ARR = 65535;
	
	TIMER0->TIM_CCMR1|=(1<<0);  		  // CH1 映射在TI1上
	TIMER0->TIM_CCMR1|=(1<<8);		 		// CH2 映射在TI2上
	TIMER0->TIM_CCMR2|=(1<<0);		 		// CH3 映射在TI3上
	TIMER0->TIM_CCMR2|=(1<<8);  		  // CH4 映射在TI4上
	
	TIMER0->TIM_CCER_b.CC3P=1; 		 		//上升和下降沿
	TIMER0->TIM_CCER_b.CC3NP=1;
	TIMER0->TIM_CCER_b.CC2P=1; 		 		//上升和下降沿
	TIMER0->TIM_CCER_b.CC2NP =1;
	TIMER0->TIM_CCER_b.CC4P = 1;
	TIMER0->TIM_CCER_b.CC1NP=1;
	TIMER0->TIM_CCER_b.CC1P=1;
	
	TIMER0->TIM_CCER_b.CC2E =1;		 		//捕获使能
  TIMER0->TIM_CCER_b.CC3E =1;		 		//捕获使能
	TIMER0->TIM_CCER_b.CC4E =1; 		  //捕获使能
	TIMER0->TIM_CCER_b.CC1E =1;
	
	TIMER0->TIM_DIER_b.UIE =1;   		  //更新中断使能
	TIMER0->TIM_DIER_b.CC2IE =1; 		  //捕捉/比较2中断使能
	TIMER0->TIM_DIER_b.CC3IE =1; 		  //捕捉/比较3中断使能
	TIMER0->TIM_DIER_b.CC4IE =1; 		  //捕捉/比较4中断使能
	TIMER0->TIM_DIER_b.CC1IE =1;
	
	TIMER0->TIM_ISR_b.Ch3_sel = 2;  	// 通道3输入信号选择：OGU2 PDout
	TIMER0->TIM_ISR_b.Ch2_sel = 2;  	// 通道2输入信号选择：OGU1 PDout
	TIMER0->TIM_ISR_b.Ch1_sel = 2;  	// 通道1输入信号选择：OGU0 PDout
	
	TIMER0->TIM_CR1_b.CEN=1; 		 			//计数器使能
	
}
