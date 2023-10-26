#ifndef  SPI_INTERFACE
#define  SPI_INTERFACE



#define NODE_TYPE						MASTER 
#define NODE_MODE						POLLING
#define NODE_CLOCK_POLARITY_PHASE		LEADING_RISING_LEADING_SETUP
#define NODE_PRE_SCALER					DIV64
#define NODE_BIT_SEND					LSB


// Choose Master or Slave
void SPI_voidInialize();

void SPI_voidTransmiter(u8 Copy_u8Data) ;

u8 SPI_u8Receiver(void) ; 

void SPI_SetCallBack(void(*ptr)(void)) ;


#endif