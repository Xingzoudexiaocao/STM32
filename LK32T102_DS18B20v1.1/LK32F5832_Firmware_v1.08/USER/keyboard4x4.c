/**
  ******************************************************************************
  * @file    矩阵键盘测试程序 
  * @author  Jerry01
  * @version V1.1
  * @date    03-FEB-2019
  * @brief   Main program body.
  ******************************************************************************
  * @attention	
  *
  ******************************************************************************
  */ 
	/**
	* @brief  4*4矩阵键盘接线说明
	* @param  SC32F5832 -> KeyBoard 矩阵键盘
	*							PB8 	-> 	CN3-R1
	*							PB9 	-> 	CN3-R2
	*							PB10 	-> 	CN3-R3
	*							PB11 	-> 	CN3-R4
	*							PB12 	-> 	CN3-C1
	*							PB13 	-> 	CN3-C2
	*							PB14 	-> 	CN3-C3
	*							PB15 	-> 	CN3-C4
	*/
/* Includes -----------------------------------------------------------------*/
#include <SC32F5832.h>
#include <DevInit.h>
#include "keyboard4x4.h"

/* 宏定义 -------------------------------------------------------------------*/
#define PORTE PB -> PIN	//读PB口引脚电压

/* 变量定义 ------------------------------------------------------------------*/
//extern uint8_t KeyTrg;
//extern uint8_t KeyCont;

/**
  * @brief  4x4 矩阵键盘扫描函数
  * @param  None
  * @retval None
  */
	
//采用翻转扫描的方法( PE口的高8位 )
//程序放在定时器中断函数中 10ms扫描一次
uint8_t scan_MatrixKey( void )
{

	uint8_t column;	//列
	uint8_t row;			//行
	uint8_t tmp;			//临时变量
	uint8_t MatrixKey_value = 20;	//初始按键值 不能是0 ~ 15 
	static uint8_t key_count = 0;	//按键被中断函数扫描的次数

	/*------------- PB 高8位端口配置 -------------*/
	PB -> OUTEN |= 0XFF00;//PB输出使能
	
	//初始值: GPIOE 高8位端口 低4位为低, 高4位为高
	PB -> OUT &= 0X00FF;
	PB -> OUT |= 0XF000;
	
	//GPIOE 高8位端口 高4位为 上拉输入
	PB -> OUTEN &= 0X0FFF;//PB输入使能
	GPIO_PUPD_SEL(PUPD_PU, PB, 12 );
	GPIO_PUPD_SEL(PUPD_PU, PB, 13 );
	GPIO_PUPD_SEL(PUPD_PU, PB, 14 );
	GPIO_PUPD_SEL(PUPD_PU, PB, 15 );

	tmp = PORTE >> 8;//读取按键值
	
	if( tmp != 0XF0 )//如果有按键按下
	{   
		//防止长按时,持续自增导致变量溢出
		if( key_count < 2 )
		{
			key_count++;
		}
	}
	//若产生按键抖动被抬起则计数清0 
	else
	{
		key_count = 0;
	}
	
	//若连续2次扫描均处于按下状态 则认定按键确实被按下
	if( key_count == 2 )
	{          
		column = tmp & 0XF0;//获取列号

		/*------------- GPIOE 高8位端口配置 -------------*/
		PB -> OUTEN |= 0XFF00;//PB输出使能
		
		//翻转: GPIOE 高8位端口 低4位为高, 高4位为低
		PB -> OUT &= 0X00FF;
		PB -> OUT |= 0X0F00;
		
		//GPIOE 高8位端口 低4位为 上拉输入
		PB -> OUTEN &= 0XF0FF;//PB输入使能
		GPIO_PUPD_SEL(PUPD_PU, PB, 8 );
		GPIO_PUPD_SEL(PUPD_PU, PB, 9 );
		GPIO_PUPD_SEL(PUPD_PU, PB, 10 );
		GPIO_PUPD_SEL(PUPD_PU, PB, 11 );
										
		row = ( PORTE >> 8 ) & 0X0F;//获取行号 
		
		switch ( column | row )//column|row为按键按下后对应端口的编码
		{   
			//按键对应的码表 可根据需求调整返回值 
			case 0XEE:
				MatrixKey_value = 1; 	//keyboard 1
				break;
			case 0XDE: 
				MatrixKey_value = 2; 	//keyboard 2
				break;	
			case 0XBE:
				MatrixKey_value = 3;	//keyboard 3
				break;                
			case 0X7E:
				MatrixKey_value = 10; //keyboard A
				break;                                              
			case 0XED:
				MatrixKey_value = 4;	//keyboard 4
				break;
			case 0XDD: 
				MatrixKey_value = 5; 	//keyboard 5 
				break;
			case 0XBD:
				MatrixKey_value = 6; 	//keyboard 6
				break;
			case 0X7D:
				MatrixKey_value = 11; //keyboard B
				break;                                  
			case 0XEB: 
				MatrixKey_value = 7; 	//keyboard 7
				break;
			case 0XDB:
				MatrixKey_value = 8;	//keyboard 8
				break;
			case 0XBB:
				MatrixKey_value = 9;	//keyboard 9
				break;
			case 0X7B:
				MatrixKey_value = 12;	//keyboard C
				break;                                    
			case 0XE7:
				MatrixKey_value = 14;	//keyboard *
			break;
			case 0XD7:
				MatrixKey_value = 0; 	//keyboard 0
				break;
			case 0XB7:
				MatrixKey_value = 15;	//keyboard #
			break;
			case 0X77:
				MatrixKey_value = 13; //keyboard D
				break;
			
			default:  
				break;     
		}                    
	}

	//若没有按键按下或中途松手则扫描次数清零	
	if( ( PORTE & 0XFF00 ) == 0xF000 )
	{
		key_count = 0;  
	}
	
	return MatrixKey_value;
}

/**
  * @brief  stm32主板按键 S1 S2 S3 S4 
  * @param  None
  * @retval None
  */
//void KeyRead( void )
//{
//	uint8_t ReadKey_Data; //读取按键输入数据
//	ReadKey_Data = GPIOC -> IDR ^ 0x0f;
//	
//	KeyTrg = ReadKey_Data & ( ReadKey_Data ^ KeyCont );
//	KeyCont = ReadKey_Data;
//}			
