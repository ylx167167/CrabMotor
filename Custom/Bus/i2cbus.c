#include "i2cbus.h"

#include "bus.h"
struct I2CBus_Node *i2cmgr_list = NULL;
void UnMount_ALlDevice(void) {
  assertptr(i2cmgr_list);
  /* 链表遍历 通过slaveaddr查看是否存在该设备 */
  struct I2CBus_Node *temp = i2cmgr_list;
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
void I2C_Register_Bus(void) {
  i2cmgr_list = (struct I2CBus_Node *)malloc(sizeof(struct I2CBus_Node));
  i2cmgr_list->element = NULL;
  i2cmgr_list->next = NULL;
  struct BUS_Type *type = (struct BUS_Type *)malloc(sizeof(struct BUS_Type));
  type->name = "i2c";
  type->data = (void *)i2cmgr_list;
  type->unmount = UnMount_ALlDevice;
  BusRegister(type);
  return;
}
void I2CBus_Printf_List(void) {
  assertptr(i2cmgr_list);
  struct I2CBus_Node *temp;
  temp = i2cmgr_list->next;
  /* 链表遍历 通过slaveaddr查看是否存在该设备 */
  while (temp) {
    CRAB_PRINTF("%d", temp->element->slaveaddr);
    temp = temp->next;  // 指向下一个节点
  }
}
struct I2CBus_Element *I2CBus_Register_Device(int slaveaddr,
                                              struct I2CBus_TypeDef *type) {
  assertptr(i2cmgr_list);
  struct I2CBus_Node *temp, *temp1;
  struct I2CBus_Element *element =
      (struct I2CBus_Element *)malloc(sizeof(struct I2CBus_Element));

  element->slaveaddr = slaveaddr;
  element->type = type;
  temp = i2cmgr_list;   // 指向第一个节点
  temp1 = i2cmgr_list;  // temp1指向最后一个节点

  /* 链表遍历到尾部 */
  if (temp->next != NULL) {  // 如果不是第一个节点
    temp1 = temp;
    temp = temp->next;
    while (temp) {
      if (temp->element->slaveaddr == slaveaddr) {  // 如果已经注册过
        return temp->element;
      }
      temp1 = temp;       // 指向当前节点（有值）
      temp = temp->next;  // 开始判断下一个节点
    }
  }
  /*	新建节点  */
  temp = (struct I2CBus_Node *)malloc(sizeof(struct I2CBus_Node));
  temp->element = element;
  temp->next = NULL;
  /*	在尾部位置插入  */
  temp1->next = temp;

  CRAB_PRINTF("%d", temp->element->slaveaddr);
  /*	调用该设备的初始化函数  */
  element->type->op->init();
  return element;
}

enum I2C_BUS_FLAG I2CBus_WriteData(struct I2CBus_Element *ele,
                                   struct I2CBus_WR_Buf *buf) {
  if (ele == NULL) {
    return I2C_WRITE_NO_FIND;
  }
  if (ele->type->op_bit == 8) {
    return ele->type->op->write8(buf->addr, buf->data, buf->len);
  } else if (ele->type->op_bit == 16) {
    return ele->type->op->write16(buf->addr, buf->data, buf->len);
  } else {
    return I2C_WRITE_FAIL;
  }
}

enum I2C_BUS_FLAG I2CBus_ReadData(struct I2CBus_Element *ele,
                                  struct I2CBus_WR_Buf *buf) {
  if (ele == NULL) {
    return I2C_READ_NO_FIND;
  }
  if (ele->type->op_bit == 8) {
    return ele->type->op->read8(buf->addr, buf->feedback, buf->len);
  } else if (ele->type->op_bit == 16) {
    return ele->type->op->read16(buf->addr, buf->feedback, buf->len);
  } else {
    return I2C_READ_FAIL;
  }
}

void I2C_UnRegister_Bus(void) {
  assertptr(i2cmgr_list);
  /*	从Bus总线上卸载i2c总线  */
  BusDelete("i2c");
}

int32_t I2CBus_UnRegister_Device(int slaveaddr) {
  assertptr(i2cmgr_list);
  struct I2CBus_Node *temp, *temp1;
  temp = i2cmgr_list;
  temp1 = i2cmgr_list;
  /* 链表遍历 通过slaveaddr查看是否存在该设备 */
  if (temp->element == NULL) {  // 如果为空列表
    return I2C_DEVICE_NO_FIND;
  }
  do {
    if (temp->element->slaveaddr == slaveaddr) {
      /*  找到该节点则进行节点删除并释放内存	*/
      temp1->next = temp->next;
      free(temp->element->type);
      free(temp->element);
      return I2C_DEVICE_UNREGISTER_SUCCESS;
    }
    temp1 = temp;       // 保存上一个节点
    temp = temp->next;  // 指向下一个节点
  } while (temp);
  return I2C_DEVICE_NO_FIND;
}