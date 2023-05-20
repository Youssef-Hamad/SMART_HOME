/*
 * LED_Interface.h
 *
 *  Created on: May 20, 2023
 *      Author: DWEEBSTARK
 */

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_
#include "LED_Config.h"


void LED_Voidinit(u8 Copy_U8_port ,u8 Copy_U8_pin);
void LED_turnon(u8 Copy_U8_port ,u8 Copy_U8_pin);
void LED_turnoff(u8 Copy_U8_port ,u8 Copy_U8_pin);
void TV_Voidinit(u8 Copy_U8_port ,u8 Copy_U8_pin);
#endif /* HAL_LED_LED_INTERFACE_H_ */
