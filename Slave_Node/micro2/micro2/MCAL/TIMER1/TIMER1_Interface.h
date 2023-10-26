
/*
 * TIMER1_Interface.h
 *
 * Created: 18/09/2023 15:01:57
 *  Author: Mostafa Maher
 */ 


#ifndef	TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#include "Std.h"
#include "Dio_int.h"

#include "TIMER1_Config.h"

#define FALLING_EDGE  0
#define RISING_EDGE   1

/*Timer0 Initialization*/
void TIMER1_VidInit();

void TIMER1_VidTIMStart();

void TIMER1_VidTIMStop();

void TIMER1_VidSetICRValue(u32 copy_value );


void TIMER1_VidSetCompareMatchValue_CHA(u16 copy_value );

void TIMER1_VidSetCompareMatchValue_CHB(u16 copy_value );

void TIMER1_VidSenseControl(u8 Copy_u8SenseControl);

void TIMER1_VidGetICRValue(u32* copy_value );



void TIMER1_VidICU_SetCallBack(void(*Copy_VidCallBack)(void));
void TIMER1_VidOVF_SetCallBack(void(*Copy_VidCallBack)(void));


#endif