/**
	******************************************************************************
	* @file    DS18B20.c �������¶ȴ�����
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
/* �궨�� -------------------------------------------------------------------*/	
#define DQ_Out_H 	PA_OUT_HIGH(15)
#define DQ_Out_L 	PA_OUT_LOW(15)
#define DQ_In			(PA -> PIN & (1 << 15))
/**
  * @brief  DS18B20 ��ʼ��
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
  * @brief  DS18B20 ���
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
			printf( "��⵽DS18B20!\r\n" );  								
	}  
}  
/**
  * @brief  ����Ϊ���豸д���� ���豸������
  * @param  None
  * @retval None
  */ 
void init_onewire_out( void )  
{  
	PA_OUT_ENABLE(15);
}  
/**
  * @brief  ����Ϊ���豸������ ���豸д����
  * @param  None
  * @retval None
  */ 
void init_onewire_in( void )  
{  
	PA_OUT_DISABLE(15);
	GPIO_AF_SEL(DIGITAL, PA, 15, 0); 
	GPIO_PUPD_SEL(PUPD_PU, PA, 15 );//���븡��
}  
/**
  * @brief  DS18B20 д������
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
			DQ_Out_L; //�� 1
			ST_delay_us( 2 );  
			DQ_Out_H;  
			ST_delay_us( 60 );  
		}  
		else  
		{  
			DQ_Out_L; //�� 0 
			ST_delay_us( 60 );  
			DQ_Out_H;  
			ST_delay_us( 2 );  
		}  
		data = data >> 1;  
	}     
}  
/**
  * @brief  DS18B20 ��ȡ1λ
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
  * @brief  DS18B20 ��ȡ�ֽ� �ȷ����ֽڵ�����
  * @param  data ���ض�ȡ����
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
  * @brief  DS18B20 ��ȡϵ�����48λ���к�
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
	printf( "ϵ�к�:%d\r\n", serial_num );  
	printf( "���к�:%d\r\n", number );  
	printf( "CRCУ����:%d\r\n", ds18b20_crc );  

}  
/**
  * @brief  DS18B20 �¶�ת����ʼ
  * @param  None
  * @retval None
  */ 
void tem_chage( void )  
{  
	init_ds18b20();  
	ds18b20_write_byte( 0xcc );   //����romָ�� 
	ds18b20_write_byte( 0x44 );   //����ת��
}  
/**
  * @brief  DS18B20 ��ȡ�¶�ֵ
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
	ds18b20_write_byte( 0xcc );   //����romָ�� 
	ds18b20_write_byte( 0xbe );   //��ȡ�¶�ת��ֵ
	TL = ds18b20_read_byte();  
	TH = ds18b20_read_byte();  

	if( TH > 7 )     //ͨ���жϴ洢���ĸ���λ��0,1���ж��¶�����
	{  
		temp = 0;   	 //��ֵ
		TH = ~TH;  
		TL = ~TL;   
	}  
	else   
		temp = 1;   	//��ֵ 
	
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
	ds18b20_write_byte( 0xcc );   //����romָ�� 
	ds18b20_write_byte( 0xbe ); 	//��ȡ�¶�ת��ֵ
	data = ds18b20_read_byte();  
	data = ds18b20_read_byte();  
	data_TH = ds18b20_read_byte();  
	data_TL = ds18b20_read_byte();  
	CONF =ds18b20_read_byte();  
	
	printf( "���±������¶�:%d��\r\n", data_TH );  
	printf( "���±������¶�:%d��\r\n", -( data_TL - 128 )); 
	
	CONF &= 0x60 ;  
	CONF = CONF >> 5;
  
	switch ( CONF ) 
	{  
		case 0:  
			printf( "ds18b20�Ĳ�������Ϊ9λ������Ϊ0.5��\r\n" );  
			break;  
		case 1:  
			printf( "ds18b20�Ĳ�������Ϊ10λ������Ϊ0.25��\r\n" );  
			break;  
		case 2:  
			printf( "ds18b20�Ĳ�������Ϊ11λ������Ϊ0.125��\r\n" );  
			break;  
		case 3:  
			printf( "ds18b20�Ĳ�������Ϊ12λ������Ϊ0.0625��\r\n" );  
			break;  
		default:  
			printf( "error!!\r\n" );  
			break;  
	}  
} 
/**
  * @brief  DS18B20 �����¶ȱ���ֵ�����þ��� TH���±���ֻ( TH > 0 ) TL���±���ֵ( TL < 0 ) mode����ģʽ����
  * @param  None
  * @retval None
  */ 
//mode = 0 ����Ϊ9λ  	00011111 		dat = 31  
//mode = 1 ����Ϊ10λ 	00111111   	dat = 63  
//mode = 2 ����Ϊ11λ 	01011111    dat = 95  
//mode = 3 ����Ϊ12λ  	01111111   	dat = 127  
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
	ds18b20_write_byte( 0xcc );   //����romָ��
	ds18b20_write_byte( 0x4e );   //д���ݴ�Ĵ��������º͵��±���ֵ
	ds18b20_write_byte( TH ); 		//д��20��Ϊ���±���ֵ
	ds18b20_write_byte( TL ); 		//д��-20��Ϊ���±���ֵ
	ds18b20_write_byte( dat );    //д�뾫�� 
	init_ds18b20();  
	ds18b20_write_byte( 0xcc );   //����romָ��
	ds18b20_write_byte( 0x48 );   //��д����ݴ�Ĵ���������EEPROM  
} 
/**
  * @brief  DS18B20 �Լ�
  * @param  None
  * @retval None
  */ 
void ds18b20_chack_self( void )  
{  
	check_ds18b20();  
	ds18b20_read_rom_number();  
	ds18b20_return_TH_TL_CONF();  
}  
