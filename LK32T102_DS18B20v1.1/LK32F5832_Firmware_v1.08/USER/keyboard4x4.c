/**
  ******************************************************************************
  * @file    ������̲��Գ��� 
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
	* @brief  4*4������̽���˵��
	* @param  SC32F5832 -> KeyBoard �������
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

/* �궨�� -------------------------------------------------------------------*/
#define PORTE PB -> PIN	//��PB�����ŵ�ѹ

/* �������� ------------------------------------------------------------------*/
//extern uint8_t KeyTrg;
//extern uint8_t KeyCont;

/**
  * @brief  4x4 �������ɨ�躯��
  * @param  None
  * @retval None
  */
	
//���÷�תɨ��ķ���( PE�ڵĸ�8λ )
//������ڶ�ʱ���жϺ����� 10msɨ��һ��
uint8_t scan_MatrixKey( void )
{

	uint8_t column;	//��
	uint8_t row;			//��
	uint8_t tmp;			//��ʱ����
	uint8_t MatrixKey_value = 20;	//��ʼ����ֵ ������0 ~ 15 
	static uint8_t key_count = 0;	//�������жϺ���ɨ��Ĵ���

	/*------------- PB ��8λ�˿����� -------------*/
	PB -> OUTEN |= 0XFF00;//PB���ʹ��
	
	//��ʼֵ: GPIOE ��8λ�˿� ��4λΪ��, ��4λΪ��
	PB -> OUT &= 0X00FF;
	PB -> OUT |= 0XF000;
	
	//GPIOE ��8λ�˿� ��4λΪ ��������
	PB -> OUTEN &= 0X0FFF;//PB����ʹ��
	GPIO_PUPD_SEL(PUPD_PU, PB, 12 );
	GPIO_PUPD_SEL(PUPD_PU, PB, 13 );
	GPIO_PUPD_SEL(PUPD_PU, PB, 14 );
	GPIO_PUPD_SEL(PUPD_PU, PB, 15 );

	tmp = PORTE >> 8;//��ȡ����ֵ
	
	if( tmp != 0XF0 )//����а�������
	{   
		//��ֹ����ʱ,�����������±������
		if( key_count < 2 )
		{
			key_count++;
		}
	}
	//����������������̧���������0 
	else
	{
		key_count = 0;
	}
	
	//������2��ɨ������ڰ���״̬ ���϶�����ȷʵ������
	if( key_count == 2 )
	{          
		column = tmp & 0XF0;//��ȡ�к�

		/*------------- GPIOE ��8λ�˿����� -------------*/
		PB -> OUTEN |= 0XFF00;//PB���ʹ��
		
		//��ת: GPIOE ��8λ�˿� ��4λΪ��, ��4λΪ��
		PB -> OUT &= 0X00FF;
		PB -> OUT |= 0X0F00;
		
		//GPIOE ��8λ�˿� ��4λΪ ��������
		PB -> OUTEN &= 0XF0FF;//PB����ʹ��
		GPIO_PUPD_SEL(PUPD_PU, PB, 8 );
		GPIO_PUPD_SEL(PUPD_PU, PB, 9 );
		GPIO_PUPD_SEL(PUPD_PU, PB, 10 );
		GPIO_PUPD_SEL(PUPD_PU, PB, 11 );
										
		row = ( PORTE >> 8 ) & 0X0F;//��ȡ�к� 
		
		switch ( column | row )//column|rowΪ�������º��Ӧ�˿ڵı���
		{   
			//������Ӧ����� �ɸ��������������ֵ 
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

	//��û�а������»���;������ɨ���������	
	if( ( PORTE & 0XFF00 ) == 0xF000 )
	{
		key_count = 0;  
	}
	
	return MatrixKey_value;
}

/**
  * @brief  stm32���尴�� S1 S2 S3 S4 
  * @param  None
  * @retval None
  */
//void KeyRead( void )
//{
//	uint8_t ReadKey_Data; //��ȡ������������
//	ReadKey_Data = GPIOC -> IDR ^ 0x0f;
//	
//	KeyTrg = ReadKey_Data & ( ReadKey_Data ^ KeyCont );
//	KeyCont = ReadKey_Data;
//}			
