#ifndef  SPI_CONFIG
#define  SPI_CONFIG



/* Node Type */ 
#define MASTER 0
#define SLAVE  1

/* Polling Or Interrupt */ 
#define POLLING		0 
#define INTERRUPT	1

/* Clock Polarity and Phase */ 
#define LEADING_RISING_LEADING_SAMPLE		0
#define LEADING_RISING_LEADING_SETUP		1
#define LEADING_FALLING_LEADING_SAMPLE		2
#define LEADING_FALLING_LEADING_SETUP		3

/* Pre_Scaler */
#define  DIV4				0
#define	 DIV16				1
#define	 DIV64				2
#define	 DIV128				3
#define	 DIV2				4
#define	 DIV8				5
#define	 DIV32				6

/* Which Bit Transfer First */ 
#define		LSB					0
#define		MSB					1



 

#endif