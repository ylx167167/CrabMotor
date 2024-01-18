#include "motor.h"
#include "hw_base.h"

// GPIO输出
#define Out_AP_H() (HW_AP_GPIO_GROUP->BSRR = HW_AP_PIN)
#define Out_AP_L() (HW_AP_GPIO_GROUP->BRR = HW_AP_PIN)
#define Out_AM_H() (HW_AM_GPIO_GROUP->BSRR = HW_AM_PIN)
#define Out_AM_L() (HW_AM_GPIO_GROUP->BRR = HW_AM_PIN)
#define Out_BP_H() (HW_BP_GPIO_GROUP->BSRR = HW_BP_PIN)
#define Out_BP_L() (HW_BP_GPIO_GROUP->BRR = HW_BP_PIN)
#define Out_BM_H() (HW_AM_GPIO_GROUP->BSRR = HW_BM_PIN)
#define Out_BM_L() (HW_AM_GPIO_GROUP->BRR = HW_BM_PIN)

void Crab_Motor_Init(void) {
  // 引脚初始化
  // 定时器初始化
}

void Crab_Motor_Sleep(void) {
  Out_AP_L();
  Out_AM_L();
  Out_BP_L();
  Out_BM_L();
}

void Crab_Motor_Brake(void) {
  Out_AP_H();
  Out_AM_H();
  Out_BP_H();
  Out_BM_H();
}