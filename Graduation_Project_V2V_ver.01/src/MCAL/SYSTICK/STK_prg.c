/*
 * STK_prg.c
 *
 *  Created on: Aug 15, 2023
 *      Author: admin
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "STK_int.h"
#include "STK_prv.h"
#include "STK_cfg.h"


void (*G_vCallBack) (void) = 0 ;
u8 G_u8Flag ;
void MSTK_vInit(void)
{
	/*Clock source*/
#if STK_CLK_SOURCE == STK_AHB
	SET_BIT(STK->CTRL,CLKSOURCE);
#elif STK_CLK_SOURCE == STK_AHB_PS_8
	CLR_BIT(STK->CTRL,CLKSOURCE);
#endif
	/*2- Interrupt  Disable*/
	CLR_BIT(STK->CTRL,STK_ENABLE);
	CLR_BIT(STK->CTRL,TICKINT);
}

void MSTK_vStopTimer(void)
{
	CLR_BIT(STK->CTRL,STK_ENABLE);
}

void MSTK_vStartTimer(void)
{
	SET_BIT(STK->CTRL,STK_ENABLE);
}
void  MSTK_vSetBusyWait(u32 A_u32Tick) //stop
{
	CLR_BIT(STK->CTRL,TICKINT);
	/*1- reset Timer value*/
	STK->VAL = 0 ;
	/*2- load timer with value*/
	STK->LOAD = A_u32Tick;
	/*3- Start the timer*/
	MSTK_vStartTimer();
	/*4- polling */
	while(GET_BIT(STK->CTRL,COUNTFLAG)!=1){}
	/*5- Stop the timer  */
	MSTK_vStopTimer();
}


void MSTK_vSetInterval_Single  (u32 A_u32Tick , void(*CallBackFun)(void))
{
	/*0- set callBack Function */
	G_vCallBack = CallBackFun ;//100
	G_u8Flag = SINGLE ;
	/*1- reset Timer value*/
	STK->VAL = 0 ;
	/*2- load timer with value*/
	STK->LOAD = A_u32Tick;
	/*3- Start the timer*/
	MSTK_vStartTimer();
	SET_BIT(STK->CTRL,TICKINT);

}
void MSTK_vSetInterval_Periodic(u32 A_u32Tick , void(*CallBackFun)(void))
{
	/*0- set callBack Function */
	G_vCallBack = CallBackFun ;//100
	G_u8Flag = PERIODIC;
	/*1- reset Timer value*/
	STK->VAL = 0 ;
	/*2- load timer with value*/
	STK->LOAD = A_u32Tick;
	/*3- Start the timer*/
	MSTK_vStartTimer();
	SET_BIT(STK->CTRL,TICKINT);
}
u32 MSTK_u32GetElapsedTime(void)
{
	return  (STK->LOAD-STK->VAL) ;
}
u32 MSTK_u32GetRemainingTime(void)
{
	return  (STK->VAL) ;
}
void  SysTick_Handler (void){
	u8 ClearFlag ;
	if(G_vCallBack != 0)
	{
		G_vCallBack();
	}
	if(G_u8Flag == SINGLE)
	{
		G_u8Flag = PERIODIC;
		MSTK_vStopTimer();
	}
	ClearFlag = GET_BIT(STK->CTRL,COUNTFLAG) ;

}




