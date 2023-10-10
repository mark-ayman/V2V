/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:          CLCD             ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/

#ifndef CLCD_config_H_
#define CLCD_config_H_

/*Choose the Operation Mode between EIGHT_BIT_MODE or FOUR_BIT_MODE*/

/*if you choose EIGHT_BIT_MODE So You need to make a Port for Control Pins and a port for
 * Data Pins
 * */
#define CLCD_OP_MODE        EIGHT_BIT_MODE

#if CLCD_OP_MODE == FOUR_BIT_MODE
#define CLCD_D4_PIN    DIO_PIN3
#define CLCD_D5_PIN    DIO_PIN4
#define CLCD_D6_PIN    DIO_PIN5
#define CLCD_D7_PIN    DIO_PIN6
#endif



#define CLCD_CTRL_PORT      DIO_PORTD
#define CLCD_RS_PIN         DIO_PIN0
#define CLCD_RW_PIN         DIO_PIN1
#define CLCD_EN_PIN         DIO_PIN2

#define CLCD_DATA_PORT      DIO_PORTC

#define CLCD_CLEAR_DISPLAY	0x01    /*ab3t send command bel address da howa hyclear ellcd*/


#endif
