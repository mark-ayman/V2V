/*
 * STK_int.h
 *
 *  Created on: Aug 15, 2023
 *      Author: admin
 */

#ifndef MCAL_SYSTICK_STK_INT_H_
#define MCAL_SYSTICK_STK_INT_H_

void MSTK_vInit(void);

void MSTK_vStopTimer(void);

void  MSTK_vSetBusyWait(u32 A_u32Tick); // stop

void MSTK_vSetInterval_Single  (u32 A_u32Tick , void(*CallBackFun)(void));
void MSTK_vSetInterval_Periodic(u32 A_u32Tick , void(*CallBackFun)(void));

u32 MSTK_u32GetElapsedTime(void);
u32 MSTK_u32GetRemainingTime(void);

#endif /* MCAL_SYSTICK_STK_INT_H_ */
