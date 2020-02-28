#ifndef	__DevInit_h
#define __DevInit_h

#include <SC32F5832.h>
#include <UART.h>
#include <ADC.h>
#include <CLK.h>
#include <GPIO.h>
#include <PWM.h>
#include <ETIMER.h>
#include <CMP.h>
#include <OPA.h>
#include <DMA.h>
#include <Coproc.h>
#include <IAP.h>
#include <Datatype.h>

extern void IRQ_Init(void);
extern void IRQ_Disable(void);
extern void IRQ_Enable(void);
extern void SetPll(void);
extern void	SetSysTick(void);
extern void	GPIO_Init(void);
extern void	PWM_Init(void);
extern void	ADC_Init(void);
extern void	T0_Init_PWM(uint32_t DB_CFG,uint32_t PRD);
extern void T0_Init_CAP(void);
extern void T0_PWM_MEASURE(void);
extern void T0_ENCODER_MODE(void);
extern void TIM6_T0_Init(void);
extern void TIM6_T1_Init(void);
extern void	OPA0_Init(void);
extern void OPA1_Init(void);
extern void	OPA2_Init(void);
extern void	CMP0_Init(void);
extern void CP10_Init(void);
extern void CP11_Init(void);
extern void CP12_Init(void);
extern void Uart0_Init(void);
extern void	Uart1_Init(void);
extern void Device_Init(void);
extern void Flash_nvr_protect(uint8_t sector,uint32_t startaddr,uint32_t endaddr);

#endif
