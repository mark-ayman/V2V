
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "Bluetooth_Config.h"
#include "Bluetooth_Interface.h"
#include "Bluetooth_Private.h"
volatile u8 arr_2[200]={0};
extern HBluetooth_Config_Data_t BluetoothInfo;
extern USART_InitType uart1_cfg ;

u8 Validate(USART_MemMap_t *USARTx)
{
	u8 ack=0;
	for(u8 i=0;i<200;i++)
	{
		if(arr_2[i] =='K' && arr_2[i-1]=='O')
		{
			ack = 'O';
			break;
		}
	}
	return ack ;
}

void HBluetooth_voidInit(USART_MemMap_t *USARTx)
{
    MUSART_vInit(&uart1_cfg,USARTx);
	/* interrupt enable */
	MUSART_vEnable(USARTx);
	/**********************/
	do{
		MUSART_vTransmitString(USARTx,(u8*)"AT\r\n");
	}while(Validate(USARTx) != 'O');

	#if HBluetooth_TYPE==HBluetooth_HC05_
	do
	{
	MUSART_vTransmitString(USARTx,(u8*)"AT+CMODE=1\r\n");
	}while(Validate(USARTx) != 'O');
	#elif  HBluetooth_TYPE==HBluetooth_HC06_

	#endif
	/**********************************/
	/************Baud Rate************/
	do
	{
	MUSART_vTransmitString(USARTx,(u8*)"AT+UART=");
	MUSART_vTransmitString(USARTx,(u8*)BluetoothInfo.BaudRate);
	MUSART_vTransmitString(USARTx,(u8*)"\r\n");
	}while(Validate(USARTx) != 'O');

}

void HBluetooth_voidSetMaster(USART_MemMap_t *USARTx)
{
	//"AT+ROLE=1"
	do
	{
	MUSART_vTransmitString(USARTx,(u8*)"AT+ROLE=1\r\n");
	}while(Validate(USARTx) != 'O');

}

void HBluetooth_voidSetSlave(USART_MemMap_t *USARTx)
{
	//"AT+ROLE=0"
	do
	{
	MUSART_vTransmitString(USARTx,(u8*)"AT+ROLE=0\r\n");
	}while(Validate(USARTx) != 'O');
}

void HBluetooth_voidSet_SlaveAddress(USART_MemMap_t *USARTx)
{
	do
	{
	MUSART_vTransmitString(USARTx,(u8*)"AT+UART=");
	MUSART_vTransmitString(USARTx,(u8*)BluetoothInfo.BaudRate);
	MUSART_vTransmitString(USARTx,(u8*)"\r\n");
	}while(Validate(USARTx) != 'O');
}

void HBluetooth_voidSetMaster_Name(USART_MemMap_t *USARTx)
{

}

void HBluetooth_voidSetSlave_Name(USART_MemMap_t *USARTx)
{

}
