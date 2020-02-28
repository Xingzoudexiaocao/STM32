/**
	******************************************************************************
	* @file    DS18B20.c 单总线温度传感器
	* @author  dotod
	* @version V1.0
	* @date    10-DEC-2017
	* @brief   Main program body.
	******************************************************************************
	* @attention	
	*
	******************************************************************************
	*/ 
/* Includes ------------------------------------------------------------------*/	
	#include <SC32F5832.h>
	#include <DevInit.h>
	#include "ds18b20.h"
	#include "delay.h"  
/* 宏定义 -------------------------------------------------------------------*/	
#define DQ_Out_H 	PA_OUT_HIGH(15)
#define DQ_Out_L 	PA_OUT_LOW(15)
#define DQ_In			(PA -> PIN & (1 << 15))
/**
  * @brief  DS18B20 初始化
  * @param  None
  * @retval None
  */  
void  init_ds18b20( void )  
{  
	init_onewire_out(); 
	PA_OUT_LOW(15);	
	//GPIO_ResetBits( GPIOE, GPIO_Pin_9 );  
	ST_delay_us( 480 ); 
	PA_OUT_HIGH(15);		
	init_onewire_in();  
	ST_delay_us( 60 );  
	if( !DQ_In )  
	{  
		ST_delay_us( 120 );  								
	}  
} 
/**
  * @brief  DS18B20 检测
  * @param  None
  * @retval None
  */ 
void  check_ds18b20( void )  
{  
	init_onewire_out(); 
	PA_OUT_LOW(15);		
	//GPIO_ResetBits( GPIOE, GPIO_Pin_9 );  
	ST_delay_us( 240 );  
	init_onewire_in();  
	ST_delay_us( 60 );  
	if( !DQ_In )  
	{  
		ST_delay_us( 80 );  
		if( !DQ_In )  
			printf( "检测到DS18B20!\r\n" );  								
	}  
}  
/**
  * @brief  设置为主设备写总线 从设备读总线
  * @param  None
  * @retval None
  */ 
void init_onewire_out( void )  
{  
	PA_OUT_ENABLE(15);
}  
/**
  * @brief  设置为主设备读总线 从设备写总线
  * @param  None
  * @retval None
  */ 
void init_onewire_in( void )  
{  
	PA_OUT_DISABLE(15);
	GPIO_AF_SEL(DIGITAL, PA, 15, 0); 
	GPIO_PUPD_SEL(PUPD_PU, PA, 15 );//输入浮空
}  
/**
  * @brief  DS18B20 写入数据
  * @param  None
  * @retval None
  */ 	
void ds18b20_write_byte( uint8_t data )  
{  
	uint8_t i;  
	uint8_t j = 0;  
	init_onewire_out();  
	for( i = 0; i < 8; i++ )  
	{  
		j = data & 0x01;  
		if( j )  
		{  
			DQ_Out_L; //置 1
			ST_delay_us( 2 );  
			DQ_Out_H;  
			ST_delay_us( 60 );  
		}  
		else  
		{  
			DQ_Out_L; //置 0 
			ST_delay_us( 60 );  
			DQ_Out_H;  
			ST_delay_us( 2 );  
		}  
		data = data >> 1;  
	}     
}  
/**
  * @brief  DS18B20 读取1位
  * @param  None
  * @retval None
  */ 
uint8_t ds18b20_read_bit( void )  
{     
		uint8_t bit; 
	
		init_onewire_out(); 
		DQ_Out_L;  
		ST_delay_us( 2 );  
		DQ_Out_H; 
	
		init_onewire_in();  
		ST_delay_us( 12 );  
		if( DQ_In )  
				bit = 1;  
		else  
				bit = 0;  
		ST_delay_us( 50 );  
		return bit;  
}  
/**
  * @brief  DS18B20 读取字节 先发送字节到总线
  * @param  data 返回读取数据
  * @retval None
  */ 
uint8_t ds18b20_read_byte( void )  
{  
	uint8_t data = 0;  
	uint8_t i = 0;  
	uint8_t j = 0;  
	for( i = 0; i < 8; i++ )  
	{  
		j = ds18b20_read_bit();  
		if( j )       
			j = j << i;  
		data |= j;  

	}  
	return data;  
}  
/**
  * @brief  DS18B20 读取系列码和48位序列号
  * @param  None
  * @retval None
  */ 
void ds18b20_read_rom_number( void )  
{  
	uint32_t number = 0;  
	int8_t data, i, serial_num, ds18b20_crc; 

	init_ds18b20();  
	ds18b20_write_byte( 0x33 );
	serial_num = ds18b20_read_byte();  
	
	for( i = 0; i < 6; i++ )  
	{  
		data = ds18b20_read_byte();  
		number |= data;  
		number = number << 8;  
	} 
	
	ds18b20_crc = ds18b20_read_byte();  
	printf( "系列号:%d\r\n", serial_num );  
	printf( "序列号:%d\r\n", number );  
	printf( "CRC校验码:%d\r\n", ds18b20_crc );  

}  
/**
  * @brief  DS18B20 温度转换开始
  * @param  None
  * @retval None
  */ 
void tem_chage( void )  
{  
	init_ds18b20();  
	ds18b20_write_byte( 0xcc );   //忽略rom指令 
	ds18b20_write_byte( 0x44 );   //开启转换
}  
/**
  * @brief  DS18B20 获取温度值
  * @param  None
  * @retval None
  */ 	
double get_temp( void )  
{  
	uint16_t temp = 0;  
	int8_t TH, TL;  
	int8_t tem;  

	tem_chage();  
	ST_delay_us( 10 );  
	init_ds18b20();  
	ds18b20_write_byte( 0xcc );   //忽略rom指令 
	ds18b20_write_byte( 0xbe );   //读取温度转换值
	TL = ds18b20_read_byte();  
	TH = ds18b20_read_byte();  

	if( TH > 7 )     //通过判断存储器的高五位的0,1来判断温度正负
	{  
		temp = 0;   	 //负值
		TH = ~TH;  
		TL = ~TL;   
	}  
	else   
		temp = 1;   	//正值 
	
	tem = TH;  
	tem = tem << 8;  
	tem = tem + TL;  
	tem = ( double )tem * 0.625;  
	if ( temp )  
		return tem;  
	else  
		return -tem;  

}  
/**
  * @brief  DS18B20 
  * @param  None
  * @retval None
  */ 
void ds18b20_return_TH_TL_CONF( void )  
{  
	uint8_t data, data_TH, data_TL, CONF;  
	
	init_ds18b20();  
	ds18b20_write_byte( 0xcc );   //忽略rom指令 
	ds18b20_write_byte( 0xbe ); 	//读取温度转换值
	data = ds18b20_read_byte();  
	data = ds18b20_read_byte();  
	data_TH = ds18b20_read_byte();  
	data_TL = ds18b20_read_byte();  
	CONF =ds18b20_read_byte();  
	
	printf( "过温报警的温度:%d℃\r\n", data_TH );  
	printf( "低温报警的温度:%d℃\r\n", -( data_TL - 128 )); 
	
	CONF &= 0x60 ;  
	CONF = CONF >> 5;
  
	switch ( CONF ) 
	{  
		case 0:  
			printf( "ds18b20的测量精度为9位，精度为0.5℃\r\n" );  
			break;  
		case 1:  
			printf( "ds18b20的测量精度为10位，精度为0.25℃\r\n" );  
			break;  
		case 2:  
			printf( "ds18b20的测量精度为11位，精度为0.125℃\r\n" );  
			break;  
		case 3:  
			printf( "ds18b20的测量精度为12位，精度为0.0625℃\r\n" );  
			break;  
		default:  
			printf( "error!!\r\n" );  
			break;  
	}  
} 
/**
  * @brief  DS18B20 设置温度报警值和配置精度 TH过温报警只( TH > 0 ) TL低温报警值( TL < 0 ) mode配置模式如下
  * @param  None
  * @retval None
  */ 
//mode = 0 精度为9位  	00011111 		dat = 31  
//mode = 1 精度为10位 	00111111   	dat = 63  
//mode = 2 精度为11位 	01011111    dat = 95  
//mode = 3 精度为12位  	01111111   	dat = 127  
void ds18b20_write_TH_TL_CONF( int8_t TH, int8_t TL, int8_t mode )  
{  
	int8_t dat;  
	switch ( mode )
	{  
		case 0:  
			dat=31;  
			break;  
		case 1:  
			dat=63;  
			break;  
		case 2:  
			dat=95;  
			break;  
		case 3:  
			dat=127;  
			break;  
		default:  
			printf( "mode error!!\r\n" );  
			dat=127;  
			break;  
	}  
	TL = TL + 128;  
	init_ds18b20();  
	ds18b20_write_byte( 0xcc );   //忽略rom指令
	ds18b20_write_byte( 0x4e );   //写入暂存寄存器，过温和低温报警值
	ds18b20_write_byte( TH ); 		//写入20°为过温报警值
	ds18b20_write_byte( TL ); 		//写入-20°为低温报警值
	ds18b20_write_byte( dat );    //写入精度 
	init_ds18b20();  
	ds18b20_write_byte( 0xcc );   //忽略rom指令
	ds18b20_write_byte( 0x48 );   //将写入的暂存寄存器拷贝到EEPROM  
} 
/**
  * @brief  DS18B20 自检
  * @param  None
  * @retval None
  */ 
void ds18b20_chack_self( void )  
{  
	check_ds18b20();  
	ds18b20_read_rom_number();  
	ds18b20_return_TH_TL_CONF();  
}  
