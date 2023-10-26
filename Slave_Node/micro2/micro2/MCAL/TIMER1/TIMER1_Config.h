/*
 * TIMER1_Config.h
 *
 * Created: 29/09/2023 09:48:02
 *  Author: Mostaf Maher
 */ 


#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_


/*Timer Prescaler Options:
 * 0- TIMER1_STOPPED
 * 1- TIMER1_NO_PRESCALER
 * 2- TIMER1_8_PRESCALER
 * 3- TIMER1_64_PRESCALER
 * 4- TIMER1_256_PRESCALER
 * 5- TIMER1_1024_PRESCALER
 * 6- TIMER1_EXTERNAL_CLOCK_SOURCE_FALLING_EDGE
 * 7- TIMER1_EXTERNAL_CLOCK_SOURCE_RISING_EDGE
 */
#define TIMER1_SET_PRESCALER   TIMER1_64_PRESCALER

/*TIMER0 Modes Options:
 * 1- TIMER0_NORMAL_MODE_ICU
 * 2- TIMER1_FAST_PWM_MODE
 */

#define TIMER1_SET_MODE   TIMER1_FAST_PWM_MODE

/*Sense control Options:
 * 1- TIMER1_FALLING_EDGE
 * 2- TIMER1_RISING_EDGE
 */

#define TIMER1_SET_SENSE_CONTROL     TIMER1_RISING_EDGE


#endif /* TIMER1_CONFIG_H_ */