/*
 * EEPROM_Interface.h
 *
 * Created: 9/25/2023 10:36:29 AM
 *  Author: Ahmed
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_voidInit() ; 
void EEPROM_voidWriteByte(u16 Copy_u16WordAddress , u8 Copy_u8Data) ;
u8 EEPROM_voidReadByte(u16 Copy_u16WordAddress) ;


void EEPROM_voidWritePage(u16 Copy_u16WordAddress , u8 Copy_u8Data[],u8 Copy_u8Size) ;
void EEPROM_voidReadPage(u16 Copy_u16WordAddress , u8 Copy_u8Data[],u8 Copy_u8Size) ;


u8 EEPROM_u8Search (u8 Copy_u8Pass[],u8 Copy_u8UsersNum) ;
void EEPROM_voidSendDataPage (u8 Copy_u8Index , u8 Copy_u8Oper[] ) ;

#endif /* EEPROM_INTERFACE_H_ */