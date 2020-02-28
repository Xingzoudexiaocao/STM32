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
			ERUģ���������MCU�ڲ����ⲿ�����������
�������У�����ģ��Ƚ�������·�����ź��˲�����������ͨ��ERU������TIMER0��ʵ�ֲ�����
*************************************************************************************/

#include "stdint.h"
#include "SC32F5832.h"
#include "DevInit.h"

/***********************************************************************************
			 �Ƚ�����ʼ������
***********************************************************************************/

void CP1_Init()
{
	GPIO_AF_SEL(ANALOGY,PB,6,0);	   	   // ѡ����������ܽ�
	GPIO_AF_SEL(ANALOGY,PB,8,0);
	GPIO_AF_SEL(ANALOGY,PC,0,0);

	
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C12AFILT = 0;        // �˲�ʹ��
  	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C12PS = 1;	    			// �ⲿ�ܽ�����
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C12EN = 1;           // �Ƚ���ʹ��
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C11AFILT = 0;        // �˲�ʹ��
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C11PS = 1;           // �ⲿ�ܽ�����
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C11EN = 1;	    			// �Ƚ���ʹ��
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C10AFILT = 0;	   	  // �˲�ʹ��
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C10PS = 1;	    			// �ⲿ�ܽ�����
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C10EN = 1;  	    		// �Ƚ���ʹ��
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1RDS = 15;          // �趨�Ƚ�ֵ  
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1VRRH = 0;	    		// ��λ
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1VRRL = 0;	    		// ��λ
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1VRHS = 0;	    		// VDD
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP1CON_b.C1REFEN = 1;         // �ڲ��ο���ѹʹ��
	SYSREG->ACCESS_EN = 0x05fa659A;
// CP10 CFG
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP10CFG_b.C10DFILT = 0;       // �˲�ʱ�����ڸ��������1023
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP10CFG_b.C10CLKD = 0;        // 2��Ƶ
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP10CFG_b.C10INTS = 3;	    	// ˫��
	SYSREG->ACCESS_EN = 0x05fa659A;
	ACMP->CP10CFG_b.C10INTM = 0;	    	// �������ж�
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
				ERUģ�������
*************************************************************************************/

void ERU_Init()
{	
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXISEL|= ((7<<24)|(7<<16)|(7<<8));	 // ѡ��ERU_1A7���룻ѡ��ERU_2A7���룻ѡ��ERU_3A7���룻

	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXICON3|=((0<<16)|(1<<2)|(1<<1));   // ETL3״̬��־���ؽ���ƽ��⣻�����ر���Ϊ�����¼���ֱ�����A
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXICON2|=((0<<16)|(1<<2)|(1<<1));	 // ETL2״̬��־���ؽ���ƽ��⣻�����ر���Ϊ�����¼���ֱ�����A
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXICON1|=((0<<16)|(1<<2)|(1<<1));   // ETL1״̬��־���ؽ���ƽ��⣻�����ر���Ϊ�����¼���ֱ�����A

	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXOCON2|=((1<<19)|(1<<2));          // ��־ ERUINCTRL3.FL����ģʽ��⣻�¼���ⱻʹ��
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXOCON1|=((1<<18)|(1<<2));					 // ��־ ERUINCTRL2.FL����ģʽ��⣻�¼���ⱻʹ��
	SYSREG->ACCESS_EN = 0x05fa659A;
	ERU->EXOCON0|=((1<<17)|(1<<2));		 			 // ��־ ERUINCTRL1.FL����ģʽ��⣻�¼���ⱻʹ��
}

/*********************************************************************************
			TIMER0�����벶������
*********************************************************************************/

void TIMER_INIT()
{
	TIMER0->TIM_PSC= 0;	              // Ԥ��Ƶ
	TIMER0->TIM_ARR = 65535;
	
	TIMER0->TIM_CCMR1|=(1<<0);  		  // CH1 ӳ����TI1��
	TIMER0->TIM_CCMR1|=(1<<8);		 		// CH2 ӳ����TI2��
	TIMER0->TIM_CCMR2|=(1<<0);		 		// CH3 ӳ����TI3��
	TIMER0->TIM_CCMR2|=(1<<8);  		  // CH4 ӳ����TI4��
	
	TIMER0->TIM_CCER_b.CC3P=1; 		 		//�������½���
	TIMER0->TIM_CCER_b.CC3NP=1;
	TIMER0->TIM_CCER_b.CC2P=1; 		 		//�������½���
	TIMER0->TIM_CCER_b.CC2NP =1;
	TIMER0->TIM_CCER_b.CC4P = 1;
	TIMER0->TIM_CCER_b.CC1NP=1;
	TIMER0->TIM_CCER_b.CC1P=1;
	
	TIMER0->TIM_CCER_b.CC2E =1;		 		//����ʹ��
  TIMER0->TIM_CCER_b.CC3E =1;		 		//����ʹ��
	TIMER0->TIM_CCER_b.CC4E =1; 		  //����ʹ��
	TIMER0->TIM_CCER_b.CC1E =1;
	
	TIMER0->TIM_DIER_b.UIE =1;   		  //�����ж�ʹ��
	TIMER0->TIM_DIER_b.CC2IE =1; 		  //��׽/�Ƚ�2�ж�ʹ��
	TIMER0->TIM_DIER_b.CC3IE =1; 		  //��׽/�Ƚ�3�ж�ʹ��
	TIMER0->TIM_DIER_b.CC4IE =1; 		  //��׽/�Ƚ�4�ж�ʹ��
	TIMER0->TIM_DIER_b.CC1IE =1;
	
	TIMER0->TIM_ISR_b.Ch3_sel = 2;  	// ͨ��3�����ź�ѡ��OGU2 PDout
	TIMER0->TIM_ISR_b.Ch2_sel = 2;  	// ͨ��2�����ź�ѡ��OGU1 PDout
	TIMER0->TIM_ISR_b.Ch1_sel = 2;  	// ͨ��1�����ź�ѡ��OGU0 PDout
	
	TIMER0->TIM_CR1_b.CEN=1; 		 			//������ʹ��
	
}
