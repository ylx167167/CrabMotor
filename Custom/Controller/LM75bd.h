/**
 * Created by preference on 2024/01/17
 * This program is for learning purposes only and may not be used for any other
 *purpose without the author's permission
 ******
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******
 * Author   : WayneYao
 * Author-QQ: 417838124
 */

#ifndef __LM75_H_
#define __LM75_H_

#include "i2c.h"
#include "main.h"

#define LM75B_CONF_OS_F_QUE_1 0b00000u
#define LM75B_CONF_OS_F_QUE_2 0b01000u
#define LM75B_CONF_OS_F_QUE_4 0b10000u
#define LM75B_CONF_OS_F_QUE_6 0b11000u

#define LM75B_CONF_OS_POL_L 0b00000u
#define LM75B_CONF_OS_POL_H 0b00100u

#define LM75B_CONF_OS_COMP_INT_CP 0b00000u
#define LM75B_CONF_OS_COMP_INT_IT 0b00010u

#define LM75B_CONF_OS_SHUTDOWN_FLASE 0b00000u
#define LM75B_CONF_OS_SHUTDOWN_TRUE 0b00001u

uint8_t LM75B_Init(uint8_t conf);

uint8_t LM75B_Reset_Conf(void);
uint8_t LM75B_Read_Conf(uint8_t *res_conf);
uint8_t LM75B_Write_THYST(uint16_t thyst);
uint8_t LM75B_Read_THYST(uint16_t *res_thyst);
uint8_t LM75B_Write_TOS(uint16_t tos);
uint8_t LM75B_Read_TOS(uint16_t *res_tos);
uint8_t LM75B_Read_Temp(uint16_t *res_temp);

#endif