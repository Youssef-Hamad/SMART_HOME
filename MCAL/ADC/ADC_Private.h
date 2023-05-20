/*
 * ADC_Private.h
 *
 *  Created on: 4 Apr 2023
 *      Author: Youssef
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_



/* ******************************** DATA REGISTERS ************************************** */
#define ADC_TWO_BYTE_DATA *((u16 volatile *)(0x24))//ADC Data Register 2 Bytes
#define ADCL 			*((u8 volatile *)(0x24))//ADC Data Register High Byte
#define ADCH 			*((u8 volatile *)(0x25))//ADC Data Register Low Byte





/* ******************************** ACSR************************************** */
#define ACSR 			*((u8 volatile *)(0x28)) //Analog Comparator Control and Status Register
#define ACSR_ACD_BIT    	7    //Analog Comparator Disable bit
#define ACSR_ACBG_BIT   	6    //Analog Comparator BandGap select bit
#define ACSR_ACO_BIT    	5    //Analog Comparator Output bit
#define ACSR_ACIF_BIT   	4    //Analog Comparator Interrupt flag bit
#define ACSR_ACIE_BIT   	3    //Analog Comparator Interrupt Enable bit
#define ACSR_ACIC_BIT 		2    //Analog Comparator Input Capture Enable bit
#define ACSR_ACIS_BIT1  	1    //Analog Comparator Interrupt Mode select bit0
#define ACSR_ACIS_BIT0	    0    //Analog Comparator Interrupt Mode select bit1



/* ******************************** ADMUX ************************************** */
#define ADMUX 			*((u8 volatile *)(0x27)) //ADC Multiplexer Selection Register

/* *************Options for Voltage REF(BITS 7,6) ******************* */
#define ADMUX_REF_MASK		0b00111111 //Mask for Reference Voltage Selections


/* *************Options For Result Adjust BIT (5) ******************* */
#define ADMUX_ADLR_BIT    			5    //ADC Left Adjust Result Bit
#define ADC_10BIT_DATA				1
#define ADC_8BIT_DATA				2
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


/* **************************** ADCSRA *************************************** */
#define ADCSRA 			*((u8 volatile *)(0x26)) //ADC Control and Status Register

#define ADCSRA_ADEN_BIT      7    //ADC ENABLE BIT
#define ADCSRA_ADCS_BIT      6    //ADC Start Conversion BIT
#define ADCSRA_ADATE_BIT     5    //ADC Auto Trigger Enable
#define ADCSRA_ADIF_BIT      4    //ADC Interrupt Flag
#define ADCSRA_ADIE_BIT      3    //ADC Auto Interrupt Enable
/* ************** Options for Pre-scaler Division BITS (0,1,2) ******************* */
#define ADCSRA_ADPS_MASK	 		0b11111000 //Mask for Pre-scaler
#define ADCSRA_PRESCALER_2_DIVISION						1
#define ADCSRA_PRESCALER_4_DIVISION						2
#define ADCSRA_PRESCALER_8_DIVISION						3
#define ADCSRA_PRESCALER_16_DIVISION					4
#define ADCSRA_PRESCALER_32_DIVISION					5
#define ADCSRA_PRESCALER_64_DIVISION					6
#define ADCSRA_PRESCALER_128_DIVISION					7



#define ADCSRA_SINGLE_MODE	1
#define ADCSRA_AUTO_MODE	2

#define ADCSRA_SYNC_MODE  			1
#define ADCSRA_ASYNC_MODE  			2
/* **************************** SFIOR *************************************** */
#define SFIOR           *((u8 volatile *)(0x50)) //Special FunctionIO Register

/* *************Options for Auto Trigger Source(BITS 7,6,5) ******************* */
#define SFIOR_ADTC_MASK	 0b00011111 //Mask for Auto Trigger Source Selection
#define SFIOR_FREE_MODE			0	 //ADC Trigger Source Selection Bit2
#define SFIOR_ANALOG_COMPARTOR	1	 //ADC Trigger Source Selection Bit2
#define SFIOR_EXTI_0			2	 //ADC Trigger Source Selection Bit2
#define SFIOR_TIMER0_MATCH		3	 //ADC Trigger Source Selection Bit2
#define SFIOR_TIMER0_OVERFLOW	4	 //ADC Trigger Source Selection Bit2
#define SFIOR_TIMER0_MATCH_B	5	 //ADC Trigger Source Selection Bit2
#define SFIOR_TIMER1_OVERFLOW	6	 //ADC Trigger Source Selection Bit2
#define SFIOR_TIMER1_CAPTURE	7 	 //ADC Trigger Source Selection Bit2

#define SFIOR_ADCTS_BIT2	7	 //ADC Trigger Source Selection Bit2
#define SFIOR_ADCTS_BIT1 	6	 //ADC Trigger Source Selection Bit1
#define SFIOR_ADCTS_BIT0	5    //ADC Trigger Source Selection Bit0
#define SFIOR_RESERVED_BIT	4    //ADC Reserved Bit
/* *************************** BITS 3,2,1 ARE OUT OF SCOPE FOR ADC *********************/



#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
