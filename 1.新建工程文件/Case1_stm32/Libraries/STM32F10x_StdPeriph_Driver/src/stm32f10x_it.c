/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "main.h"
#include "dma.h"
#include "GPIOx.h"
/* �궨�� -------------------------------------------------------------------*/

//=================================MAIN�ж���====================================
extern u16 EXIT0_CNT;
extern u8 Motor1_OriginFlag; //���1 ԭ���ʶ
extern u8 Motor2_OriginFlag; //���1 ԭ���ʶ
extern u8 Motor3_OriginFlag; //���1 ԭ���ʶ

extern u8 Motor_Arrived; 		 //���  �����ʶ
// -------------------------------- SENSOR USE---------------------------------
extern u8 Delay_1s_Finishflag;
extern void Delay_Ms( u16 time );
//=================================MAIN�ж���====================================
//*******************************************************************************
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}
/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler( void )
{
	if( TIM_GetITStatus( TIM4, TIM_IT_Update ) != RESET )
	{
		TIM_Cmd( TIM4, DISABLE ); //�رն�ʱ��TIM4
		TIM_ClearITPendingBit( TIM4, TIM_FLAG_Update ); //���TIM4�жϴ�����λ
		Delay_1s_Finishflag = 1; //��ʱ1s��ɱ�־
	}
	
}
/**********************************************************
** ������:TIM3_IRQHandler
** ��������:TIM3�жϷ������
** �������: ��
** �������: ��
***********************************************************/
void TIM3_IRQHandler( void )
{ 
	
}

/**
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler( void )
{
	
}
/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM1_UP_IRQHandler( void )
{
	if( TIM_GetITStatus( TIM1, TIM_IT_Update ) != RESET )
	{
		TIM_ClearITPendingBit( TIM1, TIM_IT_Update ); //���TIM1�жϴ�����λ
		TIM_Cmd( TIM1, DISABLE ); //�رն�ʱ��TIM1
		Motor_Arrived = 1;		//�����λ���
		LED8 = !LED8;
		
	}
	
}
/**
  * @brief  This function handles USART3 global interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler( void )
{
		GPIO_SetBits( GPIOC, GPIO_Pin_4 );
		Delay_Ms( 1000 );	
		USART_ClearFlag( USART1, USART_FLAG_RXNE );
		USART_ClearITPendingBit( USART1, USART_FLAG_RXNE );	
}

/**
  * @brief  DMA1 -> CH7 USART2�����������DMA�ж����
  * @param  None
  * @retval None
  */
void DMA1_Channel7_IRQHandler( void )
{
	LED2 = 1;

	if( DMA_GetFlagStatus( DMA1_FLAG_TC7 ) != RESET )	
	{
		LumMod_Uart_DAM_Tx_Over();
	}
}

/**
  * @brief  This function handles USART3 global interrupt request.
  * @param  None
  * @retval None
  */
void USART3_IRQHandler( void )
{
}
/**
  * @brief  DMA1 -> CH6 USART2�����������DMA�ж����
  * @param  None
  * @retval None
  */
void USART2_IRQHandler( void )
{
	LED3 = 1;
	if( USART_GetITStatus( USART2, USART_IT_IDLE ) != RESET )  // �����ж�
	{
		LumMod_Uart_DMA_Rx_Data();
		USART_ReceiveData( USART2 ); // Clear IDLE interrupt flag bit
	}
}
/**
  * @brief  This function handles EXTI0 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler( void )
{
	if( EXTI_GetITStatus( EXTI_Line0 ) != RESET )
	{
		delay_ms( 10 );//��ʱ��ֹ����
		if( LS1 == 1 )
		{
			LED5 = !LED5;
		}
		while( !LS1 );
		
		TIM_CCxCmd( TIM2, TIM_Channel_1, TIM_CCx_Disable );
		Motor1_OriginFlag = 1;//���1 ����ԭ��
		EXTI_ClearITPendingBit( EXTI_Line0 );
		EXTI -> IMR = 0x06;//�ر��ⲿ�ж�0
	
	}
}
/**
  * @brief  This function handles EXTI1 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler( void )
{
	if( EXTI_GetITStatus( EXTI_Line1 ) != RESET )
	{
		delay_ms( 10 );//��ʱ��ֹ����
		if( LS2 == 1 )
		{
			LED6 = !LED6;
		}
		while( !LS2 );
		
		TIM_CCxCmd( TIM2, TIM_Channel_2, TIM_CCx_Disable );
		Motor2_OriginFlag = 1;//���2 ����ԭ��
		EXTI_ClearITPendingBit( EXTI_Line1 );
		EXTI -> IMR = 0x05;//�ر��ⲿ�ж�1
	
	}
}
/**
  * @brief  This function handles EXTI2 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler( void )
{
	if( EXTI_GetITStatus( EXTI_Line2 ) != RESET )
	{
		delay_ms( 10 );//��ʱ��ֹ����
		if( LS3 == 1 )
		{
			LED7 = !LED7;
		}
		while( !LS3 );
		
		TIM_CCxCmd( TIM2, TIM_Channel_3, TIM_CCx_Disable );
		Motor3_OriginFlag = 1;//���3 ����ԭ��
		EXTI_ClearITPendingBit( EXTI_Line2 );
		EXTI -> IMR = 0x03;//�ر��ⲿ�ж�2
	
	}
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
