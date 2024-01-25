#ifndef _TB67H450_H_
#define _TB67H450_H_
#include "Base/kernel.h"

// // GPIO输出
// #define Out_AP_H() (HW_AP_GPIO_GROUP->BSRR = HW_AP_PIN)
// #define Out_AP_L() (HW_AP_GPIO_GROUP->BRR = HW_AP_PIN)
// #define Out_AM_H() (HW_AM_GPIO_GROUP->BSRR = HW_AM_PIN)
// #define Out_AM_L() (HW_AM_GPIO_GROUP->BRR = HW_AM_PIN)
// #define Out_BP_H() (HW_BP_GPIO_GROUP->BSRR = HW_BP_PIN)
// #define Out_BP_L() (HW_BP_GPIO_GROUP->BRR = HW_BP_PIN)
// #define Out_BM_H() (HW_AM_GPIO_GROUP->BSRR = HW_BM_PIN)
// #define Out_BM_L() (HW_AM_GPIO_GROUP->BRR = HW_BM_PIN)

struct FastSinToDac_t {
  uint16_t sinMapPtr;
  int16_t sinMapData;
  uint16_t dacValue12Bits;
} FastSinToDac_t;

/**
 * @brief tb67h450模块初始化 包括 对应的gpio初始化 用dac输出的定时器
 * @param
 * @retval
 **/
void TB67h459Init();

/**
 * @brief 设置AP的两个引脚
 * @param
 * @retval
 **/
void SetOutPutA(bool _statusAp, bool _statusAm);
/**
 * @brief 设置AB的两个引脚
 * @param
 * @retval
 **/
void SetOutPutB(bool _statusBp, bool _statusBm);

/**
 * @brief 设置tb67h450的参考电压引脚输出电平
 * @param _voltageA_3300mVIn12bits stm32的dac为12位
 * @param _voltageB_3300mVIn12bits stm32的dac为12位
 * @retval
 **/
void SetDacOutputVoltage(uint16_t _voltageA_3300mVIn12bits,
                         uint16_t _voltageB_3300mVIn12bits);

/**
 * @brief 清空相位A B
 * @param
 * @retval
 **/
void ClearPhaseABdacValue(void);

/**
 * @brief 通过反馈计算后的电流进行相位输出
 * @param _directionInCount 当前处于哪个相位
 * @param _current_mA   设置的电压大小
 * @retval
 **/
void SetFocCurrentVector(uint32_t _directionInCount, int32_t _current_mA);
#endif