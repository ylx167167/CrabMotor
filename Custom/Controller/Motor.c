#include "motor.h"

#include "TB67h450.h"

CrabMotor_Conf *config;
extern AS5047p_AngleData_t angleData{0};

void CrabMotor_Init(void) {
  // TB67h450初始化
  TB67h459Init();
  // 配置文件初始化
  config = (CrabMotor_Conf *)malloc(sizeof(CrabMotor_Conf));
  config->pid = MotorPidInit();
}

void CrabMotor_Sleep(void) {
  ClearPhaseABdacValue();
  SetDacOutputVoltage(0, 0);
  // 将四项拉低
  SetOutPutA(false, false);
  SetOutPutB(false, false);
}

void CrabMotor_Brake(void) {
  ClearPhaseABdacValue();
  SetDacOutputVoltage(0, 0);
  // 将四项拉高
  SetOutPutA(true, true);
  SetOutPutB(true, true);
}

void CrabMotor_CalcurrentOut(int32_t current) {
  if (current > 0) {
    /* code */
  } else if (current < 0) {
    config->foc_location = config->est_location + SOFT_DIVIDE_NUM;
  } else
    config->foc_location = config->est_location - SOFT_DIVIDE_NUM;
  SetFocCurrentVector(current, current);
}

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

  /*	通过电流正负判断电机位置  并通过dac输出电流  */
  CrabMotor_CalcurrentOut(config->foc_current);
  /*	开启硬件设置*/
}