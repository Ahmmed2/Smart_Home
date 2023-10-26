/*
 * TWI_Program.c
 *
 * Created: 9/24/2023 11:02:52 AM
 *  Author: Ahmed
 */ 

#include "Std.h"


#include "TWI_Private.h"
#include "TWI_Config.h"
#include "TWI_Interface.h" 




void TWI_voidInitMaster (u8 Copy_u8Adress) 

{
	/* In Case you don't want to write Address to 
	the slave write any Number to Break If Condition */ 
	if (Copy_u8Adress < 128)
	{
		TWAR = Copy_u8Adress<<1 ;
	}
	
	/* CLK = 400KHZ "Max Clock In AVR " */ 
	/* Pre_Scaler Bits "00" */
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);
	TWBR = TWBR_VALUE ;
	
	//Enable ACK 
	SET_BIT(TWCR,TWEA) ;
	
	//Enable TWI 
	SET_BIT(TWCR,TWEN);	
}


/* If You Called this Function then this Node is Master */ 
void TWI_voidStartCondition (void) 
{
	//Request Start Condition 
	SET_BIT(TWCR,TWSTA);
	//Clear Flag "If not the Clock will be Zero " "Write 1 To Clear "
	SET_BIT(TWCR,TWINT);
	//Polling on the flag to make sure the Start Condition is Sent 
	while (GET_BIT(TWCR,TWINT) == 0) ;
	//To Make Sure That Start Condition Is Sent Correctly 
	while ( (TWI_STATUS_VALUE) != (TWI_START_CONDTION_ACK)) ;
}




void TWI_voidRepeatedStartCondition (void) 
{
	//Request Start Condition
	SET_BIT(TWCR,TWSTA);
	//Clear Flag "If not the Clock will be Zero " "Write 1 To Clear "
	SET_BIT(TWCR,TWINT);
	//Polling on the flag to make sure the Start Condition is Sent
	while (GET_BIT(TWCR,TWINT) == 0) ;
	//To Make Sure That Start Condition Is Sent Correctly
	while ( (TWI_STATUS_VALUE) != (TWI_REP_START_CONDTION_ACK)) ;
	
}


void TWI_voidStopCondition (void) 
{
	//Request Stop Condition
	SET_BIT(TWCR,TWSTO);
	//Clear Flag "If not the Clock will be Zero " "Write 1 To Clear "
	SET_BIT(TWCR,TWINT);
}


void TWI_voidSendSlaveAdressWithWrite (u8 Copy_u8SlaveAdress) 
{
	
	if (Copy_u8SlaveAdress < 128)
	{
		// Slave I want to Contact With 
		TWDR = Copy_u8SlaveAdress << 1 ;
		// Select Write Operation  
		CLR_BIT(TWDR,0) ;
		//Clear Start Condition
		CLR_BIT(TWCR,TWSTA) ;
		//Clear Flag "If not the Clock will be Zero " "Write 1 To Clear "
		SET_BIT(TWCR,TWINT);
		//Polling on the flag to make sure Slave Address is Sent
		while (GET_BIT(TWCR,TWINT) == 0) ;
		//To Make Sure That Slave Address Is Sent Correctly
		while ( (TWI_STATUS_VALUE) != (TWI_SLAVE_ADRESS_WRITE_ACK) ) ;
	}
	else 
	{
		// Do Nothing 
	}
}


void TWI_voidSendSlaveAdressWithRead(u8 Copy_u8SlaveAdress) 
{
	
	
	if (Copy_u8SlaveAdress < 128)
	{
		// Slave I want to Contact With
		TWDR = Copy_u8SlaveAdress << 1 ;
		// Select Read Operation
		SET_BIT(TWDR,0) ;
		//Clear Start Condition
		CLR_BIT(TWCR,TWSTA) ;
		//Clear Flag "If not the Clock will be Zero " "Write 1 To Clear "
		SET_BIT(TWCR,TWINT);
		//Polling on the flag to make sure the Slave Address is Sent
		while (GET_BIT(TWCR,TWINT) == 0) ;
		//To Make Sure That Slave Address Is Sent Correctly
		while ( (TWI_STATUS_VALUE) != (TWI_SLAVE_ADRESS_READ_ACK) ) ;
	}
	else
	{
		// Do Nothing
	}	
	
}



void TWI_voidSendMasterDataByte (u8 Copy_u8TxData) 
{
	// Load Data on the Register 
	TWDR = 	Copy_u8TxData ;
	//Clear Flag "If not the Clock will be Zero " "Write 1 To Clear "
	SET_BIT(TWCR,TWINT);
	//Polling on the flag to make sure the Data Sent Completely 
	while (GET_BIT(TWCR,TWINT) == 0) ;
	//To Make Sure That Master Send Data Correctly 
	while ( (TWI_STATUS_VALUE) != (TWI_MASTER_SEND_DATA_ACK) ) ;
	
}



u8 TWI_voidReceiveMasterDataByte (void) 
{
	//Clear Flag "If not the Clock will be Zero " "Write 1 To Clear "
	SET_BIT(TWCR,TWINT);
	//Polling on the flag to make sure the Data Rx Completely 
	while (GET_BIT(TWCR,TWINT) == 0) ;
	//To Make Sure That Master Receive Data Correctly 
	//while ((TWI_STATUS_VALUE) != (TWI_MASTER_RX_DATA_ACK) ) ;
	
	//Return the Data 
	return TWDR ;
	
}



void TWI_voidReadACK ()
{
	
	SET_BIT(TWCR,TWEA);
}

void TWI_voidReadNONACK ()
{
	
	CLR_BIT(TWCR,TWEA);
}