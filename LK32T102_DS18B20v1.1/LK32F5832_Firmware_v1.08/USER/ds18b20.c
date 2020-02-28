/* Includes ------------------------------------------------------------------*/
#include <SC32F5832.h>
#include <DevInit.h>
#include "ds18b20.h"
#include "delay.h"

	/**
	* @brief  �������¶ȴ����� ����˵��
	* @param  SC32F5832 -> �¶ȴ�����ģ��
	*							PA15 	-> 	CN2-DSO
	*/

//��λDS18B20
void DS18B20_Rst(void)	   
{                 
	init_onewire_out(); //SET PA0 OUTPUT
	DQ_Out_L; //����DQ
	ST_delay_us(750);    //����750us
	DQ_Out_H; //DQ=1 
	ST_delay_us(15);     //15US
}
//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
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
//��DS18B20��ȡһ��λ
//����ֵ��1/0
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
//��DS18B20��ȡһ���ֽ�
//����ֵ������������
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
//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
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
//��ʼ�¶�ת��
void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();	   
		DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0x44);// convert
} 
//��ʼ��DS18B20��IO�� DQ ͬʱ���DS�Ĵ���
//����1:������
//����0:����    	 
uint8_t DS18B20_Init(void)
{
	init_onewire_out();
	DQ_Out_H;
	DS18B20_Rst();
	return DS18B20_Check();
}  
//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
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
			temp = 0;//�¶�Ϊ��  
    }
		else 
			temp = 1;//�¶�Ϊ��
		
    tem = TH; //��ø߰�λ
    tem <<= 8;    
    tem += TL;//��õͰ�λ
    tem =(float)tem * 0.0625 * 10;//ת��   
	if(temp)
		return tem; //�����¶�ֵ
	else 
		return -tem;    
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
	GPIO_PUPD_SEL(PUPD_PU, PA, 15 );
	
} 
