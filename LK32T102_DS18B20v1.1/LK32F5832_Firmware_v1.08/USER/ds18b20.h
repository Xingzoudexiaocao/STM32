#ifndef __DS18B20_H
#define __DS18B20_H 


////IO操作函数											   
#define DQ_Out_H 	PA_OUT_HIGH(15)
#define DQ_Out_L 	PA_OUT_LOW(15)
#define DQ_In			(PA -> PIN & (1 << 15))
   	
uint8_t DS18B20_Init(void);//初始化DS18B20
float DS18B20_Get_Temp(void);//获取温度
void DS18B20_Start(void);//开始温度转换
void DS18B20_Write_Byte(uint8_t dat);//写入一个字节
uint8_t DS18B20_Read_Byte(void);//读出一个字节
uint8_t DS18B20_Read_Bit(void);//读出一个位
uint8_t DS18B20_Check(void);//检测是否存在DS18B20
void DS18B20_Rst(void);//复位DS18B20  
void init_onewire_out( void );  
void init_onewire_in( void ) ;

#endif















