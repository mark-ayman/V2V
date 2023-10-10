/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:     TIMER_program.c      ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_register.h"
#include "TIMER_config.h"

static void (*TIMER0_pvCallBackFunc)(void) = NULL;

void TIMER0_voidInit ( void )
{
	// BitMasking
	/*clear the Bits in register*/
	TCCR0_REG &= PRESCALER_MASKING;
	TCCR0_REG |= TIMER_PRESCALER;

#if TIMER_MODE == CTC_MODE
	CLR_BIT(TCCR0_REG,TCCR0_WGM00);
	SET_BIT(TCCR0_REG,TCCR0_WGM01);

	//OCR0_REG = COMPARE_MATCH_VALUE;

	/*Enable PIE of CTC Output compare match interrupt enable (enable an interrupt happens at compare match event)*/
	SET_BIT(TIMSK_REG,TIMSK_OCIE0);

#elif TIMER_MODE == NORMAL_MODE
	CLR_BIT(TCCR0_REG,TCCR0_WGM00);
	CLR_BIT(TCCR0_REG,TCCR0_WGM01);
	//TCNT0_REG = PRELOAD_VALUE;
	/*Enable PIE of overflow */
	SET_BIT(TIMSK_REG,TIMSK_TOIE0);

	/*Phase Correct PWM*/
#elif TIMER_MODE == PWM_PHASE_CORRECT_MODE
	SET_BIT(TCCR0_REG,TCCR0_WGM00);
	CLR_BIT(TCCR0_REG,TCCR0_WGM01);
#if PWM_PHASE_CORRECT_MODE == NON_INVERTED_MODE
	  CLR_BIT(TCCR0_REG,TCCR0_COM00);
	  SET_BIT(TCCR0_REG,TCCR0_COM01);

#elif PWM_PHASE_CORRECT_MODE == INVERTED_MODE
	   SET_BIT(TCCRO_REG,TCCR0_COM00);
	   SET_BIT(TCCRO_REG,TCCR0_COM01);
#endif

	   /*FAST PWM */
#elif TIMER_MODE == FAST_PWM_MODE
	  SET_BIT(TCCR0_REG,TCCR0_WGM00);
	  SET_BIT(TCCR0_REG,TCCR0_WGM01);
#if  COMPARE_FASTPWMMODE == NON_INVERTED_MODE
	  CLR_BIT(TCCR0_REG,TCCR0_COM00);
	  SET_BIT(TCCR0_REG,TCCR0_COM01);
#elif COMPARE_FASTPWMMODE == INVERTED_MODE
	   SET_BIT(TCCRO_REG,TCCR0_COM00);
	   SET_BIT(TCCRO_REG,TCCR0_COM01);
#endif

#endif
}

void TIMER0_SetPreloadValue(u8 Copy_preloadValue)
{
	TCNT0_REG = Copy_preloadValue;
}

void TIMER0_SetCompareMatchValue(u8 Copy_CompareMatchValue)
{
	OCR0_REG = Copy_CompareMatchValue;
}

u8 TIMER0_GetPreloadValue(void)
{
	return TCNT0_REG;
}

u8 TIMER0_u8SetCallBack (  void (*Copy_pvCallBackFunc)(void)  )
{
	u8 Local_u8ErrorState = OK;
	if(Copy_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}

void TIMER0_voidSetDutyCycle(u8 Copy_u8DutyCycle)
{
	u8 Local_u8OCRvalue = 0;
#if COMPARE_FASTPWMMODE == NON_INVERTED_MODE
	Local_u8OCRvalue = (Copy_u8DutyCycle * 256) / 100;
	TIMER0_SetCompareMatchValue(Local_u8OCRvalue);
#elif COMPARE_FASTPWMMODE == INVERTED_MODE
	Local_u8OCRvalue = 255 - ( (Copy_u8DutyCycle * 256) / 100 ) ;
	TIMER0_SetCompareMatchValue(Local_u8OCRvalue);

#endif
}



/*ISR for TIMER0 Compare Match MODE*/
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}

/*ISR for TIMER0 OVERFLOW MODE*/
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(TIMER0_pvCallBackFunc != NULL)
	{
		TIMER0_pvCallBackFunc();
	}
}
