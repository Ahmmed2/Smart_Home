/*
 * main.c
 *
 * Created: 10/1/2023 10:57:38 AM
 *  Author: GROUP NIGHT FURY
 */ 
#include "LIB/Std.h"
#include "HAL/LCD/Lcd.h"
#include "HAL/KEYPAD/Keypad.h"
#include "MCAL/Dio/Dio_int.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/SPI/SPI_Interface.h"
#include "MCAL/TWI/TWI_Interface.h"
#include "HAL/EEPROM/EEPROM_Interface.h"




/* Global Variable and Arrays */
u8 UART_PassRx [10] ;
u8 Loc_arr[3] ;
u8 UART_IndexRx ;
u8 UART_UserPrivillege  ;
u8 Char_Rx = 0 ;
u8 SPI_Var = 0 ;
u8 Glob_Door='Y'  ;
u8 Glob_AC='Y'  ;
u8 Glob_M='Y'  ;
u8 UART_State ;
u8 Index ;
u8 Gol_Counter;
u8 Loc_GetChar=255;
u8 Loc_Password[4]={'-','-','-','-'};
s8 Loc_Count=0;
static Error_Flag = 0 ;
static u8 Loc_flag=0;
static u8 Address_Index ;
//////////////////////////

/* ADMIN Authorities */
u8 LCD_Mode1[] = "A-ADD User" ;
u8 LCD_Mode2[] = "B-Delete User" ;
u8 LCD_Mode3[] = "C-Change Pass " ;
u8 LCD_Mode4[] = "D-Continue" ;
u8 LCD_Mode5[] = "Enter Option:" ;
u8 LCD_MOde6[] = "Failed to Login " ;
u8 LCD_MOde7[] = "Warning,Someone is trying to robe you!!! " ;

//////////////////////////

/* Choose Run Mode */ 
u8 LCD_Admin[]   = "A-ADMIN" ;
u8 LCD_User[]    = "U-User" ;
//////////////////////////////

/* Commands Requirement */ 
u8 LCD_PASS[]    = "Enter Password:" ;
u8 LCD_DelPass[] = "Enter Old Password" ;
u8 LCD_EnterPass[15] =  "Enter Pass" ;
u8 LCD_EnterPass2[]  =  "Enter New Pass" ;
u8 Invalid_Command[] = "Invalid Command " ;
u8 Done[] = "Done" ;
///////////////////////////////

/* For Trials Only */ 
u8 Trials[10] ;
u8 loc_new_pass[3];
///////////////////////////////

u8 LCD_Welcome[]         =	   "Welcome" ;
u8 LCD_User_OpenDoor[20] =     "1-Open Door " ;
u8 LCD_User_OpenAC[20]   =     "2-Open AC " ;
u8 LCD_User_LED[]        =     "3-Open Media Player" ;
///////////////////////////////

/* Check Password Function */
u8 LCD_WrongPass[]       =	   "Wrong Password";
u8 LCD_TryAgain []		 =	   "Try Again" ;
u8 LCD_OutOfTrials[]     =	   "Out Of Trials " ;
///////////////////////////////

/* Action on Command Sent */
u8 LCD_Door_Open_Successfully[]      = "The Door Open " ;
u8 LCD_User_OpenAC_Successfully[]    = "The AC Open  " ;
u8 LCD_User_Successfully[]           = "Media Player Opened " ;
u8 LCD_Door_Close_Successfully[]     = "The Door Closed " ;
u8 LCD_User_CloseAC_Successfully[]   = "The AC Closed  " ;
u8 LCD_UserClose_Successfully[]      = "Media Player Closed " ;
///////////////////////////////

/* Function Declarations */
void Check_Admin(void) ;
void AddPassword (void) ;
void Add_User(void) ;
void App_Init(void) ;
void Change_User_Password(u8* Copy_Oldpassword,u8* Copy_Newpassword) ;
void Delete_User(u8* Copy_Password,u8 Num_users) ;
void Open_Door(void) ;
void Media_Player(void) ;
void Open_AC(void) ;
void Choose_Operation(void) ;
void Check_Pass(u8* arr) ;
void User_List(void);
void Password_Checking (void) ;
void lcd_view();
///////////////////////////////



int main(void)
{

	App_Init() ;
	Check_Admin() ;


	while(1)
	{
		UART_State = UART_u8ReceiveData();
		UART_VidSendChar('\r') ;
		Check_Admin();
	}
	
}

void Check_Admin(void)
{

	LCD_voidClear(); 
	/* Check User or ADMIN */
	LCD_voidWriteString(LCD_Admin) ;
	LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0) ;
	LCD_voidWriteString(LCD_User) ;

	UART_State = UART_u8ReceiveData() ;
	UART_VidSendChar('\r') ;
	
	LCD_voidClear();
	
	/* User or ADMIN Options */ 
	if (UART_State == 'A')
	{
		LCD_voidWriteString(LCD_PASS) ;
		/* All Modes */
		UART_VidSendString(LCD_Mode1) ;
		UART_VidSendChar('\r') ;
		UART_VidSendString(LCD_Mode2) ;
		UART_VidSendChar('\r') ;
		UART_VidSendString(LCD_Mode3) ;
		UART_VidSendChar('\r') ;
		UART_VidSendString(LCD_Mode4) ;
		UART_VidSendChar('\r') ;
				
		/* Choose Mode */
		UART_State = UART_u8ReceiveData() ;
		UART_VidSendChar('\r') ;

		
		if (UART_State == 'D')
		{
			UART_VidSendString(LCD_User_OpenDoor) ;
			UART_VidSendChar('\r') ;
			UART_VidSendString(LCD_User_OpenAC) ;
			UART_VidSendChar('\r') ;
			UART_VidSendString(LCD_User_LED) ;
			UART_VidSendChar('\r') ;
			UART_VidSendString(LCD_Mode5) ;
			UART_VidSendChar('\r') ;
			UART_State = UART_u8ReceiveData() ;
			UART_VidSendChar('\r') ;

		}
		
		Choose_Operation() ;
	}
	
	
	
	else if (UART_State=='U')
	{
		LCD_voidWriteString(LCD_PASS) ;
		_delay_ms(250);
		
		while (Loc_GetChar!='/')
		{
			
		Loc_GetChar = Keypad_U8GetKeyPressed();
		
		if (Loc_GetChar != 255)
		{
			switch(Loc_GetChar)
			{
				case '=':
						LCD_voidClear();
						Check_Pass(Loc_Password);
						Loc_Count = 0 ;
									
						while (Error_Flag==0)
							{
								Password_Checking () ;
							}
						break;
						
									
				default:
						LCD_voidSendChar('*');
						Loc_Password[Loc_Count]=Loc_GetChar;
						Loc_Count++;
						break;
			}
		}
	}
}
	
	else 
	{
		UART_VidSendString(Invalid_Command) ;
		UART_VidSendChar('\r') ;
	}
	
}

void Choose_Operation(){


	switch (UART_State)
	{
		case 'A': 

							Add_User() ;
							UART_VidSendString(Done) ;	
							UART_VidSendChar('\r') ;					
							break;
							
							
		case 'B': 
							UART_VidSendChar('\r') ;
							Delete_User(UART_PassRx,Gol_Counter);
							UART_VidSendString(Done) ;
							UART_VidSendChar('\r') ;
							break;
							
							
		case 'C':			
							Change_User_Password(UART_PassRx,loc_new_pass);
							UART_VidSendString(Done) ;
							UART_VidSendChar('\r') ;
							break;
							
							
		case 'Q' :		    UART_VidSendChar('\r') ;
							Check_Admin() ;
							break;	
							
		default :			UART_VidSendString(Invalid_Command) ;
							UART_VidSendChar('\r') ;		

	}
	
}

void Add_User(void)
{

	AddPassword() ;
	EEPROM_voidWritePage( (0x0000+(4*Address_Index)) , UART_PassRx,3) ;
	Address_Index++ ;
	Gol_Counter++;

		
}

void AddPassword ()
{
	UART_VidSendString(LCD_EnterPass);
	UART_VidSendChar('\r') ;
	/* Adjust Password */
	UART_IndexRx = UART_VidReceiveString(UART_PassRx) ;
	UART_VidSendChar('\r') ;

}


void Open_Door()
{
	
	SPI_voidTransmiter('O');
	
	
	if (Glob_Door=='Y')
	{
		LCD_voidClear();
		LCD_voidWriteString(LCD_Door_Open_Successfully);
		Glob_Door='N';
		
	}
	else if (Glob_Door=='N')
	{
		LCD_voidClear();
		LCD_voidWriteString(LCD_Door_Close_Successfully);
		Glob_Door='Y';
		
	}
	
	
} 

void Media_Player()
{
	SPI_voidTransmiter('M');
	
	if (Glob_M=='Y')
	{
		LCD_voidClear();
		LCD_voidWriteString(LCD_User_Successfully);
		Glob_M='N';
		
	}
	else if (Glob_M=='N')
	{
		LCD_voidClear();
		LCD_voidWriteString(LCD_UserClose_Successfully);
		Glob_M='Y';
		
	}
}


void Open_AC()
{
	SPI_voidTransmiter('A');

	
	if (Glob_AC=='Y')
	{
		LCD_voidClear();
		LCD_voidWriteString(LCD_User_OpenAC_Successfully);
		Glob_AC='N';
		
	}
	else if (Glob_AC=='N')
	{
		LCD_voidClear();
		LCD_voidWriteString(LCD_User_CloseAC_Successfully);
		Glob_AC='Y';
	}
}

void lcd_view()
{
	LCD_voidClear();
	LCD_voidWriteString(LCD_Welcome) ;
	LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0) ;
	LCD_voidWriteString(LCD_User_OpenDoor) ;
	LCD_voidGoToSpecificPosition(LCD_LINE_THREE,0) ;
	LCD_voidWriteString(LCD_User_OpenAC) ;
	LCD_voidGoToSpecificPosition(LCD_LINE_FOUR,0) ;
	LCD_voidWriteString(LCD_User_LED) ;
}


void Change_User_Password(u8* Copy_Oldpassword,u8* Copy_Newpassword)

{
	u8  Loc_Index ;
	UART_VidSendChar('\r') ;
	UART_VidSendString(LCD_DelPass);
	UART_VidSendChar('\r') ;
	
	UART_IndexRx = UART_VidReceiveString(UART_PassRx) ;
	UART_VidSendChar('\r') ;

	UART_VidSendString(LCD_EnterPass2);
	UART_VidSendChar('\r') ;
	
	UART_IndexRx = UART_VidReceiveString(loc_new_pass) ;
	UART_VidSendChar('\r') ;
	
	Loc_Index=EEPROM_u8Search(Copy_Oldpassword,Gol_Counter);
	EEPROM_voidSendDataPage(Loc_Index,Copy_Newpassword);
	
}

void Delete_User(u8* Copy_Password,u8 Num_users)
{
	
	u8 Loc_Index = 0 ;
	u8 Loc_arr[4]={'>','>','>','-'};
	UART_VidSendString(LCD_DelPass) ;
	UART_VidSendChar('\r') ;
	UART_IndexRx = UART_VidReceiveString(UART_PassRx) ;
	UART_VidSendChar('\r') ;
	Loc_Index=EEPROM_u8Search(Copy_Password,Num_users);
	EEPROM_voidSendDataPage(Loc_Index,Loc_arr);
	//Gol_Counter--;
	
}



void Check_Pass(u8* arr)
{
	

	u8 Loc_Index=500;
	u8 Local_u8Counter =0  ; 
	Loc_Index =EEPROM_u8Search (arr,Gol_Counter) ;
	

	if (arr[3] != '-')
	{
		Local_u8Counter ++ ;
		
	}
	
	 if (  (Loc_Index !=250) && (Local_u8Counter==0) )
	{
		Loc_flag = 0 ;
		Error_Flag = 1 ;
		User_List();
	}
	else
	{
		if (Loc_flag!=2)
		{
			LCD_voidClear();
			LCD_voidWriteString(LCD_WrongPass);
			_delay_ms(250);
			LCD_voidClear();
			_delay_ms(250);
			LCD_voidWriteString(LCD_TryAgain);
			_delay_ms(250);
			LCD_voidClear() ;
			LCD_voidWriteString(LCD_EnterPass);
			// Print Failed to Login 
			UART_VidSendString(LCD_MOde6);
			UART_VidSendChar('\r') ;
			Loc_flag++;
			Error_Flag = 1 ;


		}
		else if (Loc_flag == 2)
		{
			UART_VidSendString(LCD_MOde7);
			UART_VidSendChar('\r') ;
			LCD_voidWriteString(LCD_OutOfTrials) ;
			_delay_ms(500);
			LCD_voidClear() ;
			Dio_voidWritepinchannel(PC6,PIN_HIGH);
			Loc_flag = 0 ;
		}

		}
		
	for (Local_u8Counter = 0 ; Local_u8Counter<4 ; Local_u8Counter++)
	{
		Loc_Password[Local_u8Counter]='-'; 
	}

	
}

void User_List()
{
	
	u8 Loc_GetChar=255;
	LCD_voidClear();

	LCD_voidWriteString(LCD_Welcome) ;
	LCD_voidGoToSpecificPosition(LCD_LINE_TWO,0) ;
	LCD_voidWriteString(LCD_User_OpenDoor) ;
	LCD_voidGoToSpecificPosition(LCD_LINE_THREE,0) ;
	LCD_voidWriteString(LCD_User_OpenAC) ;
	LCD_voidGoToSpecificPosition(LCD_LINE_FOUR,0) ;
	LCD_voidWriteString(LCD_User_LED) ;
	
	while(Loc_GetChar!='/')
	{

		Loc_GetChar = Keypad_U8GetKeyPressed();
	
		if (Loc_GetChar != 255)
		{
			switch(Loc_GetChar)
			{
				case '1':
				Open_Door();

				break;
				case '2':
				Open_AC();
				break;
				case '3' :
				Media_Player();
				break;
				default:
				LCD_voidWriteString(Invalid_Command) ;
				_delay_ms(1000);
				LCD_voidClear() ; 
				break;
			}
			_delay_ms(1000);
			lcd_view() ;
		}
	}
	
}


void App_Init()
{

	/*Make The Buzzer Output */
	Dio_voidSetpinchmode(PC6,OUTPUT_LOW);
	
	/* SPI */ 
	//SS
	Dio_voidSetpinchmode(PA4,OUTPUT_LOW);
	//MOSI
	Dio_voidSetpinchmode(PB5,OUTPUT_LOW);
	//MISO
	Dio_voidSetpinchmode(PB6,INPUT);
	//SCK
	Dio_voidSetpinchmode(PB7,OUTPUT_LOW);
	
	
	LCD_voidInit();
	Keypad_VidInit();
	UART_VidInit();
	SPI_voidInialize() ;
	EEPROM_voidInit() ;
}


void Password_Checking ()
{
	Loc_GetChar = Keypad_U8GetKeyPressed();
		
	if (Loc_GetChar == '=')
	{
		Check_Pass(Loc_Password);
		Loc_Count = 0 ;
	}
	else if (Loc_GetChar != 255)
	{
		LCD_voidSendChar('*');
		Loc_Password[Loc_Count]=Loc_GetChar;
		Loc_Count++;
	}
	
	Loc_Count=0;
	
}