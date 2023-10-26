
/*
 * TIMER_Interface.h
 *
 * Created: 16/09/2023 14:19:22
 *  Author: Mostafa Maher
 */ 

#ifndef	TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#include "Std.h"
#include "TIMER0_Config.h"



/*Timer0 Initialization*/
void TIMER0_VidInit(void);
/*Set Preload Function*/
void TIMER0_VidSetPreload(u8 Copy_u8Preload);
/*Set CTC Value Function*/
void TIMER0_VidSetCTCValue(u8 Copy_u8CTCValue);

void TIMER0_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void));

void TIMER0_VidCTC_SetCallBack(void(*Copy_VidCallBack)(void));
void TIMER0_VidStart(void);
void TIMER0_VidStop(void);
/*Timer0 Set Delay (ms)
* Must By Configure CTC Mode Interrupt Enable
* Must By Configure 64 Prescaler
*/
void TIMER0_VidSetDelay_ms(u16 Copy_u16Delay_ms);

void TIMER0_VidSetDutyCycle_PWM(u8 copy_duty );




#endif 