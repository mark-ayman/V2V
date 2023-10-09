/*
 * STK_prv.h
 *
 *  Created on: Aug 15, 2023
 *      Author: admin
 */

#ifndef MCAL_SYSTICK_STK_PRV_H_
#define MCAL_SYSTICK_STK_PRV_H_


#define STK_BASE_ADDRESS    0xE000E010

typedef struct
{
volatile u32  CTRL;
volatile u32  LOAD;
volatile u32  VAL;//note A write of any value clears the field to 0, and also clears the COUNTFLAG bit in the STK_CTRL register to 0.
volatile u32  CALIB;
}STK_MemMap_t;

#define  STK   ((volatile STK_MemMap_t*)(STK_BASE_ADDRESS))

#define COUNTFLAG    16
#define CLKSOURCE    2
#define TICKINT      1
#define STK_ENABLE   0

#define STK_AHB       1
#define STK_AHB_PS_8  8

#define ENABLE   1
#define DISABLE  0

#define SINGLE   0
#define PERIODIC 1

#endif /* MCAL_SYSTICK_STK_PRV_H_ */
