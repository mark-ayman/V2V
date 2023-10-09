#include "Bluetooth_Config.h"
#include "Bluetooth_Interface.h"
#include "Bluetooth_Private.h"


void HBluetooth_voidInit(USART_MemMap_t *USARTx)
{
    MUSART_vInit(&uart1_cfg,USARTx);
	/* interrupt enable */
	MUSART_vEnable(USARTx);
    
}

void HBluetooth_voidSetMaster(USART_MemMap_t *USARTx)
{

}

void HBluetooth_voidSetSlave(USART_MemMap_t *USARTx)
{

}

void HBluetooth_voidGet_SlaveAddress(USART_MemMap_t *USARTx,u8 * Local_u8Return_SlaveAddress)
{

}

void HBluetooth_voidSetMaster_Name(USART_MemMap_t *USARTx)
{

}

void HBluetooth_voidSetSlave_Name(USART_MemMap_t *USARTx)
{

}