/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:     GIE_REGISTERS       ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/
#ifndef GIE_REGISTERS_H_
#define GIE_REGISTERS_H_

/*Status Register (SREG) = (GIE) General Interrupt Enable
 *  Bit7 I    1 Enable  trigger
              0 Disable trigger
 */
#define   SREG_REG          *( (volatile u8*) 0x5F)
#define   SREG_I            7


#endif
