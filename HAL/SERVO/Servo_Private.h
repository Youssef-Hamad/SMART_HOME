/*
 * Servo_Private.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Youssef
 */

#ifndef HAL_SERVO_SERVO_PRIVATE_H_
#define HAL_SERVO_SERVO_PRIVATE_H_


#define SERVO_FREQ						50
#define SERVO_MIN_ANGLE					0
#define SERVO_MAX_ANGLE					180
/*Ideally Duty Cycle should be from 5 to 10 (Error could be done better handled wtih
 * Angles instead of Duty cycle as ranges between Min and max Angles is higher
 * Ex: Min Angle could be:-7 , and Max Angle could be :190*/
#define SERVO_MIN_DUTY_CYCLE			1
#define SERVO_MAX_DUTY_CYCLE			12

#define Degree_Error					10
#endif /* HAL_SERVO_SERVO_PRIVATE_H_ */
