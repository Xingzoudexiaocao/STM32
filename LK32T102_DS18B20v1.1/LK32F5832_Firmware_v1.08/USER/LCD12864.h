#ifndef __LCD12864_H
#define	__LCD12864_H

	/**
	* @brief  LCD12864接线说明
	* @param  SC32F5832 -> LCD12864
	*							PC6 	-> 	RS
	*							PC4 	-> 	RW
	*							PC3 	-> 	E
	*							PC7 	-> 	PSB
	*							PC15 	-> 	RST
	*/
/*#define---------------------------------------------------------------------*/
#define CLK_1 	PC_OUT_HIGH(3)	//PC3输出高电平
#define CLK_0 	PC_OUT_LOW(3)		//PC3输出低电平

#define SID_1 	PC_OUT_HIGH(4)	//PC4输出高电平
#define SID_0 	PC_OUT_LOW(4)		//PC4输出低电平

#define CS_1 		PC_OUT_HIGH(6)	//PC6输出高电平
#define CS_0 		PC_OUT_LOW(6)		//PC6输出低电平

#define PSB_1 	PC_OUT_HIGH(7)	//PC7输出高电平
#define PSB_0 	PC_OUT_LOW(7)		//PC7输出低电平

#define RST_1 	PC_OUT_HIGH(15)	//PC15输出高电平
#define RST_0 	PC_OUT_LOW(15)	//PC15输出低电平
/* Definitions ---------------------------------------------------------------*/

	/* Write command or dat select */

/* Exported functions declared ---------------------------------------------- */
void Delay(__IO uint32_t nCount);
void send_dat(uint8_t dat);
void send_cmd(uint8_t cmd);
void write_char(uint8_t dat);
void lcd_clear(void);
void lcd_pos(uint8_t y_add, uint8_t x_add);
void lcd_wstr(uint8_t y_add, uint8_t x_add, char *str);
void write_figer(uint8_t y_add, uint8_t x_add, uint32_t figer);
void lcd_init(void); 
void LCD_GPIO_Init(void);

#endif


