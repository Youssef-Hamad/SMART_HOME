
#include "../../INC/STD_TYPES.h"
#include "../../INC/MATH_BIT.h"


#include "../DIO/DIO_Interface.h"
#include "ADC_Private.h"

#include "ADC_Interface.h"

static void (*CallBackPtr)(void)=NULL;
static u16* Readingptr=NULL;
static u8 Resolution=0;
static u8 ADC_CircuitState=IDLE;


void ADC_VoidInit(void){
/********Section for Initializing ADMUX REFISTER**********/
	/*1-Reference Voltage*/
	/*Masking the Reference  BITS */
	ADMUX&=ADMUX_REF_MASK;
#if (ADC_REF_VOLTAGE_SELECT<ADC_REF_VOLTGAE_AREF) || (ADC_REF_VOLTAGE_SELECT>ADC_REF_VOLTGAE_2_56)
	#error "INVALID REFERNCE VOLTAGE SELECTED"
#else
	ADMUX|=(ADC_REF_VOLTAGE_SELECT<<6);
#endif

	/*2-MUX CHANNELS*/
	/*Masking the MUX BITS */
	ADMUX &= ADMUX_MUX_MASK;
#if (ADC_ADMUX_CHANNEL_SELCET < ADC_MUX_SINGLE_PIN0 ) || (ADC_ADMUX_CHANNEL_SELCET>ADC_MUX_0V)
	#warning "Invalid Channel selected,PIN0 Single is Automatically selected"
	ADMUX |= ADC_MUX_SINGLE_PIN0;
#else
	ADMUX |= ADC_ADMUX_CHANNEL_SELCET;
#endif

	/*3-Adjusting Result*/
#if (ADC_ADMUX_RESULT_ADJUST==ADC_10BIT_DATA)
	ClearBit(ADMUX,ADMUX_ADLR_BIT);
#elif (ADC_ADMUX_RESULT_ADJUST==ADC_8BIT_DATA)
	SetBit(ADMUX,ADMUX_ADLR_BIT);
#else
	#warning "Invalid Result Adjust selected,Adjust left Automatically selected"
	SitBIT(ADMUX,ADMUX_ADLR_BIT);
#endif

	/********Section for Initializing ADCSRA REFISTER**********/

	/********1- Pre-scaler **********/
	/*Masking the PRESCALER BITS*/
	ADCSRA &= ADCSRA_ADPS_MASK;
	//If invalid Prescaler is selected
#if (ADC_ADCSRA_PRESCALER_SELECT>ADCSRA_PRESCALER_128_DIVISION) || ((ADC_ADCSRA_PRESCALER_SELECT<ADCSRA_PRESCALER_2_DIVISION))
	#warning "Invalid Pre-scaler division selected, Division 2 is Automatically selected"
	ADCSRA |= ADCSRA_PRESCALER_2_DIVISION;
#else
	ADCSRA |= ADC_ADCSRA_PRESCALER_SELECT;
#endif



#if(ADC_ADCSRA_MODE_SELECT== ADCSRA_SINGLE_MODE)
	//AUto trigger source Off
	ClearBit(ADCSRA,ADCSRA_ADATE_BIT);
//	/*ENABLE  ADC */
	SetBit(ADCSRA,ADCSRA_ADEN_BIT);

#elif(ADC_ADCSRA_MODE_SELECT== ADCSRA_AUTO_MODE)
	//Auto trigger source ON,Conversion Complete Interrupt is on (Flag still works)
	SetBit(ADCSRA,ADCSRA_ADATE_BIT);
	SetBit(ADCSRA,ADCSRA_ADIE_BIT);
	/********Section for Initializing SFIOR REFISTER**********/

	/********* TRIGGER MODE **********/
	/*Masking the TRIGGER BITS*/
	SFIOR&=SFIOR_ADTC_MASK;

	/*Choosing the trigger Mode */
	SFIOR|=ADC_SFIOR_TRIGGER_SELECT;


	/********* ENABLE ADC **********/
	/*ENABLE  ADC */
	SetBit(ADCSRA,ADCSRA_ADEN_BIT);
	/********* START CONVERSION **********/
	/*Start Conversion */
//	SetBit(ADCSRA,ADCSRA_ADCS_BIT);



#endif





}

u16 ADC_u16GetchannelReading(void){
	u16 u16Reading=0;
//	u8  Local_u8Counter=0;

#if(ADC_ADCSRA_MODE_SELECT==ADCSRA_SYNC_MODE)
	/*Start Conversion */
	SetBit(ADCSRA,ADCSRA_ADCS_BIT);
	 //WAIT(polling) FOR THE CONVERSION FLAG TO BE RAISED OR TIMEOUT HAS OCCURED
	while(GetBit(ADCSRA,ADCSRA_ADIF_BIT)==0 && Local_u8Counter<ADC_TIMEOUT)
	{
		Local_u8Counter++;
	}
	SetBit(ADCSRA,ADCSRA_ADIF_BIT); //Clear the flag after getting the reading
#elif (ADC_ADCSRA_MODE_SELECT==ADCSRA_ASYNC_MODE)
	/*Start Conversion */
	SetBit(ADCSRA,ADCSRA_ADCS_BIT);
#endif

#if(ADC_ADMUX_RESULT_ADJUST==ADC_10BIT_DATA)

		u16Reading=(ADC_TWO_BYTE_DATA & 0b0000001111111111);

#elif(ADC_ADMUX_RESULT_ADJUST==ADC_8BIT_DATA)

		u16Reading=ADCH;
		u16Reading&=0B0000000011111111;

#endif

	return u16Reading;
}


u8 ADC_u8StartConversionSync(u16 *Reading,const u8 Resolution_Mode,const s8 Channel){
	u32 Local_u32counter=0;
	u8 ADC_localErorrState=0;
	/*Checking if correct channel is selected*/
	if((Channel< ADC_MUX_SINGLE_PIN0 ) || (Channel>ADC_MUX_0V))
	{
		ADC_localErorrState=ADC_INVALID_CHANNEL_STATE;
		return ADC_localErorrState;
	}
	else
	{
		/*Masking the MUX BITS for channel selection*/
		ADMUX &= ADMUX_MUX_MASK;
		/*Choosing the channel to be used */
		ADMUX |= Channel;
//		//Auto trigger source Off
//		ClearBit(ADCSRA,ADCSRA_ADATE_BIT);
		/*Start Conversion */
		SetBit(ADCSRA,ADCSRA_ADCS_BIT);
		/*WAIT(polling) FOR THE CONVERSION FLAG TO BE RAISED OR TIMEOUT HAS OCCURED */
		while(((GetBit(ADCSRA,ADCSRA_ADIF_BIT))==0) && (Local_u32counter!=ADC_TIMEOUT) )
		{
			Local_u32counter++;
		}
		if(Local_u32counter==ADC_TIMEOUT){
			/*If loop is broken because of time out */
			ADC_localErorrState=ADC_SYNC_TIMEOUT_STATE;
		}
		else{
			/*If loop is broken because the Flag was raised */

			/*Clear the flag after getting the reading*/
			SetBit(ADCSRA,ADCSRA_ADIF_BIT);
			///*Checking if correct resolution is selected,if so return Reading*/
			if(Resolution_Mode==ADC_10BIT_DATA)
			{
				/*Right Adjust the data then read*/
				ClearBit(ADMUX,ADMUX_ADLR_BIT);
				*Reading=(ADC_TWO_BYTE_DATA);
			}
			else if(Resolution_Mode==ADC_8BIT_DATA)
			{
				/*Left Adjust the data then read*/
				SetBit(ADMUX,ADMUX_ADLR_BIT);
				*Reading=ADCH;
			}
			else
			{
				ADC_localErorrState=ADC_INVALID_RESOLUTION_STATE;
			}

		}
	}

	return ADC_localErorrState;
}

u8 ADC_u8StartConversionAsync(u16 *Reading,const u8 Resolution_Mode,const s8 Channel,Cbf FuncPtr){
	u8 ADC_localErorrState=0;
	/*Checking if correct channel is selected*/
	if(ADC_CircuitState==IDLE)
	{
		/*Checking for Channel Entered*/
		if((Channel< ADC_MUX_SINGLE_PIN0 ) || (Channel>ADC_MUX_0V))
		{
			ADC_localErorrState=ADC_INVALID_CHANNEL_STATE;
			return ADC_localErorrState;
		}
		else
		{	ADC_CircuitState=BUSY;

			/*Masking the MUX BITS */
			ADMUX &= ADMUX_MUX_MASK;
			ADMUX |= Channel;
			/*Choosing */
			if(Resolution_Mode==ADC_8BIT_DATA){
				SetBit(ADMUX,ADMUX_ADLR_BIT);
			}
			else if(Resolution_Mode==ADC_10BIT_DATA){
				ClearBit(ADMUX,ADMUX_ADLR_BIT);
			}
			/*Pass the function to be implemented during ISR to a global Pointer*/
			CallBackPtr=FuncPtr;
			/*Pass the reading address to a global Pointer to assign it the value after conversion is done*/
			Readingptr=Reading;
			/*Setting reolution Mode*/
			Resolution=Resolution_Mode;
			/*Enable Interrupt */
			SetBit(ADCSRA,ADCSRA_ADIE_BIT);
			/*Start Conversion */
			SetBit(ADCSRA,ADCSRA_ADCS_BIT);

		}
	}
	else
	{
		ADC_localErorrState=ADC_BUSY_STATE;
	}


	return ADC_localErorrState;
}

void ADC_VoidSetCallBack(void(*FuncPtr)(void)){
	CallBackPtr=FuncPtr;
}


void __vector_16 (void) __attribute__((signal));
void __vector_16 (void){
//	/* Read the result*/
//	if(Resolution==ADC_10BIT_DATA)
//	{
//		*Readingptr=(ADC_TWO_BYTE_DATA);
//	}
//	else if(Resolution==ADC_8BIT_DATA)
//	{
//		*Readingptr=ADCH;
//	}
//	/*Change state of ADC TO IDLE,SINCE CONVERSION IS COMPLETED*/
//	ADC_CircuitState=IDLE;
//	/*Invoke Callback Function*/
//	if(CallBackPtr)
//	{
//		CallBackPtr();
//	}
//	else
//	{
//		//NullPointer
//	}
//
//	/*Disable Interrupt */
//	ClearBit(ADCSRA,ADCSRA_ADIE_BIT);
	if(CallBackPtr!=NULL){
		CallBackPtr();
	}
	else{
		//NullPointer
	}

}
