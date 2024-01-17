#ifndef _AS5047P_H_
#define _AS5047P_H_

#include "spi.h"

void AS5047_Init(void);
void AS5047_SetZeroPosition(int devidx);
uint16_t AS5047_Get_ZeroPosition(int devidx);
uint16_t AS5047_Get_ERRFL(int devidx);
uint16_t AS5047_WriteData(int devidx, uint16_t addr, uint16_t data);
uint16_t AS5047_ReadData(int devidx, uint16_t addr);

#endif