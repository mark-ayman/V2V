#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "TIMER1_interface.h"
#include "CLCD_interface.h"

#include <util/delay.h>

static u16 periodTicks = 0;
static u16 OnTicks = 0;


static u16 ticksCounts = 0;
static u8 flag = 0;
static u8 counter = 0;

static u16 NewTicks = 0;

void ICU_HW(void);
int main(void)
{
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_INPUT);

	/*CLCD pins*/
	DIO_voidSetPortDirection(DIO_PORTC,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN0,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN1,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN2,DIO_OUTPUT);

	/*generate a H.W PWM signal Using TIMER0*/
	TIMER0_voidInit();
	//TIMER0_voidSetDutyCycle(50);
	TIMER0_SetCompareMatchValue(130);

	/* Normal Mode */
	TIMER1_voidInit();

	ICU_voidInterruptEnable();

	GIE_voidEnable();

	CLCD_voidInit();

	/*Initial of ICU is Rising edge lama yegelo rising edge hy3ml interrupt hyro7 yenfez elinterrupt function*/

	ICU_voidInit();
	ICU_voidSetCallBack(ICU_HW);
	//ICU_voidICUSetEdge(ICU_RISING_EDGE);
	//ICU_voidInterruptEnable();

    u8 distance = 0;
	while(1)
	{
		if(counter == 0)
		{
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_HIGH);
			_delay_us(10);
			DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_LOW);
		}
		distance = ticksCounts * 0.0175;


		CLCD_voidSetPosition(0,0);
		CLCD_voidSendString("Ticks = ");
	    CLCD_voidSendNumber(ticksCounts);
		_delay_ms(100);
		CLCD_voidSetPosition(1,0);
		CLCD_voidSendString("distance = ");
	    CLCD_voidSendNumber(distance);
		_delay_ms(100);

	}
	return 0;
}


void ICU_HW(void)
{
	if(counter == 0)
	{
/*first Rising edge we don't need the reading in TCNT1 or ICR1 register we need it to be zero*/
		TIMER1_SetTimerValue(0); /*TCNT1 register will be zero counts*/

		ICU_voidICUSetEdge(ICU_FALLING_EDGE);
		counter = 1;
		//flag = 1;

	}
	else if(counter == 1)
	{
		/*at falling edge */
		ticksCounts = ICU_voidReadICR1();

		ICU_voidICUSetEdge(ICU_RISING_EDGE);
		counter = 0;
		//flag = 0;
	}


}



/*
 * void ICU_SW(void)
{
	static u8 Local_u8Counter = 0;
	Local_u8Counter++;

	if(Local_u8Counter == 1)
	{
		//First Rising edge
		TIMER1_SetTimerValue(0);
	}
	else if(Local_u8Counter == 2)
	{
		periodTicks = TIMER1_GetTimerValue();
	    //change Trigger
		EXTI_voidSetSenseControl(EXTI_INT0,EXTI_FALLING_EDGE)
	}
	else if(Local_u8Counter == 3)
	{
		OnTicks = TIMER1_GetTimerValue();
		OnTicks = OnTicks - periodTicks;
	}
}
 *
 * */


/*
if(flag == 0)
{
	ICU_voidICUSetEdge(ICU_RISING_EDGE);
	ICU_voidSetCallBack(ICU_HW);
}
else if(flag == 1)
{

	ICU_voidSetCallBack(ICU_HW);
	counter = 0;
}
*/
