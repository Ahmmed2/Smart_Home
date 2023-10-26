/*
 * Dio_prog.c
 *
 * Created: 08/09/2023 11:11:24
 *  Author: Mostafa Maher
 */ 

#include "Dio_int.h"




const Port_ConfigType Config_arr[32]={
	
	{ PA0,PA0_MOD  },
	{ PA1,PA1_MOD  },
	{ PA2,PA2_MOD  },
	{ PA3,PA3_MOD  },
	{ PA4,PA4_MOD  },
	{ PA5,PA5_MOD  },
	{ PA6,PA6_MOD  },
	{ PA7,PA7_MOD  },
	{ PB0,PB0_MOD  },
	{ PB1,PB1_MOD  },
	{ PB2,PB2_MOD  },
	{ PB3,PB3_MOD  },
	{ PB4,PB4_MOD  },
	{ PB5,PB5_MOD  },
	{ PB6,PB6_MOD  },
	{ PB7,PB7_MOD  },
	{ PC0,PC0_MOD  },
	{ PC1,PC1_MOD  },
	{ PC2,PC2_MOD  },
	{ PC3,PC3_MOD  },
	{ PC4,PC4_MOD  },
	{ PC5,PC5_MOD  },
	{ PC6,PC6_MOD  },
	{ PC7,PC7_MOD  },
	{ PD0,PD0_MOD  },
	{ PD1,PD1_MOD  },
	{ PD2,PD2_MOD  },
	{ PD3,PD3_MOD  },
	{ PD4,PD4_MOD  },
	{ PD5,PD5_MOD  },
	{ PD6,PD6_MOD  },
	{ PD7,PD7_MOD  }
	
};

volatile u8   *index_ddrr[4]={&DDRA,&DDRB,&DDRC,&DDRD};
volatile u8   *index_port[4]={&PORTA,&PORTB,&PORTC,&PORTD};
volatile u8   *index_pin[4] ={&PINA,&PINB,&PINC,&PIND};


void Dio_voidInit()
{

	for(u8 i=0;i<32;i++)
	{
		set_mod(Config_arr[i]);
	}
}


void set_mod(Port_ConfigType copy)
{
	
	u8 port_num = copy.port_pin_num/8;
	u8 pin_num = copy.port_pin_num%8;
	
	switch(copy.port_mode)
	{
		
		case INPUT :
			CLR_BIT(*index_ddrr[port_num],pin_num);
			break;
			
		case INPUT_PULLUP :
			CLR_BIT(*index_ddrr[port_num],pin_num);
			// activate the pull-up resistor
			*index_port[port_num] |= (1<<pin_num);
			break;
			
			case OUTPUT_HIGH :
			SET_BIT(*index_ddrr[port_num],pin_num);
			SET_BIT(*index_port[port_num],pin_num);
			break;
				
			case OUTPUT_LOW :
			SET_BIT(*index_ddrr[port_num],pin_num);
			break;	
			
	}
			
	
}


void Dio_voidSetpinchmode(Port_Pin copy_port_pin_num,Port_Mode copy_port_pin_Dir)
{
	
	u8 port_num = copy_port_pin_num/8;
	u8 pin_num = copy_port_pin_num%8;
	
	switch(copy_port_pin_Dir)
	{
		
		case INPUT :
		CLR_BIT(*index_ddrr[port_num],pin_num);
		break;
		
		case INPUT_PULLUP :
		CLR_BIT(*index_ddrr[port_num],pin_num);
		// activate the pull-up resistor
		*index_port[port_num] |= (1<<pin_num);
		break;
		
		case OUTPUT_HIGH :
		SET_BIT(*index_ddrr[port_num],pin_num);
		SET_BIT(*index_port[port_num],pin_num);
		break;
		
		case OUTPUT_LOW :
		SET_BIT(*index_ddrr[port_num],pin_num);
		break;
		
	}
	
	
}

void Dio_voidWritepinchannel(Port_Pin copy_port_pin_num,u8 copy_value)
{
	
	u8 port_num = copy_port_pin_num/8;
	u8 pin_num = copy_port_pin_num%8;
		if(copy_value==PIN_HIGH)
		{
			SET_BIT(*index_port[port_num],pin_num);
		}
		else
		{
			CLR_BIT(*index_port[port_num],pin_num);
		}

		
	
}	
		
void Dio_voidReadpinchannel(Port_Pin copy_port_pin_num,u8 * copy_value)
{
	
	u8 port_num = copy_port_pin_num/8;
	u8 pin_num = copy_port_pin_num%8;
	
		*copy_value = GET_BIT(*index_pin[port_num],pin_num);

	
	
}	

void Dio_readportchannel(u8 copy_port_num,u8 * copy_value)
{
	
	
	switch(copy_port_num)
	{
		
		case DIO_PORTA:
		
		*copy_value = PORTA;

		break;
		
		/*==============================================*/
		
		case  DIO_PORTB:
		*copy_value = PORTB;

		break;
		
		/*==================================================================*/
		
		case  DIO_PORTC:
		*copy_value = PORTC;
		
		break;
		
		/*====================================================*/
		
		case  DIO_PORTD:
		*copy_value = PORTD;
		break;
		
		
		
	}
	
	
}
	
void Dio_SETportchannel(u8 copy_port_num,u8  copy_value)
{
	
	switch(copy_port_num)
	{
		
		case DIO_PORTA:
		
		 PORTA=copy_value;

		break;
		
		/*==============================================*/
		
		case  DIO_PORTB:
		 PORTB=copy_value;

		break;
		
		/*==================================================================*/
		
		case  DIO_PORTC:
		 PORTC=copy_value;
		
		break;
		
		/*====================================================*/
		
		case  DIO_PORTD:
		 PORTD=copy_value;
		break;
		
		
		
	}
	
}


void Dio_setportchmode(u8 copy_port_num,u8 copy_port_Dir)
{
	if (copy_port_Dir==PIN_OUTPUT)
	{
		*index_ddrr[copy_port_num]=0xff;
	}
	else
	{
		*index_ddrr[copy_port_num]=0x00;
	}
}
