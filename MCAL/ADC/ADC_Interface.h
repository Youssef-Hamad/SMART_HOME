/*
 * ADC_Interface.h
 *
 *  Created on: 4 Apr 2023
 *      Author: Youssef
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

#include "ADC_Config.h"

#define ADC_REF_VOLTGAE_AREF		0		//AREF, Internal Vref turned off
#define ADC_REF_VOLTGAE_AVCC		1		//AVCC with external capacitor at AREF pin
#define ADC_REF_VOLTGAE_RESERVED	2		//RESERVED (NOT USED)
#define ADC_REF_VOLTGAE_2_56		3		//Internal 2.56V Voltage Reference with external capacitor at AREF pin

#define ADC_10BIT_DATA				1
#define ADC_8BIT_DATA				  2
/* *************Options for MUX Channels(BITS 4,3,2,1,0) ******************* */
#define ADMUX_MUX_MASK	 	0b11100000 //Mask for Reference Selections Bits
#define ADC_MUX_SINGLE_PIN0							0
#define ADC_MUX_SINGLE_PIN1							1
#define ADC_MUX_SINGLE_PIN2							2
#define ADC_MUX_SINGLE_PIN3							3
#define ADC_MUX_SINGLE_PIN4							4
#define ADC_MUX_SINGLE_PIN5							5
#define ADC_MUX_SINGLE_PIN6							6
#define ADC_MUX_SINGLE_PIN7							7
#define ADC_MUX_DIFF_PIN0_PIN_0_GAIN10 				8
#define ADC_MUX_DIFF_PIN1_PIN_0_GAIN10	 			9
#define ADC_MUX_DIFF_PIN0_PIN_0_GAIN200 			10
#define ADC_MUX_DIFF_PIN1_PIN_0_GAIN200 			11
#define ADC_MUX_DIFF_PIN2_PIN_2_GAIN10 				12
#define ADC_MUX_DIFF_PIN3_PIN_2_GAIN10 				13
#define ADC_MUX_DIFF_PIN2_PIN_2_GAIN200 			14
#define ADC_MUX_DIFF_PIN3_PIN_2_GAIN200 			15
#define ADC_MUX_DIFF_PIN0_PIN_1_GAIN1 				16
#define ADC_MUX_DIFF_PIN1_PIN_1_GAIN1 				17
#define ADC_MUX_DIFF_PIN2_PIN_1_GAIN1 				18
#define ADC_MUX_DIFF_PIN3_PIN_1_GAIN1 				19
#define ADC_MUX_DIFF_PIN4_PIN_1_GAIN1 				20
#define ADC_MUX_DIFF_PIN5_PIN_1_GAIN1 				21
#define ADC_MUX_DIFF_PIN6_PIN_1_GAIN1 				22
#define ADC_MUX_DIFF_PIN7_PIN_1_GAIN1 				23
#define ADC_MUX_DIFF_PIN0_PIN_2_GAIN1 				24
#define ADC_MUX_DIFF_PIN1_PIN_2_GAIN1 				25
#define ADC_MUX_DIFF_PIN2_PIN_2_GAIN1 				26
#define ADC_MUX_DIFF_PIN3_PIN_2_GAIN1 				27
#define ADC_MUX_DIFF_PIN4_PIN_2_GAIN1 				28
#define ADC_MUX_DIFF_PIN5_PIN_2_GAIN1 				29
#define ADC_MUX_1_22V								30
#define ADC_MUX_0V									31




#define SFIOR_FREE_RUN								  0
#define SFIOR_ANALOG								    1
#define SFIOR_EXTERNAL_INT							2
#define SFIOR_TIMER0_MATCH							3
#define SFIOR_TIMER0_OVERFLOW						4
#define SFIOR_TIMER1_MATCH							5
#define SFIOR_TIMER1_OVERFLOW						6
#define SFIOR_TIMER1_CAPTURE_EVENT					7


typedef void(*Cbf)(void);

/*Pre-Build Initialize ADC with (Voltage reference, 8~10 bit , Pres-caler Division,
  * Channel selection) Configurations
  */
void ADC_VoidInit(void);
/*Pre-Build Channel Reading ADC with Polling  (Asynchronous Reading) */
u16 ADC_u16GetchannelReading(void);

u8 ADC_u8StartConversionSync(u16 *Reading,const u8 Resolution_Mode,const s8 Channel);

u8 ADC_u8StartConversionAsync(u16 *Reading,const u8 Resolution_Mode,const s8 Channel,Cbf FuncPtr);


u8 ADC_u8StartChainConversionAsync(void);

void ADC_VoidSetCallBack(void(*FuncPtr)(void));
#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
