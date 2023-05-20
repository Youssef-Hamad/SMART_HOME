/*
 * program.c
 *
 *  Created on: Mar 25, 2023
 *      Author: DWEEBSTARK
 */


#include "DIO_Interface.h"



Dio_enErrorStatus DIO_s8SetPinDirection(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8PinIDDirection){
	/*initially = 0 (ok)*/
	Dio_enErrorStatus Local_s8ErrorState = DIO_S8_OK;
	/*checking for valid Pin Direction range*/
	if(Copy_u8PinIDDirection==DIO_U8_PIN_DIR_OUTPUT || Copy_u8PinIDDirection==DIO_U8_PIN_DIR_INPUT || Copy_u8PinIDDirection==DIO_U8_PIN_DIR_INPUT_PULLUP){
		if(Copy_u8PinID>=0 && Copy_u8PinID<=7)
		{
			switch(Copy_u8PortID)
			{
			/*in case of setting the direction of a pin in port A*/
				case (DIO_U8_PORTA):
				/*switch over different directions*/
					switch(Copy_u8PinIDDirection)
					{
					/*in case of setting the pin to be output*/
						case(DIO_U8_PIN_DIR_OUTPUT):
							SetBit(DDRA,Copy_u8PinID);
							break;
					/*in case of setting the pin to be input*/
						case(DIO_U8_PIN_DIR_INPUT):
							ClearBit(DDRA,Copy_u8PinID);
							break;
					/*in case of setting the pin direction to be input pull up*/
						case(DIO_U8_PIN_DIR_INPUT_PULLUP):
							ClearBit(DDRA,Copy_u8PinID);
							SetBit(PORTA,Copy_u8PinID);
							break;
					}
					break;
		/******************************************************************************/
				/*in case of setting the direction of a pin in port B*/
				case (DIO_U8_PORTB):
					/*switch over different directions*/
					switch(Copy_u8PinIDDirection)
					{					/*in case of setting the pin to be output*/
						case(DIO_U8_PIN_DIR_OUTPUT):
							SetBit(DDRB,Copy_u8PinID);
							break;
					/*in case of setting the pin to be input*/
						case(DIO_U8_PIN_DIR_INPUT):
							ClearBit(DDRB,Copy_u8PinID);
							break;
					/*in case of setting the pin direction to be input pull up*/
						case(DIO_U8_PIN_DIR_INPUT_PULLUP):
							ClearBit(DDRB,Copy_u8PinID);
							SetBit(PORTB,Copy_u8PinID);
							break;

					}
					break;
		/******************************************************************************/
				case (DIO_U8_PORTC):
				/*switch over different directions*/
					switch(Copy_u8PinIDDirection)
					{
					/*in case of setting the pin to be output*/
						case(DIO_U8_PIN_DIR_OUTPUT):
							SetBit(DDRC,Copy_u8PinID);
							break;
					/*in case of setting the pin to be input*/
						case(DIO_U8_PIN_DIR_INPUT):
							ClearBit(DDRC,Copy_u8PinID);
							break;
					/*in case of setting the pin direction to be input pull up*/
						case(DIO_U8_PIN_DIR_INPUT_PULLUP):
							ClearBit(DDRC,Copy_u8PinID);
							SetBit(PORTC,Copy_u8PinID);
							break;

					}
					break;
		/******************************************************************************/
				case (DIO_U8_PORTD):
				/*switch over different directions*/
					switch(Copy_u8PinIDDirection)
					{
					/*in case of setting the pin to be output*/
						case(DIO_U8_PIN_DIR_OUTPUT):
							SetBit(DDRD,Copy_u8PinID);
							break;
					/*in case of setting the pin to be input*/
						case(DIO_U8_PIN_DIR_INPUT):
							ClearBit(DDRD,Copy_u8PinID);
							break;
					/*in case of setting the pin direction to be input pull up*/
						case(DIO_U8_PIN_DIR_INPUT_PULLUP):
							ClearBit(DDRD,Copy_u8PinID);
							SetBit(PORTD,Copy_u8PinID);
							break;

					}
				break;
				default:
					Local_s8ErrorState=DIO_S8_INVALID_PORT_RANGE;
					break;
			}
		}
		else
		{
			Local_s8ErrorState=DIO_S8_INVALID_PIN_RANGE;
		}
	}
	else{
		Local_s8ErrorState=DIO_S8_INVALID_PIN_DIR_RANGE;
	}
	/*Returen Error state
	 * 0 -> ok  (-4) -> Invalid Port ID  & (-1) -> invalid Pin ID & (-3) -> Invalid Pin Direction */
	return Local_s8ErrorState;
}


/*this function shall set the value of any output pin*/
Dio_enErrorStatus DIO_s8SetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8PinValue){
	/*initially = 0 (ok)*/
	Dio_enErrorStatus Local_s8ErrorState=0;
	/*checking for valid Pin Value range*/
	if(Copy_u8PinValue==DIO_U8_PIN_LOW ||Copy_u8PinValue==DIO_U8_PIN_HIGH){
		/*checking for valid Pin  range*/
		if(Copy_u8PinID>=DIO_U8_PIN0 && Copy_u8PinID<=DIO_U8_PIN7)
		{
			/*switching over ports*/
			switch(Copy_u8PortID)
			{
				/*In case of PORTA*/
				case(DIO_U8_PORTA):
					WriteBit(PORTA,Copy_u8PinID,Copy_u8PinValue);
					break;
				/*In case of PORTB*/
				case(DIO_U8_PORTB):
					WriteBit(PORTB,Copy_u8PinID,Copy_u8PinValue);
					break;
				/*In case of PORTC*/
				case(DIO_U8_PORTC):
					WriteBit(PORTC,Copy_u8PinID,Copy_u8PinValue);
					break;
				/*In case of PORTD*/
				case(DIO_U8_PORTD):
					WriteBit(PORTD,Copy_u8PinID,Copy_u8PinValue);
					break;
				default:
					Local_s8ErrorState=DIO_S8_INVALID_PORT_RANGE;
					break;
			}

		}
		else
		{
			Local_s8ErrorState=DIO_S8_INVALID_PIN_RANGE;
		}

	}
	else
		{
			Local_s8ErrorState=DIO_S8_INVALID_PIN_VALUE_RANGE;
		}
	/*Returen Error state
	 * 0 -> ok  (-4) -> Invalid Port ID  & (-1) -> invalid Pin ID & (-3) -> Invalid Pin Value */
	return Local_s8ErrorState;
}

Dio_enErrorStatus DIO_s8SetPortDirection(u8 Copy_u8PortID  , u8 Copy_u8PortDirection){
	/*Local variable for checking errors (0) is (OK) */
	Dio_enErrorStatus local_s8_ErrorState=0;
	/*Switching over PORTs */
	switch(Copy_u8PortID)
	{
	/* In case of Port A*/
		case(DIO_U8_PORTA):
			/*Switching over Port Directions*/
			switch(Copy_u8PortDirection)
			{
				/*In case of PORT OUTPUT*/
				case(DIO_U8_PORT_DIR_OUTPUT):
					DDRA=DIO_U8_PORT_DIR_HIGH;
					break;
				/*In case of PORT INPUT*/
				case(DIO_U8_PORT_DIR_INPUT):
					DDRA=DIO_U8_PORT_DIR_LOW;
					break;
			/*In case of PORT INPUT_PULLUP*/
				case(DIO_U8_PORT_DIR_INPUT_PULLUP):
					DDRA=DIO_U8_PORT_DIR_LOW;
					PORTA=DI0_U8_PORT_HIGH;
					break;
				default:
					DDRA=Copy_u8PortDirection;
					break;
			}
			break;
		/******************************************************************************/
		/* In case of Port B*/
		case(DIO_U8_PORTB):
			/*Switching over Port Directions*/
			switch(Copy_u8PortDirection)
			{
				/*In case of PORT OUTPUT*/
				case(DIO_U8_PORT_DIR_OUTPUT):
					DDRB=DIO_U8_PORT_DIR_HIGH;
					break;
				/*In case of PORT INPUT*/
				case(DIO_U8_PORT_DIR_INPUT):
					DDRB=DIO_U8_PORT_DIR_LOW;
					break;
			/*In case of PORT INPUT_PULLUP*/
				case(DIO_U8_PORT_DIR_INPUT_PULLUP):
					DDRB=DIO_U8_PORT_DIR_LOW;
					PORTB=DI0_U8_PORT_HIGH;
					break;
				default:
					DDRB=Copy_u8PortDirection;

					break;
			}
			break;
		/******************************************************************************/
		/* In case of Port C*/
		case(DIO_U8_PORTC):
			/*Switching over Port Directions*/
			switch(Copy_u8PortDirection)
			{
				/*In case of PORT OUTPUT*/
				case(DIO_U8_PORT_DIR_OUTPUT):
					DDRC=DIO_U8_PORT_DIR_HIGH;
					break;
				/*In case of PORT INPUT*/
				case(DIO_U8_PORT_DIR_INPUT):
					DDRC=DIO_U8_PORT_DIR_LOW;
					break;
			/*In case of PORT INPUT_PULLUP*/
				case(DIO_U8_PORT_DIR_INPUT_PULLUP):
					DDRC=DIO_U8_PORT_DIR_LOW;
					break;
				default:
					DDRC=Copy_u8PortDirection;
					PORTC=DI0_U8_PORT_HIGH;
					break;
			}
			break;
		/******************************************************************************/
				/* In case of Port D*/
		case(DIO_U8_PORTD):
			/*Switching over Port Directions*/
			switch(Copy_u8PortDirection)
			{
				/*In case of PORT OUTPUT*/
				case(DIO_U8_PORT_DIR_OUTPUT):
					DDRD=DIO_U8_PORT_DIR_HIGH;
					break;
				/*In case of PORT INPUT*/
				case(DIO_U8_PORT_DIR_INPUT):
					DDRD=DIO_U8_PORT_DIR_LOW;
					break;
			/*In case of PORT INPUT_PULLUP*/
				case(DIO_U8_PORT_DIR_INPUT_PULLUP):
					DDRD=DIO_U8_PORT_DIR_LOW;
					PORTD=DI0_U8_PORT_HIGH;
					break;
				default:
					DDRD=Copy_u8PortDirection;
					break;
			}
			break;
		/******************************************************************************/
		/*Invalid Port value*/
		default:
			local_s8_ErrorState=DIO_S8_INVALID_PORT_RANGE;
			break;
	}
	/*Return ErrorState
	 *  * 0 -> ok  (-4) -> Invalid Port ID  &  */
	return 	local_s8_ErrorState;
}
/*this function is to set the value of a specific output port*/

Dio_enErrorStatus DIO_u8SetPortValue(u8 Copy_u8PortID  , s32 Copy_u8PortValue){
	Dio_enErrorStatus local_s8_ErrorState=0;
	/*Switching over PORTs */
		switch(Copy_u8PortID)
		{
		/* In case of Port A*/
			case(DIO_U8_PORTA):
				PORTA=Copy_u8PortValue;
				break;
			case(DIO_U8_PORTB):
				PORTB=Copy_u8PortValue;
				break;
			case(DIO_U8_PORTC):
				PORTC=Copy_u8PortValue;
				break;
			case(DIO_U8_PORTD):
				PORTD=Copy_u8PortValue;
				break;
			default:
				local_s8_ErrorState=DIO_S8_INVALID_PORT_RANGE;
				break;
		}
	return local_s8_ErrorState;
}

Dio_enErrorStatus DIO_s8TogglePin(u8 Copy_u8PortID , u8 Copy_u8PinID){
	Dio_enErrorStatus Local_s8ErrorState=0;
	if(Copy_u8PinID>=DIO_U8_PIN0 && Copy_u8PinID<=DIO_U8_PIN7)
	{
		switch(Copy_u8PortID)
		{
	/*in case of Toggling a pin in port A*/
			case (DIO_U8_PORTA):
				ToggleBit(DDRA,Copy_u8PinID);
				break;
		/******************************************************************************/
		/*in case of Toggling a pin in port B*/
			case (DIO_U8_PORTB):
				ToggleBit(DDRB,Copy_u8PinID);
				break;

		/******************************************************************************/
		/*in case of Toggling a pin in port C*/
			case (DIO_U8_PORTC):
				ToggleBit(DDRC,Copy_u8PinID);
				break;
		/******************************************************************************/
		/*in case of Toggling a pin in port D*/
			case (DIO_U8_PORTD):
				ToggleBit(DDRD,Copy_u8PinID);
				break;
			default:
				Local_s8ErrorState=DIO_S8_INVALID_PORT_RANGE;
				break;
		}
	}
	else
	{
		Local_s8ErrorState=DIO_S8_INVALID_PIN_RANGE;
	}
return Local_s8ErrorState;
}

u8 DIO_u8GetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID){
	u8 localPinValue=0;

	if(Copy_u8PinID>=DIO_U8_PIN0 && Copy_u8PinID<=DIO_U8_PIN7)
	{
		switch(Copy_u8PortID)
		{
		/* In case of Port A*/
			case(DIO_U8_PORTA):
				localPinValue=GetBit(PINA,Copy_u8PinID);
				break;
			case(DIO_U8_PORTB):
				localPinValue=GetBit(PINB,Copy_u8PinID);
				break;
			case(DIO_U8_PORTC):
				localPinValue=GetBit(PINC,Copy_u8PinID);
				break;
			case(DIO_U8_PORTD):
				localPinValue=GetBit(PIND,Copy_u8PinID);
				break;
			default:
				break;
		}

	}
	else
	{
		// do nothing
	}
	return localPinValue;
}
