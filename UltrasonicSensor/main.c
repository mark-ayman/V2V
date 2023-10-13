#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "GIE_interface.h"
#include "TIMER1_interface.h"
#include "CLCD_interface.h"

#include <util/delay.h>

#include "TIMER1_register.h"

int TimerOverflow = 0;


ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	// Increment Timer Overflow count
}


void ICU_HW(void);
ICU_voidSetCallBack(ICU_HW);

int main(void)
{
	char string[10];
	long count;
	double distance;

	/*make PIN A0 as Output FOR TRIG PIN*/
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_OUTPUT);

	/* Turn on Pull-up for PORTD */
	DIO_voidSetPortDirection(DIO_PORTD,DIO_INPUT);
	DIO_voidSetPortValue(DIO_PORTD,DIO_HIGH);


	CLCD_voidInit();
	CLCD_voidSetPosition(1,0);
	CLCD_voidSendString("Ultrasonic");

    GIE_voidEnable();			/* Enable global interrupt */
	TIMSK_REG = (1 << TIMSK_TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A_REG = 0;                  /* Set all bit to zero Normal operation */


	while(1)
	{
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_HIGH);
		_delay_us(10);
		DIO_voidSetPinValue(DIO_PORTA,DIO_PIN0,DIO_LOW);


		TIMER1_SetTimerValue(0); /* Clear Timer counter */
		TCCR1B_REG = 0x41;	/* Capture on rising edge, No prescaler*/
		TIFR_REG = 1<<TIFR_ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR_REG = 1<<TIFR_TOV1;	/* Clear Timer Overflow flag */


		/*Calculate width of Echo by Input Capture (ICP) */

				while ((TIFR_REG & (1 << TIFR_ICF1)) == 0);/* Wait for rising edge */
				TIMER1_WR_TCNT1L = 0;	/* Clear Timer counter */
				TCCR1B_REG = 0x01;	/* Capture on falling edge, No prescaler */
				TIFR_REG = 1<<TIFR_ICF1;	/* Clear ICP flag (Input Capture flag) */
				TIFR_REG = 1<<TIFR_TOV1;	/* Clear Timer Overflow flag */
				TimerOverflow = 0;/* Clear Timer overflow count */

				while ((TIFR_REG & (1 << TIFR_ICF1)) == 0);/* Wait for falling edge */
				count = TIMER1_POINTER_TO_ICR1L + (65535 * TimerOverflow);	/* Take count */
				/* 8MHz Timer freq, sound speed =343 m/s */
				distance = (double)count / 466.47;

				CLCD_voidSendNumber(distance);

				dtostrf(distance, 2, 2, string);/* distance to string */
				strcat(string, " cm   ");	/* Concat unit i.e.cm */
				LCD_String_xy(2, 0, "Dist = ");
				LCD_String_xy(2, 7, string);	/* Print distance */
				_delay_ms(200);

	}
	return 0;
}

void ICU_HW(void)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}

