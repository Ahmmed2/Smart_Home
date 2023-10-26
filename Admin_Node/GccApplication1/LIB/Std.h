/*
 * Std.h
 *
 * Created: 08/09/2023 11:25:35
 *  Author: Mostafa Maher
 */ 

#ifndef STD_H_
#define STD_H_

#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>


#define SET_BIT(VAR,BIT_NUM)       ((VAR)|=(1<<(BIT_NUM)))
#define CLR_BIT(VAR,BIT_NUM)       (VAR)&=(~(1<<(BIT_NUM)))
#define TOGGLE_BIT(VAR,BIT_NUM)    (VAR)^=(1<<(BIT_NUM))
#define GET_BIT(VAR,BIT_NUM)      (  ( (VAR>>BIT_NUM) ) & 1  )
#define BIT_IS_CLEAR(REG,BIT)      ( !(REG & (1<<BIT)) )

#define NULL_POINTER  (void*)1
#define NULL           '\0'

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short int u16;
typedef signed short int s16;

typedef unsigned long int u32;
typedef signed long int s32;

typedef unsigned long long int u64;
typedef signed long long int s64;

typedef float f32;
typedef double f64;




#endif /* STD_H_ */