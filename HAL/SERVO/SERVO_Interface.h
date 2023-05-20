/*
 * SERVO_Interface.h
 *
 *  Created on: Apr 9, 2023
 *      Author: Youssef
 */

#ifndef HAL_SERVO_SERVO_INTERFACE_H_
#define HAL_SERVO_SERVO_INTERFACE_H_


void Servo_init(void);
void Servo_VoidStop(void);
u8 Servo_map(s32 ServoMinAngle,s32 ServoMaxAngle,s32 DutyCycleMinValue,s32 DutyCycleMaxValue,s32 DesiredAngle);
void Servo_VoidSetAngle(u8 Angle);

#endif /* HAL_SERVO_SERVO_INTERFACE_H_ */
