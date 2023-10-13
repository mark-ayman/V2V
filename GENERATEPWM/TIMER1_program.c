/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:     TIMER1_program.c      ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER1_register.h"
#include "TIMER1_interface.h"
#include "TIMER1_private.h"
#include "TIMER1_config.h"

static void (*ICU_pvCallFunction) ( void ) = NULL ;


/*Fast PWM */
void TIMER1_voidInit ( void )
{
	// BitMasking
	/*clear the Bits in register*/
	TCCR1B_REG &= PRESCALER_MASKING;
	TCCR1B_REG |= TIMER_PRESCALER;

	/*Normal mode*/
	TCCR1A_REG = 0b00000000;
	/*
    //FOR FAST PWM Non Inverted
    CLR_BIT(TCCR1A_REG,TCCR1A_COM1A0);
    CLR_BIT(TCCR1A_REG,TCCR1A_COM1B0);

    SET_BIT(TCCR1A_REG,TCCR1A_COM1A1);
    SET_BIT(TCCR1A_REG,TCCR1A_COM1B1);

    //Mode 14 Fast PWM
	CLR_BIT(TCCR1A_REG,TCCR1A_WGM10);
	SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM12);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
	*/

}
void TIMER1_SetTimerValue(u16 Copy_TimerValue)
{
	TIMER1_WR_TCNT1L = Copy_TimerValue;

}

u16 TIMER1_GetTimerValue(void)
{
	return TIMER1_WR_TCNT1L;
}

void TIMER1_SetTopValue(u16 Copy_preloadValue)
{
	TIMER1_POINTER_TO_ICR1L = Copy_preloadValue;
}

void TIMER1_SetCompareMatchValue(u16 Copy_CompareMatchValue)
{
	/*
	SET_BIT(TCCR1A_REG,TCCR1A_WGM10);
	SET_BIT(TCCR1A_REG,TCCR1A_WGM11);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM12);
	SET_BIT(TCCR1B_REG,TCCR1B_WGM13);
	*/
	TIMER1_POINTER_TO_OCR1AL = Copy_CompareMatchValue;
}

void ICU_voidInit(void)
{
	/*initialize the ICU at rising edge*/
	SET_BIT(TCCR1B_REG,TCCR1B_ICES1);
	/*ICU (PIE) interrupt Enable*/
	SET_BIT(TIMSK_REG,TIMSK_TICIE1);
}

void ICU_voidInterruptEnable(void)
{
	/*ICU (PIE) interrupt Enable*/
	SET_BIT(TIMSK_REG,TIMSK_TICIE1);
}

void ICU_voidInterruptDisable(void)
{
	/*ICU (PIE) interrupt Disable*/
	CLR_BIT(TIMSK_REG,TIMSK_TICIE1);
}


void ICU_voidICUSetEdge(u8 Copy_u8Edge)
{
	switch(Copy_u8Edge)
	{
	case ICU_FALLING_EDGE:
		CLR_BIT(TCCR1B_REG,TCCR1B_ICES1);
		break;
	case ICU_RISING_EDGE:
		SET_BIT(TCCR1B_REG,TCCR1B_ICES1);
		break;
	}
}

u16 ICU_voidReadICR1(void)
{
	return TIMER1_POINTER_TO_ICR1L;
}
void ICU_voidSetICR1(u16 Copy_Value)
{
	TIMER1_POINTER_TO_ICR1L = Copy_Value;
}

void ICU_voidSetCallBack(void (*Copy_ptrtofunc)(void) )
{
	if(Copy_ptrtofunc != NULL)
	{
		ICU_pvCallFunction = Copy_ptrtofunc;
	}
}



void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(ICU_pvCallFunction != NULL)
	{
		ICU_pvCallFunction();
	}

}
