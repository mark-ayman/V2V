/*
 * ESP_int.h
 *
 *  Created on: Aug 30, 2023
 *      Author: admin
 */

#ifndef HAL_ESP_INT_H_
#define HAL_ESP_INT_H_
#include "../../MCAL/UART/UART_int.h"
typedef struct{
	u8 Name[50];
	u8 Password[50];
}HESP_RouterCfg_t;
typedef struct
{
	u8 Url[100];
	u8 LengthOfUrl[3];
	u8 Ip[20];
	u8 Port[5];
	u8 Mode[3];
}HESP_ServerCfg_t;

void HESP_vInit(USART_MemMap_t *USARTx);
void HESP_vConnectToAccesssPoint(USART_MemMap_t *USARTx );
void HESP_vOpenServerConnection(USART_MemMap_t *USARTx);
u8 HESP_u8GetHttpRequest(USART_MemMap_t *USARTx);
#endif /* HAL_ESP_INT_H_ */
