
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
#include "pid.h"
/********************  硬件配置区  ********************/
#define Motor_Rated_Current (3000)  // 额定电流(mA)
#define Motor_Cali_Current (2000)   // 校准电流(mA)

/********************  软件配置区  ********************/
#define SOFT_DIVIDE_NUM 256;
typedef struct {
  PID_T *pid;
  /*	估计    */
  int32_t est_speed;     // 估计速度
  int32_t est_location;  // 估计位置
  /*    输出	*/
  int32_t foc_location;  // FOC矢量位置
  int32_t foc_current;   // FOC矢量大小
} CrabMotor_Conf;

/**
 * @brief 初始化引脚和定时器
 * @param void
 * @retval void
 **/
void CrabMotor_Init(void);

/**
 * @brief 睡眠
 * @param void
 * @retval void
 **/
void CrabMotor_Sleep(void);

/**
 * @brief 刹车
 * @param void
 * @retval void
 **/
void CrabMotor_Brake(void);

/**
 * @brief 电机电流控制函数
 * @param
 * @retval
 **/
void CrabMotor_ControlElectric();
#endif