/*
 * I2C_Interface.h
 *
 *  Created on: Apr 23, 2023
 *      Author: DWEEBSTARK
 */

#ifndef MCAL_I2C_INTERFACE_H_
#define MCAL_I2C_INTERFACE_H_
#include "../../INC/STD_TYPES.h"


typedef enum
{
	NoError,
	StartConditionErr,
	RepeatedStartError,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MstrWriteByteErr,
	MstrReadByteWithAckErr

}I2C_ErrorStatus;
#define ENABLE_INTERRUPT			1
#define DISABLE_INTERRUPT			2

#define ENABLE_ACK					1
#define DISABLE_ACK					2


typedef struct{
	u8 Interrupt_state;
	u8 Acknowledge_state;
	u8 Prescaler_value;
}I2C_Master_Config;

typedef struct{
	u8 Interrupt_state;
	u8 Acknowledge_state;
	u8 Address_value;
}I2C_Slave_Config;


void I2C_voidMasterInit(void);

void I2C_voidSlaveInit(const I2C_Slave_Config* const ConfigPtr);

I2C_ErrorStatus I2C_SendStartCondition(void);

I2C_ErrorStatus I2C_SendRepeatedStart(void);

I2C_ErrorStatus I2C_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAdress);

I2C_ErrorStatus I2C_SendSlaveAddressWithRead(u8 Copy_u8SlaveAdress);

I2C_ErrorStatus I2C_MstrSendDataByte(u8 Copy_u8Data);

I2C_ErrorStatus I2C_MstrReadDataByte(pstring Copy_pu8Data);

I2C_ErrorStatus I2C_MstrReadDataByteNoAck(pstring Copy_pu8Data);


void I2C_SendStopCondition(void);


#endif /* MCAL_I2C_INTERFACE_H_ */
