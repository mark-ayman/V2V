/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:          TIMER            ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/
#ifndef TIMER1_REGISTER_H_
#define TIMER1_REGISTER_H_

#define      TIMSK_REG                    *((volatile u8 *)0x59)
#define      TIMSK_TICIE1                 5
#define      TIMSK_TOIE1                  2

#define      TIFR_REG                     *((volatile u8 *)0x58)
#define      TIFR_TOV1                    2
#define      TIFR_ICF1                    5

#define      TCCR1A_REG                    *((volatile u8 *)0x4F)
#define      TCCR1A_WGM10                  0
#define      TCCR1A_WGM11                  1
#define      TCCR1A_COM1B0                 4
#define      TCCR1A_COM1B1                 5
#define      TCCR1A_COM1A0                 6
#define      TCCR1A_COM1A1                 7


#define      TCCR1B_REG                    *((volatile u8 *)0x4E)
#define      TCCR1B_WGM12                  3
#define      TCCR1B_WGM13                  4
#define      TCCR1B_ICES1                  6  /*select Rising or falling*/

#define      TCNT1H_REG                    *((volatile u8 *)0x4D)
#define      TCNT1L_REG                    *((volatile u8 *)0x4C)

#define      OCR1AH_REG                    *((volatile u8 *)0x4B)
#define      OCR1AL_REG                    *((volatile u8 *)0x4A)

#define      OCR1BH_REG                    *((volatile u8 *)0x49)
#define      OCR1BL_REG                    *((volatile u8 *)0x48)

#define      ICR1H_REG                     *((volatile u8 *)0x47) /*INPUT CAPTURE REGISTER*/
#define      ICR1L_REG                     *((volatile u8 *)0x46) /*INPUT CAPTURE REGISTER*/

#define      TIMER1_WR_TCNT1L              *((volatile u16*)0x4C)

#define      TIMER1_POINTER_TO_ICR1L       *((volatile u16*)0x46) /*To write the TOP value directly in 16 bits*/

#define      TIMER1_POINTER_TO_OCR1AL      *((volatile u16*)0x4A) /*To write the compare match value directly in 16 bits*/

#endif
