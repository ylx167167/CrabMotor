#ifndef _I2CBUS_H_
#define _I2CBUS_H_
#include "i2c.h"
#include "main.h"

/*I2C  8bit地址操作*/
typedef uint8_t (*I2C_DEVICE_8WRITE)(uint8_t, uint16_t, uint16_t);
typedef uint8_t (*I2C_DEVICE_8READ)(uint8_t, uint16_t, uint16_t);
/*I2C  16bit地址操作*/
typedef uint8_t (*I2C_DEVICE_16WRITE)(uint16_t, uint16_t, uint16_t);
typedef uint8_t (*I2C_DEVICE_16READ)(uint16_t, uint16_t, uint16_t);
typedef void (*I2C_DEVICE_INIT)(void);

struct I2CBus_Op {
  I2C_DEVICE_8WRITE write8;
  I2C_DEVICE_8READ read8;
  I2C_DEVICE_16WRITE write16;
  I2C_DEVICE_16READ read16;
  I2C_DEVICE_INIT init;
};

struct I2CBus_TypeDef {
  int op_bit;  // 寄存器操作位数 8bit 16bit
  struct I2CBus_Op *op;
};

struct I2CBus_Element {
  int slaveaddr;  // I2C从机地址
  struct I2CBus_TypeDef *type;
};

struct I2CBus_Node {
  struct I2CBus_Element *element;
  struct I2CBus_Node *next;
};

struct I2CBus_WR_Buf {
  uint16_t addr;      // i2c寄存器地址
  uint16_t data;      // 写入
  uint16_t feedback;  // 读取返回
  uint16_t len;       // 长度
};
struct I2CBus_WR {
  struct I2CBus_WR_Buf *buf;
};

/**
 * @brief I2C管理器初始化
 * @param
 * @retval
 **/
void I2C_Register_Bus(void);
/**
 * @brief 注册I2C设备
 * @param slaveaddr 设备从机地址
 * @retval 判断是否注册成功 1 注册成功 -1 注册失败 0 已经注册
 **/
struct I2CBus_Element *I2CBus_Register_Device(int slaveaddr,
                                              struct I2CBus_TypeDef *type);

/**
 * @brief 卸载i2c设备
 * @param
 * @retval
 **/
void I2CBus_UnRegister_Device(int slaveaddr);

/**
 * @brief I2C写设备
 * @param ele 设备句柄
 *          buf 写入数据
 * @retval 写入成功或者失败 I2CMGR_WRITE_SUCCESS I2CMGR_WRITE_FAIL
 **/
uint8_t I2CBus_WriteData(struct I2CBus_Element *ele, struct I2CBus_WR_Buf *buf);

/**
 * @brief I2C读设备
 * @param ele 设备句柄
 * @retval 判断 读写是否成功
 **/
uint8_t I2CBus_ReadData(struct I2CBus_Element *ele, struct I2CBus_WR_Buf *buf);

/**
 * @brief 卸载i2c总线
 * @param
 * @retval
 **/
void I2C_UnRegister_Bus();

#endif