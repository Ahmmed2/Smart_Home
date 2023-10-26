
/*
 * TIMER0_Program.c
 *
 * Created: 16/09/2023 14:36:01
 *  Author: Mostafa Maher
 */ 

#include "TIMER0_Interface.h"
#include "TIMER0_Private.h"
#include "Dio_int.h" 
void (*TIMER0_CallBack)(void);

/*Timer0 Initialization*/
void TIMER0_VidInit(void)
{
	
	/*Mode Select*/
	#if TIMER0_SET_MODE == TIMER0_NORMAL_MODE
	CLR_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	/*Timer Overflow Interrupt Enable*/
	SET_BIT(TIMSK,0);

		#elif TIMER0_SET_MODE == TIMER0_CTC_MODE
		CLR_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);
		#if TIMER0_SET_CTC_INTERRUPT == TIMER0_CTC_INTERRUPT_ENABLED
		SET_BIT(TIMSK,1);
		#elif TIMER0_SET_CTC_INTERRUPT == TIMER0_CTC_INTERRUPT_DISABLED
		CLR_BIT(TIMSK,1);
		#else
		#error "TIMER0 CTC Interrupt Mode is not valid..."
		#endif
		#if TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_DISCONNECTED
		CLR_BIT(TCCR0,5);
		CLR_BIT(TCCR0,4);
		#elif TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_TOGGLE
		CLR_BIT(TCCR0,5);
		SET_BIT(TCCR0,4);
		#elif TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_SET
		SET_BIT(TCCR0,5);
		SET_BIT(TCCR0,4);
		#elif TIMER0_SET_OC0_PIN_MODE == TIMER0_OC0_PIN_CLR
		SET_BIT(TCCR0,5);
		CLR_BIT(TCCR0,4);
		#else
		#error "TIMER0 CTC OC0 Mode is not valid..."
		#endif
		
	#elif TIMER0_SET_MODE == TIMER0_PHASECORRECT_PWM_MODE
	SET_BIT(TCCR0,6);
	CLR_BIT(TCCR0,3);
	#if TIMER0_SET_PWM_MODE == TIMER0_NON_INVERTING_PWM
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
	#elif TIMER0_SET_PWM_MODE == TIMER0_INVERTING_PWM
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
	#else
	#error "PWM Mode is not valid..."
	#endif
	
		#elif TIMER0_SET_MODE == TIMER0_FAST_PWM_MODE
		SET_BIT(TCCR0,6);
		SET_BIT(TCCR0,3);
		#if TIMER0_SET_PWM_MODE == TIMER0_NON_INVERTING_PWM
		SET_BIT(TCCR0,5);
		CLR_BIT(TCCR0,4);

		#elif TIMER0_SET_PWM_MODE == TIMER0_INVERTING_PWM
		SET_BIT(TCCR0,5);
		SET_BIT(TCCR0,4);
		#else
		#error "PWM Mode is not valid..."
		#endif
		#else
		#error "TIMER0 Mode is not valid..."
		#endif
		
	
}
void TIMER0_VidStart(void)
{
	/*Select the suitable Prescaler */
	TCCR0&=0xF8;
	TCCR0|=TIMER0_SET_PRESCALER;	
}
void TIMER0_VidStop(void)
{
	/*Select the suitable Prescaler */
	TCCR0&=0xF8;
	TCCR0|=TIMER0_STOPPED;
}
/*Set Preload Function*/
void TIMER0_VidSetPreload(u8 Copy_u8Preload)
{
	TCNT0=Copy_u8Preload;
}
/*Set CTC Value Function*/
void TIMER0_VidSetCTCValue(u8 Copy_u8CTCValue)
{
	OCR0=Copy_u8CTCValue;
}

void TIMER0_VidSetDelay_ms(u16 Copy_u16Delay_ms)
{
	OCR0=249;
	
	TIMER0_Delay_Counter=Copy_u16Delay_ms;  /*For Prescaler 64*/
	
}

void TIMER0_VidSetDutyCycle_PWM(u8 copy_duty )//.25*255
{
	if (copy_duty<=100)
	{
	#if TIMER0_SET_MODE == TIMER0_FAST_PWM_MODE	
		#if TIMER0_SET_PWM_MODE == TIMER0_NON_INVERTING_PWM
		Dio_voidSetpinchmode(PB3,OUTPUT_LOW);
			OCR0 = (((u16)copy_duty*256)/100) -1;
		#elif TIMER0_SET_PWM_MODE == TIMER0_INVERTING_PWM
		Dio_voidSetpinchmode(PB3,OUTPUT_LOW);
			copy_duty=100-copy_duty;
			OCR0 = (((u16)copy_duty*256)/100) -1;
		#else
		#error "Duty Cycle is not valid..."
		#endif
	#elif TIMER0_SET_MODE == TIMER0_PHASECORRECT_PWM_MODE	
		#if TIMER0_SET_PWM_MODE == TIMER0_NON_INVERTING_PWM
		Dio_voidSetpinchmode(PB3,OUTPUT_LOW);
		OCR0 = (((u16)copy_duty*255)/100);
		#elif TIMER0_SET_PWM_MODE == TIMER0_INVERTING_PWM
		Dio_voidSetpinchmode(PB3,OUTPUT_LOW);
		OCR0 = 255-(((u16)copy_duty*255)/100);
		#else
		#error "Duty Cycle is not valid..."
		#endif
	#endif	
	}
	
}

void TIMER0_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER0_CallBack=Copy_VidCallBack;
}
void TIMER0_VidCTC_SetCallBack(void(*Copy_VidCallBack)(void))
{
	TIMER0_CallBack=Copy_VidCallBack;
}
void __vector_11(void)   __attribute__((signal));
void __vector_11(void)
{
	TIMER0_CallBack();
}
void __vector_10(void)   __attribute__((signal));
void __vector_10(void)
{
	
	static u16 count=0;
	if (count==TIMER0_Delay_Counter)
	{
		TIMER0_CallBack();
		count=0;
	}
	else
	{
		count++;
	}
	
	
}
