/*
 * GPT_Config.h
 *
 *  Created on: Apr 8, 2023
 *      Author: Youssef
 */

#ifndef MCAL_GPT_GPT_CONFIG_H_
#define MCAL_GPT_GPT_CONFIG_H_


#define TIMER0_CompareValue					125

#define TIMER0_WaveMode						TIMER0_OverFlow
#define TIMER0_COMPARE_MATCH_MODE_SELECT	TIMER0_FAST_PWM_ClearCompare_SetTop
#define TIMER0_Prescaler					TCCR0_SOURCE_1024_PRE



/*****************************Delay Configurations*******************************/
/*OPTIONS FOR SYSTEM FREQ(MHZ):
 * 1,2,8,16
 *
 * */
#define SYSTEM_FREQ_MHZ						8ULL
/*OPTIONS FOR TIMER PRESCALER (PWM & DELAY):
 * 1,8,64,256,1024
 *
 * */
#define PWM_TIMER1_PRESECALER_DIVISOR			8
#define PWM_TIMER1_PRESECALER_Select			TCCR1B_SOURCE_8_PRE
#define Delay_TIMER_PRESECALER_DIVISOR			1024
#define Delay_TIMER_PRESECALER_Select			TCCR1B_SOURCE_1024_PRE

#define TIMER1_FREQ                 (SYSTEM_FREQ_MHZ*1000000ULL/PWM_TIMER1_PRESECALER_DIVISOR)

#define TIMER1_COMPARE_MATCH_MODE_SELECTA	TIMER1_FAST_PWM_SetTopChannelA
#define TIMER1_COMPARE_MATCH_MODE_SELECTB	TIMER1_FAST_PWM_SetTopChannelB
#define TIMER1_Prescaler					TCCR1B_SOURCE_64_PRE
#endif /* MCAL_GPT_GPT_CONFIG_H_ */
