#ifndef _SPIMGR_H_
#define _SPIMGR_H_
#include "main.h"
#include "spi.h"
#include "spibus.h"
/**
 * @brief spi设备 读写函数指针
 * @param
 * @retval
 **/

/*	*/
typedef void (*SPI_DEVICE_WRITE)(uint16_t, uint16_t, uint16_t);
typedef uint16_t (*SPI_DEVICE_READ)(uint16_t, uint16_t);
typedef void (*SPI_DEVICE_INIT)(void);

typedef struct SpiBus_Op {
  SPI_DEVICE_WRITE write;
  SPI_DEVICE_READ read;
  SPI_DEVICE_INIT init;
} SpiBus_Op;

typedef struct SpiBus_TypeDef {
  SPI_HandleTypeDef *hspin;
  GPIO_TypeDef *CSNport;
  uint16_t CSNpin;
  SpiBus_Op *op;
} SpiBus_TypeDef;

typedef struct SpiBus_Element {
  int devidx;
  SpiBus_TypeDef *type;
} SpiBus_Element;

typedef struct SpiBus_Node {
  SpiBus_Element *element;
  SpiBus_Node *next;
} SpiBus_Node;

typedef struct SpiBus_WR_Buf {
  uint16_t addr;
  uint16_t data;
  uint16_t feedback;
} SpiBus_WR_Buf;
typedef struct SpiBus_WR {
  uint16_t times;
  SpiBus_WR_Buf *buf;
} SpiBus_WR;

/**
 * @brief SPI管理器初始化
 * @param
 * @retval
 **/
void SpiBus_Init(void);
/**
 * @brief 注册spi设备
 * @param 设备信息
 * @retval 判断是否注册成功 1 注册成功 -1 注册失败 0 已经注册
 **/
int SpiBus_Register_Device(int devidx, SpiBus_TypeDef *type);

/**
 * @brief SPI写设备
 * @param devidex 设备编号
 *        addr 写入地址
 *        写入数据
 * @retval 写入成功或者失败 SPIMGR_WRITE_SUCCESS SPIMGR_WRITE_FAIL
 **/
int16_t SpiBus_WriteData(int devidx, SpiBus_WR *buf);

/**
 * @brief SPI读设备
 * @param
 * @retval
 **/
uint16_t SpiBus_ReadData(int devidx, SpiBus_WR *buf);

#endif