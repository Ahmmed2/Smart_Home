
/*
 * UART_Program.c
 *
 * Created: 22/09/2023 14:20:50
 *  Author: Mostafa Maher
 */ 
 
#include "Std.h"
#include "UART_Private.h"
#include "UART_Interface.h"
 
 void (*UART_CallBack)(void);
 
 /*UART Initialization*/
 void UART_VidInit(void)
 {
	 u8 LOC_u8Copy_UCSRC=0;
	 /*Select UART Mode*/
	 #if UART_SET_MODE==UART_ASYNCHRONOUS_MODE
	 CLR_BIT(LOC_u8Copy_UCSRC,6);
	 #elif UART_SET_MODE==UART_SYNCHRONOUS_MODE
	 SET_BIT(LOC_u8Copy_UCSRC,6);
	 #else
	 #error "UART Mode Is not valid..."
	 #endif
		 /*Parity Mode*/
		 #if UART_SET_PARITY_MODE==UART_DISABLED_PARITY
		 CLR_BIT(LOC_u8Copy_UCSRC,5);
		 CLR_BIT(LOC_u8Copy_UCSRC,4);
		 #elif UART_SET_PARITY_MODE==UART_EVEN_PARITY
		 SET_BIT(LOC_u8Copy_UCSRC,5);
		 CLR_BIT(LOC_u8Copy_UCSRC,4);
		 #elif UART_SET_PARITY_MODE==UART_ODD_PARITY
		 SET_BIT(LOC_u8Copy_UCSRC,5);
		 SET_BIT(LOC_u8Copy_UCSRC,4);
		 #else
		 #error "UART Parity Mode Is not valid..."
		 #endif
	 /*Select Stop Bit*/
	 #if UART_SET_STOP_BIT==UART_STOP_ONE_BIT
	 CLR_BIT(LOC_u8Copy_UCSRC,3);
	 #elif UART_SET_STOP_BIT==UART_STOP_TWO_BIT
	 SET_BIT(LOC_u8Copy_UCSRC,3);
	 #else
	 #error "UART Stop Bit Number Is not valid..."
	 #endif
	 /*Select Char Size */
		 #if UART_SET_CHR_SIZE==UART_CHR_SIZE_5
		 CLR_BIT(LOC_u8Copy_UCSRC,2);
		 CLR_BIT(LOC_u8Copy_UCSRC,1);
		 CLR_BIT(UCSRB,2);
		 #elif UART_SET_CHR_SIZE==UART_CHR_SIZE_6
		 CLR_BIT(LOC_u8Copy_UCSRC,2);
		 SET_BIT(LOC_u8Copy_UCSRC,1);
		 CLR_BIT(UCSRB,2);
		 #elif UART_SET_CHR_SIZE==UART_CHR_SIZE_7
		 SET_BIT(LOC_u8Copy_UCSRC,2);
		 CLR_BIT(LOC_u8Copy_UCSRC,1);
		 CLR_BIT(UCSRB,2);
		 #elif UART_SET_CHR_SIZE==UART_CHR_SIZE_8
		 SET_BIT(LOC_u8Copy_UCSRC,2);
		 SET_BIT(LOC_u8Copy_UCSRC,1);
		 CLR_BIT(UCSRB,2);
		 #elif UART_SET_CHR_SIZE==UART_CHR_SIZE_9
		 SET_BIT(LOC_u8Copy_UCSRC,2);
		 SET_BIT(LOC_u8Copy_UCSRC,1);
		 SET_BIT(UCSRB,2);
		 #else
		 #error "UART CHR SIZE Is not valid..."
		 #endif
		    /*Interrupt Mode*/
			#if UART_Interrupt_Enable==UART_Enable_Interrupt
			SET_BIT(UCSRB,7);
			SET_BIT(UCSRB,6);
			#elif UART_Interrupt_Enable==UART_Disable_Interrupt
			CLR_BIT(UCSRB,7);
			CLR_BIT(UCSRB,6);
			#else
			#error "UART Interrupt Mode Is not valid..."
			#endif
	 /*Set LOC_u8Copy_UCSRC Value in UCSRC Register and select UCSRC Register*/
	 SET_BIT(LOC_u8Copy_UCSRC,7);
	 UCSRC=LOC_u8Copy_UCSRC;
	 /*Set BuadRate -->9600*/
	 UBRRL=103;
	 /*Enable To TX and RX*/
	 SET_BIT(UCSRB,4);
	 SET_BIT(UCSRB,3);
 }
 /*UART Send Data*/
 void UART_VidSendChar(u8 Copy_u8Data)
 {
	 /*Wait until Register Empty Flag is set*/
	 while(GET_BIT(UCSRA,5)==0);
	 UDR=Copy_u8Data;
 }
 /*UART Receive Data*/
 u8 UART_u8ReceiveData(void)
 {
	 /*Wait until Receive Complete Flag is set*/
	 while(GET_BIT(UCSRA,7)==0);
	 return UDR;
 }
 void UART_VidSendString(u8 *Copy_u8Data)
 {
	 u8 LOC_CharCount=0;
	 while(Copy_u8Data[LOC_CharCount]!=NULL)
	 {
		 UART_VidSendChar(Copy_u8Data[LOC_CharCount]);
		 LOC_CharCount++;
	 }
 }
 u8 UART_VidReceiveString(u8 *Copy_u8Data )
 {
	 u8 LOC_CharCount=0;

	 do
	 {
		 Copy_u8Data[LOC_CharCount] = UART_u8ReceiveData() ;
		 LOC_CharCount ++ ;
	 }while (Copy_u8Data[LOC_CharCount-1]!='-') ;
	 return LOC_CharCount ;
 }
 /*Interrupt Functions*/
 void UATR_VidRX_SetCallBack(void(*Copy_VidCallBack)(void))
 {
	 UART_CallBack=Copy_VidCallBack;
 }
 
 void UATR_VidTX_SetCallBack(void(*Copy_VidCallBack)(void))
 {
	 UART_CallBack=Copy_VidCallBack;
 }
 
 void ISR_UART_TXc(void)   __attribute__((signal));
 void ISR_UART_TXc(void)
 {
	 UART_CallBack();
 }
 
  void __vector_15(void)   __attribute__((signal));
  void __vector_15(void)
  {
	  UART_CallBack();
  }