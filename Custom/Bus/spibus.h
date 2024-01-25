#ifndef _SPIMGR_H_
#define _SPIMGR_H_
#include "main.h"
#include "spi.h"

/**
 * @brief spi设备 读写函数指针
 * @param
 * @retval
 **/

/*	*/
typedef void (*SPI_DEVICE_WRITE)(uint16_t, uint16_t, uint16_t);
typedef uint16_t (*SPI_DEVICE_READ)(uint16_t, uint16_t);
typedef void (*SPI_DEVICE_INIT)(void);

struct SpiBus_Op {
  SPI_DEVICE_WRITE write;
  SPI_DEVICE_READ read;
  SPI_DEVICE_INIT init;
};

struct SpiBus_TypeDef {
  SPI_HandleTypeDef *hspin;
  struct GPIO_TypeDef *CSNport;
  uint16_t CSNpin;
  struct SpiBus_Op *op;
};

struct SpiBus_Element {
  int devidx;
  struct SpiBus_TypeDef *type;
};

struct SpiBus_Node {
  struct SpiBus_Element *element;
  struct SpiBus_Node *next;
};

struct SpiBus_WR_Buf {
  uint16_t addr;
  uint16_t data;
  uint16_t feedback;
};

struct SpiBus_WR {
  uint16_t times;
  struct SpiBus_WR_Buf *buf;
};

/**
 * @brief SPI管理器初始化
 * @param
 * @retval
 **/
void Spi_Register_Bus(void);
/**
 * @brief 注册spi设备
 * @param 设备信息
 * @retval 判断是否注册成功 1 注册成功 -1 注册失败 0 已经注册
 **/
struct SpiBus_Element *SpiBus_Register_Device(int devidx,
                                              struct SpiBus_TypeDef *type);

/**
 * @brief SPI写设备
 * @param devidex 设备编号
 *        addr 写入地址
 *        写入数据
 * @retval 写入成功或者失败 SPIMGR_WRITE_SUCCESS SPIMGR_WRITE_FAIL
 **/
int16_t SpiBus_WriteData(struct SpiBus_Element *ele, struct SpiBus_WR *buf);

/**
 * @brief SPI读设备
 * @param
 * @retval
 **/
uint16_t SpiBus_ReadData(struct SpiBus_Element *ele, struct SpiBus_WR *buf);

/**
 * @brief 卸载SPI总线
 * @param
 * @retval
 **/
void Spi_UnRegister_Bus();

/**
 * @brief 卸载SPI设备
 * @param
 * @retval
 **/
int32_t SpiBus_UnRegister_Device(int devidx);
#endif
