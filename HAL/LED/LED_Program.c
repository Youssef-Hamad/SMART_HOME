/*
 * LED_Program.c
 *
 *  Created on: May 20, 2023
 *      Author: DWEEBSTARK
 */

#include "../../MCAL/DIO/DIO_Interface.h"

#include "LED_Interface.h"


void TV_Voidinit(u8 Copy_U8_port ,u8 Copy_U8_pin){
	DIO_s8SetPinDirection(Copy_U8_port,Copy_U8_pin,DIO_U8_PIN_DIR_OUTPUT);
}
void LED_Voidinit(u8 Copy_U8_port ,u8 Copy_U8_pin){
	DIO_s8SetPinDirection(Copy_U8_port,Copy_U8_pin,DIO_U8_PIN_DIR_OUTPUT);
}
void LED_turnon(u8 Copy_U8_port ,u8 Copy_U8_pin){
	DIO_s8SetPinValue(Copy_U8_port ,Copy_U8_pin,DIO_U8_PIN_HIGH);
}
void LED_turnoff(u8 Copy_U8_port ,u8 Copy_U8_pin){
	DIO_s8SetPinValue(Copy_U8_port,Copy_U8_pin,DIO_U8_PIN_LOW);
}
