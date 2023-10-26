
/*
 * Dio_int.h
 *
 * Created: 08/09/2023 11:10:01
 *  Author: Mostafa Maher
 */ 

#ifndef DIO_INT_H_
#define DIO_INT_H_

#include "Std.h"
#include "Dio_cfg.h"
#include "Dio_prv.h"


#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

#define PIN_HIGH    1
#define PIN_LOW     0


#define	PIN0    0
#define	PIN1    1
#define	PIN2    2
#define	PIN3    3
#define	PIN4    4
#define	PIN5    5
#define	PIN6    6
#define	PIN7    7

typedef enum
{
	PA0=0,
	PA1,
	PA2,
	PA3,
	PA4,
	PA5,
	PA6,
	PA7,
	PB0,
	PB1,
	PB2,
	PB3,
	PB4,
	PB5,
	PB6,
	PB7,
	PC0,
	PC1,
	PC2,
	PC3,
	PC4,
	PC5,
	PC6,
	PC7,
	PD0,
	PD1,
	PD2,
	PD3,
	PD4,
	PD5,
	PD6,
	PD7,
	
	
}Port_Pin;



typedef enum
{
	PIN_OUTPUT=0,
	PIN_INPUT
}Port_PinDirection;


typedef enum
{
	INPUT_PULLUP=0,
	  INPUT ,
	   OUTPUT_HIGH,
	   OUTPUT_LOW
}Port_Mode;

typedef struct
{
	Port_Pin port_pin_num; 
	Port_Mode port_mode;
}Port_ConfigType;




/*Initial Function */
void Dio_voidInit();
/*Set Pin Direction Function */
void Dio_voidSetpinchmode(Port_Pin copy_port_pin_num,Port_Mode copy_port_pin_Dir);
/*Set Pin Value Function */
void Dio_voidWritepinchannel(Port_Pin copy_port_pin_num,u8 copy_value);
/*Get Pin Value Function */
void Dio_voidReadpinchannel(Port_Pin copy_port_pin_num,u8 * copy_value);
/*Get PORT Value Function */
void Dio_readportchannel(u8 copy_port_num,u8 * copy_value);
/*SET PORT Value Function */
void Dio_SETportchannel(u8 copy_port_num,u8  copy_value);
/*Set Port Direction Function */
void Dio_setportchmode(u8 copy_port_num,u8 copy_port_pin_Dir);

void set_mod(Port_ConfigType copy);


#endif /* DIO_INT_H_ */