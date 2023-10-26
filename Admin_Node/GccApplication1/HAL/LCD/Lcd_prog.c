/*
 * Lcd_prog.c
 *
 * Created: 10/09/2023 09:08:02
 *  Author: Mostafa Maher
 */ 
#include "Lcd.h"


#define F_CPU 16000000UL
#include <util/delay.h>



/* HAL */
#include "Lcd.h"
#include "Lcd_piv.h"


void LCD_voidInit(void)
{
	 Dio_voidSetpinchmode(LCD_RS,OUTPUT_LOW);
	 Dio_voidSetpinchmode(LCD_E,OUTPUT_LOW);
		Dio_voidSetpinchmode(LCD_D4_PIN,OUTPUT_LOW);
		Dio_voidSetpinchmode(LCD_D5_PIN,OUTPUT_LOW);
		Dio_voidSetpinchmode(LCD_D6_PIN,OUTPUT_LOW);
		Dio_voidSetpinchmode(LCD_D7_PIN,OUTPUT_LOW);
	
	_delay_ms(35);

	// set Rs pin = 0 (write command)
	Dio_voidWritepinchannel(LCD_RS,PIN_LOW);
	private_voidWriteHalfPort(0b0010);
	/* Enable Pulse *//* H => L */
	Dio_voidWritepinchannel(LCD_E,PIN_HIGH);
	_delay_ms(1);
	Dio_voidWritepinchannel(LCD_E,PIN_LOW);
	LCD_voidSendCmnd(0b00101000);
	_delay_us(45);
	
	// Display on off Control (DisplayOn, Cursor on, Blink on)
	LCD_voidSendCmnd(0b00001111);
	_delay_us(45);
	
	// Clear Display
	LCD_voidSendCmnd(0b00000001);
	_delay_ms(2);
	
	// Set Entry Mode
	LCD_voidSendCmnd(0b00000110);
}


void LCD_voidSendCmnd(u8 copy_u8Cmnd)
{
	// set Rs pin = 0 (write command)
	Dio_voidWritepinchannel(LCD_RS,PIN_LOW);

	// Write The Most 4 bits Of command on Data Pins
	private_voidWriteHalfPort(copy_u8Cmnd>>4);
	
	/* Enable Pulse *//* H => L */
	Dio_voidWritepinchannel(LCD_E,PIN_HIGH);
	_delay_ms(1);
	Dio_voidWritepinchannel(LCD_E,PIN_LOW);
	_delay_ms(1);
	// Write The Least 4 bits Of command on Data Pins
	private_voidWriteHalfPort(copy_u8Cmnd);
	
	/* Enable Pulse *//* H => L */
	Dio_voidWritepinchannel(LCD_E,PIN_HIGH);
	_delay_ms(1);
	Dio_voidWritepinchannel(LCD_E,PIN_LOW);
	_delay_ms(1);
}


void LCD_voidSendChar(u8 copy_u8Data)
{
	// set Rs pin = 1 (write data)
	Dio_voidWritepinchannel(LCD_RS,PIN_HIGH);
	
	// Write The Most 4 bits Of data on Data Pins
	private_voidWriteHalfPort(copy_u8Data>>4);
	
	/* Enable Pulse *//* H => L */
	Dio_voidWritepinchannel(LCD_E,PIN_HIGH);
	_delay_ms(1);
	Dio_voidWritepinchannel(LCD_E,PIN_LOW);
	_delay_ms(1);
	// Write The Least 4 bits Of data on Data Pins
	private_voidWriteHalfPort(copy_u8Data);
	
	/* Enable Pulse *//* H => L */
	Dio_voidWritepinchannel(LCD_E,PIN_HIGH);
	_delay_ms(1);
	Dio_voidWritepinchannel(LCD_E,PIN_LOW);
	_delay_ms(1);
}


static void private_voidWriteHalfPort(u8 copy_u8Value)
{
	Dio_voidWritepinchannel(LCD_D4_PIN,GET_BIT(copy_u8Value,0));
	Dio_voidWritepinchannel(LCD_D5_PIN,GET_BIT(copy_u8Value,1));
	Dio_voidWritepinchannel(LCD_D6_PIN,GET_BIT(copy_u8Value,2));
	Dio_voidWritepinchannel(LCD_D7_PIN,GET_BIT(copy_u8Value,3));
}


void LCD_voidWriteString(u8* copy_pu8String)
{
	u8 Loc_u8Count=0;
	while(copy_pu8String[Loc_u8Count]!='\0')
	{
		LCD_voidSendChar(copy_pu8String[Loc_u8Count]);
		_delay_ms(1);
		Loc_u8Count++;
	}
}


void LCD_voidWriteNumber(u32 copy_u32Number)
{
	
	u8 ARR_Digits[10];
	u8 LOC_Count=0;
	if(copy_u32Number>0)
	{
		while(copy_u32Number!=0)
		{
			ARR_Digits[LOC_Count]=copy_u32Number%10;
			copy_u32Number/=10;
			LOC_Count++;
		}
		for (s8 i =LOC_Count-1;i>=0;i--)
		{
			LCD_voidSendChar(ARR_Digits[i]+'0');
			_delay_ms(1);
		}
		
	}
	else
	{
		LCD_voidSendChar('0');
	}
	
}

void LCD_voidClear(void)
{
	
	
	LCD_voidSendCmnd(DISPLAY_CLEAR);
	
}

void LCD_voidShift(u8 copy_u8ShifttingDirection)
{
	
	if(copy_u8ShifttingDirection==LCD_SHIFT_LEFT)
	{
		
		LCD_voidSendCmnd(Cursor_Shift_Left);
		_delay_ms(1);
	}
	else
	{
		
		LCD_voidSendCmnd(Cursor_Shift_Right);
		_delay_ms(1);
	}
	
}

void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position)
{
	if((copy_u8LineNumber==LCD_LINE_ONE)&&((copy_u8Position>=0)&&(copy_u8Position<16)))
	{
		
		LCD_voidSendCmnd((LINE1_OFFSET_ADDRESS+copy_u8Position));
	}
	else if((copy_u8LineNumber==LCD_LINE_TWO)&&((copy_u8Position>=0)&&(copy_u8Position<16)))
	{
		
		LCD_voidSendCmnd((LINE2_OFFSET_ADDRESS+copy_u8Position));
	}
	else if((copy_u8LineNumber==LCD_LINE_THREE)&&((copy_u8Position>=0)&&(copy_u8Position<16)))
	{
		
		LCD_voidSendCmnd((LINE3_OFFSET_ADDRESS+copy_u8Position));
	}
	else if((copy_u8LineNumber==LCD_LINE_FOUR)&&((copy_u8Position>=0)&&(copy_u8Position<16)))
	{
		
		LCD_voidSendCmnd((LINE4_OFFSET_ADDRESS+copy_u8Position));
	}
	else
	{	 
		/*Do Nothing*/
	}
	
}