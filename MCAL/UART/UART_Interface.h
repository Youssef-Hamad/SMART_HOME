/*
 * UART_Interface.h
 *
 *  Created on: Apr 11, 2023
 *      Author: Youssef
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#define _9BIT 7U

#define RECEIVE_INT_ENABLE							1
#define RECEIVE_INT_DISABLE							0

#define SEND_INT_ENABLE								1
#define SEND_INT_DISABLE							0

#define EMPTY_DATA_INT_ENABLE						1
#define EMPTY_DATA_INT_DISABLE						0

#define CHAR_SIZE_5_								0
#define CHAR_SIZE_7_								1
#define CHAR_SIZE_6_								2
#define CHAR_SIZE_8_								3
#define CHAR_SIZE_9_								7

#define SYNCHRONOUS_MODE							1
#define ASYNCHRONOUS_MODE							2

#define PARITY_DISABLE								0
#define PARITY_ODD									2
#define PARITY_EVEN									3

#define STOP_1_BIT									0
#define STOP_2_BIT									1

#define SEND_RISE_CLOCK								0
#define SEND_FALL_CLOCK								1

#define PEER_TO_PEER_MODE							0
#define MASTER_SLAVE_MODE							1
typedef enum {
	Rate_1200 =    0,
	Rate_2400 =    1,
	Rate_4800 =    2,
	Rate_9600 =    3,
	Rate_19_200 =  4,
	Rate_38_400 =  5,
	Rate_57_600 =  6,
	Rate_115_200 = 7,
	Rate_250_400 = 8,

}BaudRate;

typedef struct{

	u8 Receive_Done_INT_Enable;
	u8 Send_Done_INT_Enable;
	u8 Empty_Data_Reg_INT_Enable;
	u8 Char_Size;
	u8 Mode_Select;
	u8 Parity_Mode;
	u8 Stop_Bits_Number;
	u8 Clock_Polarity;
	u8 Communication_Mode;
	BaudRate Baude_Rate;

}UART_Config;

typedef enum{
	Timeout=1,

}ERROR_STATE;


void UART_Init(const UART_Config * const UserConfig);//Const ptr to const data?



void UART_VoidSendData(u16 Copy_u16Data);
void UART_VoidReceiveData(u16 * Copy_u16Data);

void UART_VoidSendDataU8(u8 Copy_u8Data);
void UART_VoidReceiveDataU8(u8 * Copy_u8Data);

void UART_SendBufferSync(string * Copy_u8Data,u8 Copy_Size);
void UART_SendStringSync(string * Copy_u8String);




void UART_ReceiveBufferSync(string * Copy_u8Data,u8 Copy_Size);
void UART_ReceiveStringSync(string * Copy_u8String);



void UART_SendBufferAsync(u8* Copy_u8Data,u16 Copy_Size,void(*funcPtr)(void));
void UART_SendStringAsync(u8* Copy_u8String,void(*funcPtr)(void));

void UART_ReceiveBufferAsync(u8* Copy_u8Data,u8 Copy_Size,void(*funcPtr)(void));
void UART_ReceiveStringAsync(u8* Copy_u8String,void(*funcPtr)(void));



#endif /* MCAL_UART_UART_INTERFACE_H_ */

