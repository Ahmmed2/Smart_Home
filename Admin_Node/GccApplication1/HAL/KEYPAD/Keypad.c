/*
 * Keypad.c
 *
 * Created: 09/09/2023 11:30:06
 *  Author: Mostafa Maher
 */ 

#include "Keypad.h" 


u8 ROW_PIN [4]={ROW_PIN0,ROW_PIN1,ROW_PIN2,ROW_PIN3}; 
u8 COL_PIN [4]={COL_PIN0,COL_PIN1,COL_PIN2,COL_PIN3}; 

const u8 KPD_u8SwitchVal[4][4]=
{
		{'1','2','3','-'},
		{'4','5','6','+'},
		{'7','8','9','-'},
		{'=','0','c','/'}
};
/*KPD INIT*/
void Keypad_VidInit(void)
{
	/* Set Row Pins as an Input */
	for (u8 i=0;i<4;i++)
	{
		Dio_voidSetpinchmode(ROW_PIN[i], INPUT);
	}
	/* Set Column Pins as an Output */
	for (u8 i=0;i<4;i++)
	{
		Dio_voidSetpinchmode(COL_PIN[i],OUTPUT_HIGH);
	}
	
}
/*KPD Get pressed*/
u8 Keypad_U8GetKeyPressed(void)
{
	u8 LOC_U8RowCount;
	u8 LOC_U8ColCount;
	/*Initialize the switch status to NOT PRESSED*/
	u8 LOC_U8ReturnValue=255;
	u8 LOC_U8PinState;
	/*Looping on columns of the keypad*/
	for(LOC_U8ColCount=0;LOC_U8ColCount<4;LOC_U8ColCount++)
	{
		/*Active the Column */
		Dio_voidWritepinchannel(COL_PIN[LOC_U8ColCount],PIN_LOW);
		/*Loop to read the all row pins*/
		for(LOC_U8RowCount=0;LOC_U8RowCount<4;LOC_U8RowCount++)
		{
			/*check the status of the switch*/
			Dio_voidReadpinchannel(ROW_PIN[LOC_U8RowCount],&LOC_U8PinState);
			if(LOC_U8PinState==0)
			{
				/*Get the Value of the current pressed switch*/
				LOC_U8ReturnValue=KPD_u8SwitchVal[LOC_U8ColCount][LOC_U8RowCount];
				/*wait until the switch is released(Single Press)*/
				while(LOC_U8PinState==0)
				{
					Dio_voidReadpinchannel(ROW_PIN[LOC_U8RowCount],&LOC_U8PinState);
				}
				/*Delay To avoid Bouncing*/
				_delay_ms(1);
			}
			else
			{
				/*Do Nothing*/
			}
		}
		/*Deactivate the Column*/
		Dio_voidWritepinchannel(COL_PIN[LOC_U8ColCount],PIN_HIGH);
	}
	return LOC_U8ReturnValue;
}
