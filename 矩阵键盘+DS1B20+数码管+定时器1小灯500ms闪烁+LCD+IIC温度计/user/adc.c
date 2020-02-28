#include "adc.h"
#include "delay.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
void adc_init()
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1, ENABLE );
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init( GPIOA, &GPIO_InitStructure );

	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent ;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE ;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	
	ADC_Init(ADC1 ,&ADC_InitStructure);
	
	ADC_Cmd(ADC1 , ENABLE);
	
	ADC_ResetCalibration(ADC1);
	
	while(ADC_GetCalibrationStatus(ADC1));

}
uint16_t Get_adc(uint8_t ch)
{
	ADC_RegularChannelConfig(ADC1 , ch , 1 , ADC_SampleTime_239Cycles5 );
	ADC_SoftwareStartConvCmd(ADC1 , ENABLE );
	while(! ADC_GetFlagStatus(ADC1 , ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADC1);
}
uint16_t Get_ADC_V(uint8_t ch , uint8_t times)
{
	uint32_t temp_v =0;
	uint8_t t;
	for(t=0;t<times;t++)
	{
		temp_v+=Get_adc(ch);
		delay_ms(5);
	}
	return temp_v/times;
}

