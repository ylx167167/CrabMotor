
/**
 * Created by preference on 2024/01/17
 * This program is for learning purposes only and may not be used for any other
 * purpose without the author's permission
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
#ifndef _MOTOR_H_
#define _MOTOR_H_

/**
 * @brief 刹车
 * @param void
 * @retval void
 **/
void Crab_Motor_Sleep(void);

/**
 * @brief 刹车
 * @param void
 * @retval void
 **/
void Crab_Motor_Brake(void);

/**
 * @brief 初始化引脚和定时器
 * @param void
 * @retval void
 **/
void Crab_Motor_Init(void);

#endif