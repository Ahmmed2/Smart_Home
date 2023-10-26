
/*
 * TIMER0_Private.h
 *
 * Created: 16/09/2023 14:35:28
 *  Author: Mostafa Maher
 */ 
#ifndef	TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

u16 TIMER0_Delay_Counter=0;

#define TCCR0     *((volatile u8*)0x53)
#define TIMSK     *((volatile u8*)0x59)
#define TCNT0     *((volatile u8*)0x52)
#define OCR0      *((volatile u8*)0x5C)


#define TIMER0_STOPPED         0
#define TIMER0_NO_PRESCALER    1
#define TIMER0_8_PRESCALER     2
#define TIMER0_64_PRESCALER    3
#define TIMER0_256_PRESCALER   4
#define TIMER0_1024_PRESCALER  5
#define TIMER0_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE  6
#define TIMER0_EXTERNAL_CLOCK_SOURCE_RISING_EDGE   7


#define TIMER0_NORMAL_MODE             1
#define TIMER0_CTC_MODE                2
#define TIMER0_PHASECORRECT_PWM_MODE   3
#define TIMER0_FAST_PWM_MODE           4

#define TIMER0_CTC_INTERRUPT_ENABLED      0
#define TIMER0_CTC_INTERRUPT_DISABLED     1


#define TIMER0_OC0_PIN_DISCONNECTED     0
#define TIMER0_OC0_PIN_TOGGLE           1
#define TIMER0_OC0_PIN_SET              2
#define TIMER0_OC0_PIN_CLR              3

#define TIMER0_NON_INVERTING_PWM    1
#define TIMER0_INVERTING_PWM         2

#endif 