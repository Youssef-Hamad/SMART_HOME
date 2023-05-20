/*
 * TEMP_SENSOR_Program.c
 *
 *  Created on: May 20, 2023
 *      Author: DWEEBSTARK
 */

#ifndef HAL_TEMP_SENSOR_TEMP_SENSOR_PROGRAM_C_
#define HAL_TEMP_SENSOR_TEMP_SENSOR_PROGRAM_C_

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/GPT/GPT_Interface.h"
#include "../../MCAL/GIE/GIE_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"

#include "TEMP_SENSOR_Interface.h"
#include "../../MCAL/ADC/ADC_Private.h"
#define MAX_DIGITAL_READING 		0X3FF
#define MAX_TEMP					149536

void TempSensorVoidInit(u8 Copyu8PortId,u8 Copyu8PinId,Cbf UserFunc){
	DIO_s8SetPinDirection(Copyu8PortId,Copyu8PinId,DIO_U8_PIN_DIR_INPUT);//FOR SENSOR READINGS
	DIO_s8SetPinDirection(DIO_U8_PORTB,DIO_U8_PIN6,DIO_U8_PIN_DIR_OUTPUT);//FOR FAN(LED)
	ADC_VoidSetCallBack(UserFunc);
	GIE_VoidEnable();
	TIMER0_VoidInit();
	ADC_VoidInit();
}

u32 TempReading(void){
	u16 localReading=0;
	localReading=ADC_TWO_BYTE_DATA;
	u32 Degree=0;
	Degree=(localReading * MAX_TEMP)/MAX_DIGITAL_READING;//MAXTMEP IS MULTIPLIED BY 1000 AS A FACTOR
	Degree/=1000;
	/*Degree=(Reading x 149.536)÷1024
	 * If Reading less than 30c, Following this equation 30c is 0xce or 206*/
	return Degree;
}
#endif /* HAL_TEMP_SENSOR_TEMP_SENSOR_PROGRAM_C_ */
