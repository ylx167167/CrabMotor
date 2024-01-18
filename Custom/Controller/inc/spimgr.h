#ifndef _SPIMGR_H_
#define _SPIMGR_H_
/**
 * @brief spi设备 读写函数指针
 * @param
 * @retval
 **/
typedef uint16_t (*SPI_DEVICE_WRITE)(uint16_t, uint16_t);
typedef uint16_t (*SPI_DEVICE_READ)(uint16_t);
typedef void (*SPI_DEVICE_INIT)();
typedef struct SpiMgr_Op {
  SPI_DEVICE_WRITE write;
  SPI_DEVICE_READ read;
  SPI_DEVICE_INIT init;
} SpiMgr_Op;

typedef struct SpiMgr_TypeDef {
  SPI_HandleTypeDef *hspin;
  GPIO_TypeDef *CSNport;
  uint16_t CSNpin;
  SpiMgr_Op *op;
} SpiMgr_TypeDef;

typedef struct SpiMgr_Element {
  int devidx;
  SpiMgr_TypeDef *type;
} SpiMgr_Element;

typedef struct SpiMgr_Node {
  SpiMgr_Element *element;
  SpiMgr_Node *next;
} SpiMgr_Node;

/**
 * @brief SPI管理器初始化
 * @param
 * @retval
 **/
void SpiMgr_Init(void);
/**
 * @brief 注册spi设备
 * @param 设备信息
 * @retval 判断是否注册成功 1 注册成功 -1 注册失败 0 已经注册
 **/
int SpiMgr_Register_Device(int devidx, SpiMgr_TypeDef *type);

/**
 * @brief SPI写设备
 * @param
 * @retval
 **/
uint16_t SpiMgr_WriteData(int devidx, uint16_t addr, uint16_t data);

/**
 * @brief SPI读设备
 * @param
 * @retval
 **/
uint16_t SpiMgr_ReadData(int devidx, uint16_t addr);

#endif