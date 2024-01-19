#ifndef _AS5047P_H_
#define _AS5047P_H_

#include "as5047p_device.h"

void     AS5047_SetZeroPosition();
uint16_t AS5047_Get_ZeroPosition();
uint16_t AS5047_Get_ERRFL();
uint16_t AS5047_WriteData();
uint16_t AS5047_ReadData();

#endif