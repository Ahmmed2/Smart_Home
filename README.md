# Smart_Home
## This project based on Atmega32.   
### System have two modes the first is Admin mode which have full acess on everything and he is higher priority than the user.   
### Second mode is User mode, Lower priority mode which have Control over the home through User-Interface.    
## How the system works ?
#### Admin mode have authorties to add user,delete user,change password of certain user this functionality not provided to user mode, 
#### also the admin can control Door,Buzzer and air conditioner , Admin mode interact with the system through terminal using UART.
#### user can only control Door,Buzzer and air conditioner through the keypad and all the options mentioned is visualized on LCD.
#### you have 3 times to enter the password after that alarm will be on and every time the password is wrong there is warning send to 
#### the Admin that someone try to enter the home but the password is wrong.
## How the sysytem works ? 
#### on the first Run, LCD is asking if you want Admin mode or User mode, upon your choice the system will act,   
#### if you choose Admin mode then he will ask to choose options which will be visualized on the terminal,    
#### all the password interfaces is stored in EEPROM for next operations.
## what is the SW interfaces and HW used ? 
#### SW used TWI,UART,TIMERS,ADC,SPI,DIO.
#### HW used keypad,LCD,SERVO,DC motor,Motor Driver,LM35,UART interface,EEPROM,LEDS.
