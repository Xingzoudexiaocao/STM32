/**
* @file          : main.c
* @author        : Motor Lab 
* @date          : 17/11/2017
* @brief         : This file is the main function.
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
/* Includes ------------------------------------------------------------------*/
#include <SC32F5832.h>
#include <DevInit.h>
#include "keyboard4x4.h"
#include "delay.h"
#include "UART.h"
#include "printf.h"
#include "ds18b20.h"
#include "LCD12864.h"
/**
  * @brief      .
  * @param[in]  void : None.
  * @param[out] void : None.
  * @retval     None
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * main();
  * @endcode
  * @warning:
*/
/*#define---------------------------------------------------------------------*/
#define BUZZER_OFF 	PA -> OUTSET = (1 << 12)//PA12输出高电平
#define BUZZER_ON 	PA -> OUTCLR = (1 << 12)//PA12输出低电平

//点亮LED
#define LED1_ON PB -> OUTCLR = (1 << 0)//PB0 -D9  输出低电平 LED1点亮
#define LED2_ON PB -> OUTCLR = (1 << 1)//PB0 -D10 输出低电平 LED1点亮
#define LED3_ON PB -> OUTCLR = (1 << 2)//PB0 -D11 输出低电平 LED1点亮
#define LED4_ON PB -> OUTCLR = (1 << 3)//PB0 -D12 输出低电平 LED1点亮
#define LED5_ON PB -> OUTCLR = (1 << 4)//PB0 -D14 输出低电平 LED1点亮
#define LED6_ON PB -> OUTCLR = (1 << 5)//PB0 -D15 输出低电平 LED1点亮
#define LED7_ON PB -> OUTCLR = (1 << 6)//PB0 -D16 输出低电平 LED1点亮
#define LED8_ON PB -> OUTCLR = (1 << 7)//PB0 -D17 输出低电平 LED1点亮
//熄灭LED
#define LED1_OFF PB -> OUTSET = (1 << 0)//PB0 -D9  输出低电平 LED1点亮
#define LED2_OFF PB -> OUTSET = (1 << 1)//PB0 -D10 输出低电平 LED1点亮
#define LED3_OFF PB -> OUTSET = (1 << 2)//PB0 -D11 输出低电平 LED1点亮
#define LED4_OFF PB -> OUTSET = (1 << 3)//PB0 -D12 输出低电平 LED1点亮
#define LED5_OFF PB -> OUTSET = (1 << 4)//PB0 -D14 输出低电平 LED1点亮
#define LED6_OFF PB -> OUTSET = (1 << 5)//PB0 -D15 输出低电平 LED1点亮
#define LED7_OFF PB -> OUTSET = (1 << 6)//PB0 -D16 输出低电平 LED1点亮
#define LED8_OFF PB -> OUTSET = (1 << 7)//PB0 -D17 输出低电平 LED1点亮

unsigned char display_code[]={	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x80,0x40,0x00,
																0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef };
unsigned char display_cache[]={0,1,2,3};
/* Private variables ---------------------------------------------------------*/
extern uint8_t Key_Value; //keyboard4x4.c 中定义
float  DS18B20_Temp = 0;//DS18B20读取温度值

/* Private functions declared ------------------------------------------------*/
void delay_ms( int );
void delay_us( int );
void _cror_( void );
void _crol_( void );
void display_led(unsigned char *p);
int i = 0,j = 0,k = 0,l = 0;


void TIM6_T0_IRQHandler()
{
	TIM6 -> CTC0_b.COUNT0INT_EN = 0;
	
	PB_OUT_TOGGLE(1);
	
	Key_Value = scan_MatrixKey();
	
	TIM6 -> CTC0_b.COUNTFW = 0;
	TIM6 -> COUNT0 = 0;
	display_led(display_cache);
	NVIC_ClearPendingIRQ(TIM6_T0_IRQn);//清除中断
	TIM6 -> CTC0_b.COUNT0INT_EN = 1;
}


int main( void )
{
	
	Device_Init();
	TIM6_T0_Init();//定时器T6-T0初始化
	IRQ_Init();//中断初始化
	
	
	//外部中断配置
	PA_INT_ENABLE(10);//开启PA10中断
	PA_INT_EDGE(10);//配置为边沿中断
	PA_INT_BE_DISABLE(10);//配置为单边沿触发
	PA_INT_POL_LOW(10);//配置为下降沿触发
	PA_INT_FLAG_CLR(10);//清除中断标志
	
	
	
	PA -> OUTEN |= 0x07ff;//PA输出使能
	PB -> OUTEN |= 0xf0ff;//PB输出使能
	PB -> OUT |= 0xffff;
//	PA_OUT_ENABLE(12);//蜂鸣器端口输出使能，上电复位提示

//LCD12864============================
	delay_ms(500);	
	LCD_GPIO_Init();//LCD12864 GPIO口初始化
	PSB_0;
	CS_1;
  lcd_init();//LCD12864初始化
		
  delay_ms(100);
	lcd_clear();//清屏
	delay_ms(100);
	
  lcd_wstr(1, 1, "恒温控制系统");//字符显示
  lcd_wstr(2, 0, "当前温度");//字符显示
	lcd_wstr(3, 0, "当前状态");//字符显示
	lcd_wstr(4, 2, "@LUNTEK");//字符显示
	PA -> OUTSET = (1 << 0);
	PA -> OUTSET = (1 << 1);
	PA -> OUTSET = (1 << 2);
	PA -> OUTSET = (1 << 3);
	PA -> OUTSET = (1 << 4);
	PA -> OUTSET = (1 << 5);
	PA -> OUTSET = (1 << 6);
	PA -> OUTSET = (1 << 7);

	write_figer(2,5,0);
	lcd_wstr(2,6,"℃");
	lcd_wstr(3, 4, "NO  CMD");//字符显示
//LCD12864============================	
	
	while(1)
	{
		
		//矩阵键盘
		i = Key_Value;//读取键盘扫描函数返回值	
		if(1 == i)		//按键1触发
		{
			LED3_ON;
			lcd_wstr(3, 4, "LED3 ON");//字符显示
		}
			
		else
		{
			LED3_OFF;
		}
		
		if(5 == i)		//按键5触发
		{
			LED4_ON;
			lcd_wstr(3, 4, "LED4 ON");//字符显示
		}
		else
		{
			LED4_OFF;
		}

		if(9 == i )		//按键9触发
		{
			LED5_ON;
			lcd_wstr(3, 4, "LED5 ON");//字符显示
		}
		else
		{
			LED5_OFF;
		}
		
		if(13 == i )	//按键D触发
		{
			BUZZER_ON;
			lcd_wstr(3, 4, "BUZ ON");//字符显示
		}
		else
		{
			BUZZER_OFF;
		}
		if(20 == i)
			lcd_wstr(3, 4, "NO CMD ");//字符显示
		
		//工作状态指示		
		LED1_ON;
		ST_delay_ms(500);
		LED1_OFF;
		ST_delay_ms(500);
				
		//DS18B20 温度采集
		DS18B20_Temp = DS18B20_Get_Temp();
		write_figer(2,4,DS18B20_Temp);
		
		printf( "当前温度:%F℃\r\n", DS18B20_Temp ); 
		printf( "----------TestFinished----------\r\n" );  
//		UartSendByte(65);
//		UartSendString("hello");
//		UartSentUint32ToASCII(64);
//		ReadUartBuf();
//		SendResponse();		
//		UartSendStart();
	}
	
}
void display_led(unsigned char *p)
{
	static unsigned char disnum=0;
	
	switch (disnum)
	{
		case 3 : 	PA -> OUTCLR = (1 << 8);
							PA -> OUTCLR = (1 << 9);
							PA -> OUTCLR = (1 << 10);
			break;
		
		case 2 : 	
							PA -> OUTSET = (1 << 8);
							PA -> OUTCLR = (1 << 9);
							PA -> OUTCLR = (1 << 10);
			break;
		
		case 1 : 	PA -> OUTCLR = (1 << 8);
							PA -> OUTSET = (1 << 9);
							PA -> OUTCLR = (1 << 10);
			break;
		case 0 : 	PA -> OUTSET = (1 << 8);
							PA -> OUTSET = (1 << 9);
							PA -> OUTCLR = (1 << 10);
			break;
		
		default :
			break;
	}
	if(display_code[p[disnum]]&0x01)
		{
			PA -> OUTSET = (1 << 0);
		}
	else
		{
			PA -> OUTCLR = (1 << 0);
		}
	if((display_code[p[disnum]]&0x02)>>1)
		{
			PA -> OUTSET = (1 << 1);
		}
	else
		{
			PA -> OUTCLR = (1 << 1);
		}
	if((display_code[p[disnum]]&0x04)>>2)
		{
			PA -> OUTSET = (1 << 2);
		}
	else
		{
			PA -> OUTCLR = (1 << 2);
		}
	if((display_code[p[disnum]]&0x08)>>3)
		{
			PA -> OUTSET = (1 << 3);
		}
	else
		{
			PA -> OUTCLR = (1 << 3);
		}
	if((display_code[p[disnum]]&0x10)>>4)
		{
			PA -> OUTSET = (1 << 4);
		}
	else
		{
			PA -> OUTCLR = (1 << 4);
		}
	if((display_code[p[disnum]]&0x20)>>5)
		{
			PA -> OUTSET = (1 << 5);
		}
	else
		{
			PA -> OUTCLR = (1 << 5);
		}
	if((display_code[p[disnum]]&0x40)>>6)
		{
			PA -> OUTSET = (1 << 6);
		}
	else
		{
			PA -> OUTCLR = (1 << 6);
		}
	if((display_code[p[disnum]]&0x80)>>7)
		{
			PA -> OUTSET = (1 << 7);
		}
	else
		{
			PA -> OUTCLR = (1 << 7);
		}
		disnum++;
		if(disnum==4)
			disnum=0;
}

void delay_us(int set_us_Times)
{
	int i,j;
	for(i = 0; i < set_us_Times; i++)
	{
		for(j = 0; j < 5; j++);
	}
}

void delay_ms(int set_ms_Times)
{
	int i = 1000;
	while( set_ms_Times-- )
	{
		while( i-- );
		i = 5000;
	}
}

/*
 *循环右移
 */
void _cror_( void )
{
	//u8 PB_Value = 1;
	u8 i;
	
	for(i = 0; i <= 8; i++)
	{
		delay_ms(200);
		PB_OUT_ENABLE(i);	
		PB_OUT_LOW((i));
		
		delay_ms(200);
		PB_OUT_DISABLE(i);	
	}
}
/*
 *循环左移
 */
void _crol_( void )
{
	//u8 PB_Value = 1;
	u8 i;
	
	for(i = 8; i >= 1; i--)
	{
		delay_ms(200);
		PB_OUT_ENABLE((i - 1));	
		PB_OUT_LOW((i - 1));	
		
		delay_ms(200);
		PB_OUT_DISABLE((i - 1));	
	}
}
