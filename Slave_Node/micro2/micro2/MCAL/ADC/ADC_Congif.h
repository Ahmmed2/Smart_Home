#ifndef  _ADC_CONFIG_
#define  _ADC_CONFIG_


/* ADC Channels */ 
#define ADC0   0
#define ADC1   1
#define ADC2   2
#define ADC3   3
#define ADC4   4
#define ADC5   5
#define ADC6   6
#define ADC7   7


/* Pre_Scaler */ 
#define Div2    0
#define Div4    1
#define Div8    2
#define Div16   3
#define Div32   4
#define Div64   5
#define Div128  6


/* Auto Trigger Modes */ 
#define FREE_RUNNING_MODE					0
#define ANALOG_COMPARATOR                   1
#define EXTERNAL_INTERRUPT_REQUEST_0		2
#define TIMER_COUNTER0_COMPARE_MATCH        3
#define	TIMER_COUNTER0_OVERFLOW             4
#define TIMER_COUNTER1_COMPARE_MATCHB       5
#define	TIMER_COUNTER1_OVERFLOW             6
#define TIMER_COUNTER1_CAPTURE_EVENT		7
	
/* Modes */ 
#define SINGLE_MODE  0
#define SYNCHRONUS   1
#define ASYNCHRONUS  2

/* Clock Types */ 
//AVCC is internal 5V 
#define AREF_VREF_OFF		 0
#define AVCC_CAP_AT_AREF	 1
#define INTERNAL_CAP_AT_AREF 2


#endif
