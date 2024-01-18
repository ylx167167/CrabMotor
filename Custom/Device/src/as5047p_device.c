#include "as5047p_device.h"
#include "hw_base.h"
#include "spimgr.h"
#include "stdlib.h"

#define SPI_Handle &hspi1
#define assert_idx(__devidx) 0

#define CS_SET                                                                 \
  HAL_GPIO_WritePin(AS5047_SPI_CS_GPIO_GROUP, AS5047_SPI_CS_PIN, GPIO_PIN_SET)
#define CS_RESET                                                               \
  HAL_GPIO_WritePin(AS5047_SPI_CS_GPIO_GROUP, AS5047_SPI_CS_PIN, GPIO_PIN_RESET)

void error_inf_loop() {
  while (1)
    ;
}

uint16_t Parity_bit_Calculate(uint16_t data_2_cal) {
  uint16_t parity_bit_value = 0;

  while (data_2_cal != 0) { // 自低位开始统计奇偶
    //(((⑤^④)^③)^②)^①——表达式1假设⑤和④不同，则⑤^④运算结果为1，表示有一个1。表达式1可以化成：((1^③)^②)^①——表达式2
    parity_bit_value ^= data_2_cal;
    data_2_cal >>= 1;
  }

  return (parity_bit_value & 0x1);
}

uint16_t SPI_ReadWrite_OneByte(int devidx, uint16_t _txdata) {

  uint16_t rxdata;
  // waring不用管,传进去的是地址数据不会被截断，HAL库根据配置，按16字节的数据格式将16字节的发送出去
  if (HAL_SPI_TransmitReceive(AS5047_SPI_CS_PIN, (uint8_t *)&_txdata,
                              (uint8_t *)&rxdata, 1, 100) != HAL_OK)
    rxdata = 0;
  CS_SET;
  return rxdata;
}

uint16_t AS5047_WriteData(uint16_t addr, uint16_t data) {
  // 发送地址指令
  //  & 0x3fff 得到 13:0位 data数据 进行奇偶校验位计算
  if (Parity_bit_Calculate(addr & 0x3fff) == 1) {
    addr |= 0x8000; // 将15bit 置1  偶校验
  }
  CS_RESET;
  SPI_ReadWrite_OneByte(devidx, addr);
  CS_SET;
  // 发送数据指令
  if (Parity_bit_Calculate(data & 0x3fff) == 1) {
    data |= 0x8000;
  }
  uint16_t feedback;
  CS_RESET;
  feedback = SPI_ReadWrite_OneByte(devidx, data);
  CS_SET;

  return feedback;
}
uint16_t AS5047_ReadData(uint16_t addr) {
  uint16_t data;
  if (Parity_bit_Calculate(addr) == 0) {
    addr |= 0x8000; // 1000 0000 0000 0000
  }
  addr |= AS5047_COMMAND_READ; // 0100 0000 0000 0000
  SPI_ReadWrite_OneByte(devidx, addr);
  data = SPI_ReadWrite_OneByte(
      devidx,
      NOP_AS5047P_VOL_REG_ADD); // ANGLECOM_AS5047P_VOL_REG_ADD=11 1111 1111
  data &= 0x3fff;

  // 此处可以做奇偶校验判断是否接收到正确数据，但是也可以不做，直接去掉15，14bit
  data &= 0x3fff;
  return data;
}

void AS5047_PowerUp(void) {
  // 设置ABI模式，输出分辨1024.
  AS5047_WriteData(i, SETTINGS1_AS5047P_nVOL_REG_ADD, 5); // 0000 0101
  AS5047_WriteData(i, SETTINGS2_AS5047P_nVOL_REG_ADD, 0);
}

void AS5047_Init(void) {
  SpiMgr_Element *element = (SpiMgr_Element *)malloc(sizeof(SpiMgr_Element));
  element->devidx = SPI_DEVIDX_AS5047;
  element->type = (SpiMgr_TypeDef *)malloc(sizeof(SpiMgr_TypeDef));
  /*初始化操作函数	*/
  element->type->op = (SpiMgr_Op *)malloc(sizeof(SpiMgr_Op));
  element->type->op->read = AS5047_ReadData;
  element->type->op->write = AS5047_WriteData;
  element->type->op->init = AS5047_PowerUp;
  /* 初始化设备资源 */
  element->type->CSNport = AS5047_SPI_CS_GPIO_GROUP;
  element->type->hspin = &hspi1;
  element->type.CSNpin = AS5047_SPI_CS_PIN;
  SpiMgr_Register_Device(element);
  return;
}
