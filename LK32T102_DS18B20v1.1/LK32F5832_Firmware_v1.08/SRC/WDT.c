#include "stdint.h"
#include "SC32F5832.h"

 void WDT_Init()
 {
	 WDT->WDOGLOCK = 0x1ACCE551;         // write enable
	 WDT->WDOGLOAD = 0x0fffffff;         // load value
	 WDT->WDOGCONTROL_b.RSTEN = 1;	     // reset enable
	 WDT->WDOGCONTROL_b.INTEN = 1;       // interrupt enable
	 
	 NVIC_ClearPendingIRQ(WWDT_IRQn);    
	 NVIC_SetPriority(WWDT_IRQn,0);
	 NVIC_EnableIRQ(WWDT_IRQn);	
	 
 }
