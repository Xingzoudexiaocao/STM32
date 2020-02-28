#include "stm32f10x.h"
#include "IIC.h"
#include "GPIOx.h"
#include "delay.h"      
/******************************引脚定义*********************************/
#define SDA_out  PAout(0)   //P1.0模拟I2C总线的SDA
#define SDA_in  PAin(0)
#define SCL  PAout(1)   //P1.1模拟I2C总线的SCL

unsigned char ack_mk;	       //应答标志位，有应答为1，无应答为0
void SDA_Out_PP()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init( GPIOA, &GPIO_InitStructure );	
}
void SDA_IN_UP()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init( GPIOA, &GPIO_InitStructure );	
}
void Delay5us()		//@11.0592MHz
{
	delay_us(6);
}
/*************************************************************************
功能发送起始信号
入口参数：无
出口参数：无
**************************************************************************/
void start()	
{
	SDA_Out_PP();
	SDA_out=1;   	 	//将SDA、SCL置为1
	SCL=1;
	Delay5us();     //起始条件建立时间大于4.7us,故延时5us 
	SDA_out=0;   		//SCL为高时，SDA由高变低，发送起始信号
 	Delay5us();     //延时5us
	SCL=0;   		//SCL变低，准备发送或接收数据 
}

/*************************************************************************
功能发送结束信号
入口参数：无
出口参数：无
**************************************************************************/
void stop()  	
{ 
	SDA_Out_PP();
	SDA_out=0;  		//将SDA清0， SCL置1
 	SCL=1;  
 	Delay5us();	    //结束条件建立时间大于4.7us，所以延时5us
 	SDA_out=1;  		//当SCL为高电平时，SDA由低变高，产生结束信号
 	Delay5us();     //延时5us
	SCL=0;
}

/*************************************************************************
功能产生应答信号
入口参数：无
出口参数：无
**************************************************************************/
void Ack(void)  
{ 
	SDA_Out_PP();
	SDA_out=0;     	//SDA先清0，发应答信号 
	SCL=1;    	//SCL由低变高，产生一个时钟
	Delay5us();   //延时5us
 	SCL=0;     	//时钟线SCL恢复到低电平，以便继续接收
}

/*************************************************************************
功能产生非应答信号
入口参数：无
出口参数：无
**************************************************************************/
 void NAck(void)
{ 
	SDA_Out_PP();
	SDA_out=1;     	//SDA先置1，发非应答信号 
	SCL=1;     	//SCL由低变高，产生一个时钟
	Delay5us(); //延时5us
	SCL=0;     	//时钟线SCL恢复到低电平，以便继续接收 
}

/*************************************************************************
功能向I2C总线发送一个字节
入口参数：c 待发送字节
出口参数：无
**************************************************************************/
void  SendByte(unsigned char c)
{
	SDA_Out_PP();
	unsigned char  n ;
	for(n=0;n<8;n++)  	   //一字节为8位，循环8次
	{
		if(c&0x80)
 			SDA_out=1; 	       //根据发送位将数据线SDA置为1或清0
     	else 
     		SDA_out=0;                
     	SCL=1;             //置SCL为高，通知被控从机开始接收数据位
     	Delay5us();        //延时5us
     	SCL=0;             //SCL变低电平，准备发送下一位数据 
     	c=c<<1;            //将下一位要发送的数据移到最高位,先高后低
    }
    Delay5us();            //延时5us
    SDA_out=1;                 //一字节发送完后释放数据线，准备接收应答位
    Delay5us();  
    SCL=1;                 //SCL由低变高，产生一个时钟，读取SDA的状态
    Delay5us();            //延时5us
		SDA_IN_UP();
    if (SDA_in==1)
         ack_mk=0;    	   //如果SDA=1，则发送失败，将ack_mk清0
    else 
         ack_mk=1;         //否则发送成功，将ack_mk置1
    SCL=0;				   //SCL变低
}


/*************************************************************************
功能接收一个字节
入口参数：无
出口参数：c 返回字节
**************************************************************************/
unsigned char  RcvByte()
{
	SDA_Out_PP();
	unsigned char  c;
	unsigned char  n;
	
	SDA_out=1;
	SDA_IN_UP();
	for(n=0;n<8;n++) 	  //一字节为8位，循环8次
	{
	delay_us(1);	
	SCL=0;
	Delay5us();
	SCL=1;
	delay_us(1);	
	c=c<<1;
	if(SDA_in==1)
		c=c+1;
	Delay5us();
	SCL=0;
	Delay5us();	 
	}
	return(c);  
}

/*************************************************************************
功能向有子地址器件发送多个字节
入口参数：sla 从器件地址	suba 子地址		s 指向要发送数据		n 要发送数据的字节数
出口参数：返回1表示成功，否则操作失败
**************************************************************************/
unsigned char SendStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char n)
{  
	unsigned char i;
	start();                  		//发起始信号，启动总线
	SendByte(sla);          	 	//发送器件地址
	if(ack_mk==0)return(0);	        //如果没能应答，操作失败
	SendByte(suba);         		//发送器件子地址
	if(ack_mk==0)return(0);	        //如果没能应答，操作失败
	for(i=0;i<n;i++) 				//循环n次
    { 
		SendByte(*s);               //发送一个字节数据
      	if(ack_mk==0)return(0);	    //如果没有应答，操作失败
      	s++;						//指向下一个字节
	} 
	stop();                  	    //发结束信号，结束本次数据传送 
	return(1);
}

/*************************************************************************
功能向有子地址器件读取多个字节
入口参数：x 从器件地址	y 子地址	
出口参数：返回读取数据
**************************************************************************/
unsigned int RcvStr(unsigned char x,unsigned char y)
{  

	unsigned int i;
	start();                    //发起始信号，启动总线
	SendByte(x);             //发送器件地址
	if(ack_mk==0)return(0); 	//如果没能应答，操作失败
	SendByte(y);            	//发送器件子地址
	if(ack_mk==0)return(0); 	//如果没能应答，操作失败
	start();                    //再次发起始信号*/
	SendByte(x+1);           	//x+1表示对该器件进行读操作
	if(ack_mk==0)return(0); 	//如果没能应答，操作失败
	i=RcvByte();                //接收一个字节
	Ack();
	i=i<<8;
	i=i|RcvByte(); 
	NAck();                     //发送非应答信号
	stop();                     //发结束信号，结束本次数据传送

	return(i);
}
