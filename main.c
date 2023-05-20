/*
 * main.c
 *
 *  Created on: May 16, 2023
 *      Author: DWEEBSTARK
 */

#include "INC/MATH_BIT.h"
#include "INC/STD_TYPES.h"
//
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/I2C/I2C_Interface.h"
#include "MCAL/UART/UART_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "MCAL/GPT/GPT_Interface.h"
#include "MCAL/GIE/GIE_Interface.h"

#include "HAL/EEPROM/EEPROM_Interface.h"
#include "HAL/SERVO/SERVO_Interface.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/BUZZER/Buzzer_Interface.h"
#include "HAL/TEMP_SENSOR/TEMP_SENSOR_Interface.h"
#include "HAL/DCMOTOR/DCMOTOR_Interface.h"

// #include "HAL/LCD/LCD_Interface.h"
UART_Config User = {RECEIVE_INT_DISABLE,
		SEND_INT_DISABLE,
		EMPTY_DATA_INT_DISABLE,
		CHAR_SIZE_8_,
		ASYNCHRONOUS_MODE,
		PARITY_DISABLE,
		STOP_1_BIT,
		SEND_RISE_CLOCK,
		PEER_TO_PEER_MODE,
		Rate_9600};



#define USER1_NAME_LOC			0x10
#define USER1_PASS_LOC			0x15
#define USER2_NAME_LOC			0x20
#define USER2_PASS_LOC			0x25
#define USER3_NAME_LOC			0x30
#define USER3_PASS_LOC			0x35

#define ADMIN_MODE '2'
#define USER_MODE '1'
#define CORRECT 1
#define FALSE 0
#define EXIT 9
u8 STR_u8length(string *str);
u8 STR_u8compare(string *str1, string *str2);
u8 AdminMode(void);
u8 UserMode(void);
void UserFunc(void);

	pstring UserWel1 ="Hey!";
	string User_username[6];
void main(void)
{

	pstring Wel = "Please Choose Mode USER (1) OR ADMIN (2) \n\r";
	pstring Wel1 = "Admin Mode Selected, Enter Admin USERNAME, 3 ATTEMPTS ONLY USERNAME & PASSWORD \n\r";
	pstring Wel2 = "User Mode Selected, Enter User USERNAME, 3 ATTEMPTS ONLY for USERNAME & PASSWORD \n\r";
	pstring UserWel2 = "\n\rPlease Enter your Password\n\r";

	UART_Init(&User);
	//	LCD_VoidInit();
	EEPROM_VoidInit();

	string Ans[1];
	string Admin_user[6];
	string Admin_pass[5];

	string User_pass[5];

	string A_U[6] = {0, 0, 0, 0, 0, 0};
	string A_P[5] = {0, 0, 0, 0, 0};

	string U_U[6];
	string U_P[5];

	EEPROM_VoidReceiveBuffer(0, Admin_user, 5);
	EEPROM_VoidReceiveBuffer(6, Admin_pass, 4);

	UART_SendStringSync(Wel);
	UART_ReceiveBufferSync(Ans, 1);

	u8 Counter = '3';
	if (Ans[0] == ADMIN_MODE)
	{
		UART_SendStringSync(Wel1);
		UART_ReceiveBufferSync(A_U, 5);

		while (Counter > '0')
		{
			if (STR_u8compare(Admin_user, A_U)==CORRECT)
			{
				UART_SendStringSync("Enter Admin PASSWORD,\n\r");
				UART_ReceiveBufferSync(A_P, 4);
				if (STR_u8compare(Admin_pass, A_P) == CORRECT)
				{
					AdminMode();
					break;
				}
				else
				{
					--Counter;
					UART_SendStringSync("Wrong PASSWORD, ");
					UART_SendBufferSync((pstring)(&Counter), 1);
					UART_SendStringSync(" Entries left \n\r");
				}
			}
			else
			{
				--Counter;
				UART_SendStringSync("Wrong USERNAME, ");
				UART_SendBufferSync((pstring)(&Counter), 1);
				UART_SendStringSync(" Entries left \n\r");
				UART_ReceiveBufferSync(A_U, 5);
			}
		}
	}
	else if (Ans[0] == USER_MODE)
	{
		// Check if the user selected user mode
		UART_SendStringSync(Wel2); // Send a prompt to enter the username
		while (Counter > '0')
		{
			// Enter a loop with a counter that decrements each time a login attempt is made
			EEPROM_VoidReceiveBuffer(USER1_NAME_LOC, User_username, 5); // Read the stored user username from the EEPROM
			UART_ReceiveBufferSync(U_U, 5);					  // Receive the entered username from the user
			if (STR_u8compare(User_username, U_U) == CORRECT)
			{												  // Check if the entered username matches the stored usernames
				EEPROM_VoidReceiveBuffer(USER1_PASS_LOC, User_pass, 4); // Read the stored user password from the EEPROM
				UART_SendStringSync(UserWel2);				  // Send a prompt to enter the user password
				Counter = '3';								  // Reset the counter
				// Enter a loop with a counter that decrements each time a login attempt is made
				while (Counter > '0')
				{

					UART_ReceiveBufferSync(U_P, 4); // Receive the entered password from the user
					if (STR_u8compare(User_pass, U_P) == CORRECT)
					{				// Check if the entered password matches the stored password
						UserMode(); // Call the UserMode function and exit the loop
						break;
					}
					else
					{
						// Decrement the counter if the password is incorrect
						--Counter;
						// Send an error message indicating that the entered password is incorrect
						UART_SendStringSync("Wrong PASSWORD, ");
						// Send an error message indicating the number of attempts remaining
						UART_SendBufferSync((pstring)(&Counter), 1);
						UART_SendStringSync(" Entries left \n\r");
					}
				}
			}
			else
			{
				// Move to the next stored username in the EEPROM
				EEPROM_VoidReceiveBuffer(USER2_NAME_LOC, User_username, 5);
				// Check if the entered username matches the next stored username
				if (STR_u8compare(User_username, U_U) == CORRECT)
				{
					EEPROM_VoidReceiveBuffer(USER2_PASS_LOC, User_pass, 4); // Read the stored password for this username from the EEPROM
					UART_SendStringSync(UserWel2);				  // Send a prompt to enter the user password
					Counter = '3';								  // Reset the counter

					// Enter a loop with a counter that decrements each time a login attempt is made
					while (Counter > '0')
					{
						// Receive the entered password from the user
						UART_ReceiveBufferSync(U_P, 4);
						// Check if the entered password matches the stored password
						if (STR_u8compare(User_pass, U_P) == CORRECT)
						{
							UserMode(); // Call the UserMode function and exit the loop
							break;
						}
						else
						{
							// Decrement the counter if the password is incorrect
							--Counter;
							// Send an error message indicating that the entered password is incorrect
							UART_SendStringSync("Wrong PASSWORD, ");
							// Send an error message indicating the number of attempts remaining
							UART_SendBufferSync((pstring)(&Counter), 1);
							UART_SendStringSync(" Entries left \n\r");
						}
					}
				}
				else
				{
					// Move to the next stored username in the EEPROM
					EEPROM_VoidReceiveBuffer(USER3_NAME_LOC, User_username, 5);
					// Check if the entered username matches the next stored username
					if (STR_u8compare(User_username, U_U) == CORRECT)
					{
						EEPROM_VoidReceiveBuffer(USER3_PASS_LOC, User_pass, 4); // Read the stored password for this username from the EEPROM
						UART_SendStringSync(UserWel2);				  // Send a prompt to enter the user password
						Counter = '3';								  // Reset the counter

						// Enter a loop with a counter that decrements each time a login attempt is made
						while (Counter > '0')
						{

							UART_ReceiveBufferSync(U_P, 4); // Receive the entered password from the user
							// Check if the entered password matches the stored password
							if (STR_u8compare(User_pass, U_P) == CORRECT)
							{
								UserMode(); // Call the UserMode function and exit the loop
								break;
							}
							else
							{
								// Decrement the counter if the password is incorrect
								--Counter;
								// Send an error message indicating that the entered password is incorrect
								UART_SendStringSync("Wrong PASSWORD, ");
								// Send an error message indicating the number of attempts remaining
								UART_SendBufferSync((pstring)(&Counter), 1);
								UART_SendStringSync(" Entries left \n\r");
							}
						}
					}
					else
					{
						// Decrement the counter if the username is incorrect
						--Counter;
						// Send an error message indicating that the entered username is incorrect
						UART_SendStringSync("Wrong USERNAME, ");
						// Send an error message indicating the number of attempts remaining
						UART_SendBufferSync((pstring)(&Counter), 1);
						UART_SendStringSync(" Entries left \n\r");
					}
				}
			}
		}
	}
	else
	{
		UART_SendStringSync("Wrong Mode, Aborting! \n\r");
		Buzzer_Voidinit();
		Buzzer_VoidAlarm();
	}
	while (1)
	{
	}
}

u8 AdminMode(void)
{
	while(1){
		string Admin_Ans[1]={0};
		string New_Cred[6]={0};

		UART_SendStringSync("HI ADMIN! \n\r");
		UART_SendStringSync("Send 1 to modify first user\n\r2 to modify Second user\n\r"
				"3 to modify third user\n\rAny other key to End\n\r");
		UART_ReceiveBufferSync(Admin_Ans,1);
		if(Admin_Ans[0]=='1'){//If first user is chosen
			Admin_Ans[0]=0;
			UART_SendStringSync("Send 1 to modify UserName\n\r2 to modify Password\n\r");
			UART_ReceiveBufferSync(Admin_Ans,1);
			if(Admin_Ans[0]=='1'){//If username is chosen
				UART_SendStringSync("Please send your new username\n\r");
				UART_ReceiveBufferSync(New_Cred,5);
				EEPROM_VoidSendBuffer(USER1_NAME_LOC,New_Cred,5);
				UART_SendStringSync("Username Has been modified\n\r");
			}
			else if(Admin_Ans[0]=='2'){//If password is chosen
				UART_SendStringSync("Please send your new password\n\r");
				UART_ReceiveBufferSync(New_Cred,4);
				EEPROM_VoidSendBuffer(USER1_PASS_LOC,New_Cred,4);
				UART_SendStringSync("Password Has been modified\n\r");
			}
			else{
				UART_SendStringSync("Invalid choice\n\r"); // Send an error message to the user
			}
		}
		else if(Admin_Ans[0]=='2'){
			Admin_Ans[0]=0;
			UART_SendStringSync("Send 1 to modify UserName\n\r2 to modify Password\n\r");
			UART_ReceiveBufferSync(Admin_Ans,1);
			if(Admin_Ans[0]=='1'){//If username is chosen
				UART_SendStringSync("Please send your new username\n\r");
				UART_ReceiveBufferSync(New_Cred,5);
				EEPROM_VoidSendBuffer(USER2_NAME_LOC,New_Cred,5);
				UART_SendStringSync("Username Has been modified\n\r");
			}
			else if(Admin_Ans[0]=='2'){//If password is chosen
				UART_SendStringSync("Please send your new password\n\r");
				UART_ReceiveBufferSync(New_Cred,4);
				EEPROM_VoidSendBuffer(USER2_PASS_LOC,New_Cred,4);
				UART_SendStringSync("Password Has been modified\n\r");
			}
			else{
				UART_SendStringSync("Invalid choice\n\r"); // Send an error message to the user
			}
		}
		else if(Admin_Ans[0]=='3'){
			Admin_Ans[0]=0;
			UART_SendStringSync("Send 1 to modify UserName\n\r2 to modify Password\n\r");
			UART_ReceiveBufferSync(Admin_Ans,1);
			if(Admin_Ans[0]=='1'){//If username is chosen
				UART_SendStringSync("Please send your new username\n\r");
				UART_ReceiveBufferSync(New_Cred,5);
				EEPROM_VoidSendBuffer(USER3_NAME_LOC,New_Cred,5);
				UART_SendStringSync("Username Has been modified\n\r");
			}
			else if(Admin_Ans[0]=='2'){//If password is chosen
				UART_SendStringSync("Please send your new password\n\r");
				UART_ReceiveBufferSync(New_Cred,4);
				EEPROM_VoidSendBuffer(USER3_PASS_LOC,New_Cred,4);
				UART_SendStringSync("Password Has been modified\n\r");
			}
			else{
				UART_SendStringSync("Invalid choice\n\r"); // Send an error message to the user
			}
		}
		else{
			UART_SendStringSync("Pleased to serve you, Bye!"); // Send a farewell message to the user
			return EXIT; // End the UserMode function and return the exit code
		}
	}
}
u8 UserMode(void)
{
	UART_SendStringSync(UserWel1);				  // Send a welcome message to the user
	UART_SendStringSync(User_username);			  // Send the user's username

	string Reply[1]={0}; // Initialize an array to store the user's reply
	string LedAns[1]={0}; // Initialize an array to store the user's LED choice
	string TvAns[1]={0}; // Initialize an array to store the user's LED choice
	UART_SendStringSync("\n\rWelcome to Smart Home\n\r"); // Send a welcome message to the user
	DCMOTOR_VoidInit();
	TempSensorVoidInit(TEMPSENSOR_PIN,UserFunc); //Initialize Auto fan mode with Temprature sensor
	while (1) // Enter an infinite loop
	{
		UART_SendStringSync("Send\n\r1 to Open the door \n\r2 to Turn On/Off the lights\n\r3 to Turn On/Off the TV \n\rAny other key to End\n\r"); // Send the options menu to the user

		UART_ReceiveBufferSync(Reply, 1); // Receive the user's reply

		if (Reply[0] == '1') // Check if the user selected to open the door
		{
			Servo_init(); // Initialize the servo motor
			Servo_VoidSetAngle(90); // Set the servo angle to 90 degrees
			_delay_ms(600); // Delay for 600 ms
			Servo_VoidSetAngle(0); // Setthe servo angle to 0 degrees
			_delay_ms(600); // Delay for 600 ms
			Servo_VoidStop(); // Stop the servo motor
		}
		else if (Reply[0] == '2') // Check if the user selected to turn on/off the lights
		{
			LED_Voidinit(LED_1); // Initialize the LED
			UART_SendStringSync("Please choose 1 for ON or 2 for OFF\n\r"); // Prompt the user to choose ON or OFF
			UART_ReceiveBufferSync(LedAns,1); // Receive the user's LED choice

			if(LedAns[0]=='1'){ // Check if the user chose to turn the LED on
				LED_turnon(LED_1); // Turn the LED on
			}
			else if(LedAns[0]=='2'){ // Check if the user chose to turn the LED off
				LED_turnoff(LED_1); // Turn the LED off
			}
			else{ // Handle an invalid LED choice
				UART_SendStringSync("Invalid choice\n\r"); // Send an error message to the user
			}
		}
		else if (Reply[0] == '3') // Check if the user selected to turn on/off the TV
		{
			TV_Voidinit(TV_1);
			UART_SendStringSync("Please choose 1 for ON or 2 for OFF\n\r"); // Prompt the user to choose ON or OFF
			UART_ReceiveBufferSync(TvAns,1); // Receive the user's TV choice
			if(TvAns[0]=='1'){ // Check if the user chose to turn the LED on
				LED_turnon(TV_1); // Turn the LED on
			}
			else if(TvAns[0]=='2'){ // Check if the user chose to turn the LED off
				LED_turnoff(TV_1); // Turn the LED off
			}
			else{ // Handle an invalid LED choice
				UART_SendStringSync("Invalid choice\n\r"); // Send an error message to the user
			}
		}
		else // Handle the case where the user selects any other key
		{
			UART_SendStringSync("Pleased to serve you, Bye!"); // Send a farewell message to the user
			return EXIT; // End the UserMode function and return the exit code
		}
	}
}


void UserFunc(void){
	u32 TempDegree=0;
	TempDegree=TempReading();
	if(TempDegree>=30){
		DCMOTOR_VoidClockWise();
	}
	else{
		DCMOTOR_VoidTurnOff();
	}
	TIMER0_VoidLowerOVFlag();
}

u8 STR_u8length(string *str)
{
	u8 i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

u8 STR_u8compare(string *str1, string *str2)
{
	u8 i;
	if (STR_u8length(str1) != STR_u8length(str2))
	{
		return FALSE;
	}
	else
	{
		for (i = 0; str2[i] != '\0'; i++)
		{
			if (str1[i] != str2[i])
				return FALSE;
		}
		return CORRECT;
	}
}
