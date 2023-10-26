
#include "Std.h"


#include "SPI_Private.h"
#include "SPI_Config.h"
#include "SPI_Interface.h"



void (*SPI_GPTR)(void)	;


void SPI_voidInialize()
{
	
#if NODE_MODE == POLLING 
	CLR_BIT(SPCR,7);
	
#elif NODE_MODE == INTERRUPT 
	SET_BIT(SPCR,7);	
#endif
//////////////////////////////////////
	
#if NODE_BIT_SEND == LSB
	SET_BIT(SPCR,5);

#elif NODE_BIT_SEND == MSB
	CLR_BIT(SPCR,7);
#endif
/////////////////////////////////////

#if NODE_TYPE == MASTER 
	SET_BIT(SPCR,4);
#elif NODE_TYPE == SLAVE
	CLR_BIT(SPCR,4);
#endif 
/////////////////////////////////////	

#if NODE_CLOCK_POLARITY_PHASE == LEADING_RISING_LEADING_SAMPLE
	CLR_BIT(SPCR,3);
	CLR_BIT(SPCR,2);	
#elif NODE_CLOCK_POLARITY_PHASE == LEADING_RISING_LEADING_SETUP		
	CLR_BIT(SPCR,3);
	SET_BIT(SPCR,2);
#elif NODE_CLOCK_POLARITY_PHASE == LEADING_FALLING_LEADING_SAMPLE	
	SET_BIT(SPCR,3);
	CLR_BIT(SPCR,2);
#elif NODE_CLOCK_POLARITY_PHASE == LEADING_FALLING_LEADING_SETUP	
	SET_BIT(SPCR,3);
	SET_BIT(SPCR,2);
#endif	
/////////////////////////////////////////

#if NODE_PRE_SCALER == DIV4 		
	CLR_BIT(SPCR,0);
	CLR_BIT(SPCR,1);
	CLR_BIT(SPSR,0);
#elif NODE_PRE_SCALER == DIV16
	SET_BIT(SPCR,0);
	CLR_BIT(SPCR,1);
	CLR_BIT(SPSR,0);
#elif NODE_PRE_SCALER == DIV64
	CLR_BIT(SPCR,0);
	SET_BIT(SPCR,1);
	CLR_BIT(SPSR,0);	
	
#elif NODE_PRE_SCALER == DIV128
	SET_BIT(SPCR,0);
	SET_BIT(SPCR,1);
	CLR_BIT(SPSR,0);	
	
#elif NODE_PRE_SCALER == DIV2
	CLR_BIT(SPCR,0);
	CLR_BIT(SPCR,1);
	SET_BIT(SPSR,0);

#elif NODE_PRE_SCALER == DIV8
	SET_BIT(SPCR,0);
	CLR_BIT(SPCR,1);
	SET_BIT(SPSR,0);

#elif NODE_PRE_SCALER == DIV32
	CLR_BIT(SPCR,0);
	SET_BIT(SPCR,1);
	SET_BIT(SPSR,0);
	
#elif NODE_PRE_SCALER == DIV64
	SET_BIT(SPCR,0);
	SET_BIT(SPCR,1);
	SET_BIT(SPSR,0);
	
#endif
////////////////////////////////////////// 
	
	//SPI Enable
	SET_BIT(SPCR,6);
	

}




void SPI_voidTransmiter(u8 Copy_u8Data)
{
#if NODE_MODE == POLLING
	SPDR = Copy_u8Data ;
	while(GET_BIT(SPSR,7)==0);

	
#elif NODE_MODE == INTERRUPT
	SPDR = Copy_u8Data ;

#endif 


}

u8 SPI_u8Receiver(void)
{
		while(GET_BIT(SPSR,7)==0);
		return SPDR ;
	
}

///////////////////////////////////////////////////////////////

void __vector_12()__attribute__((signal));
void __vector_12()
{
	SPI_GPTR();

}


/* Call Back */

/* SPI Interrupt Call Back  */
void SPI_SetCallBack(void(*ptr)(void))
{
	SPI_GPTR=ptr;
} 