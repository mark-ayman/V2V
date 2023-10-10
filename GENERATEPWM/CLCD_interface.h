/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:          CLCD             ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/


#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidInit(void);

void CLCD_voidSendString(const char *Copy_chString);
void CLCD_voidSendNumber(s32 Copy_s32Number);
void CLCD_voidSetPosition(u8 Copy_u8Row , u8 Copy_u8Col);

void CLCD_voidSendSpecialCharacter(u8 *Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8Row,u8 Copy_u8Col);

#endif
