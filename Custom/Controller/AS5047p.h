#ifndef _AS5047P_H_
#define _AS5047P_H_

#include "spi.h"

// spi command frame 格式
#define AS5047_COMMAND_READ 0x4000

// Volatil Registers 的 addrees mapping
#define NOP_AS5047P_VOL_REG_ADD 0x0000
#define ERRFL_AS5047P_VOL_REG_ADD 0x0001
#define PROG_AS5047P_VOL_REG_ADD 0x0003
#define DIAAGC_AS5047P_VOL_REG_ADD 0x3ffc
#define MAG_AS5047P_VOL_REG_ADD 0x3ffd
#define ANGLEUNC_AS5047P_VOL_REG_ADD 0x3ffe
#define ANGLECOM_AS5047P_VOL_REG_ADD 0x3fff

// non-volatile-registers 的 addrees mapping
#define ZPOSM_AS5047P_nVOL_REG_ADD 0x0016
#define ZPOSL_AS5047P_nVOL_REG_ADD 0x0017
#define SETTINGS1_AS5047P_nVOL_REG_ADD 0x0018
#define SETTINGS2_AS5047P_nVOL_REG_ADD 0x0019
#define RED_AS5047P_VOL_nREG_ADD 0x001a

struct AS5047p {
  uint16_t angle_data;     // 角度数据
  uint16_t rectify_angle;  // 校准的角度数据
  bool rectify_valid;      // 校准数据有效标志
};

struct AS5047p_AngleData_t {
  uint16_t rawAngle;        // raw data
  uint16_t rectifiedAngle;  // calibrated rawAngle data
  bool rectifyValid;
};

/**
 * @brief  AS5047 初始化
 * @param
 * @retval
 **/
void AS5047_Init(void);

/**
 * @brief 将指定位置设置为零。
 * @param
 * @retval
 **/
void AS5047_SetZeroPosition();

/**
 * @brief 获取初始位置
 * @param
 * @retval
 **/
uint16_t AS5047_Get_ZeroPosition();

/**
 * @brief 获取角度
 * @param
 * @retval
 **/

void AS5047_Get_AngleData();
#endif