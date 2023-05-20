/*
 * I2C_Program.c
 *
 *  Created on: Apr 23, 2023
 *      Author: DWEEBSTARK
 */
#include "../../INC/MATH_BIT.h"
#include "../../INC/STD_TYPES.h"

#include <util/delay.h>

#include "I2C_Private.h"
#include "I2C_Config.h"
#include "I2C_Interface.h"


void I2C_voidMasterInit(){

	/*enable ACK bit  */

	ClearBit(TWCR,TWCR_TWEA_BIT);

	/*Set frequency to 400kbps*/
	ClearBit(TWSR,0);
	ClearBit(TWSR,0);

	TWBR=2;

	/*Enable TWI */
	SetBit(TWCR,TWCR_TWEN_BIT);

}







I2C_ErrorStatus I2C_SendStartCondition(void){
	u8 ErrorStatus=NoError;

	/*Writing one to START Condition Bit */
	SetBit(TWCR,TWCR_TWSTA_BIT);
	/*Clearing the flag by Writing one to it, To start the operation*/
	SetBit(TWCR,TWCR_TWINT_BIT);
	/*Wait for the transmission flag to be up*/
	while(GetBit(TWCR,TWCR_TWINT_BIT)==0);

	if((TWSR&TWSR_PRE_SCALER_MASK)!=TWSR_START_DONE){
		ErrorStatus=StartConditionErr;
	}
	else{

	}

return ErrorStatus;
}

I2C_ErrorStatus I2C_SendRepeatedStart(void){
	u8 ErrorStatus=NoError;
	/*Set the start condition*/
	SetBit(TWCR,TWCR_TWSTA_BIT);

	/*Clear interrupt flag to start the previous operation*/
	SetBit(TWCR,TWCR_TWINT_BIT);

	/*Polling on the interrupt flag*/
	while((GetBit(TWCR,TWCR_TWINT_BIT))==0);

	/*check on the operation status ID*/
//	if((TWSR&TWSR_PRE_SCALER_MASK) != TWSR_RE_START_DONE)
//	{
//		ErrorStatus= RepeatedStartError;
//	}
//	else
//	{
//		/*Do nothing*/
//	}

	return ErrorStatus;
}

I2C_ErrorStatus I2C_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAdress){
	/*Before using the function,Please Check the return status of TWSR of
	the function I2C_SendStartCondition (START CONDITION RETURN)*/
	/*TWDR MUST BE SET BEFORE MANIPULATING TWCR VALUES */
	u8 ErrorStatus=NoError;
	/*Assigning the 7 bit address to TWDR*/
	TWDR=((Copy_u8SlaveAdress<<1));
	/*Sending the write command */
	ClearBit(TWDR,0);

	/*Clearing Start Condition Bit */
	ClearBit(TWCR,TWCR_TWSTA_BIT);
	/*Clearing the flag by Writing one to it, To start the operation*/
	SetBit(TWCR,TWCR_TWINT_BIT);
	/*Wait for the transmission flag to be up*/
	while(GetBit(TWCR,TWCR_TWINT_BIT)==0);

	if((TWSR&TWSR_PRE_SCALER_MASK)!=TWSR_SLAVE_ADD_W_ACK && (TWSR&TWSR_PRE_SCALER_MASK)!=TWSR_SLAVE_ADD_W_NO_ACK){
		ErrorStatus=SlaveAddressWithWriteErr;
	}
	else{

	}


	return ErrorStatus;
}

I2C_ErrorStatus I2C_SendSlaveAddressWithRead(u8 Copy_u8SlaveAdress){
	/*Before using the function,Please Check the return status of TWSR of
	the function I2C_SendStartCondition (START CONDITION RETURN)*/
	u8 ErrorStatus=NoError;
	/*Assigning the 7 bit address to TWDR*/
	TWDR=((Copy_u8SlaveAdress<<1));
	/*Sending the Reading command */
	SetBit(TWDR,0);
	//*Clearing Start Condition Bit */
	ClearBit(TWCR,TWCR_TWSTA_BIT);


	/*Clearing the flag by Writing one to it, To start the operation*/
	SetBit(TWCR,TWCR_TWINT_BIT);
	/*Wait for the transmission flag to be up*/
	while(GetBit(TWCR,TWCR_TWINT_BIT)==0);

	if((TWSR&TWSR_PRE_SCALER_MASK)!=TWSR_SLAVE_ADD_R_ACK && (TWSR&TWSR_PRE_SCALER_MASK)!=TWSR_SLAVE_ADD_R_NO_ACK){
		ErrorStatus=SlaveAddressWithReadErr;
	}
	else{

	}

	return ErrorStatus;
}

I2C_ErrorStatus I2C_MstrSendDataByte(u8 Copy_u8Data){
	/*Before using the function,Please Check the return status of TWSR of
	 * the function I2C_SendSlaveAddressWithWrite (Send address Write RETURN)*/
	u8 ErrorStatus=NoError;
	/*Assigning the Data TWDR*/
	TWDR=Copy_u8Data;

	/*Writing one to START Condition Bit */
	ClearBit(TWCR,TWCR_TWSTA_BIT);
	/*Clearing the flag by Writing one to it, To start the operation*/
	SetBit(TWCR,TWCR_TWINT_BIT);
	/*Wait for the transmission flag to be up*/
	while(GetBit(TWCR,TWCR_TWINT_BIT)==0);

	if((TWSR&TWSR_PRE_SCALER_MASK)!=TWSR_DATA_W_ACK	 && (TWSR&TWSR_PRE_SCALER_MASK)!=TWSR_DATA_W_NO_ACK){
		ErrorStatus=MstrWriteByteErr;
	}
	else{

	}

	return ErrorStatus;
}

I2C_ErrorStatus I2C_MstrReadDataByte(pstring Copy_pu8Data){
	/*Before using the function,Please Check the return status of TWSR of
	  the function I2C_SendSlaveAddressWithRead (Send address Read RETURN)*/
	u8 ErrorStatus=NoError;

	/*Enable Acknowledge bit generation of master receiver*/
	SetBit(TWCR,TWCR_TWEA_BIT);


	/*Wait for the transmission flag to be up*/
	while(GetBit(TWCR,TWCR_TWINT_BIT)==0);

	ErrorStatus=(TWSR&TWSR_PRE_SCALER_MASK);
//	if((TWSR&TWSR_PRE_SCALER_MASK)==TWSR_DATA_R_ACK){
		/*Assigning the Data TWDR*/
		*Copy_pu8Data=TWDR;
//	}
//	else{
//		ErrorStatus=MstrReadByteWithAckErr;
//	}

	return ErrorStatus;
}





I2C_ErrorStatus I2C_MstrReadDataByteNoAck(pstring Copy_pu8Data){
	/*Before using the function,Please Check the return status of TWSR of
	the function I2C_SendSlaveAddressWithRead (Send address Read RETURN)*/
	u8 ErrorStatus=NoError;
	u8 temp;

	/*Disable Acknowledge bit generation of master receiver*/
		ClearBit(TWCR,TWCR_TWEA_BIT);

	/*Wait for the transmission flag to be up*/
	while(GetBit(TWCR,TWCR_TWINT_BIT)==0);

	ErrorStatus=(TWSR&TWSR_PRE_SCALER_MASK);
	if((TWSR&TWSR_PRE_SCALER_MASK)==TWSR_DATA_R_NO_ACK){
		/*Assigning the Data TWDR*/
		temp=TWDR;

	}
	else{
		ErrorStatus=MstrReadByteWithAckErr;
	}

	return ErrorStatus;
}






void I2C_SendStopCondition(void){
	/*Writing one to STOP Condition Bit */
	SetBit(TWCR,TWCR_TWSTO_BIT);
	/*Clear interrupt flag to start the previous operation*/
	SetBit(TWCR,TWCR_TWINT_BIT);
}





