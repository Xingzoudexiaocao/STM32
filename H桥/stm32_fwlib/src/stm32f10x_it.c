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
#include "GPIOx.h"
#define AIN1_1 PAout(8)	
#define AIN1_2 PAout(10)	
#define BIN1_1 PAout(12)	
#define BIN1_2 PAout(9)	
extern unsigned char L_or_R;
//#include "main.h"
//#include "dma.h"
//#include "GPIOx.h"
/* 宏定义 -------------------------------------------------------------------*/

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
//void SysTick_Handler(void)
//{
//}
/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler( void )
{
}
/**********************************************************
** 函数名:TIM3_IRQHandler
** 功能描述:TIM3中断服务程序
** 输入参数: 无
** 输出参数: 无
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
	
	static unsigned char motor_num =0;
	if(L_or_R==0)
	{
		if(motor_num==0)
		{
			AIN1_1=1; 
			AIN1_2=0; 
			BIN1_1=1; 
			BIN1_2=0; //1拍 1.8°
		}
		else if(motor_num==1)
		{
			AIN1_1=0; 
			AIN1_2=1; 
			BIN1_1=1; 
			BIN1_2=0; //1拍 1.8°
		}
		else if(motor_num==2)
		{
			AIN1_1=0; 
			AIN1_2=1; 
			BIN1_1=0; 
			BIN1_2=1; //1拍 1.8°
		}
		else if(motor_num==3)
		{
			AIN1_1=1; 
			AIN1_2=0; 
			BIN1_1=0; 
			BIN1_2=1; //1拍 1.8°
		}
	}
	if(L_or_R==1)
	{
		if(motor_num==3)
		{
			AIN1_1=1; 
			AIN1_2=0; 
			BIN1_1=1; 
			BIN1_2=0; //1拍 1.8°
		}
		else if(motor_num==2)
		{
			AIN1_1=0; 
			AIN1_2=1; 
			BIN1_1=1; 
			BIN1_2=0; //1拍 1.8°
		}
		else if(motor_num==1)
		{
			AIN1_1=0; 
			AIN1_2=1; 
			BIN1_1=0; 
			BIN1_2=1; //1拍 1.8°
		}
		else if(motor_num==0)
		{
			AIN1_1=1; 
			AIN1_2=0; 
			BIN1_1=0; 
			BIN1_2=1; //1拍 1.8°
		}
	}
	motor_num++;
	if(motor_num>=4)
		motor_num=0;




	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
}
/**
  * @brief  This function handles USART3 global interrupt request.
  * @param  None
  * @retval None
  */
void USART1_IRQHandler( void )
{
}

/**
  * @brief  DMA1 -> CH7 USART2发送数据完成DMA中断入口
  * @param  None
  * @retval None
  */
void DMA1_Channel7_IRQHandler( void )
{
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
  * @brief  DMA1 -> CH6 USART2接收数据完成DMA中断入口
  * @param  None
  * @retval None
  */
void USART2_IRQHandler( void )
{

}
/**
  * @brief  This function handles EXTI0 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler( void )
{
}
/**
  * @brief  This function handles EXTI1 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler( void )
{
}
/**
  * @brief  This function handles EXTI2 global interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler( void )
{
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
