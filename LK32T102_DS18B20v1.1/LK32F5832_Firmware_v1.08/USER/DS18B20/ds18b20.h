/**
  ******************************************************************************
  * @file    传感器模块测试程序
  * @author  dotod
  * @version V1.0
  * @date    10-DEC-2017
  * @brief   Main program body.
  ******************************************************************************
  * @attention	
  *
  ******************************************************************************
  */ 
	
#ifndef __DS18B20_H
#define __DS18B20_H

/* Includes -----------------------------------------------------------------*/
#include <stdio.h>
/* 宏定义 -------------------------------------------------------------------*/
		
/* 变量声明------------------------------------------------------------------*/

/* 函数声明 ------------------------------------------------------------------*/
void init_ds18b20( void );
void check_ds18b20( void );
void init_onewire_out( void );
void init_onewire_in( void );
void ds18b20_write_byte( uint8_t data ) ;
uint8_t ds18b20_read_bit( void );
uint8_t ds18b20_read_byte( void );
void ds18b20_read_rom_number( void );
void tem_chage( void );
double get_temp( void );  
void ds18b20_return_TH_TL_CONF( void );
void ds18b20_write_TH_TL_CONF( int8_t TH, int8_t TL, int8_t mode );
void ds18b20_chack_self( void );
#endif

