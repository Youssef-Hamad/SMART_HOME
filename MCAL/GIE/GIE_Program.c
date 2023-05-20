/*
 * GIE_Program.c
 *
 *  Created on: 3 Apr 2023
 *      Author: Youssef
 */

#include "../../INC/STD_TYPES.h"
#include "../../INC/MATH_BIT.h"

#include "GIE_Private.h"
#include "GIE_Interface.h"

void GIE_VoidEnable(void){
	SetBit(SREG,GlobalIntrruptEnableBit);
}
void GIE_VoidDisable(void){
	ClearBit(SREG,GlobalIntrruptEnableBit);

}
