/*
 * I2C_Private.h
 *
 *  Created on: Apr 23, 2023
 *      Author: DWEEBSTARK
 */

#ifndef MCAL_I2C_PRIVATE_H_
#define MCAL_I2C_PRIVATE_H_

#define TWCR				*((volatile u8 *)0x56)  //Two-wire Serial Control Register
#define TWCR_TWINT_BIT		7					  	//Two-wire Interrupt Flag
#define TWCR_TWEA_BIT		6						//Two-wire Enable Acknowledge Bit
#define TWCR_TWSTA_BIT		5						//Two-wire START Condition Bit
#define TWCR_TWSTO_BIT		4						//Two-wire STOP Condition Bit
#define TWCR_TWWC_BIT		3					 	//Two-wire Write Collision Flag
#define TWCR_TWEN_BIT		2					 	//Two-wire ENABLE Bit
#define TWCR_TWIE_BIT		0					  	//Two-wire Interrupt ENABLE Bit

#define TWDR				*((volatile u8 *)0x23) //Two-wire Serial Interface Data Register


//TWI (Slave) Address Register assigned for current MCU
#define TWAR				*((volatile u8 *)0x22)
#define TWAR_TWGCE_BIT		0			//General Call(Broadcasting) Recognition Enable Bit



#define TWSR				*((volatile u8 *)0x21) //Two-wire Serial Status Register
#define TWSR_PRE_SCALER_MASK			0xF8
/*MASTER TRASMITTER STATUS*/
#define TWSR_START_DONE					0x08	//START CONDITION DONE
#define TWSR_RE_START_DONE				0x10	//REPEATED START CONDITION DONE
#define TWSR_SLVE_ADD_W_ACK				0x18	//SLAVE ADDRESS WITH WRITE, ACKOLEDMGENT RECEIVED
#define TWSR_SLAVE_ADD_W_NO_ACK			0x20	//SLAVE ADDRESS WITH WRITE,NO ACKOLEDMGENT RECEIVED
#define TWSR_DATA_W_ACK					0x28	//DATA BYTE WRITE ACKOLEDMGENT RECEIVE
#define TWSR_DATA_W_NO_ACK				0x30	//DATA BYTE WRITE ,NO ACKOLEDMGENT RECEIVE
#define TWSR_ARBITIRATION_WRITE_LOSS	0x38	//Arbitration lost IN WRITING (DATA OR SLAVE ADDRESS)
/*MASTER RECEIVER STATUS */
#define TWSR_SLAVE_ADD_R_ACK				0x40	//SLAVE ADDRESS WITH READ ACKOLEDMGENT RECEIVED
#define TWSR_SLAVE_ADD_R_NO_ACK			0x48	//SLAVE ADDRESS WITH R,NO ACKOLEDMGENT RECEIVED
#define TWSR_DATA_R_ACK					0x50	//DATA BYTE READ, ACKOLEDMGENT SENT
#define TWSR_DATA_R_NO_ACK				0x58	//DATA BYTE READ,NO ACKOLEDMGENT SENT
#define TWSR_ARBITIRATION_READ_LOSS		0x38	//Arbitration lost IN WRITING (DATA OR SLAVE ADDRESS)


/*SLAVE TRASMITTER STATUS*/
#define TWSR_START_DONE					0x08	//START CONDITION DONE
#define TWSR_RE_START_DONE				0x10	//REPEATED START CONDITION DONE
#define TWSR_SLAVE_ADD_W_ACK			0x18	//SLAVE ADDRESS WITH WRITE ACKOLEDMGENT RECEIVED
#define TWSR_SLAVE_ADD_W_NO_ACK			0x20	//SLAVE ADDRESS WITH WRITE,NO ACKOLEDMGENT RECEIVED
#define TWSR_DATA_W_ACK					0x28	//DATA BYTE WRITE ACKOLEDMGENT RECEIVE
#define TWSR_DATA_W_NO_ACK				0x30	//DATA BYTE WRITE ,NO ACKOLEDMGENT RECEIVE




#define TWBR				*((volatile u8 *)0x20) //Two-wire Serial Interface Bit Rate Register






#endif /* MCAL_I2C_PRIVATE_H_ */
