
/*
 * Keypad.h
 *
 * Created: 09/09/2023 11:29:41
 *  Author: Mostafa Maher
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Std.h"
#include "Keypad_confg.h"
#include "Dio_int.h"
#include <util/delay.h>


#define NOT_PRESSED 255

/*KPD INIT*/
void Keypad_VidInit(void);
/*KPD Get pressed*/
u8 Keypad_U8GetKeyPressed(void);

#endif /* KEYPAD_H_ */
