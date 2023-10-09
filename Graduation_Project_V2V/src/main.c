#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"

#include "MCAL/RCC/RCC_int.h"
#include "MCAL/UART/UART_int.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/SYSTICK/STK_int.h"
#include "MCAL/NVIC/NVIC_int.h"
#include "HAL/Bluetooth/Bluetooth_Interface.h"
u8 Flag=1;

void main(void)
{
	/*1- system clock 16MHZ from HSI */
	MRCC_vInit();
	/*2- Enable GPIO peripheral clock for port B */
	MRCC_vEnableClock(RCC_AHB1,RCC_EN_GPIOB);
	/*3- Enable USART2 peripheral clock */
	MRCC_vEnableClock(RCC_APB2,RCC_EN_UART1);
	/////////////////////////////////////////////////////
	MGPIO_vSetPinMode(GPIO_PORTA,GPIO_PIN0,GPIO_MODE_OUTPUT);
	MGPIO_vSetPinOutputType(GPIO_PORTA,GPIO_PIN0,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTA,GPIO_PIN0,GPIO_OUTSPEED_LOW);
	/////////////////////////////////////////////////////
	/*4- Set Pin Mode For Pins 6 , 7 -> Alternative Function */
	MGPIO_vSetPinMode(GPIO_PORTB,GPIO_PIN6,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType(GPIO_PORTB,GPIO_PIN6,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTB,GPIO_PIN6,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTB,GPIO_PIN6,7);
	///////////////////////////////////////////////////////////////////////
	MGPIO_vSetPinMode(GPIO_PORTB,GPIO_PIN7,GPIO_MODE_ALTFUN);
	MGPIO_vSetPinOutputType(GPIO_PORTB,GPIO_PIN7,GPIO_OUTPUTTYPE_PUSHPULL);
	MGPIO_vSetPinOutputSpeed(GPIO_PORTB,GPIO_PIN7,GPIO_OUTSPEED_LOW);
	MGPIO_vSetAlternativeFunction(GPIO_PORTB,GPIO_PIN7,7);
	////////////////////////////////////////////////////////////////////////
//	/*5-MUSART Initialization*/
//	uart2_cfg.BaudRate = 115200 ;
//	MUSART_vInit(&uart2_cfg,USART2);
//	/*6-Enable USARTx*/
//	MUSART_vEnable(USART2);
	////////////////////////////////////////////////////////////////////////
	/*7- initialize SysTick*/
	//15s
//	MSTK_vInit();
	//////////////////////////////////////////////////////////////////////
HBluetooth_voidInit(USART1);
HBluetooth_voidSetMaster(USART1);
	while(1)
	{


	}
}
