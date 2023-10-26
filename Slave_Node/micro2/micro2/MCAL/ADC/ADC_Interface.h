#ifndef  _ADC_INTERFACE_
#define  _ADC_INTERFACE_

#include "ADC_Congif.h"
/* Group Scan */
typedef struct
{
	u8 Channel1  ;
	u8 Channel2  ;
}ADC_Scan ;

void ADC_voidInit(); 
/* Pre_Scaler */ 
void ADC_voidSelectPreScaler(u8 Copy_u8ClkDiv);  
/* Which Channel is Operating */
void ADC_voidSelectChannel(u8 Copy_u8ChannelNUM);
/* Choose the Clock Source to ADC */
void ADC_voidSelectClock(u8 Copy_u8ClockType);
/* Select Certain Mode */ 
void ADC_voidStartConversion(u8 Copy_u8ADCType,u8 Copy_u8AutoTriggerMode) ;
/*Determine the Type of Auto Trigger Mode */ 
void ADC_voidAutoTriggerMode(u8 Copy_u8AutoTriggerMode) ;
/* Return Results for different Modes */ 
u16 ADC_u16GetResult(u8 Copy_u8ModeSelect);
/* Scan Group of Channels with Array  */ 
void ADC_voidScanGroup (u8 Copy_u8Channels[] , u16 Copy_u16Buffer[]);
/* Scan Group of channels with struct */ 
void ADC_voidScanGroupStruct(ADC_Scan *Copy_ADC_ScanChannel , u16 Copy_u16Buffer[]);


/* Set Call Back */ 
void ADCINT_SetCallBack(void(*ptr)(void));






#endif
