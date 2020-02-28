#include "SC32F5832.h"
#include "stdio.h"
#include "IAP.h"

/**
  * @brief      .
  * @param[in]  void : addr,data.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * WriteFlashWord(uint32_t addr,uint32_t data);
  * @endcode
  * @warning:
*/

void WriteFlashWord(uint32_t addr,uint32_t data)
{
	IAP->IEN = 0x07;
	IAP->ADDR = addr;
	IAP->DATA = data;
	IAP->CSET_b.PROGEN = 1;
	IAP->FEED = 0x12345678;
	IAP->FEED = 0x87654321;
	IAP->CSET_b.OPSTART = 1;
	while(IAP->ISR_b.COMPLETE == 0);	
	IAP->ICR_b.COMPCLR = 1;
	IAP->CCLR_b.PROGEN = 1;
}
/**
  * @brief      .
  * @param[in]  void : addr.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * EraseFlashSector(uint32_t addr);
  * @endcode
  * @warning:
*/

void EraseFlashSector(uint32_t addr)
{

	IAP->IEN = 0x07;
	IAP->ADDR = addr;
	IAP->CSET_b.PAGEEN = 1;
	IAP->FEED = 0x12345678;
	IAP->FEED = 0x87654321;	
	IAP->CSET_b.OPSTART = 1;
	while(IAP->ISR_b.COMPLETE == 0);
	IAP->ICR_b.COMPCLR = 1;
	IAP->CCLR_b.PAGEEN = 1;				
	
}

/**
  * @brief      .
  * @param[in]  void : adr,size,buff.
  * @param[out] void : 
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * FlashRead(unsigned long adr, unsigned long size, unsigned char *buff);
  * @endcode
  * @warning:
*/
int	FlashRead(unsigned long adr, unsigned long size, unsigned char *buff)
	{
		
		IAP->CCLR = 0xFF;
		IAP->IEN  = 0xFF;
		IAP->ICR  = 0xFF;
		
		while(size)
		{
			IAP->CSET = (1<<4);   //读取使能
			IAP->ADDR = adr;
			IAP->FEED = 0x12345678ul;
		  IAP->FEED = 0x87654321ul;
		  IAP->CSET = 0x01ul;			// 操作开始
					while ((IAP->ISR & 0x01) == 0x00)
		{
			if((IAP->ISR & 0x02) == 0x02)
			{
				return(1);
			}
			if((IAP->ISR & 0x04) == 0x04)
			{
				return(1);
			}				
			if((IAP->ISR & 0x08) == 0x08)
			{
				return(1);
			}
			if((IAP->ISR & 0x10) == 0x10)
			{
				return(1);
			}
		}
				IAP->ICR = 0x01;
				IAP->CCLR = 0x10;
		*buff = IAP->DATA;
		*(buff + 1) = (IAP->DATA >> 8);
		*(buff + 2) = (IAP->DATA >> 16);
		*(buff + 3) = (IAP->DATA >> 24);
		buff += 0x04;
		adr += 0x04;
		size -= 0x04;
		}
			IAP->IEN = 0x00; 
	return (0); 	
}
