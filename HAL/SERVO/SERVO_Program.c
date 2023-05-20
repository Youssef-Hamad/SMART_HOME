/*
 * SERVO_Program.c
 *
 *  Created on: Apr 9, 2023
 *      Author: Youssef
 */

#include "../../INC/STD_TYPES.h"
#include "../../INC/MATH_BIT.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/GPT/GPT_Interface.h"

#include "Servo_Config.h"
#include "Servo_Private.h"
#include "SERVO_Interface.h"

void Servo_init(void){
	DIO_s8SetPinDirection(SERVO_PIN,DIO_U8_PIN_DIR_OUTPUT);
}
u8 Servo_map(s32 ServoMinAngle,s32 ServoMaxAngle,s32 DutyCycleMinValue,s32 DutyCycleMaxValue,s32 DesiredAngle){

	u8 Local_u8DesiredDutyCyle=0;
	s32 DutyDiff= (DutyCycleMaxValue - DutyCycleMinValue);
	s32 AngleDiff= (ServoMaxAngle- ServoMinAngle);
	s32 DesAngleDiff= (DesiredAngle-ServoMinAngle);
	Local_u8DesiredDutyCyle=((u64)(DesAngleDiff*DutyDiff)/AngleDiff);
	Local_u8DesiredDutyCyle+=DutyCycleMinValue;

	return Local_u8DesiredDutyCyle;
}

void Servo_VoidSetAngle(u8 Copy_u8Angle){
	PWM_VoidStopPWM();
//	u8 AngleCalibrationError=Copy_u8Angle+Degree_Error;
//	u8 Local_u8DesireDutyCycle=Servo_map(SERVO_MIN_ANGLE,SERVO_MAX_ANGLE,SERVO_MIN_DUTY_CYCLE,SERVO_MAX_DUTY_CYCLE,AngleCalibrationError);
	PWM_VoidStartPWM(SERVO_FREQ,Copy_u8Angle,CHANNEL_B);
}

void Servo_VoidStop(void){
	PWM_VoidStopPWM();
}
