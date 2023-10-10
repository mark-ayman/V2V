/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:          TIMER1            ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#define ICU_RISING_EDGE        0
#define ICU_FALLING_EDGE       1


void TIMER1_voidInit ( void );
void TIMER1_SetTimerValue(u16 Copy_TimerValue);
u16  TIMER1_GetTimerValue(void);
void TIMER1_SetTopValue(u16 Copy_preloadValue);
void TIMER1_SetCompareMatchValue(u16 Copy_CompareMatchValue);

void ICU_voidInit(void);
void ICU_voidInterruptEnable(void);
void ICU_voidInterruptDisable(void);
void ICU_voidICUSetEdge(u8 Copy_u8Edge);
u16  ICU_voidReadICR1(void);
void ICU_voidSetICR1(u16 Copy_Value);
void ICU_voidSetCallBack(void (*Copy_ptrtofunc)(void) );

#endif
