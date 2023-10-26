/*
 * TWI_Interface.h
 *
 * Created: 9/24/2023 11:03:06 AM
 *  Author: Ahmed
 */ 

/* All of This Functions is For Master Only */ 

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_


void TWI_voidInitMaster (u8 Copy_u8Adress) ;
void TWI_voidStartCondition (void) ;
void TWI_voidRepeatedStartCondition (void) ;
void TWI_voidStopCondition (void) ;
void TWI_voidSendSlaveAdressWithRead (u8 Copy_u8SlaveAdress) ;
void TWI_voidSendSlaveAdressWithWrite(u8 Copy_u8SlaveAdress) ;
void TWI_voidSendMasterDataByte (u8 Copy_u8TxData) ;
u8   TWI_voidReceiveMasterDataByte (void) ;


void TWI_voidReadACK () ;
void TWI_voidReadNONACK ();

#endif /* TWC_INTERFACE_H_ */