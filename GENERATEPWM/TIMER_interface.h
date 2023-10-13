/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:          TIMER            ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_



void TIMER0_voidInit ( void );

u8 TIMER0_GetPreloadValue(void);

void TIMER0_SetPreloadValue(u8 Copy_preloadValue);

void TIMER0_SetCompareMatchValue(u8 Copy_CompareMatchValue);

u8 TIMER0_u8SetCallBack( void (*Copy_pvCallBackFunc)(void) );

void TIMER0_voidSetDutyCycle(u8 Copy_u8DutyCycle);


#endif
