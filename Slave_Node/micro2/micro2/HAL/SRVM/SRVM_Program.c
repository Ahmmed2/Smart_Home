
/*
 * SRVM_Program.c
 *
 * Created: 20/09/2023 16:34:29
 *  Author: Mostafa Maher
 */ 

#include "SRVM_Interface.h"


void SRVM_voidOn (u8 Copy_u8Angle)
{
	TIMER1_VidSetICRValue (4999);
	switch(Copy_u8Angle)
	{
		case 0 :
		TIMER1_VidSetCompareMatchValue_CHA(374);
		break;
		
		case 90 :
		TIMER1_VidSetCompareMatchValue_CHA(499);
		break;
		
		case 180 :
		TIMER1_VidSetCompareMatchValue_CHA(249);
		break;
		default:
		TIMER1_VidSetCompareMatchValue_CHA(374);
		break;
	}

	/* TMR1 start */
	TIMER1_VidTIMStart();
}
	
void SRVM_voidOff(void)
{
	TIMER1_VidTIMStop();
}

void SRVM_voidSetAngle(u8 Copy_u8Angle)
{
	/*when pre-scaler =8 the tick time = 0.5 micro-sec*******So 1ms = 2000 tick********2ms =4000ticks******20 ms Ttotal =40000 tick all this values -1 for the tick zero*/
	/* Set Top Value in ICR1 */
	TIMER1_VidSetICRValue (40000);
	TIMER1_VidSetCompareMatchValue_CHA((((u32)Copy_u8Angle*2000)/180+1999));
	/* TMR1 start */
	TIMER1_VidTIMStart();
	_delay_ms(2);
	//TIMER1_VidSetCompareMatchValue_CHA(0);
}