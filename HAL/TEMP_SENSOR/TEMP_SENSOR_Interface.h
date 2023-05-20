/*
 * TEMP_SENSOR_Interface.h
 *
 *  Created on: May 20, 2023
 *      Author: DWEEBSTARK
 */

#ifndef HAL_TEMP_SENSOR_TEMP_SENSOR_INTERFACE_H_
#define HAL_TEMP_SENSOR_TEMP_SENSOR_INTERFACE_H_

#include "TEMP_SENSOR_Config.h"

void TempSensorVoidInit(u8 Copyu8PortId,u8 Copyu8PinId,Cbf UserFunc);
u32 TempReading(void);
#endif /* HAL_TEMP_SENSOR_TEMP_SENSOR_INTERFACE_H_ */
