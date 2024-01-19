#include "spibus.h"

#include "spi.h"
#include "statu.h"
#include "stdio.h"
#include "stdlib.h"

SpiBus_Node *spimgr_list = NULL;

void SpiBus_Init(void) {
  spimgr_list = (SpiBus_Node *)malloc(sizeof(SpiBus_Node));
  spimgr_list->element = NULL;
  spimgr_list->next = NULL;
  return;
}

int SpiBus_Register_Device(SpiBus_Element *element) {
  SpiBus_Node *node = NULL;
  SpiBus_Node *temp1;
  node = (SpiBus_Node *)malloc(sizeof(SpiBus_Node));
  node->element = element;
  if (spimgr_list->element == NULL) {  // 如果链表中没有元素
    spimgr_list->element = node->element;
    return REGISTER_SUCCESS;
  }
  temp1 = spimgr_list;
  /* 链表遍历 通过devidx查看是否存在该设备 */
  while (!temp1->next == NULL) {
    if (temp1->element->devidx == element->devidx) {  // 如果已经注册过
      return HAS_BEEN_REGISTER;
    }
    temp1 = temp1->next;
  }
  temp1->next = node;

  /*	调用该设备的初始化函数  */
  node->element->type->op->init;
  return REGISTER_SUCCESS;
}
SpiBus_Element *SpiBus_Find(int devidx) {
  SpiBus_Node *temp1;
  temp1 = spimgr_list;
  while (!temp1->next) {
    if (temp1->element->devidx == devidx) {
      return temp1->element;
    }
  }
  return NULL;
}

/**
 * @brief SPI写设备
 * @param
 * @retval
 **/
uint16_t SpiBus_WriteData(int devidx, SpiBus_WR *wr) {
  SpiBus_Element *element = SpiBus_Find(devidx);
  if (element == NULL) {
    return SPIMGR_WRITE_NO_FIND;
  }
  for (uint16_t i = 0; i < wr->times; wr->times++) {
    element->type->op->write(wr->buf->addr, wr->buf->data, wr->buf->feedback);
  }
  return SPIMGR_WRITE_SUCCESS;
}

/**
 * @brief SPI读设备
 * @param
 * @retval
 **/
uint16_t SpiBus_ReadData(int devidx, SpiBus_WR *wr) {
  SpiBus_Element *element = SpiBus_Find(devidx);
  if (element == NULL) {
    return SPIMGR_READ_NO_FIND;
  }
  element->type->op->read(wr->buf->addr, wr->buf->feedback);
  return SPIMGR_READ_SUCCESS;
}