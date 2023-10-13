/*******************************************************/
/****   Author : Ibrahim Elshimy      ******************/
/****   SWC:          CLCD             ******************/
/****   Date :        5/8/2023        ******************/
/****   Version : 1.00                ******************/
/*******************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"

#include "util/delay.h"

#if CLCD_OP_MODE == FOUR_BIT_MODE
static void voidSetLcdHalfDataPort(u8 Copy_u8Nipple)
{
	DIO_voidSetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN,GET_BIT(Copy_u8Nipple,0));
	DIO_voidSetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN,GET_BIT(Copy_u8Nipple,1));
	DIO_voidSetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN,GET_BIT(Copy_u8Nipple,2));
	DIO_voidSetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN,GET_BIT(Copy_u8Nipple,3));
}
#endif

static void voidSendEnablePulse(void)
{
	/*
	 Send enable pulse 3shan elData elet5znet fe Input/Output Buffer
	 tetn2al lel Instruction Register lo hya kanet command aw tetn2al
	 lel Data Register lo hya kanet Data
	 */
	DIO_voidSetPinValue(CLCD_CTRL_PORT,CLCD_EN_PIN,DIO_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(CLCD_CTRL_PORT,CLCD_EN_PIN,DIO_LOW);
}


void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	// RS = 0 low for sending 8 bits data to Instruction Register/
	DIO_voidSetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_LOW);

	// RW = 0 for write
	DIO_voidSetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);

#if CLCD_OP_MODE == EIGHT_BIT_MODE
	DIO_voidSetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	voidSendEnablePulse();


#elif CLCD_OP_MODE == FOUR_BIT_MODE

	voidSetLcdHalfDataPort(Copy_u8Command>>4); /*Send the Most Significant 4 bits*/
	voidSendEnablePulse();

	voidSetLcdHalfDataPort(Copy_u8Command); /*Send the Least Significant 4 bits*/
	voidSendEnablePulse();
#endif
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	// RS = 1 high for sending 8 bits data to Data Register
	DIO_voidSetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_HIGH);

	// RW = 0 for write
	DIO_voidSetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);


#if CLCD_OP_MODE == EIGHT_BIT_MODE
	DIO_voidSetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	voidSendEnablePulse();


#elif CLCD_OP_MODE == FOUR_BIT_MODE

	voidSetLcdHalfDataPort(Copy_u8Data>>4); /*Send the Most Significant 4 bits*/
	voidSendEnablePulse();

	voidSetLcdHalfDataPort(Copy_u8Data); /*Send the Least Significant 4 bits*/
	voidSendEnablePulse();
#endif

}

void CLCD_voidInit(void)
{
	/*
	 after we power the Lcd we need to delay the lcd before we input any command
	 */
	_delay_ms(30);
#if CLCD_OP_MODE == EIGHT_BIT_MODE
	/*function set*/
	CLCD_voidSendCommand(0b00111100);

#elif CLCD_OP_MODE == FOUR_BIT_MODE
	voidSetLcdHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetLcdHalfDataPort(0b0010);
	voidSendEnablePulse();
	voidSetLcdHalfDataPort(0b1100);
	voidSendEnablePulse();
#endif

	/* Display on/off command */
	CLCD_voidSendCommand(0b00001100);

	/*clear all characters on lcd and will start from the first location on the lcd*/
	CLCD_voidSendCommand(0b00000001);
	/* 0x01 da address DDRAM gowah address tany bta3 elspace
	   w eladdress da fe CGROM w gowa elascii value bta3t elspace asln hytkteb
	 */
}

void CLCD_voidSendString(const char *Copy_chString)
{
	u8 Local_u8Counter = 0;
	for(Local_u8Counter =0; Copy_chString[Local_u8Counter] != '\0';Local_u8Counter++)
	{
		CLCD_voidSendData( Copy_chString[Local_u8Counter] );
	}
}

void CLCD_voidSendNumber(s32 Copy_s32Number)
{
	/*the input number must not contain a zero before the number
	  as the tool chain will implement it as an octal number
	 */
	u8 Local_u8Remainder = 0;
	s8 Local_u8Counter = 0;
	char array[10];

	if(Copy_s32Number == 0)
	{
		CLCD_voidSendData('0');
	}
	else if(Copy_s32Number < 0)
	{
		Copy_s32Number = Copy_s32Number * -1;
		CLCD_voidSendData('-');
	}

	while(Copy_s32Number != 0)
	{
		Local_u8Remainder  = Copy_s32Number % 10;
		array[Local_u8Counter] = Local_u8Remainder + 0x30; //0x30=48
		Copy_s32Number = Copy_s32Number / 10;
		Local_u8Counter++;
	}
	/*lazem a3ml Local_s8Counter2 signed 3shan yb2a negative*/
	for(s8 Local_s8Counter2 =Local_u8Counter-1; Local_s8Counter2>=0;Local_s8Counter2--)
	{
		CLCD_voidSendData(array[Local_s8Counter2]);
	}
}

void CLCD_voidSetPosition(u8 Copy_u8Row , u8 Copy_u8Col)
{
	u8 Local_u8DDRAMAddress;

	if(Copy_u8Row == 0u)
	{
		Local_u8DDRAMAddress = Copy_u8Col;
	}
	else if(Copy_u8Row == 1u)
	{
		Local_u8DDRAMAddress = 0x40 + Copy_u8Col; // 0x40in hexa or 64 in decimal
	}

	/*Set bit no 7 by 1 for Set DDRAM Address */
	Local_u8DDRAMAddress = (Local_u8DDRAMAddress) | (1<<7u);

	CLCD_voidSendCommand(Local_u8DDRAMAddress);
}

void CLCD_voidSendSpecialCharacter(u8 *Copy_pu8Pattern,u8 Copy_u8PatternNumber,u8 Copy_u8Row,u8 Copy_u8Col)
{
	u8 Local_u8CGRAMAddress = Copy_u8PatternNumber * 8;
	Local_u8CGRAMAddress = Local_u8CGRAMAddress | (1<<6);
	Local_u8CGRAMAddress = Local_u8CGRAMAddress | (0<<7);
	CLCD_voidSendCommand(Local_u8CGRAMAddress);

	/*write the pattern into CGRAM*/
	for(int i=0;i<8;i++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[i]);
	}

	/*Go to DDRAM to Display the pattern */
	CLCD_voidSetPosition(Copy_u8Row,Copy_u8Col);

	/*Display the pattern written inside CGRAM*/
	CLCD_voidSendData(Copy_u8PatternNumber);

}

