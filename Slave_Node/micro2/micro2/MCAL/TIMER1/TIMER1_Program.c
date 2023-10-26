
/*
 * TIMER1_Program.c
 *
 * Created: 18/09/2023 15:03:09
 *  Author: Mostafa Maher
 */ 

#include "TIMER1_Interface.h"
#include "TIMER1_Private.h"


void (*TIMER1_CallBack_ICU)(void);
void (*TIMER1_CallBack_OVF)(void);
void TIMER1_VidInit()
{
	#if TIMER1_SET_MODE == TIMER0_NORMAL_MODE_ICU
	/*Set Normal mode */
	CLR_BIT(TCCR1B,4);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1A,0);
	#if TIMER1_SET_SENSE_CONTROL == TIMER1_RISING_EDGE
	/*ICU Edge Select-->Rising edge*/
	SET_BIT(TCCR1B,6);
	#elif TIMER1_SET_SENSE_CONTROL == TIMER1_FALLING_EDGE
	/*ICU Edge Select-->Falling edge*/
	CLR_BIT(TCCR1B,6);
	#endif
	/*TIMER OVERFLOW INTERRUPT ENABLLED*/
	SET_BIT(TIMSK,2);
	/*ICU INTERRUPT ENABLLED*/
	SET_BIT(TIMSK,5);
	#elif TIMER1_SET_MODE == TIMER1_FAST_PWM_MODE
	// Select Mode = Fast PWM Mode(14)
	CLR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	// Select Non Inverting Mode
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	// ICR1 >> period time = 20ms >> freq. = 50HZ
	
	#endif
}

void TIMER1_VidTIMStart()
{
	
	/*Select the suitable Prescaler */
	TCCR1B&=0xF8;
	TCCR1B|=TIMER1_SET_PRESCALER;
	
}
void TIMER1_VidTIMStop()
{
	// Select Prescaler Value = 0
	CLR_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
	
}

void TIMER1_VidSetICRValue(u32 copy_value )
{
	
	ICR1_u16=copy_value;
	
}

void TIMER1_VidSetCompareMatchValue_CHA(u16 copy_value )
{
	//Dio_voidSetpinchmode(PD5,OUTPUT_LOW);
	OCR1A_u16=copy_value;
	
}


void TIMER1_VidSetCompareMatchValue_CHB(u16 copy_value )
{
	//Dio_voidSetpinchmode(PD4,OUTPUT_LOW);
	OCR1B_u16=copy_value;
	
}

void TIMER1_VidGetICRValue(u32* copy_value )
{
	
	*copy_value=ICR1_u16;
	
}



void TIMER1_VidSenseControl(u8 Copy_u8SenseControl)
{
	switch(Copy_u8SenseControl)
	{
		case FALLING_EDGE :
		/*ICU Edge Select-->Falling edge*/
		CLR_BIT(TCCR1B,6);
		break;
		case RISING_EDGE :
		/*ICU Edge Select-->Rising edge*/
		SET_BIT(TCCR1B,6);
		break;
		
	}
}


void TIMER1_VidICU_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER1_CallBack_ICU=Copy_VidCallBack;
}
void TIMER1_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER1_CallBack_OVF=Copy_VidCallBack;
}
void __vector_6(void)   __attribute__((signal));
void __vector_6(void)
{
	TIMER1_CallBack_ICU();
}


void __vector_9(void)      __attribute__((signal));
void __vector_9(void)
{
	TIMER1_CallBack_OVF();
}


/*Added Function*/
void Timer1_Fast_PWM_Play( u16 Freq)
{

	TCNT1_u16 = 0;		/* Set timer1 initial count to zero */

	ICR1_u16 = ((u32)16000000UL/(64*Freq))-1;	/* Set TOP count for timer1 in ICR1 register */

	OCR1B_u16 =(ICR1_u16/2); /* Set the compare value */


}
