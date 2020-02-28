#include "ds18b20.h"
#include "GPIOx.h"
#include "delay.h"
#define DQ_OUT PAout (12) 
#define DQ_IN PAin (12) 


void ds18b20init_out(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init( GPIOA, &GPIO_InitStructure );
}

void ds18b20init_in(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init( GPIOA, &GPIO_InitStructure );
}

void Write_DS18B20(unsigned char dat)
{
	ds18b20init_out();
	unsigned char i;
	for(i=0;i<8;i++)
	{
		DQ_OUT = 0;
		delay_us(4);
		DQ_OUT = dat&0x01;
		delay_us(80);
		DQ_OUT = 1;
		dat >>= 1;
	}
}



unsigned char Read_DS18B20(void)
{
	unsigned char i;
	unsigned char dat;
  
	for(i=0;i<8;i++)
	{
		dat >>= 1;
		ds18b20init_out();
		DQ_OUT = 0;
		delay_us(4);
		DQ_OUT = 1;
		delay_us(10);
		ds18b20init_in();
		if(DQ_IN)
		{
			dat |= 0x80;
		}	    
		delay_us(60);
	}
	return dat;
}

unsigned char init_ds18b20(void)
{
  	unsigned char initflag = 1;
  	ds18b20init_out();
  	DQ_OUT = 0;
  	delay_us(500);
  	DQ_OUT = 1;
  	delay_us(80);
		ds18b20init_in();
    initflag = DQ_IN;     
  	delay_us(500);
  
  	return initflag;
}

unsigned char read_temp (void)
{
		unsigned char low,high,byte;
		unsigned int temp;
		
		init_ds18b20(); 
		Write_DS18B20(0xcc); 
		Write_DS18B20(0x44); 
			
		init_ds18b20();			
		Write_DS18B20(0xcc);  
		Write_DS18B20(0xbe);	
		
		low=Read_DS18B20();  
		high=Read_DS18B20();	

//		if(high>7)
//    {
//      temp = ~(high<<8|low) + 1;  
//    }
//    else 
//    {
//      temp = high<<8 | low;
//    }    

		low=low>>4;          
		high=high<<4;        
		
		temp=high | low;     
		return temp;
}
