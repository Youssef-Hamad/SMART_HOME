/*
 * UART_Private.h
 *
 *  Created on: Apr 11, 2023
 *      Author: Youssef
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_


/*USART Baud Rate Register Low Byte && USART Control and Status Register*/
#define UCSRC						*((volatile u8 *)0x40)
#define UBRRH						*((volatile u8 *)0x40)
/*Register Select*/
#define UCSRC_URSEL_BIT						7
/*UART MODE SELECT*/
#define UCSRC_UMSEL_BIT						6
/*PARITY MODE SELECT*/
#define UCSRC_UPM_BIT						4
/*STOP BIT SELECT*/
#define UCSRC_USBS_BIT						3
/*Character Size Bit*/
#define UCSRC_UCSZ_BIT						1

/*USART Baud Rate Register Low Byte*/
#define UBRRL 						*((volatile u8 *)0x29)

#define UDR							*((volatile u8 *)0x2C)



/*USART Control and Status Register A*/
#define UCSRA						*((volatile u8 *)0x2B)


#define UCSRA_RXC_BIT				7			//RECEIVE COMPLETE FLAG
#define UCSRA_TXC_BIT				6			//SEND COMPLETE	FLAG
#define UCSRA_UDRE_BIT				5			//DATA REGISTER EMPTY FLAG
#define UCSRA_FE_BIT				4			//FRAME ERROR FLAG
#define UCSRA_DOR_BIT				3			//DATA OVERRUN ERROR FLAG
#define UCSRA_PE_BIT				2			//PARITY ERROR FLAG
#define UCSRA_RECEIVE_BIT			1
#define UCSRA_TRASMIT_BIT			0

/*U2X: Double the USART Transmission Speed*/
#define UCSRA_U2X_BIT				1
/*MPCM: MULTI-PROCESSOR COMMUNICATION MODE*/
#define UCSRA_MPCM_BIT				0

/*USART Control and Status Register B*/
#define UCSRB						*((volatile u8 *)0x2A)

#define UCSRB_RECEIVE_INT_BIT		7
#define UCSRB_SEND_INT_BIT			6
#define UCSRB_EMPTY_INT_BIT			5

#define UCSRB_RECEIVE_BIT			4
#define UCSRB_SEND_BIT				3

#define UCSRB_UCSZ2_BIT				2



#define UBRRH_MASK					0x0F
#define MAX_8BIT_VALUE				0XFF


#endif /* MCAL_UART_UART_PRIVATE_H_ */
