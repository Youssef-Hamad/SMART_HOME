/*
 * EEPROM_Program.c
 *
 *  Created on: Apr 24, 2023
 *      Author: DWEEBSTARK
 */
#include <util/delay.h>
#include "EEPROM_Private.h"
#include "EEPROM_Config.h"
#include "../../MCAL/I2C/I2C_Interface.h"
#include "EEPROM_Interface.h"




void EEPROM_VoidInit(void){
	I2C_voidMasterInit();
}
u8  EEPROM_VoidSendDataByte(u16 Copy_u16address,u8 Copy_u8Data){
	u8 Local_ErrorState=NoError;
	Local_ErrorState=I2C_SendStartCondition();
	if(Local_ErrorState==NoError){
		Local_ErrorState=I2C_SendSlaveAddressWithWrite(EEPROM_FIXED_ADDRESS | EEPROM_A2_VALUE | ((u8)((Copy_u16address>>8)&EEPROM_8K_ADDRESS_MASK)));
		if(Local_ErrorState==NoError){
			Local_ErrorState=I2C_MstrSendDataByte((u8)Copy_u16address);
			if(Local_ErrorState==NoError){
				Local_ErrorState=I2C_MstrSendDataByte(Copy_u8Data);
				if(Local_ErrorState==NoError){
					I2C_SendStopCondition();
						_delay_ms(15);
					/*Writing Process delay for EEPROM minimum 10ms*/

				}
				else{

				}
			}
			else{

			}

		}
		else{

		}
	}
	else{

	}
	return Local_ErrorState;
}



u8  EEPROM_VoidReadDataByteOnly(u16 Copy_u16address,pstring Copy_pu8Data){
	u8 Local_ErrorState=NoError;
	Local_ErrorState=I2C_SendStartCondition();
	if(Local_ErrorState==NoError){
	Local_ErrorState=I2C_SendSlaveAddressWithWrite(EEPROM_FIXED_ADDRESS | EEPROM_A2_VALUE | ((u8)((Copy_u16address>>8)&EEPROM_8K_ADDRESS_MASK)));
		if(Local_ErrorState==NoError){
			Local_ErrorState=I2C_MstrSendDataByte((u8)Copy_u16address&0x00ff);
			if(Local_ErrorState==NoError){
				Local_ErrorState=I2C_SendRepeatedStart();
				if(Local_ErrorState==NoError){
					Local_ErrorState=I2C_SendSlaveAddressWithRead(EEPROM_FIXED_ADDRESS | EEPROM_A2_VALUE | ((u8)((Copy_u16address>>8)&EEPROM_8K_ADDRESS_MASK)));
					if(Local_ErrorState==NoError){
	//Reading a single byte with no acknowledgment results in flushing TWDR
	//So An ACK read is done,then a NOACK read.
						I2C_MstrReadDataByte(Copy_pu8Data);
						I2C_MstrReadDataByteNoAck(Copy_pu8Data);
						if(Local_ErrorState==NoError){

							I2C_SendStopCondition();

							_delay_ms(20);
						}
						else{

						}
					}
					else{

					}
				}
				else{

				}
			}
			else{

			}
		}
		else{

		}
	}
	else{

	}
	return Local_ErrorState;
}



u8  EEPROM_VoidReadDataFirstByte(u16 Copy_u16address,pstring Copy_pu8Data){
	u8 Local_ErrorState=NoError;
	Local_ErrorState=I2C_SendStartCondition();
	if(Local_ErrorState==NoError){
	Local_ErrorState=I2C_SendSlaveAddressWithWrite(EEPROM_FIXED_ADDRESS | EEPROM_A2_VALUE | ((u8)((Copy_u16address>>8)&EEPROM_8K_ADDRESS_MASK)));
		if(Local_ErrorState==NoError){
			Local_ErrorState=I2C_MstrSendDataByte((u8)Copy_u16address);
			if(Local_ErrorState==NoError){
				Local_ErrorState=I2C_SendRepeatedStart();
				if(Local_ErrorState==NoError){
					Local_ErrorState=I2C_SendSlaveAddressWithRead(EEPROM_FIXED_ADDRESS | EEPROM_A2_VALUE | ((u8)((Copy_u16address>>8)&EEPROM_8K_ADDRESS_MASK)));
					if(Local_ErrorState==NoError){
						I2C_MstrReadDataByte(Copy_pu8Data);
//						I2C_MstrReadDataByteNoAck(Copy_pu8Data);
					}
					else{

					}
				}
				else{

				}
			}
			else{

			}
		}
		else{

		}
	}
	else{

	}
	return Local_ErrorState;
}






u8  EEPROM_VoidReadDataByte(u16 Copy_u16address,pstring Copy_pu8Data){
	u8 Local_ErrorState=NoError;
	Local_ErrorState=I2C_SendStartCondition();
	if(Local_ErrorState==NoError){
	Local_ErrorState=I2C_SendSlaveAddressWithWrite(EEPROM_FIXED_ADDRESS | EEPROM_A2_VALUE | ((u8)((Copy_u16address>>8)&EEPROM_8K_ADDRESS_MASK)));
		if(Local_ErrorState==NoError){
			Local_ErrorState=I2C_MstrSendDataByte((u8)Copy_u16address);
			if(Local_ErrorState==NoError){
				Local_ErrorState=I2C_SendRepeatedStart();
				if(Local_ErrorState==NoError){
					Local_ErrorState=I2C_SendSlaveAddressWithRead(EEPROM_FIXED_ADDRESS | EEPROM_A2_VALUE | ((u8)((Copy_u16address>>8)&EEPROM_8K_ADDRESS_MASK)));
					if(Local_ErrorState==NoError){
						I2C_MstrReadDataByte(Copy_pu8Data);
						I2C_MstrReadDataByteNoAck(Copy_pu8Data);
						if(Local_ErrorState==NoError){
							I2C_SendStartCondition();
							_delay_ms(20);
						}
					}
					else{

					}
				}
				else{

				}
			}
			else{

			}
		}
		else{

		}
	}
	else{

	}
	return Local_ErrorState;
}


void  EEPROM_VoidSendBuffer(u16 Copy_u16address,pstring Copy_u8Data,u8 size){

	for(u8 LocalIterator=0;LocalIterator<size;LocalIterator++){
			EEPROM_VoidSendDataByte(Copy_u16address+LocalIterator,Copy_u8Data[LocalIterator]);

		}

}


void  EEPROM_VoidSendAndReceiveBuffer(u16 Copy_u16address,pstring Copy_u8Data,u8 size,pstring Copy_u8RData){
	/*Data is sent by (Byte write) method not Page write, why ?
	 * Cuz, Pages layout are fixed i.e Page0 bytes are from byte 0 to byte 15, if user chooses
	 * Byte address 14 or chooses a Buffer larger than 16, the EEPROM will reach the
	 * end of this page then re-roll and overwrite the data written at the page beginning
	 *therefore, the data is written Byte by Byte*/


	for(u8 LocalIterator=0;LocalIterator<size;LocalIterator++){
		EEPROM_VoidSendDataByte(Copy_u16address+LocalIterator,Copy_u8Data[LocalIterator]);

	}

	/*Read data bytes one by one , Reading could be done sequentially by Acknowledging the read
	 * Data (By the MCU) and atomically reading the next byte of data
	 * without sending STOP condition, till last byte is reached, Acknowledging it then not
	 * Acknowledging the next data then sending Stop Condition. this process successfully
	 * stops the reading operation (If a data byte is not acknowledged by the MCU
	 * it is not recognized by MCU) therefore an extra reading is required if data is read
//	 * sequentially */
	for(u8 LocalIterator=0;LocalIterator<size;LocalIterator++){
		EEPROM_VoidReadDataByte((Copy_u16address+LocalIterator),(Copy_u8RData+LocalIterator));
		}
}



void  EEPROM_VoidReceiveBuffer(u16 Copy_u16address,pstring  Copy_u8RData,u8 size){

	EEPROM_VoidReadDataFirstByte(Copy_u16address,Copy_u8RData);

	for(u8 i=1;i<size;i++){
		I2C_MstrReadDataByte(Copy_u8RData+i);
	}
	I2C_MstrReadDataByteNoAck(Copy_u8RData+size);
	I2C_SendStopCondition();

	_delay_ms(20);



}


void  EEPROM_VoidReceiveBufferNonSeq(u16 Copy_u16address,pstring  Copy_u8RData,u8 size){

	for(u8 LocalIterator=0;LocalIterator<size;LocalIterator++){
		EEPROM_VoidReadDataByteOnly((Copy_u16address+LocalIterator),(Copy_u8RData+LocalIterator));
	}



}

