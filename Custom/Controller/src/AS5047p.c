#include "AS5047p.h"

#include "hw_base.h"
#include "spibus.h"

#define assert_idx(__devidx) 0

void AS5047_Diagnostics(void) { ; }

void AS5047_SetZeroPosition() {
  SpiBus_WR_Buf rwbuf[2];
  rwbuf[0].addr = DIAAGC_AS5047P_VOL_REG_ADD;
  rwbuf[0].feedback = 0;
  rwbuf[1].addr = ANGLEUNC_AS5047P_VOL_REG_ADD;
  rwbuf[1].feedback = 0;
  SpiBus_WR rw = {
      .times = 2,
      .buf = rwbuf,
  };
  uint16_t ANGLEUNC = SpiBus_ReadData(SPI_DEVIDX_AS5047, &rw);  // 获取当前角度

  rwbuf[0].addr = ZPOSM_AS5047P_nVOL_REG_ADD;
  rwbuf[0].data = (ANGLEUNC >> 6) & 0x00ff;
  rwbuf[0].feedback = 0;
  rwbuf[1].addr = ANGLEUNC_AS5047P_VOL_REG_ADD;
  rwbuf[1].data = ANGLEUNC & 0x003f;
  rwbuf[1].feedback = 0;
  SpiBus_WR rw1 = {
      .times = 2,
      .buf = rwbuf,
  };
  SpiBus_WriteData(SPI_DEVIDX_AS5047, &rw1);  //& 11 1111
}

uint16_t AS5047D_Get_MAGCORDIC_Value() {
  SpiBus_WR_Buf rwbuf[0];
  rwbuf[0].addr = MAG_AS5047P_VOL_REG_ADD;
  rwbuf[0].feedback = 0;
  SpiBus_WR rw = {
      .times = 1,
      .buf = rwbuf,
  };
  SpiBus_ReadData(MAG_AS5047P_VOL_REG_ADD, &rw);
  return rwbuf.feedback;
}

unsigned int AS5047P_Get_AGC_Value() {
  SpiBus_WR_Buf rwbuf[0];
  rwbuf[0].addr = DIAAGC_AS5047P_VOL_REG_ADD;
  rwbuf[0].feedback = 0;
  SpiBus_WR rw = {
      .times = 1,
      .buf = rwbuf,
  };
  SpiBus_ReadData(SPI_DEVIDX_AS5047, &rw);
  return (unsigned char)((rwbuf.feedback >> 8) & 0x00FF);
}

uint16_t AS5047_Get_ZeroPosition() {
  SpiBus_WR_Buf rwbuf[2];
  rwbuf[0].addr = ZPOSM_AS5047P_nVOL_REG_ADD;
  rwbuf[0].feedback = 0;
  rwbuf[1].addr = ZPOSL_AS5047P_nVOL_REG_ADD;
  rwbuf[1].feedback = 0;
  SpiBus_WR rw = {
      .times = 2,
      .buf = rwbuf,
  };
  SpiBus_ReadData(SPI_DEVIDX_AS5047, &rw);
  return (rwbuf[0].feedback << 6) &
         (rwbuf[1].feedback & 0x003f);  // 将高八位和低6位拼起来
}

uint16_t AS5047_Get_ERRFL() {
  return SpiBus_ReadData(SPI_DEVIDX_AS5047, ERRFL_AS5047P_VOL_REG_ADD);
}