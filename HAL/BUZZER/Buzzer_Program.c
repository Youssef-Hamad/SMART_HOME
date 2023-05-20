/*
 * Buzzer_Program.c
 *
 *  Created on: May 20, 2023
 *      Author: DWEEBSTARK
 */


#include "Buzzer_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/GPT/GPT_Interface.h"

void Buzzer_Voidinit(void){
	DIO_s8SetPinDirection(DIO_U8_PORTB,DIO_U8_PIN3,DIO_U8_PIN_DIR_OUTPUT);
}
void Buzzer_VoidStart(void){

	TIMER0_VoidPWM();
}
void Buzzer_VoidStop(void){
	TIMER0_VoidStop();
}
void Buzzer_VoidAlarm(void){
	for(u8 Local_counter=0;Local_counter<3;Local_counter++){
		DIO_s8SetPinValue(DIO_U8_PORTB,DIO_U8_PIN3,DIO_U8_PIN_HIGH);
		_delay_ms(550);
		DIO_s8SetPinValue(DIO_U8_PORTB,DIO_U8_PIN3,DIO_U8_PORT_DIR_LOW);
		_delay_ms(550);
	}
}
