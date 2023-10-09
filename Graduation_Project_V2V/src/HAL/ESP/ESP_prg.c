/*
 * ESP_prg.c
 *
 *  Created on: Aug 30, 2023
 *      Author: admin
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/SYSTICK/STK_int.h"
#include "../../MCAL/NVIC/NVIC_int.h"
#include "ESP_int.h"
volatile u8 arr_1[200]={0};
volatile u32 counter=1 ;
extern HESP_RouterCfg_t  RouterInfo ;
extern HESP_ServerCfg_t  SurverInfo ;
u32 i=0;
extern USART_InitType uart1_cfg ;
u8 flag=0;
u8 Acknoladge(USART_MemMap_t *USARTx)
{
	u8 ack=0;
	for(i=0;i<200;i++)
	{
		if(flag==0)
		{
			flag=1;
			arr_1[i] = MUSART_u8ReceiveByteSynchBlocking(USARTx);
		}
		else arr_1[i] = MUSART_u8ReceiveByteSynchNonBlocking(USARTx);
		if(arr_1[5] =='D' && arr_1[6]=='I' && arr_1[7] =='S' && arr_1[8] =='C' && arr_1[9] =='O' && arr_1[10] =='N' && arr_1[11] =='N'
				&& arr_1[12] =='E'   && arr_1[13] =='C' && arr_1[14] =='T'  )
		{
			if(i<=16) flag=0;
		}//wifi connected
		if(arr_1[i] =='D' && arr_1[i-1]=='E' && arr_1[i-2] =='T' && arr_1[i-3] =='C' && arr_1[i-4]=='E' &&
				arr_1[i-5] =='N' && arr_1[i-6]=='N' && arr_1[i-7] =='O'
						&& arr_1[i-8] =='C' && arr_1[i-9] ==' ' && arr_1[i-10] =='I'
								&& arr_1[i-11] =='F' && arr_1[i-12] =='I'&& arr_1[i-13] =='W'  )//&& arr_1[12] =='E' &&  arr_1[13] =='D'
		{
			ack = 'W';//wifi connnect
//			break;
		}
		else if(arr_1[i] =='T' && arr_1[i-1]=='C' && arr_1[i-2] =='E' && arr_1[i-3] =='N' && arr_1[i-4] =='N' && arr_1[i-5] =='O'
				&&arr_1[i-6] =='C'   )//&& arr_1[12] =='E' &&  arr_1[13] =='D'
		{
			ack = 'C'; // server connect
		}
		else if(arr_1[i] =='K' && arr_1[i-1]=='O')
		{
			ack = 'O';
			//break;
		}
		else if(arr_1[i] =='D' && arr_1[i-1] == 'E'&& arr_1[i-2] == 'S'&& arr_1[i-3] == 'O'&& arr_1[i-4] == 'L'&& arr_1[i-5] == 'C')
		{
			counter = i-6;
			ack = 'D';
			break;
		}
	}
	//MUSART_vTransmitString(USART1,arr_1);
	flag=0;
	return ack ;
}
void HESP_vInit(USART_MemMap_t *USARTx)
{
	MUSART_vInit(&uart1_cfg,USARTx);
	/* interrupt enable */
	MUSART_vEnable(USARTx);
	/*disable echo*/
	do{
		MUSART_vTransmitString(USARTx,(u8*)"ATE1\r\n");
	}while(Acknoladge(USARTx) != 'O');
	do
	{
		MUSART_vTransmitString(USARTx,(u8*)"AT+CWMODE=1\r\n");
	}while(Acknoladge(USARTx) != 'O');

}
void HESP_vConnectToAccesssPoint(USART_MemMap_t *USARTx )
{
	do{
		MUSART_vTransmitString(USARTx,(u8*)"AT+CWJAP=\"");//AT+CWJAP_CUR="RouterInfo.Name","
		MUSART_vTransmitString(USARTx,RouterInfo.Name);
		MUSART_vTransmitString(USARTx,(u8*)"\",\"");
		MUSART_vTransmitString(USARTx,RouterInfo.Password);
		MUSART_vTransmitString(USARTx,(u8*)"\"\r\n");
	}while(Acknoladge(USARTx) != 'W');
}

//SurverInfo
void HESP_vOpenServerConnection(USART_MemMap_t *USARTx)
{
	do{
		MUSART_vTransmitString(USARTx,(u8*)"AT+CIPSTART=\"TCP\",\"");//AT+CIPSTART="TCP","
		MUSART_vTransmitString(USARTx,SurverInfo.Ip);
		MUSART_vTransmitString(USARTx,(u8*)"\",");
		MUSART_vTransmitString(USARTx,SurverInfo.Port);
		MUSART_vTransmitString(USARTx,(u8*)"\r\n");
	}while(Acknoladge(USARTx) != 'C');

}

u8 HESP_u8GetHttpRequest(USART_MemMap_t *USARTx)
{
	u8 L_u8Return = 0 ;
	do{
		HESP_vOpenServerConnection(USARTx);
		MUSART_vTransmitString(USARTx,(u8*)"AT+CIPSEND=");
		MUSART_vTransmitString(USARTx,SurverInfo.LengthOfUrl);
		MUSART_vTransmitString(USARTx,(u8*)"\r\n");
		MSTK_vSetBusyWait(1000);
		MUSART_vTransmitString(USARTx,SurverInfo.Url);
		MUSART_vTransmitString(USARTx,(u8*)"\r\n");
	}while(Acknoladge(USARTx) != 'D');
	L_u8Return = arr_1[counter] ;
	return L_u8Return;
}

