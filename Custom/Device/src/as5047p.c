#include "as5047p.h"
#include "hw_base.h"
#include "spimgr.h"
#include "stdlib.h"

#define SPI_Handle &hspi1
#define assert_idx(__devidx) 0

void AS5047_SetZeroPosition() {
  uint16_t DIAAGC =
      SpiMgr_ReadData(SPI_DEVIDX_AS5047, DIAAGC_AS5047P_VOL_REG_ADD);
  uint16_t ANGLEUNC = SpiMgr_ReadData(
      SPI_DEVIDX_AS5047, ANGLEUNC_AS5047P_VOL_REG_ADD); // 获取当前角度

  // ANGLEUNC是13:0  14个有效数字，右移6获取高8位。	得到低6位
  AS5047_WriteData(SPI_DEVIDX_AS5047, ZPOSM_AS5047P_nVOL_REG_ADD,
                   (ANGLEUNC >> 6) & 0x00ff);

  AS5047_WriteData(SPI_DEVIDX_AS5047, ZPOSL_AS5047P_nVOL_REG_ADD,
                   ANGLEUNC & 0x003f); //& 11 1111
}

void AS5047_Diagnostics(void) { ; }

uint16_t AS5047D_Get_MAGCORDIC_Value() {
  unsigned int CORDICMAG = SpiMgr_ReadData(MAG_AS5047P_VOL_REG_ADD);
  return CORDICMAG;
}

unsigned int AS5047P_Get_AGC_Value(int devidx) {
  unsigned int DIAAGC =
      SpiMgr_ReadData(SPI_DEVIDX_AS5047, DIAAGC_AS5047P_VOL_REG_ADD);
  return (unsigned char)((DIAAGC >> 8) & 0x00FF);
}

uint16_t AS5047_Get_ZeroPosition(int devidx) {
  uint16_t ZPOSM =
      SpiMgr_ReadData(SPI_DEVIDX_AS5047, ZPOSM_AS5047P_nVOL_REG_ADD);
  uint16_t ZPOSL =
      SpiMgr_ReadData(SPI_DEVIDX_AS5047, ZPOSL_AS5047P_nVOL_REG_ADD);
  return (ZPOSM << 6) & (ZPOSL & 0x003f); // 将高八位和低6位拼起来
}

uint16_t AS5047_Get_ERRFL(int devidx) {
  return SpiMgr_ReadData(SPI_DEVIDX_AS5047, ERRFL_AS5047P_VOL_REG_ADD);
}