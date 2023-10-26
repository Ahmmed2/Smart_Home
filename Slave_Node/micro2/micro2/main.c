/*
 * main.c
 *
 * Created: 10/1/2023 3:39:49 PM
 *  Author: GROUP NIGHT FURY
 */
#include "LIB/Std.h"
#include "HAL/LCD/Lcd.h"
#include "HAL/SRVM/SRVM_Interface.h"
#include "MCAL/Dio/Dio_int.h"
#include "MCAL/TIMER0/TIMER0_Interface.h"
#include "MCAL/TIMER1/TIMER1_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "MCAL/SPI/SPI_Interface.h"
#include "MCAL/TIMER1/TIMER1_Private.h"

////////////////////////////////////////////

/* Media Mode 1*/

// Defining frequency of each music note
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988

// Music notes of the song, 0 is a rest/pulse

u16 notes[] = {

NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
NOTE_A4, NOTE_G4, NOTE_A4, 0,

NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
NOTE_A4, NOTE_G4, NOTE_A4, 0,

NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
NOTE_D5, NOTE_E5, NOTE_A4, 0,
NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
NOTE_C5, NOTE_A4, NOTE_B4, 0,

NOTE_A4, NOTE_A4,

//Repeat of first part
NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
NOTE_A4, NOTE_G4, NOTE_A4, 0,

NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
NOTE_A4, NOTE_G4, NOTE_A4, 0,

NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
NOTE_D5, NOTE_E5, NOTE_A4, 0,
NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
NOTE_C5, NOTE_A4, NOTE_B4, 0,

//End of Repeat

NOTE_E5, 0, 0, NOTE_F5, 0, 0,
NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
NOTE_D5, 0, 0, NOTE_C5, 0, 0,
NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

NOTE_E5, 0, 0, NOTE_F5, 0, 0,
NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
NOTE_D5, 0, 0, NOTE_C5, 0, 0,
NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4

};

// Durations (in ms)
u16 durations[] = {
125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 375, 125,

125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 375, 125,

125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 125, 250, 125,

125, 125, 250, 125, 125,
250, 125, 250, 125,
125, 125, 250, 125, 125,
125, 125, 375, 375,

250, 125,

//Rpeat of First Part
125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 375, 125,

125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 375, 125,

125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 250, 125, 125,
125, 125, 125, 250, 125,

125, 125, 250, 125, 125,
250, 125, 250, 125,
125, 125, 250, 125, 125,
125, 125, 375, 375,

//End of Repeat

250, 125, 375, 250, 125, 375,
125, 125, 125, 125, 125, 125, 125, 125, 375,
250, 125, 375, 250, 125, 375,
125, 125, 125, 125, 125, 500,

250, 125, 375, 250, 125, 375,
125, 125, 125, 125, 125, 125,
125, 125, 375,
250, 125, 375, 250, 125, 375,
125, 125, 125, 125, 125, 500

};




// Defining frequency of each music note
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


// change this to make the song slower or faster
int tempo = 70;

// notes of the moledy followed by the duration.
int melody[] = {

  NOTE_G4,8,//1
  NOTE_AS4,4, NOTE_C5,8, NOTE_D5,-8, NOTE_DS5,16, NOTE_D5,8,
  NOTE_C5,4, NOTE_A4,8, NOTE_F4,-8, NOTE_G4,16, NOTE_A4,8,
  NOTE_AS4,4, NOTE_G4,8, NOTE_G4,-8, NOTE_FS4,16, NOTE_G4,8,
  NOTE_A4,4, NOTE_FS4,8, NOTE_D4,4, NOTE_G4,8,

  NOTE_AS4,4, NOTE_C5,8, NOTE_D5,-8, NOTE_DS5,16, NOTE_D5,8,//6
  NOTE_C5,4, NOTE_A4,8, NOTE_F4,-8, NOTE_G4,16, NOTE_A4,8,
  NOTE_AS4,-8, NOTE_A4,16, NOTE_G4,8, NOTE_FS4,-8, NOTE_E4,16, NOTE_FS4,8,
  NOTE_G4,-2,
  NOTE_F5,2, NOTE_E5,16, NOTE_D5,8,

  NOTE_C5,4, NOTE_A4,8, NOTE_F4,-8, NOTE_G4,16, NOTE_A4,8,//11
  NOTE_AS4,4, NOTE_G4,8, NOTE_G4,-8, NOTE_FS4,16, NOTE_G4,8,
  NOTE_A4,4, NOTE_FS4,8, NOTE_D4,04,
  NOTE_F5,2, NOTE_E5,16, NOTE_D5,8,
  NOTE_C5,4, NOTE_A4,8, NOTE_F4,-8, NOTE_G4,16, NOTE_A4,8,

  NOTE_AS4,-8, NOTE_A4,16, NOTE_G4,8, NOTE_FS4,-8, NOTE_E4,16, NOTE_FS4,8,//16
  NOTE_G4,-2,

};

#define MUSIC_END 0

void Run_Melody(void);

///////////////////////////////////////////




void App_Init();

void Open_Door();

void Open_Ac();

void Open_Media();

void check(void);

u8 Glob_Door=0;
u8 Glob_AC=0;
u8 Glob_Media=0;
u8 Glob_u8signal=1;


int main(void)
{
	App_Init();

    while(1)
    {

		check();
    }
}


void Open_Door()
{
	Glob_Door++;
	TIMER1_VidTIMStart();


	if (Glob_Door==1)
	{
		SRVM_voidOn(90);
		SPI_voidTransmiter('Y');

	}
	else
	{
		Glob_Door=0;
		SRVM_voidOn(0);
		SPI_voidTransmiter('N');

	}

	TIMER1_VidTIMStop();
}


void Open_Ac()
{

	Glob_AC++;
		u16 Loc_ADC_Value,Loc_TempValue;


		if (Glob_AC==1)
		{

		//	Loc_ADC_Value =ADC_u16GetResult(SINGLE_MODE);
			Loc_TempValue = Loc_ADC_Value/2;
			TIMER0_VidStart();

			if (Loc_TempValue>0 && Loc_TempValue<15)
			{
				TIMER0_VidSetDutyCycle_PWM(25);
			}
			else if (Loc_TempValue>15 && Loc_TempValue<25)
			{
				TIMER0_VidSetDutyCycle_PWM(50);
			}

			else if (Loc_TempValue>25 && Loc_TempValue<35)
			{
				TIMER0_VidSetDutyCycle_PWM(75);
			}

			else
			{
				TIMER0_VidSetDutyCycle_PWM(99);
			}

		}
		else
		{
			Glob_AC=0;
			TIMER0_VidStop();
			Dio_voidWritepinchannel(PB3,PIN_LOW);
		}
	}

void Open_Media()
{
	static u8  Lamp_Media_mode = 0;

	Glob_Media++;
	SET_BIT(TCCR1A,COM1B1);
	TIMER1_VidTIMStart();


	if (Glob_Media==1)
	{

		if (Lamp_Media_mode == 0){

		// Lamps one by one mode

		for (u8 i=0;i<4;i++)
    		{

    		SET_BIT(PORTC,i);
    		_delay_ms(250);

    		}

		// media mode 1
		const u8 NOTE_Length = sizeof(notes) / sizeof(notes[0]);
		u16 i;

		for (i = 0 ; i <= NOTE_Length ; i++){

		Timer1_Fast_PWM_Play(notes[i]); _delay_ms(durations[i]);

		}


		Lamp_Media_mode = 1;

		}

		else if (Lamp_Media_mode == 1){

		// Lamps one by one mode
		for (u8 i=0;i<4;i++)
    		{
		  SET_BIT(PORTC,i);
    		  _delay_ms(250);
    		  CLR_BIT(PORTC,i);
    		  _delay_ms(250);
		}

    		for (u8 i=0;i<4;i++)
    	    	{

    	    	SET_BIT(PORTC,i);
    	    	_delay_ms(250);

    	    	}

		// media mode 2
		Run_Melody();
		Lamp_Media_mode = 0;

		}
	}



	else
	{
		Glob_Media=0;
		SPI_voidTransmiter('N');
	}


	Dio_SETportchannel(DIO_PORTC,OUTPUT_LOW);
	TIMER1_VidTIMStop();

}



void Run_Melody(void){

	// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
		// there are two values per note (pitch and duration), so for each note there are four bytes
		int notes = sizeof(melody) / sizeof(melody[0]) / 2;

		// this calculates the duration of a whole note in ms
		int wholenote = ((u32)60000 * 4) / tempo;

		int divider = 0, noteDuration = 0;


		for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

			// calculates the duration of each note
			   divider = melody[thisNote + 1];

			   if (divider > 0) {
			   // regular note, just proceed
			      noteDuration = (wholenote) / divider;
			   }

			   else if (divider < 0) {
			   // dotted notes are represented with negative durations!!
			      noteDuration = (wholenote) / (-1)*(divider);
			      noteDuration *= 1.5; // increases the duration in half for dotted notes
			    }

			   // we only play the note for 90% of the duration, leaving 10% as a pause
			   Timer1_Fast_PWM_Play(melody[thisNote]);
			   _delay_ms(noteDuration*0.9);

			   // Wait for the specief duration before playing the next note.
			   _delay_ms(noteDuration);

		}


}


void check()
{

	Glob_u8signal= SPI_u8Receiver();
	switch(Glob_u8signal)
	{
		case 'O':
		Open_Door();
		break;
		case 'A':
		ADC_voidStartConversion(SINGLE_MODE, 0);
		Open_Ac();
		break;
		case 'M':
		Open_Media();
		break;
	}

}

void App_Init()
{
	Dio_voidSetpinchmode(PA1,INPUT);
	// Lamp pins
	Dio_voidSetpinchmode(PC0,OUTPUT_LOW);
	Dio_voidSetpinchmode(PC1,OUTPUT_LOW);
	Dio_voidSetpinchmode(PC2,OUTPUT_LOW);
	Dio_voidSetpinchmode(PC3,OUTPUT_LOW);

	Dio_voidSetpinchmode(PB3,OUTPUT_LOW);

	//SPI Pins
	Dio_voidSetpinchmode(PB5,INPUT);
	Dio_voidSetpinchmode(PB6,OUTPUT_LOW);
	Dio_voidSetpinchmode(PA4,INPUT);
	Dio_voidSetpinchmode(PB7,INPUT);

	Dio_voidSetpinchmode(PD4,OUTPUT_LOW);
	Dio_voidSetpinchmode(PD5,OUTPUT_LOW);

	TIMER0_VidInit();

	TIMER1_VidInit();

	ADC_voidInit();
	ADC_voidSelectChannel(1);
	ADC_voidStartConversion(SINGLE_MODE, 0);
	ADC_voidSelectPreScaler(Div64);
	LCD_voidInit();
	SPI_voidInialize();


}