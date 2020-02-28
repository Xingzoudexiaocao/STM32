#ifndef __DS18B20_H
#define __DS18B20_H 


////IO��������											   
#define DQ_Out_H 	PA_OUT_HIGH(15)
#define DQ_Out_L 	PA_OUT_LOW(15)
#define DQ_In			(PA -> PIN & (1 << 15))
   	
uint8_t DS18B20_Init(void);//��ʼ��DS18B20
float DS18B20_Get_Temp(void);//��ȡ�¶�
void DS18B20_Start(void);//��ʼ�¶�ת��
void DS18B20_Write_Byte(uint8_t dat);//д��һ���ֽ�
uint8_t DS18B20_Read_Byte(void);//����һ���ֽ�
uint8_t DS18B20_Read_Bit(void);//����һ��λ
uint8_t DS18B20_Check(void);//����Ƿ����DS18B20
void DS18B20_Rst(void);//��λDS18B20  
void init_onewire_out( void );  
void init_onewire_in( void ) ;

#endif















