#include "lm75bd.h"

#include "Bus/i2cbus.h"
#include "kernel.h"
#define LM75B_I2C hi2c1
#define LM75B_ADDR (0x48u << 1)  // A0 A1 A2拉低 地址0b01001000=0x48
#define LM75B_TX_DELAY 100
#define LM75B_RX_DELAY 100

#define LM75B_TEMP_REG 0x00u
#define LM75B_CONF_REG 0x01u
#define LM75B_THYST_REG 0x02u
#define LM75B_TOS_REG 0x03u

uint8_t I2C_TX_DATA[2];
uint8_t I2C_RX_DATA[2];

struct I2CBus_Element *lm75bd_element = NULL;

uint8_t LM75B_Write(uint8_t mem_addr, uint16_t data, uint16_t len) {
  if (HAL_I2C_Mem_Write(&LM75B_I2C, LM75B_ADDR, mem_addr, I2C_MEMADD_SIZE_8BIT,
                        data, len, LM75B_TX_DELAY) == HAL_OK) {
    return TRUE;
  }
  return FALSE;
}

uint8_t LM75B_Read(uint8_t mem_addr, uint16_t data, uint16_t len) {
  if (HAL_I2C_Mem_Read(&LM75B_I2C, LM75B_ADDR, mem_addr, I2C_MEMADD_SIZE_8BIT,
                       data, len, LM75B_RX_DELAY) == HAL_OK) {
    return TRUE;
  }

  return FALSE;
}

uint8_t LM75B_Reset_Conf(void) { return LM75B_Init(0x00); }

void LM75B_PowerUP() {
  I2C_TX_DATA[0] = conf & 0x1F;
  if (LM75B_Write(LM75B_CONF_REG, I2C_TX_DATA, 1)) {
    return TRUE;
  }
  return FALSE;
}

uint8_t LM75B_Init(uint8_t conf) {
  struct I2CBus_TypeDef *type =
      (struct I2CBus_TypeDef *)malloc(sizeof(struct I2CBus_TypeDef));
  type = (struct I2CBus_TypeDef *)malloc(sizeof(struct I2CBus_TypeDef));
  /*初始化操作函数	*/
  type->op = (struct I2CBus_Op *)malloc(sizeof(struct I2CBus_Op));
  type->op->read = LM75B_Read;
  type->op->write = LM75B_Write;
  type->op->init = LM75B_PowerUP;
  type->op_bit = 8;
  /* 初始化设备资源 */
  /*	在I2C总线上注册设备 并返回句柄*/
  lm75bd_element = I2CBus_Register_Device(LM75B_ADDR, type);
  return;
}

uint8_t LM75B_Read_Conf(uint8_t *res_conf) {
  struct I2CBus_WR_Buf rwbuf[1];
  rwbuf[0].addr = LM75B_CONF_REG;
  rwbuf[0].len = 1;
  if (I2CBus_ReadData(lm75bd_element, rwbuf)) {
    *res_conf = &(rwbuf->data);
    return TRUE;
  }
  return FALSE;
}

uint8_t LM75B_Write_THYST(uint16_t thyst) {
  //   I2C_TX_DATA[0] = thyst >> 1;
  //   I2C_TX_DATA[1] = (thyst & 0x01) << 7;

  struct I2CBus_WR_Buf rwbuf[1];
  rwbuf[0].addr = LM75B_THYST_REG;
  rwbuf[0].len = 2;
  rwbuf[0].data = ;
  if (LM75B_Write(LM75B_THYST_REG, rwbuf)) {
    return TRUE;
  }
  return FALSE;
}

uint8_t LM75B_Read_THYST(uint16_t *res_thyst) {
  struct I2CBus_WR_Buf rwbuf[1];
  rwbuf[0].addr = LM75B_THYST_REG;
  rwbuf[0].len = 2;
  if (LM75B_Read(LM75B_THYST_REG, rwbuf)) {
    // *res_thyst = (uint16_t)I2C_RX_DATA[0] << 1;
    // *res_thyst += I2C_RX_DATA[1] >> 7;
    *res_thyst = rwbuf->data << 1;
    *res_thyst += (uint8_t)rwbuf->data[1] >> 7;

    return TRUE;
  }
  return FALSE;
}

uint8_t LM75B_Write_TOS(uint16_t tos) {
  //   I2C_TX_DATA[0] = tos >> 1;
  //   I2C_TX_DATA[1] = (tos & 0x01) << 7;
  struct I2CBus_WR_Buf rwbuf[1];
  rwbuf[0].addr = LM75B_TOS_REG;
  rwbuf[0].len = 2;
  rwbuf[0].data = ;

  if (LM75B_Write(LM75B_TOS_REG, rwbuf)) {
    return TRUE;
  }
  return FALSE;
}

uint8_t LM75B_Read_TOS(uint16_t *res_tos) {
  struct I2CBus_WR_Buf rwbuf[1];
  rwbuf[0].addr = LM75B_TOS_REG;
  rwbuf[0].len = 2;
  if (LM75B_Read(LM75B_TOS_REG, rwbuf)) {
    // *res_tos = (uint16_t)I2C_RX_DATA[0] << 1;
    // *res_tos += I2C_RX_DATA[1] >> 7;
    *res_thyst = rwbuf->data << 1;
    *res_thyst += (uint8_t)rwbuf->data[1] >> 7;
    return TRUE;
  }
  return FALSE;
}

uint8_t LM75B_Read_Temp(uint16_t *res_temp) {
  struct I2CBus_WR_Buf rwbuf[1];
  rwbuf[0].addr = LM75B_TEMP_REG;
  rwbuf[0].len = 2;
  if (LM75B_Read(LM75B_TEMP_REG, rwbuf)) {
    // *res_temp = (uint16_t)I2C_RX_DATA[0] << 3;
    // *res_temp += I2C_RX_DATA[1] >> 5;
    *res_thyst = rwbuf->data << 1;
    *res_thyst += (uint8_t)rwbuf->data[1] >> 5;

    return TRUE;
  }
  return FALSE;
}