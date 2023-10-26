/*
 * TWI_Private.h
 *
 * Created: 9/24/2023 11:03:52 AM
 *  Author: Ahmed
 */ 


#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define TWBR   *((volatile u8*) 0x20)
///////////////////////////////////////////
#define TWSR   *((volatile u8*) 0x21)
#define TWPS0        0
#define TWPS1        1
///////////////////////////////////////////
#define TWAR   *((volatile u8*) 0x22)
#define TWGCE        0
///////////////////////////////////////////
#define TWDR   *((volatile u8*) 0x23)
///////////////////////////////////////////
#define TWCR   *((volatile u8*) 0x56)
#define TWIE         0
#define TWEN         2
#define TWWC         3
#define TWSTO        4
#define TWSTA        5
#define TWEA         6
#define TWINT        7
//////////////////////////////////////////




#define TWI_STATUS_VALUE	(TWSR&0xF8)
#define TWBR_VALUE			12 

// Status 
#define TWI_START_CONDTION_ACK					0X08
#define TWI_REP_START_CONDTION_ACK				0x10
#define TWI_SLAVE_ADRESS_WRITE_ACK				0x18
#define TWI_SLAVE_ADRESS_READ_ACK				0X40
#define TWI_MASTER_SEND_DATA_ACK				0x28
#define TWI_MASTER_RX_DATA_ACK					0x50


#endif /* TWC_PRIVATE_H_ */