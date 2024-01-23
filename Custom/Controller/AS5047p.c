//
#include "AS5047p.h"

#include "Base/kernel.h"
#include "Bus/spibus.h"

#define assert_idx(__devidx) 0

#define SPI_Handle &hspi1
#define assert_idx(__devidx) 0

#define CS_SET \
  HAL_GPIO_WritePin(AS5047_SPI_CS_GPIO_GROUP, AS5047_SPI_CS_PIN, GPIO_PIN_SET)
#define CS_RESET \
  HAL_GPIO_WritePin(AS5047_SPI_CS_GPIO_GROUP, AS5047_SPI_CS_PIN, GPIO_PIN_RESET)

struct SpiBus_Element *as5047_element = NULL;
void error_inf_loop() {
  while (1)
    ;
}

uint16_t Parity_bit_Calculate(uint16_t data_2_cal) {
  uint16_t parity_bit_value = 0;

  while (data_2_cal != 0) {  // 自低位开始统计奇偶
    //(((⑤^④)^③)^②)^①——表达式1假设⑤和④不同，则⑤^④运算结果为1，表示有一个1。表达式1可以化成：((1^③)^②)^①——表达式2
    parity_bit_value ^= data_2_cal;
    data_2_cal >>= 1;
  }

  return (parity_bit_value & 0x1);
}

uint16_t SPI_ReadWrite_OneByte(uint16_t _txdata) {
  uint16_t rxdata;
  rxdata = 0;
  // waring不用管,传进去的是地址数据不会被截断，HAL库根据配置，按16字节的数据格式将16字节的发送出去
  if (HAL_SPI_TransmitReceive(AS5047_SPI_CS_PIN, (uint8_t *)&_txdata,
                              (uint8_t *)&rxdata, 1, 100) != HAL_OK)
    ;
  return rxdata;
}

void AS5047_WriteData(uint16_t addr, uint16_t data, uint16_t feedback) {
  // 发送地址指令
  //  & 0x3fff 得到 13:0位 data数据 进行奇偶校验位计算
  if (Parity_bit_Calculate(addr & 0x3fff) == 1) {
    addr |= 0x8000;  // 将15bit 置1  偶校验
  }
  CS_RESET;
  SPI_ReadWrite_OneByte(addr);
  CS_SET;
  // 发送数据指令
  if (Parity_bit_Calculate(data & 0x3fff) == 1) {
    data |= 0x8000;
  }

  CS_RESET;
  feedback = SPI_ReadWrite_OneByte(data);
  CS_SET;
}

void AS5047_ReadData(uint16_t addr, uint16_t feedback) {
  if (Parity_bit_Calculate(addr) == 0) {
    addr |= 0x8000;  // 1000 0000 0000 0000
  }
  addr |= AS5047_COMMAND_READ;  // 0100 0000 0000 0000
  SPI_ReadWrite_OneByte(addr);
  feedback = SPI_ReadWrite_OneByte(
      NOP_AS5047P_VOL_REG_ADD);  // ANGLECOM_AS5047P_VOL_REG_ADD=11 1111 1111
  feedback &= 0x3fff;

  // 此处可以做奇偶校验判断是否接收到正确数据，但是也可以不做，直接去掉15，14bit
  feedback &= 0x3fff;
}

void AS5047_PowerUp(void) {
  // 设置ABI模式，输出分辨1024.
  AS5047_WriteData(SETTINGS1_AS5047P_nVOL_REG_ADD, 5);  // 0000 0101
  AS5047_WriteData(SETTINGS2_AS5047P_nVOL_REG_ADD, 0);
}

void AS5047_Init(void) {
  struct SpiBus_TypeDef *type =
      (struct SpiBus_TypeDef *)malloc(sizeof(struct SpiBus_TypeDef));
  type = (struct SpiBus_TypeDef *)malloc(sizeof(struct SpiBus_TypeDef));
  /*初始化操作函数	*/
  type->op = (struct SpiBus_Op *)malloc(sizeof(struct SpiBus_Op));
  type->op->read = AS5047_ReadData;
  type->op->write = AS5047_WriteData;
  type->op->init = AS5047_PowerUp;
  /* 初始化设备资源 */
  type->CSNport = AS5047_SPI_CS_GPIO_GROUP;
  type->hspin = SPI_Handle;
  type.CSNpin = AS5047_SPI_CS_PIN;
  /*	在spi总线上注册设备 并返回句柄*/
  as5047_element = SpiBus_Register_Device(SPI_DEVIDX_AS5047, type);
  return;
}

void AS5047_Diagnostics(void) { ; }

void AS5047_SetZeroPosition() {
  struct SpiBus_WR_Buf rwbuf[2];
  rwbuf[0].addr = DIAAGC_AS5047P_VOL_REG_ADD;
  rwbuf[0].feedback = 0;
  rwbuf[1].addr = ANGLEUNC_AS5047P_VOL_REG_ADD;
  rwbuf[1].feedback = 0;
  struct SpiBus_WR rw = {
      .times = 2,
      .buf = rwbuf,
  };
  uint16_t ANGLEUNC = SpiBus_ReadData(as5047_element, &rw);  // 获取当前角度

  rwbuf[0].addr = ZPOSM_AS5047P_nVOL_REG_ADD;
  rwbuf[0].data = (ANGLEUNC >> 6) & 0x00ff;
  rwbuf[0].feedback = 0;
  rwbuf[1].addr = ANGLEUNC_AS5047P_VOL_REG_ADD;
  rwbuf[1].data = ANGLEUNC & 0x003f;
  rwbuf[1].feedback = 0;
  struct SpiBus_WR rw1 = {
      .times = 2,
      .buf = rwbuf,
  };
  SpiBus_WriteData(as5047_element, &rw1);  //& 11 1111
}

uint16_t AS5047D_Get_MAGCORDIC_Value() {
  struct SpiBus_WR_Buf rwbuf[0];
  rwbuf[0].addr = MAG_AS5047P_VOL_REG_ADD;
  rwbuf[0].feedback = 0;
  struct SpiBus_WR rw = {
      .times = 1,
      .buf = rwbuf,
  };
  SpiBus_ReadData(as5047_element, &rw);
  return rwbuf.feedback;
}

unsigned int AS5047P_Get_AGC_Value() {
  struct SpiBus_WR_Buf rwbuf[0];
  rwbuf[0].addr = DIAAGC_AS5047P_VOL_REG_ADD;
  rwbuf[0].feedback = 0;
  struct SpiBus_WR rw = {
      .times = 1,
      .buf = rwbuf,
  };
  SpiBus_ReadData(as5047_element, &rw);
  return (unsigned char)((rwbuf.feedback >> 8) & 0x00FF);
}

uint16_t AS5047_Get_ZeroPosition() {
  struct SpiBus_WR_Buf rwbuf[2];
  rwbuf[0].addr = ZPOSM_AS5047P_nVOL_REG_ADD;
  rwbuf[0].feedback = 0;
  rwbuf[1].addr = ZPOSL_AS5047P_nVOL_REG_ADD;
  rwbuf[1].feedback = 0;
  struct SpiBus_WR rw = {
      .times = 2,
      .buf = rwbuf,
  };
  SpiBus_ReadData(as5047_element, &rw);
  return (rwbuf[0].feedback << 6) &
         (rwbuf[1].feedback & 0x003f);  // 将高八位和低6位拼起来
}

uint16_t AS5047_Get_ERRFL() {
  return SpiBus_ReadData(as5047_element, ERRFL_AS5047P_VOL_REG_ADD);
}