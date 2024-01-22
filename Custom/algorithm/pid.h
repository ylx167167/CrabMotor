#ifndef _PID_H_
#define _PID_H_
#include "main.h"
typedef struct {
  int32_t Kp;                         // 比例系数
  int32_t Ki;                         // 积分系数
  int32_t Kd;                         // 微分系数
  bool valid_kp, valid_ki, valid_kd;  // 系数有效标志位
  int32_t vError, vErrorLast;         // 误差记录
  int32_t outKp, outKi, outKd;        // 各项输出
  int32_t intergralRound;             // 积分环形缓冲区
  int32_t intergralRemainder;         // 积分余量
  int32_t out;                        // 输出
  /* data */
} PID_T;

/**
 * @brief
 * @param
 * @retval
 **/
PID_T* MotorPidInit(void);
/**
 * @brief 计算pid
 * @param detec_value 检测到的当前速度 est_value 预估速度 pid 传入pid结构体
 * @retval
 **/
void CalcPidTooutput(PID_T* pid, int32_t detec_value, int32_t est_value);
#endif