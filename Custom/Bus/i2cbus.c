#include "i2cbus.h"

#include "Base/kernel.h"
struct I2CBus_Node *i2cmgr_list = NULL;
void I2C_Register_Bus(void) {
  i2cmgr_list = (struct I2CBus_Node *)malloc(sizeof(struct I2CBus_Node));
  i2cmgr_list->element = NULL;
  i2cmgr_list->next = NULL;
  struct BUS_Type *type = (struct BUS_Type *)malloc(sizeof(struct BUS_Type));
  type->name = "i2c";
  type->data = (void *)i2cmgr_list;
  BusRegister(type);
  return;
}

struct I2CBus_Element *I2CBus_Register_Device(int slaveaddr,
                                              struct I2CBus_TypeDef *type) {
  assertptr(i2cmgr_list);
  struct I2CBus_Node *temp1;
  struct I2CBus_Element element =
      (struct I2CBus_Element *)malloc(sizeof(struct I2CBus_Element));
  element.slaveaddr = slaveaddr;
  element.type = type;

  temp1 = i2cmgr_list;
  /* 链表遍历 通过slaveaddr查看是否存在该设备 */
  do {
    if (temp1->element == NULL) {
      break;
    } else if (temp1->element->devidx == element->devidx) {  // 如果已经注册过
      return temp1->element;
    }
    temp1 = temp1->next;
  } while (temp1);

  temp1 = (struct I2CBus_Node *)malloc(sizeof(struct I2CBus_Node));
  temp1->element = element;
  temp1->next = NULL;

  /*	调用该设备的初始化函数  */
  element->type->op->init;
  return REGISTER_SUCCESS;
}

uint8_t I2CBus_WriteData(struct I2CBus_Element *ele,
                         struct I2CBus_WR_Buf *buf) {
  if (ele == NULL) {
    return I2C_WRITE_NO_FIND;
  }
  if (ele->type->op_bit == 8) {
    return ele->type->op->write8(buf->addr, buf->data, buf->len);
  } else if (ele->type->op_bit == 16) {
    return ele->type->op->write16(buf->addr, buf->data, buf->len);
  } else {
    return FALSE;
  }
}

uint8_t I2CBus_ReadData(struct I2CBus_Element *ele, struct I2CBus_WR_Buf *buf) {
  if (ele == NULL) {
    return I2C_READ_NO_FIND;
  }
  if (ele->type->op_bit == 8) {
    return ele->type->op->read8(buf->addr, buf->feedback, buf->len);
  } else if (ele->type->op_bit == 16) {
    return ele->type->op->read16(buf->addr, buf->feedback, buf->len);
  } else {
    return FALSE;
  }
}

void I2C_UnRegister_Bus() {
  assertptr(i2cmgr_list);
  BusDelete("i2c");
}

void I2CBus_UnRegister_Device(int slaveaddr) {}