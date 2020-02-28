/*****************************************************************************
				本文件展示了Coproc模块的各种运算功能
******************************************************************************/

#ifndef __COPROC_H__
#define __COPROC_H__

#include "SC32F5832.h"
#include "stdint.h"

typedef   signed           int int32;
typedef   signed       long long int64;

/**
  * @brief      .
  * @param[in]  void : a,b.
  * @param[out] void : c.
  * @retval     c
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_mult(int32 a, int32 b)
  * @endcode
  * @warning:
*/

/****************************************************************************
				乘法
***************************************************************************/	

	__INLINE int32 silan_mult(int32 a, int32 b)
	{
		int32 c;

		__disable_irq();
		COPROC->MULT_CTRL = 1;		
		COPROC->MULT_CTRL = 0x80080000;
		COPROC->MULTA	= a;
		COPROC->MULTB	= b;
		c= COPROC->MULT_RESULLO;
		__enable_irq();  
		return c;
		
	}
	
/**
  * @brief      .
  * @param[in]  void : a,b,c
  * @param[out] void : d
  * @retval     d
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int64 silan_mult_Iqx(int32 a, int32 b, int32 c)
  * @endcode
  * @warning:
*/

/**************************************************************************
		乘法（乘完移位）
***************************************************************************/
	
	__INLINE int64 silan_mult_Iqx(int32 a, int32 b, int32 c)
	{
		int64 d;

		__disable_irq();
		COPROC->MULT_CTRL = 1;		
		COPROC->MULT_CTRL |= 0x800B0000; 
		COPROC->SHIFT_NUM = c;			
		COPROC->MULTA = a; 			
		COPROC->MULTB = b;			
		 d = COPROC->MULT_RESULHI;
		 d <<= 32;
		 d |= COPROC->MULT_RESULLO;
		__enable_irq();
		return d;
		
	}
/**
  * @brief      .
  * @param[in]  void : a,b,c,d
  * @param[out] void : e.
  * @retval     e
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_mult_abPcd(int32 a, int32 b,int32 c,int32 d)
  * @endcode
  * @warning:
*/	

/**********************************************************************************
		乘法（乘完相加）	
**********************************************************************************/
	
	__INLINE int32 silan_mult_abPcd(int32 a, int32 b,int32 c,int32 d)
	{
		int32 e;
		__disable_irq();
		COPROC->MULT_CTRL = 1;		
		COPROC->MULT_CTRL |= 0x80080000; 
		COPROC->MULTA	= a;
		COPROC->MULTB	= b;
		COPROC->MULTA_ADD	= c;
		COPROC->MULTB_ADD	= d;
		e= COPROC->MULT_RESULLO;
		__enable_irq(); 
		return e;  
	}
/**
  * @brief      .
  * @param[in]  void : a,b,c,d
  * @param[out] void : e.
  * @retval     e.
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_mult_abMcd(int32 a, int32 b,int32 c,int32 d)
  * @endcode
  * @warning:
*/	
/**********************************************************************************
		乘法（乘完做差）	
**********************************************************************************/
	
	__INLINE int32 silan_mult_abMcd(int32 a, int32 b,int32 c,int32 d)
	{
		int32 e;
		__disable_irq();
		COPROC->MULT_CTRL = 1;		
		COPROC->MULT_CTRL |= 0x80080000; 
		COPROC->MULTA	= a;
		COPROC->MULTB	= b;
		COPROC->MULTA_SUB	= c;
		COPROC->MULTB_SUB	= d;
		e= COPROC->MULT_RESULLO;
		__enable_irq();
		return e;  
	}
/**
  * @brief      .
  * @param[in]  void : dividend,divisor.
  * @param[out] void : tmp.
  * @retval     tmp
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32	silan_div(int32 dividend, int32 divisor)
  * @endcode
  * @warning:
*/

/***************************************************************************
			除法（被除数32位）
*****************************************************************************/
	
#define	DIVIDER_32BIT	(1<<8)
#define	DIVIDER_64BIT	(0<<8)
	
#define	DIV_RESET		(COPROC->DIV_CTRL |= 0x01)
#define	DIV_INIT_MACRO()								\
		COPROC->DIV_CTRL	=	DIVIDER_64BIT;		\
		DIV_RESET;

	__INLINE int32	silan_div(int32 dividend, int32 divisor)
	{
		int32	tmp;
		__disable_irq();
		COPROC->DIV_CTRL = 1;		
		COPROC->DIV_CTRL = 0x00000100;

		COPROC->DIV_ALO	= dividend;
		COPROC->DIV_B	= divisor;
		tmp = COPROC->DIV_QUOTLO;
		__enable_irq();
		return tmp;
	}
/**
  * @brief      .
  * @param[in]  void : dividend,divisor.
  * @param[out] void : tmp.
  * @retval     tmp
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int64	silan_div_64(int64 dividend, int32 divisor)
  * @endcode
  * @warning:
*/
/***************************************************************************
			除法（被除数64位）
*****************************************************************************/
	__INLINE int64	silan_div_64(int64 dividend, int32 divisor)
	{
		int64 tmp;
		__disable_irq();
		COPROC->DIV_CTRL = 1;		
		COPROC->DIV_CTRL = 0x00000000;
		
		COPROC->DIV_ALO = dividend;
		COPROC->DIV_AHI = dividend>>32;
		COPROC->DIV_B = divisor;
		tmp = COPROC->DIV_QUOTHI;
		tmp = (tmp<<32)|COPROC->DIV_QUOTLO;
		__enable_irq();
		return tmp;
	}
	
/**
  * @brief      .
  * @param[in]  void : c
  * @param[out] void : tmp2.
  * @retval     tmp2
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_sinpu(int32 c)
  * @endcode
  * @warning:
*/
/********************************************************************************
			标幺正弦函数
********************************************************************************/
	
	__INLINE int32 silan_sinpu(int32 c)
	{
		int32 tmp1,tmp2;
		__disable_irq();

		COPROC->Cordic_config_b.mode = 0;     //rotate
		COPROC->Cordic_config_b.func_mode = 1;  //circle
		COPROC->Cordic_config_b.Cordic = 30;   //  运行迭代数
		
		tmp1 =(int32)(c*128);
		COPROC->Cordic_Xi = (int32)(10188013.6); // (1/1.646760258121*2^24);
		COPROC->Cordic_Yi = 0;
		COPROC->Cordic_Zi = tmp1;
		COPROC->Cordic_CTRL_b.Cordic_done = 0;  //清标志
		COPROC->Cordic_CTRL_b.cordic = 1;      // cordic start
		
		while((COPROC->Cordic_CTRL_b.Cordic_done&1)==0);
		tmp2 = COPROC->Cordic_YO; 
		__enable_irq();
		return tmp2;
	}
/**
  * @brief      .
  * @param[in]  void : c
  * @param[out] void : tmp4
  * @retval     tmp4
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_cospu(int32 c)
  * @endcode
  * @warning:
*/
/********************************************************************************
			标幺余弦函数
********************************************************************************/
	
	__INLINE int32 silan_cospu(int32 c)
	{
		int32 tmp3,tmp4;
		__disable_irq();
		
		COPROC->Cordic_config_b.mode = 0;
		COPROC->Cordic_config_b.func_mode = 1;
		COPROC->Cordic_config_b.Cordic = 30;
		
		tmp3 = (int32)(c*128);
		COPROC->Cordic_Xi = (int32)(10188013.6); 
		COPROC->Cordic_Yi = 0;
		COPROC->Cordic_Zi = tmp3;
		COPROC->Cordic_CTRL_b.Cordic_done = 0;
		COPROC->Cordic_CTRL_b.cordic = 1;
		
		while((COPROC->Cordic_CTRL_b.Cordic_done&1)==0);
		tmp4 = COPROC->Cordic_XO;
		__enable_irq();
		return tmp4;
		
	}
/**
  * @brief      .
  * @param[in]  void : a,b.
  * @param[out] void : tmp3.
  * @retval     tmp3
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_sqrt_plus(int32 a,int32 b)
  * @endcode
  * @warning:
*/
	
/******************************************************************************	
			求模函数
******************************************************************************/

__INLINE int32 silan_sqrt_plus(int32 a,int32 b)
{
		int64 tmp1,tmp2;
		int32 tmp3;
		__disable_irq();
	
		COPROC->Cordic_config_b.mode = 1;    // Vector mode
		COPROC->Cordic_config_b.func_mode = 1;     // circle 
		COPROC->Cordic_config_b.Cordic = 30;
	
		tmp1 = (int64)a*10188013;
		tmp2 = (int64)b*10188013;
		COPROC->Cordic_Xi = tmp1>>24;
		COPROC->Cordic_Yi = tmp2>>24;
		COPROC->Cordic_Zi = 0;
		COPROC->Cordic_CTRL_b.Cordic_done = 0;
		COPROC->Cordic_CTRL_b.cordic = 1;
	
		while((COPROC->Cordic_CTRL_b.Cordic_done&1)==0);
		tmp3 = COPROC->Cordic_XO;
		__enable_irq();
		return tmp3;
	
}
/**
  * @brief      .
  * @param[in]  void : a,b.
  * @param[out] void : tmp3
  * @retval     tmp3
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_atan(int32 a,int32 b)
  * @endcode
  * @warning:
*/

/******************************************************************************
			反正切函数，用于求辐角主值
*******************************************************************************/

__INLINE int32 silan_atan(int32 a,int32 b)
{
		int64 tmp1,tmp2;
		int32 tmp3;
		__disable_irq();
	
		COPROC->Cordic_config_b.mode = 1;    //Vector mode
		COPROC->Cordic_config_b.func_mode = 1;      // circle
		COPROC->Cordic_config_b.Cordic = 30;
	
		tmp1 = (int64)a*10188013;
		tmp2 = (int64)b*10188013;
		COPROC->Cordic_Xi = tmp1>>24;
		COPROC->Cordic_Yi = tmp2>>24;
		COPROC->Cordic_Zi = 0;
		COPROC->Cordic_CTRL_b.Cordic_done = 0;
		COPROC->Cordic_CTRL_b.cordic = 1;
	
		while((COPROC->Cordic_CTRL_b.Cordic_done&1)==0);
		tmp3 = COPROC->Cordic_ZO>>7;
		__enable_irq();
		return tmp3;
	
}
/**
  * @brief      .
  * @param[in]  void : c.
  * @param[out] void : tmp2
  * @retval     tmp2
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_coshpu(int32 c)
  * @endcode
  * @warning:
*/

/*******************************************************************************
			双曲余弦函数
*********************************************************************************/

__INLINE int32 silan_coshpu(int32 c)
{
		int32 tmp1,tmp2;
		if((c<=234976)|(c>5634073)) return (0);
		else{
		__disable_irq();
	
		COPROC->Cordic_config_b.mode = 0;     // rotate
		COPROC->Cordic_config_b.func_mode = 3;     // atanth
		COPROC->Cordic_config_b.Cordic = 30;       // iteration 
	
		tmp1 = (int32)(c*128);
		COPROC->Cordic_Xi = (int32)(20258439.1);
		COPROC->Cordic_Yi = 0;
		COPROC->Cordic_Zi = tmp1;
		COPROC->Cordic_CTRL_b.Cordic_done = 0;  //清标志
		COPROC->Cordic_CTRL_b.cordic = 1;      // cordic start
	
		while((COPROC->Cordic_CTRL_b.Cordic_done&1)==0);
		tmp2 = COPROC->Cordic_XO; 
		__enable_irq();
		return tmp2;
		}
}
/**
  * @brief      .
  * @param[in]  void : c.
  * @param[out] void : tmp2
  * @retval     tmp2
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_sinhpu(int32 c)
  * @endcode
  * @warning:
*/

/*******************************************************************************
			双曲正弦函数
******************************************************************************/

__INLINE int32 silan_sinhpu(int32 c)
{
		int32 tmp1,tmp2;
		if((c<=234976)|(c>5634073)) return (0);
		else{
		__disable_irq();
	
		COPROC->Cordic_config_b.mode = 0;     // rotate
		COPROC->Cordic_config_b.func_mode = 3;     // atanth
		COPROC->Cordic_config_b.Cordic = 30;       // iteration 
	
		tmp1 = (int32)(c*128);
		COPROC->Cordic_Xi = (int32)(20258439.1);
		COPROC->Cordic_Yi = 0;
		COPROC->Cordic_Zi = tmp1;
		COPROC->Cordic_CTRL_b.Cordic_done = 0;  //清标志
		COPROC->Cordic_CTRL_b.cordic = 1;      // cordic start
	
		while((COPROC->Cordic_CTRL_b.Cordic_done&1)==0);
		tmp2 = COPROC->Cordic_YO; 
		__enable_irq();
		return tmp2;
		}
}
/**
  * @brief      .
  * @param[in]  void : a,b.
  * @param[out] void : tmp3.
  * @retval     tmp3
  * @pre // 
  * @see // 
  * @par        Example:
  * -This example shows how to call the function:
  * @code
  * __INLINE int32 silan_sqrt_minus(int32 a,int32 b)  
  * @endcode
  * @warning:
*/
/*******************************************************************************
											计算X和Y的平方差开根
******************************************************************************/
	__INLINE int32 silan_sqrt_minus(int32 a,int32 b)  
{
	int64 tmp1,tmp2;
	int32 tmp3;
	__disable_irq();
	
	COPROC->Cordic_config_b.mode = 1;			// vector
	COPROC->Cordic_config_b.func_mode = 3;     // atanth
	COPROC->Cordic_config_b.Cordic = 30;       // iteration 
	
	tmp1 = (int64)a*20258439;
	tmp2 = (int64)b*20258439;
	COPROC->Cordic_Xi = tmp1>>24;
	COPROC->Cordic_Yi = tmp2>>24;
	COPROC->Cordic_Zi = 0;
	COPROC->Cordic_CTRL_b.Cordic_done = 0;
	COPROC->Cordic_CTRL_b.cordic = 1;
	
	while((COPROC->Cordic_CTRL_b.Cordic_done&1)==0);
	tmp3 = COPROC->Cordic_XO;
	__enable_irq();
	return tmp3;
	
}
	
#define	MULT_MACRO(a,b)	silan_mult(a,b)
#define	MULT_MACRO_IQX(a,b,c)	silan_mult_Iqx(a,b,c)
#define MULT_PLUS_MACRO(a,b,c,d) silan_mult_abPcd(a,b,c,d)
#define MULT_MINUS_MACRO(a,b,c,d) silan_mult_abMcd(a,b,c,d)
#define	DIV_MACRO(a,b)	 silan_div(a,b)
#define DIV_MACRO_64(a,b) silan_div_64(a,b)
#define SINPU_MACRO(a)   silan_sinpu(a)
#define COSPU_MACRO(a)   silan_cospu(a)
#define SQRT_PLUS_MACRO(a,b)	 silan_sqrt_plus(a,b)
#define ATAN_MACRO(a,b)  silan_atan(a,b)
#define COSHPU_MACRO(a)  silan_coshpu(a)	
#define SINHPU_MACRO(a)  silan_sinhpu(a)
#define SQRT_MINUS_MACRO(a,b) silan_sqrt_minus(a,b)

extern void MultiTest(void);
extern void MultiIQTest(void);
extern void DivTest(void);
extern void MultiabPcd(void);
extern void MultiabMcd(void);

#endif






