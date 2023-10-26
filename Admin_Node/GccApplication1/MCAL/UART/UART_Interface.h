
/*
 * UART_Interface.h
 *
 * Created: 22/09/2023 14:18:53
 *  Author: Mostafa Maher
 */ 

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


 #include "UART_Config.h"
 
 
 #define ISR_UART_TXc(void)  __vector_13(void)
 
/*UART Initialization*/
void UART_VidInit(void);
/*UART Send Data*/
void UART_VidSendChar(u8 Copy_u8Data);
/*UART Receive Data*/
u8 UART_u8ReceiveData(void);

void UART_VidSendString(u8 *Copy_u8Data);
 u8 UART_VidReceiveString(u8 *Copy_u8Data );


void UATR_VidRX_SetCallBack(void(*Copy_VidCallBack)(void));


void UATR_VidTX_SetCallBack(void(*Copy_VidCallBack)(void));


#define UDR        *((volatile u8*)0x2C)
#endif