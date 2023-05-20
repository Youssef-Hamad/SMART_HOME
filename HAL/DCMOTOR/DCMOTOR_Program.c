/*
 * DCMOTOR_Program.c
 *
 *  Created on: 2 Apr 2023
 *      Author: Youssef
 */

#include "../../MCAL/DIO/DIO_Interface.h"
#include "DCMOTOR_Config.h"
#include "DCMOTOR_Interface.h"



void DCMOTOR_VoidInit(){
	DIO_s8SetPinDirection(MOTOR_PIN1,DIO_U8_PIN_DIR_OUTPUT);//Pin for controlling Relay1
	DIO_s8SetPinDirection(MOTOR_PIN2,DIO_U8_PIN_DIR_OUTPUT);//Pin for controlling Relay2
}
void DCMOTOR_VoidCounterClockWise(){
	DIO_s8SetPinValue(MOTOR_PIN1,DIO_U8_PIN_LOW);
	DIO_s8SetPinValue(MOTOR_PIN2,DIO_U8_PIN_HIGH);
}
void DCMOTOR_VoidClockWise(){
	DIO_s8SetPinValue(MOTOR_PIN2,DIO_U8_PIN_LOW);
	DIO_s8SetPinValue(MOTOR_PIN1,DIO_U8_PIN_HIGH);
}
void DCMOTOR_VoidTurnOff(){
	DIO_s8SetPinValue(MOTOR_PIN1,DIO_U8_PIN_HIGH);
	DIO_s8SetPinValue(MOTOR_PIN2,DIO_U8_PIN_HIGH);
}
