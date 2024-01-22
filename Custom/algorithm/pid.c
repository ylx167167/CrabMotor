#include "pid.h"

#include "stdio.h"
#include "stdlib.h"

PID_T *MotorPidInit(void) {
  PID_T *pid = (PID_T *)malloc(sizeof(PID_T));
  pid->Kp = 5;
  pid->Ki = 30;
  pid->Kd = 0;
  pid->outKp = 0;
  pid->outKi = 0;
  pid->outKd = 0;
  pid->valid_kp = true;
  pid->valid_ki = true;
  pid->valid_kd = false;
  pid->vError = 0;
  pid->vErrorLast = 0;
  pid->intergralRound = 0;
  pid->intergralRemainder = 0;
  return pid;
}

void CalcPidTooutput(PID_T *pid, int32_t detec_value, int32_t est_value) {
  /*	就算误差    */
  pid->vErrorLast = pid->vError;
  pid->vError = detec_value - est_value;
  if (pid->vError > (1024 * 1024)) pid->vError = (1024 * 1024);
  if (pid->vError < (-1024 * 1024)) pid->vError = (-1024 * 1024);
  /*	比例输出    */
  pid->outKp = ((pid->Kp) * (pid->vError));
  /*	积分输出    */
  pid->intergralRound += ((pid->Ki) * (pid->vError));
  pid->intergralRemainder = (pid->intergralRound >> 10);
  pid->intergralRound -= (pid->intergralRound << 10);
  pid->outKi += pid->intergralRemainder;
  /*	微分输出    */
  pid->outKd = ((pid->Kd) * (pid->vError - pid->vErrorLast));
}
