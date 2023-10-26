/*
 * EEPROM_Program.c
 *
 * Created: 9/25/2023 10:37:16 AM
 *  Author: Ahmed
 */ 


#include "Std.h"


#include "TWI_Config.h"
#include "TWI_Interface.h"


#include "EEPROM_Private.h"
#include "EEPROM_Config.h"
#include "EEPROM_Interface.h"

#include "Lcd.h"

void EEPROM_voidInit() 
{
	// Skip Master Address 
	TWI_voidInitMaster (0xFF) ; 
}


void EEPROM_voidWriteByte(u16 Copy_u16WordAddress , u8 Copy_u8Data ) 
{
	// Hex 50 ---> 0b01010000  , MSB is don't Care 
	u8 Local_u8Temp = (EEPROM_CHIP_ADDRESS) | (Copy_u16WordAddress>>8) ;
	/* Frame Sequence */
	// Send Start Condition
	TWI_voidStartCondition () ;
	// Send Slave Address
	TWI_voidSendSlaveAdressWithWrite(Local_u8Temp) ;
	// Send Word Address
	TWI_voidSendMasterDataByte((u8)Copy_u16WordAddress) ;
	// Send Byte Data 
	TWI_voidSendMasterDataByte(Copy_u8Data) ;
	// Send Stop Condition 
	TWI_voidStopCondition() ;
	/* Self Time Delay */ 
	_delay_ms(8) ;
		
}

u8 EEPROM_voidReadByte(u16 Copy_u16WordAddress) 
{
	u8 Local_u8RxValue ;
	
	// Hex 50 ---> 0b01010000  , MSB is don't Care
	u8 Local_u8Temp = (EEPROM_CHIP_ADDRESS) | (Copy_u16WordAddress>>8) ;
	/* Frame Sequence */
	// Send Start Condition
	TWI_voidStartCondition () ;
	// Send Slave Address with Write 
	TWI_voidSendSlaveAdressWithWrite(Local_u8Temp) ;
	// Send Word Address
	TWI_voidSendMasterDataByte((u8)Copy_u16WordAddress) ;
	//Repeated Start 
	TWI_voidRepeatedStartCondition() ;
	//Send Slave Address with read
	TWI_voidSendSlaveAdressWithRead(Local_u8Temp) ;
	//Receive Data 
	Local_u8RxValue = TWI_voidReceiveMasterDataByte () ;
	//Send Stop Condition
	TWI_voidStopCondition() ;
	/* Self Time Delay */
	_delay_ms(8) ;
	

	return Local_u8RxValue ;
	
}


void EEPROM_voidWritePage(u16 Copy_u16WordAddress , u8 Copy_u8Data[],u8 Copy_u8Size)
{
	// Hex 50 ---> 0b01010000  , MSB is don't Care
	u8 Local_u8Temp = (EEPROM_CHIP_ADDRESS) | (Copy_u16WordAddress>>8) ;
	/* Frame Sequence */
	// Send Start Condition
	TWI_voidStartCondition () ;
	// Send Slave Address
	TWI_voidSendSlaveAdressWithWrite(Local_u8Temp) ;
	// Send Word Address
	TWI_voidSendMasterDataByte((u8)Copy_u16WordAddress) ;
	
	for (u8 Local_u8LoopCounter = 0 ;Local_u8LoopCounter<Copy_u8Size ;Local_u8LoopCounter++ )
	{
		
		// Send Byte Data
		TWI_voidSendMasterDataByte(Copy_u8Data[Local_u8LoopCounter]) ;
		
	}

	// Send Stop Condition
	TWI_voidStopCondition() ;
	
	/* Self Time Delay */
	_delay_ms(10) ;
	
	

	
}

void EEPROM_voidReadPage(u16 Copy_u16WordAddress , u8 Copy_u8Data[],u8 Copy_u8Size)
{
		// Hex 50 ---> 0b01010000  , MSB is don't Care
		u8 Local_u8Temp = (EEPROM_CHIP_ADDRESS) | (Copy_u16WordAddress>>8) ;
		/* Frame Sequence */
		// Send Start Condition
		TWI_voidStartCondition () ;
		// Send Slave Address with Read
		TWI_voidSendSlaveAdressWithWrite(Local_u8Temp) ;
		// Send Word Address
		TWI_voidSendMasterDataByte((u8)Copy_u16WordAddress) ;
		//Repeated Start
		TWI_voidRepeatedStartCondition() ;
		//Send Slave Address with read
		TWI_voidSendSlaveAdressWithRead(Local_u8Temp) ;
		
	for (u8 Local_u8LoopCounter = 0 ;Local_u8LoopCounter<Copy_u8Size ;Local_u8LoopCounter++ )
	{
		if (Local_u8LoopCounter == Copy_u8Size-1 )
		{
			TWI_voidReadNONACK() ;
		}
		//Receive Data
		Copy_u8Data[Local_u8LoopCounter] = TWI_voidReceiveMasterDataByte () ;
	}
		_delay_ms(10);
	
		//Send Stop Condition
		TWI_voidStopCondition() ;
		/* Self Time Delay */
		_delay_ms(10) ;
		
		TWI_voidReadACK() ;
	
}


u8 EEPROM_u8Search (u8 Copy_u8Pass[] , u8 Copy_u8UsersNum)
{
	
	u8 Local_u8Counter1, Local_u8Counter2 , Local_u8ReturnValue ;
	u8 Local_u8CompareFlag = 0 ;
	u8 EEPROM_Pass[4] ;
	

	for (Local_u8Counter1 = 0 ; Local_u8Counter1 < Copy_u8UsersNum ; Local_u8Counter1++ )
	{
		Local_u8CompareFlag = 0 ;
		EEPROM_voidReadPage ( ((0x0000 + Local_u8Counter1*4)) , EEPROM_Pass ,3 ) ;
		
		for (Local_u8Counter2 = 0 ; Local_u8Counter2 < 3 ; Local_u8Counter2 ++)
		{
			if (Copy_u8Pass[Local_u8Counter2] == EEPROM_Pass [Local_u8Counter2])
			{
				Local_u8CompareFlag ++ ;
			}
			else   break ;


			
		}
	 if (Local_u8CompareFlag == 3)
	 {

		 break ;
	 }

}		

		

		
	if (Local_u8CompareFlag == 3)
	{

		Local_u8ReturnValue = Local_u8Counter1; 

	}
	else Local_u8ReturnValue = 250 ;



	 
	return Local_u8ReturnValue ;
	
}

void EEPROM_voidSendDataPage (u8 Copy_u8Index , u8 Copy_u8Oper[] ) 
{

	EEPROM_voidWritePage((0X0000+(Copy_u8Index*4)) , Copy_u8Oper,3) ;
}