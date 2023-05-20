/*
 * GPT_Program.c
 *
 *  Created on: Apr 8, 2023
 *      Author: Youssef
 */
#include "../../INC/MATH_BIT.h"
#include "../../INC/STD_TYPES.h"
#include "GPT_private.h"
#include "GPT_Config.h"
#include "GPT_Interface.h"

static void(*CallBackPtrCompareMatch)(void)=NULL;
static void(*DelayCallBackPtrCompareMatch)(void)=NULL;
static void(*CallBackPtrICU)(void)=NULL;


void TIMER0_VoidInit(void){
	/*Initialize Wave Mode */
#if (TIMER0_WaveMode==TIMER0_OverFlow)
	ClearBit(TCCR0,TCCR0_WaveGeneration_BIT00);
	ClearBit(TCCR0,TCCR0_WaveGeneration_BIT01);
#elif (TIMER0_WaveMode==TIMER0_PhaseCorrectedPWM)
	SetBit(TCCR0,TCCR0_WaveGeneration_BIT00);
	ClearBit(TCCR0,TCCR0_WaveGeneration_BIT01);
#elif (TIMER0_WaveMode==TIMER0_CaptureCompareMatch)
	ClearBit(TCCR0,TCCR0_WaveGeneration_BIT00);
	SetBit(TCCR0,TCCR0_WaveGeneration_BIT01);

	/*Assign the compare match value to Output Compare Register*/
	OCR0=TIMER0_CompareValue;
	/*ENABLE CAPTURE COMPARE TIMER Interrupt*/
	SetBit(TIMSK,TIMSK_OCIE0_BIT);

#elif (TIMER0_WaveMode==TIMER0_FastPWM)
	SetBit(TCCR0,TCCR0_WaveGeneration_BIT01);
	SetBit(TCCR0,TCCR0_WaveGeneration_BIT00);

#else
#error "Invalid Wave selected"
#endif
	//
	//	/*Do nothing to PIN0 Upon finding a match */
	//	ClearBit(TCCR0,TCCR0_CompareMatchOutMode_BIT0);
	//	ClearBit(TCCR0,TCCR0_CompareMatchOutMode_BIT1);

	TCCR0&=TCCR0_CompareMatch_Mask;
//	TCCR0|=TIMER0_COMPARE_MATCH_MODE_SELECT;

	/*Choosing the Pre-scaler CLOCK AND start counting */
#if(TIMER0_Prescaler<TCCR0_SOURCE_NOSOURCE || TIMER0_Prescaler>TCCR0_SOURCE_EXT_RISE)
#warning "Invalid CLOCK SOURCE, CLOCK IS DISABLED"
	TCCR0&=TCCR0_ClockSelectMask;
	TCCR0|=TCCR0_SOURCE_NOSOURCE
#else
	TCCR0&=TCCR0_ClockSelectMask;
	TCCR0|=TIMER0_Prescaler;

#endif




}
void TIMER0_SetCompareValue(u8 Copy_u8Value){
	OCR0= Copy_u8Value;
}
void TIMER0_VoidCallBack(void (*FunctionCopy)(void)){
	/*If a function pointer is passed to the call back function */
	if(FunctionCopy!=NULL){
		CallBackPtrCompareMatch=FunctionCopy;
	}
	else{
		/*Do nothing (Assign an Error) */
	}

}
void TIMER0_VoidPWM(void){
	/*Setting the timer to fast PWM*/
	SetBit(TCCR0,TCCR0_WaveGeneration_BIT01);
	SetBit(TCCR0,TCCR0_WaveGeneration_BIT00);
	/*NON inverting PWM CLEAR TOP, SET UPON MATCH*/
	ClearBit(TCCR0,TCCR0_CompareMatchOutMode_BIT0);
	SetBit(TCCR0,TCCR0_CompareMatchOutMode_BIT1);

	/*Generating PWM with a period of 255Micro and 25% DutyCycle*/
	/*Example: For a 8MHZ clock & 8 pre-scaler division, 0.25*256 =64,OCR=64 */
	OCR0=128;
	ClearBit(TCCR0,TCCR0_ClockSelect_BIT0);
	SetBit(TCCR0,TCCR0_ClockSelect_BIT1);
	ClearBit(TCCR0,TCCR0_ClockSelect_BIT2);

}
void TIMER0_VoidStop(void){
	TCCR0&=TCCR0_ClockSelectMask;
	/*Flush Timer Counter Register*/
	TCNT0=0;
}

void TIMER0_VoidLowerOVFlag(void){
	TCNT0=0;
	SetBit(TIFR,TIFR_TOV1_BIT);
}


void SyncDelay_ms(u16 Copy_u16Delaytime){
	/*Delay Time must be more than 0ms*/
	if(Copy_u16Delaytime>0){
		/*Please configure The system freq and pre-scaler*/
		/*OCR=(system freq*Delayfreq/Prescaler)*/

		/*Assigning compare value*/
		OCR1A_2BYTE=(SYSTEM_FREQ_MHZ*1000ULL*Copy_u16Delaytime/(1024ULL));
		/*If Start counter only if OCR1A is 16bit range*/
		if(OCR1A_2BYTE<MAX_16_BIT_VALUE)
		{
			/*Choosing CTC MODE for timer 1*/
			ClearBit(TCCR1A,TCCR1A_WaveFormModeBit0);
			ClearBit(TCCR1A,TCCR1A_WaveFormModeBit1);
			SetBit(TCCR1B,TCCR1B_WaveFormModeBit0);
			ClearBit(TCCR1B,TCCR1B_WaveFormModeBit1);

			/*Choosing Normal operation for pin at channel A*/
			TCCR1A&=TCCR1A_Match_MaskChannelA;
			TCCR1A|=TIMER1_CompareMatch_DisconnectOC1A;
			/*Disable OCR1A Interrupt*/
			ClearBit(TIMSK,TIMSK_OCIE0_BIT);

			/*Choosing Pre-scaler for timer 1 */
			TCCR1B&=TCCR0_ClockSelectMask;
			TCCR1B|=TCCR1B_SOURCE_1024_PRE;


			/*WAIT TILL delay finishes*/
			while(GetBit(TIFR,TIFR_OCF1A_BIT)==0);
			/*Clear Flag after delay is done*/
			SetBit(TIFR,TIFR_OCF1A_BIT);
		}
		else{

		}
	}
	else
	{

	}
}

void AsyncDelay_ms(u16 Copy_u16Delaytime,void (*FunctionCopy)(void)){
	/*Please configure The system freq and pre-scaler*/
	/*Delay Time must be more than 0ms*/
	if(Copy_u16Delaytime>0)
	{
		/*Assigning to app funtion to ISR*/
		DelayCallBackPtrCompareMatch=FunctionCopy;

		/*OCR=(system freq*Delayfreq/Prescaler)*/
		/*Assigning compare value*/
		OCR1A_2BYTE=(SYSTEM_FREQ_MHZ*1000ULL*Copy_u16Delaytime/(Delay_TIMER_PRESECALER_DIVISOR));
		if(OCR1A_2BYTE<MAX_16_BIT_VALUE)
		{
			/*Choosing CTC MODE for timer 1*/
			ClearBit(TCCR1A,TCCR1A_WaveFormModeBit0);
			ClearBit(TCCR1A,TCCR1A_WaveFormModeBit1);
			SetBit(TCCR1B,TCCR1B_WaveFormModeBit0);
			ClearBit(TCCR1B,TCCR1B_WaveFormModeBit1);

			/*Choosing Normal operation for pin at channel A*/
			TCCR1A&=TCCR1A_Match_MaskChannelA;
			TCCR1A|=TIMER1_CompareMatch_DisconnectOC1A;
			/*Enable OCR1A Interrupt Channel A interrupt*/
			SetBit(TIMSK,TIMSK_OCIE1A_BIT);

			/*Choosing Pre-scaler for timer 1 */
			TCCR1B&=TCCR0_ClockSelectMask;
			TCCR1B|=Delay_TIMER_PRESECALER_Select;
		}
		else{

		}
	}
	else{

	}
}


void TIMER1_VoidInit(void){

	/*Choosing Out Mode upon match (Set/Clear) for channel A*/
	TCCR1A&=TCCR1A_Match_MaskChannelA;
	TCCR1A|=TIMER1_COMPARE_MATCH_MODE_SELECTA;


	/*Choosing WaveGeneration Mode (FAST PWM ICR1 TOP)*/
	ClearBit(TCCR1A,TCCR1A_WaveFormModeBit0);
	SetBit(TCCR1A,TCCR1A_WaveFormModeBit1);
	SetBit(TCCR1B,TCCR1B_WaveFormModeBit0);
	SetBit(TCCR1B,TCCR1B_WaveFormModeBit1);

	/*Choosing the Pre-scaler CLOCK AND start counting */
#if(TIMER1_Prescaler<TCCR1B_SOURCE_NOSOURCE || TIMER1_Prescaler>TCCR1B_SOURCE_EXT_RISE)
#warning "Invalid CLOCK SOURCE, CLOCK IS DISABLED"
	TCCR1B&=TCCR1B_ClockSelectMask;
	TCCR1B|=TCCR1_SOURCE_NOSOURCE
#else
	TCCR1B&=TCCR1B_ClockSelectMask;
	TCCR1B|=TIMER1_Prescaler;
#endif



}
void TIMER1SetChannelACompareValue(u16 Copy_u16CompareValue){
	/*Setting Compare Value*/
	OCR1A_2BYTE=Copy_u16CompareValue;
}
void TIMER1_VoidSetICR(u16 Copy_u16TopValue){
	/*Setting TOP value*/
	ICR1_2BYTE=Copy_u16TopValue;
}

void TIMER1_VoidStart(void){
/*Set PRESCALER AND START TIMER 1*/
	TCCR1B&=TCCR1B_ClockSelectMask;
	TCCR1B|=TIMER1_Prescaler;
}
void TIMER1_VoidStop(void){
	TCCR1B&=TCCR1B_ClockSelectMask;
	/*Flush Timer Counter Register*/
	TCNT1_2BYTE=0;

}


void PWM_VoidSetFreq(u8 Copy_u8Freq){

	u64 Local_TimerFreq=(u64)((SYSTEM_FREQ_MHZ*1000000)/PWM_TIMER1_PRESECALER_DIVISOR);

	ICR1_2BYTE=(Local_TimerFreq/Copy_u8Freq);


}
void PWM_VoidSetDutyCycle(u8 Copy_u8DutyCycle){
	u16 Local_u8Temp=0;
	Local_u8Temp=(ICR1_2BYTE*Copy_u8DutyCycle)/100;
	OCR1A_2BYTE=Local_u8Temp;
}
void PWM_VoidStartPWM(u8 Copy_u8Freq,u8 Copy_u8DutyCycle,u8 Copy_u8Channel){

	u64 Local_TimerFreq=(u64)((SYSTEM_FREQ_MHZ*1000000ULL)/(PWM_TIMER1_PRESECALER_DIVISOR*Copy_u8Freq));
	u64 Local_OCR1x=0;
	if(Copy_u8DutyCycle<100)
	{
		if(Local_TimerFreq<MAX_16_BIT_VALUE){
			/*If Tick counts and duty cycle are in range*/
			ICR1_2BYTE= Local_TimerFreq;
			Local_OCR1x=((u64)ICR1_2BYTE*Copy_u8DutyCycle)/100Ull;
			OCR1B_2BYTE=Local_OCR1x;

			/*Setting the timer to fast PWM With ICR ON TOP */
			ClearBit(TCCR1A,TCCR1A_WaveFormModeBit0);
			SetBit(TCCR1A,TCCR1A_WaveFormModeBit1);
			SetBit(TCCR1B,TCCR1B_WaveFormModeBit0);
			SetBit(TCCR1B,TCCR1B_WaveFormModeBit1);
			/*Choose channel output wave on */
			if(Copy_u8Channel==CHANNEL_A){
			/*NON inverting PWM CLEAR TOP, SET UPON MATCH FOR CHANNEL A*/
				ClearBit(TCCR1A,TCCR1A_OutModeChannelA_BIT0);
				SetBit(TCCR1A,TCCR1A_OutModeChannelA_BIT1);
			}
			else if(Copy_u8Channel==CHANNEL_B){
				/*NON inverting PWM CLEAR TOP, SET UPON MATCH FOR CHANNEL B*/
				ClearBit(TCCR1A,TCCR1A_OutModeChannelB_BIT0);
				SetBit(TCCR1A,TCCR1A_OutModeChannelB_BIT1);
			}
			else{
				/*No output will be generated since an invalid channel was selected*/
				ClearBit(TCCR1A,TCCR1A_OutModeChannelA_BIT0);
				ClearBit(TCCR1A,TCCR1A_OutModeChannelA_BIT1);
				ClearBit(TCCR1A,TCCR1A_OutModeChannelB_BIT0);
				ClearBit(TCCR1A,TCCR1A_OutModeChannelB_BIT1);
			}
			/*Set clock prescaler and start timer*/
			TCCR1B&=TCCR1B_ClockSelectMask;
			TCCR1B|=PWM_TIMER1_PRESECALER_Select;

		}
		else{
			/*Do nothing if Ticks counts are too high*/
		}
	}
	else
	{
		/*Do nothing if Duty cycle is too high*/
	}
}
void PWM_VoidStopPWM(void){
	/*Flushing clock Select*/
	TCCR1B&=TCCR1B_ClockSelectMask;
	/*Flushing Timer counter Register*/
	TCNT1_2BYTE=0;
	/*Flushing compare match value CHANNEL A*/
	OCR1A_2BYTE=0;
	/*Flushing compare match value CHANNEL B*/
	OCR1B_2BYTE=0;
}

void ICU_SetEdgeTrigger(u8 Copy_u8Edege){
	/*Select ICU EDGE TRIGGER*/
	switch (Copy_u8Edege)
	{
	case ICU_FALL_TRIGGER:
		ClearBit(TCCR1B,TCCR1B_ICES1);
		break;
	case ICU_RISE_TRIGGER:
		SetBit(TCCR1B,TCCR1B_ICES1);
		break;
	default:
		break;
	}
}
void ICU_VoidDisableICU(void){
	/*Disable Input capture Interrupt */
	ClearBit(TIMSK,TIMSK_TICIE_BIT);
}
void ICU_VoidEnableICU(u8 Copy_u8Edege){

	/*Select ICU EDGE TRIGGER*/
	switch (Copy_u8Edege)
	{
	case ICU_FALL_TRIGGER:
		ClearBit(TCCR1B,TCCR1B_ICES1);
		break;
	
	case ICU_RISE_TRIGGER:
		SetBit(TCCR1B,TCCR1B_ICES1);
		break;
	default:
		break;
	}
	/*Enable Noise Mitigation*/
	SetBit(TCCR1B,TCCR1B_ICNC1);
	/*Enable Input capture Interrupt */
	SetBit(TIMSK,TIMSK_TICIE_BIT);
}

void ICU_VoidSetCallBack(void(*UserFunction)(void)){

	CallBackPtrICU=UserFunction;
}
u16 ICU_VoidReadICR(void){
	return ICR1_2BYTE;
}
/*Interrupt Vector for Timer/Counter0 Compare Match*/
void __vector_10(void) __attribute__((signal));
void __vector_10(void){
	if(CallBackPtrCompareMatch !=NULL){
		CallBackPtrCompareMatch();
	}
	else
	{
		/*No function is passed to the ISR*/
	}

}

/*Interrupt Vector for Timer1 Compare Match A*/
void __vector_7(void) __attribute__((signal));
void __vector_7(void){
	if(DelayCallBackPtrCompareMatch!=NULL){
		DelayCallBackPtrCompareMatch();
	}
	else
	{
		/*No function is passed to the ISR*/
	}

}

/*Interrupt Vector for Input capture event*/
void __vector_6(void) __attribute__((signal));
void __vector_6(void){

	if(CallBackPtrICU!=NULL){
		CallBackPtrICU();
	}
	else{
		/*Do nothing*/
	}
}
