#include "GPIOx.h"
	/**
	* @brief  LCD12864����˵��
	* @param  SC32F5832 -> LCD12864
	*							PC3 	-> 	E		PA2
	*							PC4 	-> 	RW	PA1
	*							PC6 	-> 	RS  PA0
	*							PC7 	-> 	PSB	PA3
	*/
/*#define---------------------------------------------------------------------*/
#define CLK_1 	PAout(0)=1	//PC3����ߵ�ƽ	E
#define CLK_0 	PAout(0)=0	//PC3����͵�ƽ

#define SID_1 	PAout(1)=1	//PC4����ߵ�ƽ	RW
#define SID_0 	PAout(1)=0	//PC4����͵�ƽ

#define CS_1 		PAout(2)=1	//PC6����ߵ�ƽ	RS
#define CS_0 		PAout(2)=0	//PC6����͵�ƽ

#define PSB_1 	PAout(3)=1	//PC7����ߵ�ƽ	PSB
#define PSB_0 	PAout(3)=0	//PC7����͵�ƽ
/* Definitions ---------------------------------------------------------------*/

	/* Write command or dat select */

/* Exported functions declared ---------------------------------------------- */
void Delay(__IO uint32_t nCount);
void send_dat(uint8_t dat);
void send_cmd(uint8_t cmd);
void write_char(uint8_t dat);
void lcd_clear(void);
void lcd_pos(uint8_t y_add, uint8_t x_add);
void lcd_wstr(uint8_t y_add, uint8_t x_add, unsigned char *str);
void write_figer(uint8_t y_add, uint8_t x_add, uint32_t figer);
void lcd_init(void);  