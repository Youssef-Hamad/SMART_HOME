#ifndef MCAL_GPT_GPT_INTERFACE_H_
#define MCAL_GPT_GPT_INTERFACE_H_

#include "GPT_Config.h"
#define CHANNEL_A					1
#define CHANNEL_B					2

#define ICU_RISE_TRIGGER            1
#define ICU_FALL_TRIGGER            0

void TIMER0_VoidLowerOVFlag(void);
void TIMER0_VoidInit(void);
void TIMER0_SetCompareValue(u8 Copy_u8Value);
void TIMER0_VoidCallBack(void (*FunctionCopy)(void));
void TIMER0_VoidPWM(void);
void TIMER0_VoidStop(void);


void TIMER1_VoidInit(void);
void TIMER1SetChannelACompareValue(u16 Copy_u16CompareValue);
void TIMER1_VoidSetICR(u16 Copy_u16TopValue);
void TIMER1_VoidStart(void);
void TIMER1_VoidStop(void);

void SyncDelay_ms(u16 Copy_u16Delaytime);
void AsyncDelay_ms(u16 Copy_u16Delaytime,void (*FunctionCopy)(void));

void PWM_VoidSetFreq(u8 Copy_u8Freq);
void PWM_VoidSetDutyCycle(u8 Copy_u8DutyCycle);
void PWM_VoidStartPWM(u8 Copy_u8Freq,u8 Copy_u8DutyCycle,u8 Copy_u8Channel);
void PWM_VoidStopPWM(void);

void ICU_SetEdgeTrigger(u8 Copy_u8Edege);
void ICU_VoidEnableICU(u8 Copy_u8Edege);
void ICU_VoidDisableICU(void);
u16 ICU_VoidReadICR(void);
void ICU_VoidSetCallBack(void (*UserFunction)(void));
#endif /* MCAL_GIE_GIE_PRIVATE_H_ */
