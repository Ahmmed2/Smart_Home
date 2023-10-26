
/*
 * Lcd_config.h
 *
 * Created: 10/09/2023 09:07:40
 *  Author: Mostafa Maher
 */ 

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

    /* MACROS FOR LCD CONTROL PORTS & PINS CONFIGURATION */
        
    /* Macros For Rs configuration */
    #define LCD_RS_PORT           DIO_PORTA
    #define LCD_RS                 PA3

    /* Macros For En configuration */
    #define LCD_E_PORT            DIO_PORTA
    #define LCD_E             PA2


   
   #define LCD_LINE1    1
   #define LCD_LINE2    2


    /* 4 Bit Mode Pins Configuration */

    #define LCD_D4_PIN            PB0
    #define LCD_D4_PORT           DIO_PORTB
        
    #define LCD_D5_PIN            PB1
    #define LCD_D5_PORT           DIO_PORTB
        
    #define LCD_D6_PIN            PB2
    #define LCD_D6_PORT           DIO_PORTB
        
    #define LCD_D7_PIN            PB4
    #define LCD_D7_PORT           DIO_PORTB

#endif