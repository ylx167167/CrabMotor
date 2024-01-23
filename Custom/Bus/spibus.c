#include "spibus.h"

#include "Base/kernel.h"
#include "bus.h"
#include "spi.h"
struct SpiBus_Node *spimgr_list = NULL;

void Spi_Register_Bus(void) {
  spimgr_list = (struct SpiBus_Node *)malloc(sizeof(struct SpiBus_Node));
  spimgr_list->element = NULL;
  spimgr_list->next = NULL;
  struct BUS_Type *type = (struct BUS_Type *)malloc(sizeof(struct BUS_Type));
  type->name = "spi";
  type->data = (void *)spimgr_list;
  BusRegister(type);
  return;
}

struct SpiBus_Element *SpiBus_Register_Device(int devidx,
                                              struct SpiBus_TypeDef *type) {
  assertptr(spimgr_list);
  // struct SpiBus_Node *node = NULL;
  struct SpiBus_Node *temp1 = spimgr_list;
  struct SpiBus_Element *element =
      (struct SpiBus_Element *)malloc(sizeof(struct SpiBus_Element));
  element->devidx = devidx;
  element->type = type;

  /* 链表遍历 通过devidx查看是否存在该设备 */
  do {
    if (temp1->element == NULL) {
      break;
    } else if (temp1->element->devidx == element->devidx) {  // 如果已经注册过
      return temp1->element;
    }
    temp1 = temp1->next;
  } while (temp1);
  temp1 = (struct SpiBus_Node *)malloc(sizeof(struct SpiBus_Node));
  temp1->element = element;
  temp1->next = NULL;

  /*	调用该设备的初始化函数  */
  element->type->op->init;

  return element;
}
struct SpiBus_Element *SpiBus_Find(int devidx) {
  struct SpiBus_Node *temp1;
  temp1 = spimgr_list;
  do {
    if (temp1->element == NULL) {
      return NULL;
    } else if (temp1->element->devidx == devidx) {
      return temp1->element;
    }
    temp1 = temp1->next;
  } while (temp1);
  return NULL;
}

/**
 * @brief SPI写设备
 * @param
 * @retval
 **/
uint16_t SpiBus_WriteData(struct SpiBus_Element *ele, struct SpiBus_WR *wr) {
  if (ele == NULL) {
    return SPIMGR_WRITE_NO_FIND;
  }
  for (uint16_t i = 0; i < wr->times; wr->times++) {
    ele->type->op->write(wr->buf->addr, wr->buf->data, wr->buf->feedback);
  }
  return SPIMGR_WRITE_SUCCESS;
}

/**
 * @brief SPI读设备
 * @param
 * @retval
 **/
uint16_t SpiBus_ReadData(struct SpiBus_Element *ele, struct SpiBus_WR *wr) {
  if (ele == NULL) {
    return SPIMGR_READ_NO_FIND;
  }
  ele->type->op->read(wr->buf->addr, wr->buf->feedback);
  return SPIMGR_READ_SUCCESS;
}

void Spi_UnRegister_Bus() {
  assertptr(spimgr_list);
  BusDelete("spi");
}