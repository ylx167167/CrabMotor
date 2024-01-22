#include "motor.h"

#include "hw_base.h"
#include "stdio.h"
#include "stdlib.h"
// GPIO输出
#define Out_AP_H() (HW_AP_GPIO_GROUP->BSRR = HW_AP_PIN)
#define Out_AP_L() (HW_AP_GPIO_GROUP->BRR = HW_AP_PIN)
#define Out_AM_H() (HW_AM_GPIO_GROUP->BSRR = HW_AM_PIN)
#define Out_AM_L() (HW_AM_GPIO_GROUP->BRR = HW_AM_PIN)
#define Out_BP_H() (HW_BP_GPIO_GROUP->BSRR = HW_BP_PIN)
#define Out_BP_L() (HW_BP_GPIO_GROUP->BRR = HW_BP_PIN)
#define Out_BM_H() (HW_AM_GPIO_GROUP->BSRR = HW_BM_PIN)
#define Out_BM_L() (HW_AM_GPIO_GROUP->BRR = HW_BM_PIN)

CrabMotor_Conf *config;
void CrabMotor_Init(void) {
  // 引脚初始化
  // 定时器初始化
  // 配置文件初始化
  config = (CrabMotor_Conf *)malloc(sizeof(CrabMotor_Conf));
  config->pid = MotorPidInit();
}

void CrabMotor_Sleep(void) {
  Out_AP_L();
  Out_AM_L();
  Out_BP_L();
  Out_BM_L();
}

void CrabMotor_Brake(void) {
  Out_AP_H();
  Out_AM_H();
  Out_BP_H();
  Out_BM_H();
}
void CrabMotor_CalcurrentOut() {}
void CrabMotor_ControlElectric(int32_t dect_sepeed) {
  /*    通过检测值与预测值进行pid三项运算	*/
  CalcPidTooutput(config->pid, dect_sepeed, config->est_speed);

  /*	pi电流限制      */
  if (config->pid->outKi > (Motor_Rated_Current << 10)) {
    config->pid->outKi = Motor_Rated_Current << 10;
  } else if (config->pid->outKi > -(Motor_Rated_Current << 10)) {
    config->pid->outKi = -(Motor_Rated_Current << 10);
  } else {
  }

  /*	pid 综合输出  ->foc_current */
  config->foc_current =
      ((config->pid->outKp + config->pid->outKi + config->pid->outKd) >> 10);
  if (config->foc_current > Motor_Rated_Current) {
    config->foc_current = Motor_Rated_Current;
  } else if (config->foc_current > -Motor_Rated_Current) {
    config->foc_current = -Motor_Rated_Current;
  }

  /*	通过电流正负判断电机位置    */
  CrabMotor_CalcurrentOut();
  /*	开启硬件设置*/
}