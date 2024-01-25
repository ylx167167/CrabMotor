#include "TB67H450.h"

#include "tim.h"

// 将sin对应到DAC
struct FastSinToDac_t phaseB {};
struct FastSinToDac_t phaseA {};

void TB67h459Init() {
  /*    GPIO初始化      */

  /*	定时器初始化    */
  MX_TIM3_Init(void);
}
void SetOutPutA(bool _statusAp, bool _statusAm) {
  _statusAp ? (HW_AP_GPIO_GROUP->BSRR = HW_AP_PIN)
            : (HW_AP_GPIO_GROUP->BRR = HW_AP_PIN);
  _statusAm ? (HW_AM_GPIO_GROUP->BSRR = HW_AM_PIN)
            : (HW_AM_GPIO_GROUP->BRR = HW_AM_PIN);
}
void SetOutPutB(bool _statusBp, bool _statusBm) {
  _statusBp ? (HW_BP_GPIO_GROUP->BSRR = HW_BP_PIN)
            : (HW_BP_GPIO_GROUP->BRR = HW_BP_PIN);
  _statusBm ? (HW_BM_GPIO_GROUP->BSRR = HW_BM_PIN)
            : (HW_BM_GPIO_GROUP->BRR = HW_BM_PIN);
}

void SetDacOutputVoltage(uint16_t _voltageA_3300mVIn12bits,
                         uint16_t _voltageB_3300mVIn12bits) {
  __HAL_TIM_SET_COMPARE(&htim3, HW_APWM_CHANNEL, _voltageA_3300mVIn12bits >> 2);
  __HAL_TIM_SET_COMPARE(&htim3, HW_BPWM_CHANNEL, _voltageB_3300mVIn12bits >> 2);
}
void ClearPhaseABdacValue() {
  phaseA.dacValue12Bits = 0;
  phaseB.dacValue12Bits = 0;
}

void SetFocCurrentVector(uint32_t _directionInCount, int32_t _current_mA) {
  /*	基于当前计数点去获取相位值  */
  phaseB.sinMapPtr =
      (_directionInCount) & (0x000003FF);  // 只有4096个点 所以在4096个点中循环

  phaseA.sinMapPtr = (_directionInCount + (256)) & (0x000003FF);  // 滞后90°
  phaseB.sinMapData = SIN_PI_M2[phaseB.sinMapPtr];
  phaseA.sinMapData = SIN_PI_M2[phaseA.sinMapPtr];

  /*	通过电流设置电流大小和相位值求出dac准确值   */
  uint32_t dac_amp = abs(_current_mA);
  dac_amp = (uint32_t)(dac_amp * 5083) >> 12;  //(dac_reg * 4095 / 3300)的变种
  dac_amp = dac_amp & (0x00000FFF);            //(对4096取余)不能超过3300
  phaseA.dacValue12Bits =
      (uint32_t)(dac_amp * abs(phaseA.sinMapData)) >> SIN_PI_M2_DPIXBIT;
  phaseB.dacValue12Bits =
      (uint32_t)(dac_amp * abs(phaseB.sinMapData)) >> SIN_PI_M2_DPIXBIT;
  /*	对引脚进行输出  */
  SetDacOutputVoltage(phaseA.dacValue12Bits, phaseB.dacValue12Bits);
}