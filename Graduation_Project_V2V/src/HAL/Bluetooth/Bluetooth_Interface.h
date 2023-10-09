#ifndef HAL_Bluetooth_Bluetooth_INTERFACE_H_
#define HAL_Bluetooth_Bluetooth_INTERFACE_H_


#include "../../MCAL/UART/UART_int.h"


#define HBluetooth_Master 1   
#define HBluetooth_Slave  0   

#define HBluetooth_HC05_  1
#define HBluetooth_HC06_  0

typedef enum 
{
    HBL_BR_1200=1       ,
    HBL_BR_2400         ,
    HBL_BR_4800         ,
    HBL_BR_9600         ,
    HBL_BR_19200        ,
    HBL_BR_38400        ,
    HBL_BR_57600        ,
    HBL_BR_115200       ,
}HBluetooth_BaudRate;



typedef struct 
{
    u8  Bluetooth_Name[50];
    //HBluetooth_BaudRate BaudRate;
    u8 BaudRate [10];
    u8 Address  [50];

}HBluetooth_Config_Data_t;


void HBluetooth_voidInit(USART_MemMap_t *USARTx);
void HBluetooth_voidSetMaster(USART_MemMap_t *USARTx);
void HBluetooth_voidSetSlave(USART_MemMap_t *USARTx);
void HBluetooth_voidGet_SlaveAddress(USART_MemMap_t *USARTx);
void HBluetooth_voidSetMaster_Name(USART_MemMap_t *USARTx);
void HBluetooth_voidSetSlave_Name(USART_MemMap_t *USARTx);

#endif
