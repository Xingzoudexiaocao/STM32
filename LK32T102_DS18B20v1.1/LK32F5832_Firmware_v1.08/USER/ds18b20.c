/* Includes ------------------------------------------------------------------*/
#include <SC32F5832.h>
#include <DevInit.h>
#include "ds18b20.h"
#include "delay.h"

	/**
	* @brief  单总线温度传感器 接线说明
	* @param  SC32F5832 -> 温度传感器模块
	*							PA15 	-> 	CN2-DSO
	*/

//复位DS18B20
void DS18B20_Rst(void)	   
{                 
	init_onewire_out(); //SET PA0 OUTPUT
	DQ_Out_L; //拉低DQ
	ST_delay_us(750);    //拉低750us
	DQ_Out_H; //DQ=1 
	ST_delay_us(15);     //15US
}
//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry = 0;
	init_onewire_in();//SET PA0 INPUT	
  while (DQ_In && retry < 200)
	{
		retry++;
		ST_delay_us(1);
	};	 
	if(retry>=200)
		return 1;
	else 
		retry=0;
  while (!DQ_In&&retry<240)
	{
		retry++;
		ST_delay_us(1);
	};
	if(retry>=240)
		return 1;	    
	return 0;
}
//从DS18B20读取一个位
//返回值：1/0
uint8_t DS18B20_Read_Bit(void) 			 // read one bit
{
    uint8_t data;
	init_onewire_out();//SET PA0 OUTPUT
    DQ_Out_L; 
	ST_delay_us(2);
    DQ_Out_H; 
	init_onewire_in();//SET PA0 INPUT
	ST_delay_us(12);
	if(DQ_In)data=1;
    else data=0;	 
    ST_delay_us(50);           
    return data;
}
//从DS18B20读取一个字节
//返回值：读到的数据
uint8_t DS18B20_Read_Byte(void)    // read one byte
{        
    uint8_t i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}
//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(uint8_t dat)     
 {             
    uint8_t j;
    uint8_t testb;
	init_onewire_out();//SET PA15 OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DQ_Out_L;// Write 1
            ST_delay_us(2);                            
            DQ_Out_H;
            ST_delay_us(60);             
        }
        else 
        {
            DQ_Out_L;// Write 0
            ST_delay_us(60);             
            DQ_Out_H;
            ST_delay_us(2);                          
        }
    }
}
//开始温度转换
void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();	   
		DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0x44);// convert
} 
//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在    	 
uint8_t DS18B20_Init(void)
{
	init_onewire_out();
	DQ_Out_H;
	DS18B20_Rst();
	return DS18B20_Check();
}  
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
float  DS18B20_Get_Temp(void)
{
	uint8_t temp = 0;
	uint8_t TL = 0,TH = 0;
	short tem;
	DS18B20_Start ();// ds1820 start convert
	DS18B20_Rst();
	DS18B20_Check();	 
	DS18B20_Write_Byte(0xcc);// skip rom
	DS18B20_Write_Byte(0xbe);// convert	    
	TL = DS18B20_Read_Byte(); // LSB   
	TH = DS18B20_Read_Byte(); // MSB  
	    	  
    if(TH > 7)
    {
			TH = ~TH;
			TL = ~TL; 
			temp = 0;//温度为负  
    }
		else 
			temp = 1;//温度为正
		
    tem = TH; //获得高八位
    tem <<= 8;    
    tem += TL;//获得低八位
    tem =(float)tem * 0.0625 * 10;//转换   
	if(temp)
		return tem; //返回温度值
	else 
		return -tem;    
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
	GPIO_PUPD_SEL(PUPD_PU, PA, 15 );
	
} 
