/*
 * GPT_Private.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Youssef
 */

#ifndef MCAL_GPT_GPT_PRIVATE_H_
#define MCAL_GPT_GPT_PRIVATE_H_

/* ******************************** TCNT0************************************** */
/*8BIT TIMER0/Counter Register (value of counter)   */
#define TCNT0						*((u8 volatile *)0x52)
/* ******************************** TCCR0************************************** */
/* Timer/Counter Control Register   */
#define TCCR0  						*((u8 volatile *)0x53)
/*Bit to force a Match Event */
#define TCCR0_ForceOutCompare_BIT     				7
/* Sequence Mode of  the counter*/
#define TCCR0_WaveGeneration_BIT00					6
#define TCCR0_WaveGeneration_BIT01					3

#define TIMER0_OverFlow								1
#define TIMER0_CaptureCompareMatch					2
#define TIMER0_FastPWM								3
#define TIMER0_PhaseCorrectedPWM					4


/*Bits to control output upon Match Event */
#define TCCR0_CompareMatch_Mask  					0b11001111
#define TCCR0_CompareMatchOutMode_BIT1				5
#define TCCR0_CompareMatchOutMode_BIT0				4

/*Fast PWM Set PIN(OC0,PORT B PIN3)on Compare Match, Clear it on TOP*/
#define TIMER0_FAST_PWM_ClearCompare_SetTop						(0B10<<4)
#define TIMER0_FAST_PWM_SetCompare_ClearTop						(0B11<<4)

/*Bits to select clock source */
#define TCCR0_ClockSelect_BIT2				2
#define TCCR0_ClockSelect_BIT1				1
#define TCCR0_ClockSelect_BIT0				0

#define TCCR0_ClockSelectMask				0b11111000
#define TCCR0_SOURCE_NOSOURCE				0
#define TCCR0_SOURCE_0_PRE					1
#define TCCR0_SOURCE_8_PRE					2
#define TCCR0_SOURCE_64_PRE					3
#define TCCR0_SOURCE_256_PRE				4
#define TCCR0_SOURCE_1024_PRE				5
#define TCCR0_SOURCE_EXT_FALL				6
#define TCCR0_SOURCE_EXT_RISE				7


/* ******************************** OCR0 ************************************** */
/*Output Compare Register (8Bit value that is compared to the counter to trigger an INTs)*/
#define OCR0  						*((volatile u8 *)0x5C)

/* ******************************** TIMSK ************************************** */
/*  Timer/Counter Interrupt Mask Register */
#define TIMSK						*((volatile u8 *)0x59)
/*Timer/Counter0 Overflow Interrupt Enable*/
#define TIMSK_TOIE0_BIT						0
/*Timer/Counter0 Compare Match Interrupt Enable*/
#define TIMSK_OCIE0_BIT						1


/*Timer/Counter1 Overflow Interrupt Enable*/
#define TIMSK_TOIE1_BIT						2
/*Timer/Counter1 Compare Match Interrupt Enable CHANNEL B*/
#define TIMSK_OCIE1B_BIT					3
/*Timer/Counter1 Compare Match Interrupt Enable CHANNEL A*/
#define TIMSK_OCIE1A_BIT					4
/*Timer/Counter1 Input Capture Interrupt Enable*/
#define TIMSK_TICIE_BIT						5
/* ******************************** TIFR ************************************** */

/*Timer/Counter Interrupt Flag Register*/
#define TIFR						*((volatile u8 *)0x58)
/*Output Compare Flag 0*/
#define TIFR_OCF0_BIT							1
/*Timer/Counter0 Overflow Flag*/
#define TIFR_TOVF0_BIT							0
/*Timer/Counter1 Overflow Flag*/
#define TIFR_TOV1_BIT							2
/*Timer/Counter1 Channel B Compare match Flag*/
#define TIFR_OCF1B_BIT							3
/*Timer/Counter1 Channel A Compare match Flag*/
#define TIFR_OCF1A_BIT							4
/*Timer/Counter1 Channel A Compare match Flag*/
#define TIFR_ICF_BIT							5

/* ******************************** TCCR1A ************************************** */
/*Timer/Counter1 Control Register for Register A*/
#define TCCR1A 						*((volatile u8 *)0x4F)
#define TCCR1A_OutModeChannelA_BIT1			7
#define TCCR1A_OutModeChannelA_BIT0			6



#define TCCR1A_Match_MaskChannelA			0b00111111
/*TIMER1 CHANNELA PIN (OC1A,PORT D PIN5)*/
#define TIMER1_FAST_PWM_SetTopChannelA						(0b10<<6)
#define TIMER1_FAST_PWM_ClearTopChannelA					(0b11<<6)

#define TIMER1_CompareMatch_DisconnectOC1A					(0b00<<6)
#define TIMER1_CompareMatch_ToggleOC1A						(0b01<<6)
#define TIMER1_CompareMatch_ClearOC1A						(0b10<<6)
#define TIMER1_CompareMatch_SetOC1A							(0b11<<6)

#define TIMER1_PhaseCorrect_ClearUp_SetDownOC1A				(0b10<<6)
#define TIMER1_PhaseCorrect_SetUp_ClearDownOC1A				(0b11<<6)

#define TCCR1A_OutModeChannelB_BIT1			5
#define TCCR1A_OutModeChannelB_BIT0			4

#define TCCR1A_Match_MaskChannelB			0B11001111
/*TIMER1 CHANNELB PIN (OC1B,PORT D PIN4)*/
#define TIMER1_FAST_PWM_SetTopChannelB						(0B10<<4)
#define TIMER1_FAST_PWM_ClearTopChannelB					(0B11<<4)

#define TIMER1_CompareMatch_ToggleOC1B						(0b01<<4)
#define TIMER1_CompareMatch_ClearOC1B						(0b10<<4)
#define TIMER1_CompareMatch_SetOC1B							(0b11<<4)

#define TIMER1_PhaseCorrect_ClearUp_SetDownOC1B				(0b10<<4)
#define TIMER1_PhaseCorrect_SetUp_ClearDownOC1B				(0b11<<4)


#define TCCR1A_WaveFormModeBit0						0
#define TCCR1A_WaveFormModeBit1						1
/* ******************************** TCCR1B ************************************** */
#define TCCR1B 						*((volatile u8 *)0x4E)


#define TCCR1B_ClockSelect_BIT2				2
#define TCCR1B_ClockSelect_BIT1				1
#define TCCR1B_ClockSelect_BIT0				0

#define TCCR1B_ClockSelectMask				0b11111000
#define TCCR1B_SOURCE_NOSOURCE				0
#define TCCR1B_SOURCE_1_PRE					1
#define TCCR1B_SOURCE_8_PRE					2
#define TCCR1B_SOURCE_64_PRE				3
#define TCCR1B_SOURCE_256_PRE				4
#define TCCR1B_SOURCE_1024_PRE				5
#define TCCR1B_SOURCE_EXT_FALL				6
#define TCCR1B_SOURCE_EXT_RISE				7

#define TCCR1B_WaveFormModeBit0				3
#define TCCR1B_WaveFormModeBit1				4

#define TCCR1B_ICNC1                        7   //INPUT CAPTURE NOISE CANCELER
#define TCCR1B_ICES1                        6   //INPUT CAPTURE EDGE SELECT

/* ******************************** OCR1A ************************************** */
#define OCR1AH				 		*((volatile u8 *)0x4B)
#define OCR1AL						*((volatile u8 *)0x4A)
#define OCR1A_2BYTE					*((volatile u16 *)0x4A)
/* ******************************** OCR1A ************************************** */
#define OCR1BH				 		*((volatile u8 *)0x49)
#define OCR1BL						*((volatile u8 *)0x48)
#define OCR1B_2BYTE					*((volatile u16 *)0x48)

/* ******************************** TCNT1 ************************************** */
#define TCNT1H						*((volatile u8 *)0x4D)
#define TCNT1L						*((volatile u8 *)0x4C)
#define TCNT1_2BYTE					*((volatile u16 *)0x4C)

/* ******************************** ICR1 ************************************** */
#define ICR1H						*((volatile u8 *)0x47)
#define ICR1L						*((volatile u8 *)0x46)
#define ICR1_2BYTE					*((volatile u16 *)0x46)

/************************************OUTPUT MODES********************************/


#define MAX_16_BIT_VALUE			0XFFFF


#endif /* MCAL_GPT_GPT_PRIVATE_H_ */
