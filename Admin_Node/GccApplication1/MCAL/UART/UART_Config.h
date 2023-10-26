
/*
 * UART_Config.h
 *
 * Created: 22/09/2023 12:04:41
 *  Author: Mostafa Maher
 */ 

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*UART Mode Options:
 * 1- UART_ASYNCHRONOUS_MODE
 * 2- UART_SYNCHRONOUS_MODE
 */
#define UART_SET_MODE			UART_ASYNCHRONOUS_MODE

/*UART Parity Mode Options:
 * 1- UART_DISABLED_PARITY
 * 2- UART_EVEN_PARITY
 * 3- UART_ODD_PARITY
 */
#define UART_SET_PARITY_MODE     UART_DISABLED_PARITY

/*UART Stop Bit Number Options:
 * 1- UART_STOP_ONE_BIT
 * 2- UART_STOP_TWO_BIT
 */
#define UART_SET_STOP_BIT			UART_STOP_ONE_BIT

/*UART Char Size Options:
 * 1- UART_CHR_SIZE_5
 * 2- UART_CHR_SIZE_6
 * 3- UART_CHR_SIZE_7
 * 4- UART_CHR_SIZE_8
 * 5- UART_CHR_SIZE_9
 */
#define UART_SET_CHR_SIZE			UART_CHR_SIZE_8

/*UART Interrupt Enable:
 * 1- UART_Enable_Interrupt
 * 2- UART_Disable_Interrupt
 */
#define UART_Interrupt_Enable			UART_Disable_Interrupt

#endif