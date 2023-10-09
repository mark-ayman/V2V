#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/RCC/RCC_int.h"
#include "MCAL/UART/UART_int.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/SYSTICK/STK_int.h"
#include "MCAL/NVIC/NVIC_int.h"


extern USART_InitType uart2_cfg ;

void main(void)
{
	/*1- system clock ...MHZ from HSI */
	MRCC_vInit();
	/*2- Enable GPIO peripheral clock for port B , A */
	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOB);
	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOA);
	/*3- Enable USART2 peripheral clock */
	MRCC_vEnableClock(RCC_APB1,RCC_EN_UART2);
	/////////////////////////////////////////////////////
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN0,GPIO_MODE_INPUT);
	MGPIO_vSetPinInputPull(GPIO_PORTA,GPIO_PIN0,GPIO_INPUTTYPE_PU);

	/////////////////////////////////////////////////////
	/*4- Set Pin Mode For Pins 6 , 7 -> Alternative Function */
	MGPIO_vSetPinMode		     (GPIO_PORTA,GPIO_PIN3,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType		 (GPIO_PORTA,GPIO_PIN3,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed	 (GPIO_PORTA,GPIO_PIN3,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTA,GPIO_PIN3,7);
	///////////////////////////////////////////////////////////////////////
	MGPIO_vSetPinMode			 (GPIO_PORTA,GPIO_PIN2,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType		 (GPIO_PORTA,GPIO_PIN2,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed	 (GPIO_PORTA,GPIO_PIN2,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTA,GPIO_PIN2,7);
	////////////////////////////////////////////////////////////////////////
	/*5-MUSART Initialization*/
	uart2_cfg.BaudRate = 9600 ;
	MUSART_vInit(&uart2_cfg,USART2);
	/*6-Enable USARTx*/
	MUSART_vEnable(USART2);
	////////////////////////////////////////////////////////////////////////
	/*7- initialize SysTick*/
	//15s
	MSTK_vInit();
	//////////////////////////////////////////////////////////////////////
	u8 Button_status='A';
	while(1)
	{

		if(MGPIO_u8GetPinValue(GPIO_PORTA,GPIO_PIN0)==0)
		{
			Button_status='B';
		}
		else
		{
			Button_status='A';
		}
		MUSART_vTransmitByteSynch(USART2,Button_status);
	}
}
