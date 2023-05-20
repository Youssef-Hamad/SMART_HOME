/*
 * UART_Program.c
 *
 *  Created on: Apr 11, 2023
 *      Author: Youssef
 */

#include "../../INC/STD_TYPES.h"
#include "../../INC/MATH_BIT.h"
#include "UART_Private.h"
#include "UART_Config.h"
#include "UART_Interface.h"


static void(*SendPtrCallBack)(void)=NULL;
static u8 GlobalSendSize=0;
static u8 *GlobalData=NULL;

static void(*ReceivePtrCallBack)(void)=NULL;
static u8 GlobalReceiveSize=0;
static u8 *GlobalReceiveData=NULL;


void UART_Init(const UART_Config * const UserConfig){

	u32 Loc_u32Baudrate = 0;
	u8 Loc_u8TempRegister = 0;

	if(UserConfig) //If configurations are passed to the function
	{	/*Configuring UBRR*/
		switch(UserConfig->Baude_Rate)
		{
		case 0:
			Loc_u32Baudrate = 1200;
			break;
		case 1:
			Loc_u32Baudrate = 2400;
			break;
		case 2:
			Loc_u32Baudrate = 4800;
			break;
		case 3:
			Loc_u32Baudrate = 9600;
			break;
		case 4:
			Loc_u32Baudrate = 19200;
			break;
		case 5:
			Loc_u32Baudrate = 38400;
			break;
		case 6:
			Loc_u32Baudrate = 57600;
			break;
		case 7:
			Loc_u32Baudrate = 115200;
			break;
		case 8:
			Loc_u32Baudrate = 250400;
			break;
		default:
			break;
		}
		/*Calculating UBRR VALUE*/
		u64 LocalTemp_UBRR= (SYSTEM_CLOCK_HZ/(16ULL * Loc_u32Baudrate));
		LocalTemp_UBRR-=1;

		if(LocalTemp_UBRR<MAX_8BIT_VALUE){
			UBRRL = LocalTemp_UBRR;
		}
		else
		{
			/*Make sure we are accessing UBRRH*/
			ClearBit(UBRRH,UCSRC_URSEL_BIT);
			/*Write HIGH REGISTER FIRST*/
			UBRRH=(LocalTemp_UBRR>>8)&(UBRRH_MASK);

			/*Write Lowest BYTE only*/
			UBRRL=(u8)LocalTemp_UBRR;

		}
		/*Configuring UCSRA*/
		UCSRA |= UserConfig->Communication_Mode <<UCSRA_MPCM_BIT;
		/*Configuring UCSRB (Has to be configured first otherwise CHARSIZE bit will be overwritten by 0*/
		UCSRB = (UserConfig->Receive_Done_INT_Enable <<UCSRB_RECEIVE_INT_BIT) | (UserConfig->Send_Done_INT_Enable <<UCSRB_SEND_INT_BIT) | (UserConfig->Empty_Data_Reg_INT_Enable <<UCSRB_EMPTY_INT_BIT);

		/*Configuring UCSRC*/
		Loc_u8TempRegister = 0;
		Loc_u8TempRegister |= (UserConfig->Mode_Select)<<UCSRC_UMSEL_BIT;			//BIT 	6
		Loc_u8TempRegister |= (UserConfig->Parity_Mode)<<UCSRC_UPM_BIT;				//BITS	5,4
		Loc_u8TempRegister |= (UserConfig->Stop_Bits_Number)<<UCSRC_USBS_BIT;		//BIT 	3
		Loc_u8TempRegister |= (UserConfig->Char_Size) << UCSRC_UCSZ_BIT;				//BITS 	2,1
		if(UserConfig->Char_Size >CHAR_SIZE_8_){
			SetBit(UCSRB,UCSRB_UCSZ2_BIT);
		}
		Loc_u8TempRegister |= (UserConfig->Clock_Polarity);							//BIT 	0

		/*Accessing UCSRC BY BIT SETTING BIT 7 AND ASSIGNING IT THE SETTINGS VALUE*/
		UCSRC = (1<<UCSRC_URSEL_BIT)|Loc_u8TempRegister;

		/*Enable Receiver*/
		SetBit(UCSRB,UCSRB_RECEIVE_BIT);
		/*Enable Transmitter*/
		SetBit(UCSRB,UCSRB_SEND_BIT);
	}
	else{
		/*NULL POINTER IS PASSED, DO NOTHING*/
	}

}




void UART_VoidSendData(u16 Copy_u16Data){

	/*WAIT TILL TRANSMIT FLAG IS UP*/
	while(GetBit(UCSRA,UCSRA_UDRE_BIT)==0);
	/*Checking if 9 character size is configured*/
	if(GetBit(UCSRB,UCSRB_UCSZ2_BIT)==1){
		/*If 9 bits data are going to be sent*/
		if(Copy_u16Data>MAX_8BIT_VALUE){
			SetBit(UCSRA,UCSRA_TRASMIT_BIT);
		}
		else{
			/*If less than 9 bits are sent do nothing*/
		}
	}
	else{

	}
	/*Send the first 8 bits to UDR*/
	UDR=(u8)Copy_u16Data;
}


void UART_VoidReceiveData(u16 * Copy_u16Reading){

	if((Copy_u16Reading)!=NULL){
		/*WAIT TILL RECEVIE COMPLETE FLAG IS UP*/
		while(GetBit(UCSRA,UCSRA_RXC_BIT)==0);
		/*Checking if 9 character size is configured*/
		if(GetBit(UCSRB,UCSRB_UCSZ2_BIT)==1){
			/*Get the ninth data bit first, then assign its value to the Reading variable*/
			*Copy_u16Reading=(GetBit(UCSRA,UCSRA_RECEIVE_BIT)<<9);
		}
		else{
			/*Do nothing*/
		}
		/*Read the first 8 bits to UDR*/
		*Copy_u16Reading=UDR;
	}
}


void UART_VoidSendDataU8(u8 Copy_u8Data){

	/*WAIT TILL DATA REGISTER EMPTY FLAG IS UP (CAN TRANSIMIT)*/
	while(GetBit(UCSRA,UCSRA_UDRE_BIT)==0);
	/*Send the first 8 bits to UDR*/
	UDR=Copy_u8Data;
}


void UART_VoidReceiveDataU8(u8 * Copy_u8Reading){

	if((Copy_u8Reading)!=NULL){
		/*WAIT TILL RECEVIE COMPLETE FLAG IS UP*/
		while(GetBit(UCSRA,UCSRA_RXC_BIT)==0);
		/*Read the first 8 bits to UDR*/
		*Copy_u8Reading=UDR;
	}
	else{

	}
}













void UART_SendBufferSync(string * Copy_u8Array,u8 Copy_Size){
	u8 Local_u8Iterator=0;
	for(Local_u8Iterator=0;Local_u8Iterator<Copy_Size;Local_u8Iterator++){
		UART_VoidSendDataU8(Copy_u8Array[Local_u8Iterator]);
	}

}
void UART_SendStringSync(string * Copy_u8String){
	u8 Local_u8Iterator=0;
//		UART_VoidSendDataU8(*(Copy_u8String));
	while(*(Copy_u8String+Local_u8Iterator)!='\0'){
		UART_VoidSendDataU8(*(Copy_u8String+Local_u8Iterator));
		Local_u8Iterator++;
	}
}



void UART_ReceiveBufferSync(string* Copy_u8Data,u8 Copy_Size){
	u8 Local_u8Iterator=0;
	if(Copy_u8Data!=NULL){
		for(Local_u8Iterator=0;Local_u8Iterator<Copy_Size;Local_u8Iterator++){
			UART_VoidReceiveDataU8((u8 *)(Copy_u8Data+Local_u8Iterator));
		}
	}
	else{

	}
}
void UART_ReceiveStringSync(string * Copy_u8String){
	s8 Local_u8Iter=-1;
	u8 Local_u8Iterator=0;
	do{//Receive characters one by one till a termination null is encountered
		if(Copy_u8String[Local_u8Iterator]=='\0'){
			break;
		}
		//Type casting the string to address of u8
		UART_VoidReceiveDataU8((u8 *)(Copy_u8String+Local_u8Iterator));
		Local_u8Iterator++;
		Local_u8Iter++;
	}
	while(Copy_u8String[Local_u8Iter]!='\0');
}




void UART_SendBufferAsync(u8* Copy_u8Data,u16 Copy_Size,void(*funcPtr)(void)){
	/*Sending Async can be done in 2 ways , by sending first byte(element) in the function
	 * and enabling the Sending complete INT, and letting its interrupt send the rest. AYSYC function
	 * Initializes the needed parameters and sends first element.
	 * OR
	 * By Enabling the EMPTY UDR INT which indicates that the UDR is empty and ready to
	 * receive new data to send (ready to be written), and letting its INT send all elements.(AYSYC function
	 * only Initializes the needed parameters)
	 * */
	/*Checking if a Callback function is sent*/
	if(funcPtr!=NULL){
		/*Enable transmit complete interrupt OR Enable Empty UDR interrupt*/

//		SetBit(UCSRB,UCSRB_SEND_INT_BIT);
		SetBit(UCSRB,UCSRB_EMPTY_INT_BIT);

		/*Checking if there is Buffer sent */
		if(Copy_u8Data !=NULL){
			/*Initializing Global array*/
			GlobalData=Copy_u8Data;
			/*Setting call back function*/
			SendPtrCallBack=funcPtr;
			/*Assign Global size to size passed*/
			GlobalSendSize=Copy_Size;

			/*Send the first 8 bits to UDR (ONLY IF SEND INT IS ENABLED) */
//			UDR=Copy_u8Data[0];
		}
		else{
			/*Return Error-state No array is passed*/
		}
	}
	else{
		/*Return Error-state no function is passed*/
	}
}


void UART_ReceiveBufferAsync(u8* Copy_u8Data,u8 Copy_Size,void(*funcPtr)(void)){
	/*The Receive Complete Flag is flag which indicate that there is new data received in the UDR ready to be
	 * read, so by Enabling its INT, First element to last elements are read in the INT, AYSYC function
	 * only Initializes the needed parameters.
	 * */
	if(funcPtr!=NULL){
		if(Copy_u8Data!=NULL){
			/*Enable Receive data interrupt*/
			SetBit(UCSRB,UCSRB_RECEIVE_INT_BIT);
			/*Initialize Receiving array*/
			GlobalReceiveData=Copy_u8Data;
			/*Initialize Size */
			GlobalReceiveSize=Copy_Size;
			/*Initialize Callback pointer*/
			ReceivePtrCallBack=funcPtr;
		}
		else{
			/*If no data is sent , Error state No data sent*/
		}
	}
	else{
		/*If no Application function is sent , Error state No function is sent sent*/
	}
}










/*UART RECEIVE COMPLETE INT*/
void __vector_13 (void)__attribute((signal));
void __vector_13(void){
	if(ReceivePtrCallBack!=NULL){
		static u8 Local_u8counter=0;
		/*Receive next characters, till the last one */
		GlobalReceiveData[Local_u8counter]=UDR;
		Local_u8counter++;
		if(Local_u8counter==GlobalReceiveSize){
			/*Disable Interrupt*/
			ClearBit(UCSRB,UCSRB_RECEIVE_INT_BIT);
			/*After Receiving all elements,Invoke Callbackptr */
			ReceivePtrCallBack();
		}

	}

	else{
		/*If no Pointer is passed to the global pointer, Do nothing*/
	}
}
/*UART EMPTY UDR INT*/
void __vector_14 (void)__attribute((signal));
void __vector_14(void){
	if(SendPtrCallBack!=NULL){
		static u8 Local_u8counter=0;

		UDR=GlobalData[Local_u8counter];
		Local_u8counter++;
		if(Local_u8counter==GlobalSendSize){
			/*Disable Interrupt*/
			ClearBit(UCSRB,UCSRB_EMPTY_INT_BIT);
			/*After Sending all elements,Invoke Callbackptr */
			SendPtrCallBack();
		}
	}
	else{
		/*If no Pointer is passed to the global pointer, Do nothing*/
	}

}


/*UART SEND COMPLETE INT*/
void __vector_15 (void)__attribute((signal));
void __vector_15(void){
	if(SendPtrCallBack!=NULL){
		static u8 Local_u8counter=0;
		Local_u8counter++;
		if(Local_u8counter<GlobalSendSize){
			/*Send next character */
			UDR=GlobalData[Local_u8counter];
		}
		else{
			/*Disable Interrupt*/
			ClearBit(UCSRB,UCSRB_SEND_INT_BIT);
			/*After sending all elements,Invoke Callbackptr */
			SendPtrCallBack();
		}
	}
	else{
		/*If no Pointer is passed to the global pointer, Do nothing*/
	}

}
