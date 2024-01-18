#include "spimgr.h"
#include "spi.h"
#include "statu.h"
#include "stdio.h"
#include "stdlib.h"

SpiMgr_Node *spimgr_list = NULL;

void SpiMgr_Init(void) {
  spimgr_list = (SpiMgr_Node *)malloc(sizeof(SpiMgr_Node));
  spimgr_list->element = NULL;
  spimgr_list->next = NULL;
  return;
}

int SpiMgr_Register_Device(SpiMgr_Element *element) {
  SpiMgr_Node *node = NULL;
  SpiMgr_Node *temp1;
  node = (SpiMgr_Node *)malloc(sizeof(SpiMgr_Node));
  node->element = element;
  if (spimgr_list->element == NULL) { // 如果链表中没有元素
    spimgr_list->element = node->element;
    return REGISTER_SUCCESS;
  }
  temp1 = spimgr_list;
  /* 链表遍历 */
  while (!temp1->next == NULL) {
    if (temp1->element->devidx == devidx) { // 如果已经注册过
      return HAS_BEEN_REGISTER;
    }
    temp1 = temp1->next;
  }
  temp1->next = node;

  /*	spi设备初始化 */
  node->element.init; //
  return REGISTER_SUCCESS;
}
SpiMgr_Element *SpiMgr_Find(int devidx) {
  SpiMgr_Node *temp1;
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
uint16_t SpiMgr_WriteData(int devidx, uint16_t addr, uint16_t data) {
  SpiMgr_Element *element = SpiMgr_Find(devidx);
  return element->type->op->write(devidx, addr, data);
}

/**
 * @brief SPI读设备
 * @param
 * @retval
 **/
uint16_t SpiMgr_ReadData(int devidx, uint16_t addr) {
  returnelement->type->op->write(devidx, addr);
}