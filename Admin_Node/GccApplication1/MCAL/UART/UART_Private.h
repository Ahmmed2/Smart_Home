
/*
 * UART_Private.h
 *
 * Created: 22/09/2023 12:02:28
 *  Author: Mostafa Maher
 */ 
#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR        *((volatile u8*)0x2C)
#define UCSRA      *((volatile u8*)0x2B)
#define UCSRB      *((volatile u8*)0x2A)
#define UCSRC      *((volatile u8*)0x40)
#define UBRRL      *((volatile u8*)0x29)
#define UBRRH      *((volatile u8*)0x40)

#define UART_ASYNCHRONOUS_MODE   0
#define UART_SYNCHRONOUS_MODE    1

#define UART_DISABLED_PARITY     0
#define UART_EVEN_PARITY         1
#define UART_ODD_PARITY          2

#define UART_CHR_SIZE_5      5
#define UART_CHR_SIZE_6      6
#define UART_CHR_SIZE_7      7
#define UART_CHR_SIZE_8      8
#define UART_CHR_SIZE_9      9


#define UART_STOP_ONE_BIT  1
#define UART_STOP_TWO_BIT  2

#define UART_Enable_Interrupt  1
#define UART_Disable_Interrupt  2


#endif 
