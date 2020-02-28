/*****************************************************************************
		本文件定义了DMA传输的数据结构体
******************************************************************************/

#ifndef __DMA_H
#define __DMA_H




/*******************************************************************************************
                                      DMA数据结构                                      
********************************************************************************************/
typedef struct {                               /* (@ 0x20000100) DMA数据结构体      */
  __IO uint32_t   *SOURCE;                     /* (@ 0x00000000) 主用源地址指针     */
  __IO uint32_t   *DESTIN;                     /* (@ 0x00000004)  主用目标地址指针  */
  __IO uint32_t   CTL;                         /* (@ 0x00000008) 主用控制存储器     */
	__I  uint32_t   RESERVED0;
  __IO uint32_t   *ALT_SOURCE;                 /* (@ 0x00000010) 备用源地址指针     */
  __IO uint32_t   *ALT_DESTIN;                 /* (@ 0x00000014)  备用目标地址指针  */
  __IO uint32_t   ALT_CTL;                     /* (@ 0x00000018) 备用控制存储器     */
	__I  uint32_t   RESERVED1;	
} DMA_DATA_Type;
#define DMA_DATA_BASE0                0x20000100UL									// 0通道
#define DMA_DATA_BASE1                (DMA_DATA_BASE0+0x20)					// 1通道
#define DMA_DATA_BASE2                (DMA_DATA_BASE0+0x40)					// 2通道
#define DMA_DATA_BASE3                (DMA_DATA_BASE0+0x60)					// 3通道
#define DMA_DATA_BASE4                (DMA_DATA_BASE0+0x80)					// 4通道
#define DMA_DATA_BASE5                (DMA_DATA_BASE0+0xa0)					// 5通道
#define DMA_DATA                      ((DMA_DATA_Type*)                DMA_DATA_BASE0)
#define DMA_DATA1                     ((DMA_DATA_Type*)                DMA_DATA_BASE1)
#define DMA_DATA2                     ((DMA_DATA_Type*)                DMA_DATA_BASE2)
#define DMA_DATA3                     ((DMA_DATA_Type*)                DMA_DATA_BASE3)
#define DMA_DATA4                     ((DMA_DATA_Type*)                DMA_DATA_BASE4)
#define DMA_DATA5                     ((DMA_DATA_Type*)                DMA_DATA_BASE5)


extern void DMA_CH0_UART0TX(void);
extern void DMA_CH1_UART0RX(void);
extern void DMA_UART_INIT(void);
extern void DMA_CH0_ADC(void);


extern uint16_t DMA_FLAG;
#endif

