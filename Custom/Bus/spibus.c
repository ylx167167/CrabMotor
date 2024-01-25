#include "spibus.h"

#include "Base/kernel.h"
#include "bus.h"
#include "spi.h"
struct SpiBus_Node *spi_list = NULL;
/**
 * @brief 挂载设备函数
 * @param
 * @retval
 **/
void UnMount_ALlDevice(void) {
  assertptr(spi_list);
  /* 链表遍历 通过slaveaddr查看是否存在该设备 */
  struct SpiBus_Node *temp = spi_list;
  do {
    if (temp->element != NULL) {
      if (temp->element->type != NULL) {
        free(temp->element->type);
      }
      free(temp->element);
    }
    temp = temp->next;
  } while (temp);
}

void Spi_Register_Bus(void) {
  spi_list = (struct SpiBus_Node *)malloc(sizeof(struct SpiBus_Node));
  spi_list->element = NULL;
  spi_list->next = NULL;
  struct BUS_Type *type = (struct BUS_Type *)malloc(sizeof(struct BUS_Type));
  type->name = "spi";
  type->data = (void *)spi_list;
  type->unmount = UnMount_ALlDevice;
  BusRegister(type);
  return;
}
void SpiBus_Printf_List(void) {
  assertptr(spi_list);
  struct I2CBus_Node *temp;
  temp = spi_list->next;
  /* 链表遍历 通过slaveaddr查看是否存在该设备 */
  while (temp) {
    CRAB_PRINTF("%d", temp->element->devidx);
    temp = temp->next;  // 指向下一个节点
  }
}

struct SpiBus_Element *SpiBus_Register_Device(int devidx,
                                              struct SpiBus_TypeDef *type) {
  assertptr(spi_list);
  // struct SpiBus_Node *node = NULL;
  struct SpiBus_Node *temp, *temp1;

  struct SpiBus_Element *element =
      (struct SpiBus_Element *)malloc(sizeof(struct SpiBus_Element));
  element->devidx = devidx;
  element->type = type;
  temp = spi_list;
  temp1 = spi_list;

  /* 链表遍历到尾部 */
  if (temp->next != NULL) {  // 如果不是第一个节点
    temp1 = temp;
    temp = temp->next;
    while (temp) {
      if (temp->element->devidx == devidx) {  // 如果已经注册过
        return temp->element;
      }
      temp1 = temp;       // 指向当前节点（有值）
      temp = temp->next;  // 开始判断下一个节点
    }
  }
  /*	新建节点  */
  temp = (struct SpiBus_Node *)malloc(sizeof(struct SpiBus_Node));
  temp->element = element;
  temp->next = NULL;
  /*	在尾部位置插入  */
  temp1->next = temp;
  /*	调用该设备的初始化函数  */
  element->type->op->init();

  return element;
}
struct SpiBus_Element *SpiBus_Find(int devidx) {
  struct SpiBus_Node *temp;
  temp = spi_list;
  /* 链表遍历到尾部 */
  if (temp->next != NULL) {  // 如果不是第一个节点
    temp = temp->next;
    while (temp) {
      if (temp->element->devidx == devidx) {  // 如果已经注册过
        return temp->element;
      }
      temp = temp->next;  // 开始判断下一个节点
    }
  }
  return NULL;
}

/**
 * @brief SPI写设备
 * @param
 * @retval
 **/
enum SPI_BUS_FLAG SpiBus_WriteData(struct SpiBus_Element *ele,
                                   struct SpiBus_WR *wr) {
  if (ele == NULL) {
    return SPI_WRITE_NO_FIND;
  }
  for (uint16_t i = 0; i < wr->times; wr->times++) {
    ele->type->op->write(wr->buf->addr, wr->buf->data, wr->buf->feedback);
  }
  return SPI_WRITE_SUCCESS;
}

/**
 * @brief SPI读设备
 * @param
 * @retval
 **/
enum SPI_BUS_FLAG SpiBus_ReadData(struct SpiBus_Element *ele,
                                  struct SpiBus_WR *wr) {
  if (ele == NULL) {
    return SPI_READ_NO_FIND;
  }
  ele->type->op->read(wr->buf->addr, wr->buf->feedback);
  return SPI_READ_SUCCESS;
}

void Spi_UnRegister_Bus() {
  assertptr(spi_list);
  BusDelete("spi");
}

int32_t SpiBus_UnRegister_Device(int devidx) {
  assertptr(spi_list);
  struct SpiBus_Node *temp, *temp;
  temp = spi_list;
  temp = spi_list;
  /* 链表遍历 通过slaveaddr查看是否存在该设备 */
  if (temp->element == NULL) {  // 如果为空列表
    return SPI_DEVICE_NO_FIND;
  }
  do {
    if (temp->element->devidx == devidx) {
      /*  找到该节点则进行节点删除并释放内存	*/
      temp->next = temp->next;
      free(temp->element->type);
      free(temp->element);
      return SPI_DEVICE_UNREGISTER_SUCCESS;
    }
    temp = temp;        // 保存上一个节点
    temp = temp->next;  // 指向下一个节点
  } while (temp);
  return SPI_DEVICE_NO_FIND;
}