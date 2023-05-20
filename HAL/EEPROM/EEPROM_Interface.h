/*
 * EEPROM_Interface.h
 *
 *  Created on: Apr 24, 2023
 *      Author: DWEEBSTARK
 */

#ifndef HAL_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EEPROM_EEPROM_INTERFACE_H_


void EEPROM_VoidInit(void);

u8  EEPROM_VoidSendDataByte(u16 Copy_u16address,u8 Copy_u8Data);
u8  EEPROM_VoidReadDataByteOnly(u16 Copy_u16address,pstring Copy_pu8Data);


u8  EEPROM_VoidReadDataFirstByte(u16 Copy_u16address,pstring Copy_pu8Data);

u8  EEPROM_VoidReadDataByte(u16 Copy_u16address,pstring Copy_pu8Data);


void  EEPROM_VoidSendBuffer(u16 Copy_u16address,pstring Copy_u8Data,u8 size);
void  EEPROM_VoidReceiveBuffer(u16 Copy_u16address,pstring Copy_u8RData,u8 size);

void  EEPROM_VoidSendAndReceiveBuffer(u16 Copy_u16address,pstring Copy_u8Data,u8 size,pstring Copy_u8RData);


void  EEPROM_VoidReceiveBufferNonSeq(u16 Copy_u16address,pstring  Copy_u8RData,u8 size);
#endif /* HAL_EEPROM_EEPROM_INTERFACE_H_ */
