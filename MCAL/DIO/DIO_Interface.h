/*
 * interface.h
 *
 *  Created on: Mar 25, 2023
 *      Author: DWEEBSTARK
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#include <util/delay.h>
#include "../../INC/STD_TYPES.h"
#include "../../INC/MATH_BIT.h"
#include "DIO_Private.h"
#include "DIO_config.h"

#define DIO_U8_PORTA 				1
#define DIO_U8_PORTB				2
#define DIO_U8_PORTC 				3
#define DIO_U8_PORTD 				4

#define DIO_U8_PIN0					0
#define DIO_U8_PIN1 				1
#define DIO_U8_PIN2 				2
#define DIO_U8_PIN3 				3
#define DIO_U8_PIN4 				4
#define DIO_U8_PIN5 				5
#define DIO_U8_PIN6 				6
#define DIO_U8_PIN7 				7

#define DIO_U8_PIN_DIR_OUTPUT			1
#define DIO_U8_PIN_DIR_INPUT			2
#define DIO_U8_PIN_DIR_INPUT_PULLUP		3

#define DIO_U8_PIN_HIGH					1
#define DIO_U8_PIN_LOW					0


#define DIO_U8_PORT_DIR_OUTPUT			1
#define DIO_U8_PORT_DIR_INPUT			2
#define DIO_U8_PORT_DIR_INPUT_PULLUP	3

#define DIO_U8_PORT_DIR_HIGH			0xFF
#define DIO_U8_PORT_DIR_LOW				0x00

#define DI0_U8_PORT_HIGH				0xFF
#define DI0_U8_PORT_LOW					0x00


typedef enum {
    
    DIO_S8_INVALID_PIN_RANGE = -5,
    DIO_S8_INVALID_PIN_VALUE_RANGE,
    DIO_S8_INVALID_PIN_DIR_RANGE,
    DIO_S8_INVALID_PORT_RANGE,
    DIO_S8_INVALID_PORT_DIR_RANGE,
    DIO_S8_OK = 0,

} Dio_enErrorStatus;



/*this function shall set the direction of a specific pin*/
/*return : error state
 * 0 -> ok  (-4) -> Invalid Port ID  & (-1) -> invalid Pin ID & (-3) -> Invalid Pin Direction   */
Dio_enErrorStatus DIO_s8SetPinDirection(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8PinIDDirection);


/*this function shall set the value of any output pin*/
/*return : error state
 * 0 -> ok  (-4) -> Invalid Port ID  & (-1) -> invalid Pin ID & (-3) -> Invalid Pin Vlaue   */
Dio_enErrorStatus DIO_s8SetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8Port);

/*this function is to set the direction of a specific port*/
/*Return ErrorState
 * 0 -> ok  (-4) -> Invalid Port ID  &  */
Dio_enErrorStatus DIO_s8SetPortDirection(u8 Copy_u8PortID  , u8 Copy_u8PortDirection);

/*this function is to set the value of a specific output port*/
/*return : error state
 * 0 -> ok   & 1-> invalid port ID & 2->value out of range   */
Dio_enErrorStatus DIO_u8SetPortValue(u8 Copy_u8PortID  , s32 Copy_u8PortValue);

/*this function is to toggle the pin value*/
Dio_enErrorStatus DIO_s8TogglePin(u8 Copy_u8PortID , u8 Copy_u8PinID);

/*this function is to get the value of an input pin*/
u8 DIO_u8GetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID);

#endif /* DIO_INTERFACE_H_ */
