/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:          TIMER            ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/
#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define    TCCR0_REG         *((volatile u8 *)0x53) /*Timer/counter Control Register*/
#define    TCCR0_WGM00       6                      /*Waveform Generation Mode Bit 6*/
#define    TCCR0_WGM01       3                      /*Waveform Generation Mode Bit 3*/
#define    TCCR0_COM00       4
#define    TCCR0_COM01       5
//#define    TCCR0_CS02       2   /* we use bitMasking */
//#define    TCCR0_CS01       1
//#define    TCCR0_CS00       0

#define    TCNT0_REG         *((volatile u8 *)0x52)  /* Timer counter Register when we use the Overflow mode*/

#define    OCR0_REG          *((volatile u8 *)0x5C) /* Output Compare Register */

#define    TIMSK_REG         *((volatile u8 *)0x59)
#define    TIMSK_TOIE0       0 /* Timer/Counter0 Overflow Interrupt Enable*/
#define    TIMSK_OCIE0       1 /* Output Compare Match Interrupt Enable */


#endif
