#ifndef __GPIO_H
#define __GPIO_H

#define DIGITAL		(0<<4)
#define ANALOGY		(1<<4)

#define ODEN			(1<<13)
#define ODDIS			(0<<13)

#define DRV_HIGH	(1<<10)
#define DRV_LOW		(0<<10)

#define PUPD_NULL  (0<<6)
#define PUPD_PU    (2<<6)
#define PUPD_PD    (1<<6)
#define PUPD_REPEATER  (3<<6)


/******************************************************
		GPIO���ʹ����ȥʹ��
*******************************************************/
#define PA_OUT_ENABLE(x) PA->OUTEN|=(1<<x);					// ���ʹ��
#define PB_OUT_ENABLE(x) PB->OUTEN|=(1<<x);
#define PC_OUT_ENABLE(x) PC->OUTEN|=(1<<x);

#define PA_OUT_DISABLE(x) PA->OUTEN&=~(1<<x);				// ����ʹ��
#define PB_OUT_DISABLE(x) PB->OUTEN&=~(1<<x);		
#define PC_OUT_DISABLE(x) PC->OUTEN&=~(1<<x);		
/******************************************************
		GPIO����ø�
****************************************************/
#define PA_OUT_HIGH(x) PA -> OUTSET = (1<<x);
#define PB_OUT_HIGH(x) PB -> OUTSET = (1<<x);
#define PC_OUT_HIGH(x) PC -> OUTSET = (1<<x);
/******************************************************
		GPIO����õ�
*******************************************************/
#define PA_OUT_LOW(x) PA -> OUTCLR = (1<<x);
#define PB_OUT_LOW(x) PB -> OUTCLR = (1<<x);
#define PC_OUT_LOW(x) PC -> OUTCLR = (1<<x);
/*****************************************************
		GPIO�����ת
******************************************************/
#define PA_OUT_TOGGLE(x) PA->OUTTGL = (1<<x);
#define PB_OUT_TOGGLE(x) PB->OUTTGL = (1<<x);
#define PC_OUT_TOGGLE(x) PC->OUTTGL = (1<<x);
/*****************************************************
		GPIO�ж�ʹ����ȥʹ��
******************************************************/
#define PA_INT_ENABLE(x) PA->INTMASK&=~(1<<x);					//�ж�ʹ��
#define PB_INT_ENABLE(x) PB->INTMASK&=~(1<<x);	
#define PC_INT_ENBALE(x) PC->INTMASK&=~(1<<x);	

#define PA_INT_DISABLE(x) PA->INTMASK|=(1<<x);			//�ж�����
#define PB_INT_DISABLE(x) PB->INTMASK|=(1<<x);
#define PC_INT_DISBALE(x) PC->INTMASK|=(1<<x);

/****************************************************
		GPIO�����ж�����ѡ��
*****************************************************/
#define PA_INT_LEVEL(x) PA->INTTYPE&=~(1<<x);					//����Ϊ��ƽ�����ж�
#define PB_INT_LEVEL(x) PB->INTTYPE&=~(1<<x);	
#define PC_INT_LEVEL(x) PC->INTTYPE&=~(1<<x);	

#define PA_INT_EDGE(x) PA->INTTYPE|=(1<<x);				//����Ϊ���ش����ж�
#define PB_INT_EGDE(x) PB->INTTYPE|=(1<<x);			
#define PC_INT_EGDE(x) PC->INTTYPE|=(1<<x);			
/****************************************************
		GPIOѡ��/˫���ش����ж�
*****************************************************/
#define PA_INT_BE_ENABLE(x) PA->INTBV|=(1<<x);					//˫���ش���
#define PB_INT_BE_ENABLE(x) PB->INTBV|=(1<<x);			
#define PC_INT_BE_ENABLE(x) PC->INTBV|=(1<<x);			

#define PA_INT_BE_DISABLE(x) PA->INTBV&=~(1<<x);				//�����ش���
#define PB_INT_BE_DISABLE(x) PB->INTBV&=~(1<<x);	
#define PC_INT_BE_DISABLE(x) PC->INTBV&=~(1<<x);	
/*****************************************************
		GPIO�жϴ�������ѡ��
******************************************************/
#define PA_INT_POL_HIGH(x) PA->INTPOL|=(1<<x);			// �����ػ�ߵ�ƽ����
#define PB_INT_POL_HIGH(x) PB->INTPOL|=(1<<x);	
#define PC_INT_POL_HIGH(x) PC->INTPOL|=(1<<x);	

#define PA_INT_POL_LOW(x) PA->INTPOL&=~(1<<x);				// �½��ػ�͵�ƽ����
#define PB_INT_POL_LOW(x) PA->INTPOL&=~(1<<x);
#define PC_INT_POL_LOW(x) PA->INTPOL&=~(1<<x);
/****************************************************
		GPIO�жϱ�־λ���
*****************************************************/
#define PA_INT_FLAG_CLR(x)	PA->RIS=(1<<x);
#define PB_INT_FLAG_CLR(x)	PB->RIS=(1<<x);
#define PC_INT_FLAG_CLR(x)	PC->RIS=(1<<x);

extern void GPIO_AF_SEL(uint8_t AD,PA_Type* GPIOx,uint8_t gpiopin,uint8_t fun_num);
extern void GPIO_OD_SEL(uint8_t OD,PA_Type* GPIOx,uint8_t gpiopin);
extern void GPIO_DRV_SEL(uint8_t DRV,PA_Type* GPIOx,uint8_t gpiopin);
extern void GPIO_PUPD_SEL(uint8_t PUPD,PA_Type* GPIOx,uint8_t gpiopin);

#endif
