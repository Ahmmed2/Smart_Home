#include "Std.h"


#include "ADC_Private.h"
#include "ADC_Interface.h"
#include "ADC_Congif.h"




void (*GPTF_ADC)(void) ;

void ADC_voidInit()
{
	/* AVCC with external capacitor at AREF pin */ 
	SET_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
	
	/* Right Adjust */
	CLR_BIT(ADMUX,ADLAR); 
	
	/* Enable ADC */
	SET_BIT(ADCSRA,ADEN);
}



/* To Select Pre_Scaler */
void ADC_voidSelectPreScaler(u8 Copy_u8ClkDiv)
{
	switch(Copy_u8ClkDiv)
	{


		case(Div2) :

		CLR_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
		break ;

		case(Div4) :

		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
		break ;

		case(Div8) :

		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		CLR_BIT(ADCSRA,ADPS2);
		break ;

		case(Div16) :

		CLR_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break ;

		case(Div32) :

		SET_BIT(ADCSRA,ADPS0);
		CLR_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break ;

		case(Div64) :

		CLR_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break ;

		case(Div128) :

		SET_BIT(ADCSRA,ADPS0);
		SET_BIT(ADCSRA,ADPS1);
		SET_BIT(ADCSRA,ADPS2);
		break ;

	}

}


/* Select Channel in ADC */
void ADC_voidSelectChannel(u8 Copy_u8ChannelNUM)
{
	switch(Copy_u8ChannelNUM)
	{
		case ADC0 :
		CLR_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
		break ;
		
		case ADC1 :
		SET_BIT(ADMUX,  MUX0);
		CLR_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
		break ;
		
		case ADC2 :
		CLR_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
		break ;
		
		case ADC3 :
		SET_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		CLR_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
		break ;
		
		case ADC4 :
		CLR_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
		break ;
		
		case ADC5 :
		SET_BIT(ADMUX,MUX0);
		CLR_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
		break ;
		
		case ADC6 :
		CLR_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
		break ;
		
		case ADC7 :
		SET_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		SET_BIT(ADMUX,MUX2);
		CLR_BIT(ADMUX,MUX3);
		CLR_BIT(ADMUX,MUX4);
		break ;


	}

}


void ADC_voidSelectClock(u8 Copy_u8ClockType)
{
	
	switch (Copy_u8ClockType)
	{
		
		case AREF_VREF_OFF         : CLR_BIT(ADMUX,REFS0)	;	CLR_BIT(ADMUX,REFS1);  break ; 
		case AVCC_CAP_AT_AREF      : SET_BIT(ADMUX,REFS0)	;	CLR_BIT(ADMUX,REFS1);  break ; 
		case INTERNAL_CAP_AT_AREF  : SET_BIT(ADMUX,REFS0)	;	SET_BIT(ADMUX,REFS1)  ;	 break ; 
		
	}
}


void ADC_voidAutoTriggerMode(u8 Copy_u8AutoTriggerMode)
{
	
	switch (Copy_u8AutoTriggerMode)
	{
		case FREE_RUNNING_MODE :
										/* Free Running Mode */
										CLR_BIT(SFIOR,ADTS0);
										CLR_BIT(SFIOR,ADTS1);
										CLR_BIT(SFIOR,ADTS2);
										break ; 	
										
		case ANALOG_COMPARATOR : 
										/* Analog Comparator  */
										SET_BIT(SFIOR,ADTS0);
										CLR_BIT(SFIOR,ADTS1);
										CLR_BIT(SFIOR,ADTS2);
										break ;
		
		case EXTERNAL_INTERRUPT_REQUEST_0 : 
		
										/* External Interrupt  */
										CLR_BIT(SFIOR,ADTS0);
										SET_BIT(SFIOR,ADTS1);
										CLR_BIT(SFIOR,ADTS2);
										break ; 
										
		case TIMER_COUNTER0_COMPARE_MATCH :
			
										/* Timer/Counter0 Compare Match  */
										SET_BIT(SFIOR,ADTS0);
										SET_BIT(SFIOR,ADTS1);
										CLR_BIT(SFIOR,ADTS2);
										break ;
										
		case TIMER_COUNTER0_OVERFLOW :
			
										/* Timer/Counter0 Overflow */
										CLR_BIT(SFIOR,ADTS0);
										CLR_BIT(SFIOR,ADTS1);
										SET_BIT(SFIOR,ADTS2);
										break ;
										
										
		case TIMER_COUNTER1_COMPARE_MATCHB :
			
										/* Timer/Counter1 Compare Match B */
										SET_BIT(SFIOR,ADTS0);
										CLR_BIT(SFIOR,ADTS1);
										SET_BIT(SFIOR,ADTS2);
										break ;
										
										
										
		case TIMER_COUNTER1_OVERFLOW :
												
										/* Timer/Counter1 Overflow */
										CLR_BIT(SFIOR,ADTS0);
										SET_BIT(SFIOR,ADTS1);
										SET_BIT(SFIOR,ADTS2);
										break ;
										
		case TIMER_COUNTER1_CAPTURE_EVENT :
												
										/* Timer/Counter1 Capture Event */
										SET_BIT(SFIOR,ADTS0);
										SET_BIT(SFIOR,ADTS1);
										SET_BIT(SFIOR,ADTS2);
										break ;
										
									
	}
	
}

void ADC_voidStartConversion(u8 Copy_u8ADCType , u8 Copy_u8AutoTriggerMode)
{
	
	switch (Copy_u8ADCType)
	{
		case SINGLE_MODE : 	
								/* Start Conversion */
								SET_BIT(ADCSRA,ADSC);
								break ; 
								
		case SYNCHRONUS :
								/* Disable Interrupt */
								CLR_BIT(ADCSRA,ADIE);
								/* Auto Trigger Enable */
								SET_BIT(ADCSRA,ADATE);
								/* Select Mode */ 
								ADC_voidAutoTriggerMode(Copy_u8AutoTriggerMode);
								/* Start Conversion */
								SET_BIT(ADCSRA,ADSC);
								break ; 
								
		case ASYNCHRONUS : 
								/* Enable Interrupt */
								SET_BIT(ADCSRA,ADIE);
								/* Auto Trigger Enable */
								SET_BIT(ADCSRA,ADATE);
								/* Select Mode */
								ADC_voidAutoTriggerMode(Copy_u8AutoTriggerMode);
								/* Start Conversion */
								SET_BIT(ADCSRA,ADSC);
								break ; 
								
	}
}



u16 ADC_u16GetResult(u8 Copy_u8ModeSelect)
{ 
	u16 Local_u16CopyValue ; 
	
	switch (Copy_u8ModeSelect)
	{
		
		case SINGLE_MODE : Local_u16CopyValue = ADC ; break;
		case SYNCHRONUS  : 	
							while (GET_BIT(ADCSRA,ADIF)==0);
							 Local_u16CopyValue = ADC ;
							/* To Reset the Flag */
							SET_BIT(ADCSRA,ADIF);
							break ; 
		case ASYNCHRONUS : 
							Local_u16CopyValue = ADC ;
							/* To Reset the Flag */
							SET_BIT(ADCSRA,ADIF);
							return ADC ;
							break ; 
	}
		
	return Local_u16CopyValue ; 
	
}



/* To scan Group of channels at same time */ 
void ADC_voidScanGroup(u8 Copy_u8Channels[] , u16 Copy_u16Buffer[])
{
	u8 Local_u8Counter = 0 ; 
	while (Copy_u8Channels[Local_u8Counter] != 10)
	{
		ADC_voidSelectChannel(Copy_u8Channels[Local_u8Counter]);
		ADC_voidStartConversion(SINGLE_MODE,0);
		_delay_ms(1500);
		Copy_u16Buffer[Local_u8Counter] = ADC_u16GetResult(SINGLE_MODE);
		Local_u8Counter ++ ;
	}
	
}

void ADC_voidScanGroupStruct(ADC_Scan *Copy_ADC_ScanChannel , u16 Copy_u16Buffer[])
{
	u8 Local_u8Counter = 0 ; 

	
	ADC_voidSelectChannel((*Copy_ADC_ScanChannel).Channel1);
	ADC_voidStartConversion(SINGLE_MODE,0);
	_delay_ms(1500);
	Copy_u16Buffer[Local_u8Counter] = ADC_u16GetResult(SINGLE_MODE);
	Local_u8Counter ++ ;
	
	ADC_voidSelectChannel((*Copy_ADC_ScanChannel).Channel2);
	ADC_voidStartConversion(SINGLE_MODE,0);
	_delay_ms(500);
	Copy_u16Buffer[Local_u8Counter] = ADC_u16GetResult(SINGLE_MODE);
	Local_u8Counter ++ ;
	
}












void ADCINT_SetCallBack(void(*ptr)(void))
{

	GPTF_ADC=ptr;
}



void __vector_16()__attribute__((signal));
void __vector_16()
{
	
	if (GPTF_ADC!='\0')
	{
		GPTF_ADC();
	}
	
}