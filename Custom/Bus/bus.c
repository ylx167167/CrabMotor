#include "bus.h"

#include "Base/kernel.h"
#define Assert(node)                        \
  if (node->data != NULL) {                 \
    print("there has no gurd pointer\r\n"); \
  // return -1;
}

struct BUS_Node *bus_list = NULL;
void SystemBusInit(void) { /*	初始化双向链表  */
  bus_list = (struct BUS_Node *)malloc(sizeof(struct BUS_Node));
  if (node == NULL) {
    printf("malloc failed");
  }
  bus_list->next = bus_list;
  bus_list->pre = bus_list;
  bus_list->data = NULL;  // 创建第一个节点 哨兵位置
}

void BusRegister(const struct BUS_Type *type) {
  Assert(bus_list);
  struct BUS_Node *newnode = (struct BUS_Node *)malloc(sizeof(struct BUS_Node));
  if (newnode == NULL) {
    printf("malloc failed");
  }
  /*	在双向链表尾部插入节点*/
  newnode->next = NULL;
  newnode->pre = NULL;
  newnode->data = type;
  struct BUS_Node *tail = bus_list->pre;
  tail->next = newnode;
  newnode->pre = tail;
  newnode->next = bus_list;
  bus_list->pre = newnode;
}

struct BUS_Node *BusCheck(const char *busname) {
  Assert(bus_list);
  struct BUS_Node *temp = bus_list;
  if (temp->data == NULL) {
    return;
  }
  do {
    if (strcmp(temp->data->name, busname) == 0) {
      return temp;
    }
    temp = temp->next;
  } while (temp->data != NULL);
  return NULL;
}

void BusDelete(const char *busname) {
  Assert(bus_list);
  struct BUS_Node *temp = bus_list;
  if (temp->data == NULL) {
    return;
  }
  struct BUS_Node *temp = BusCheck(busname);
  if (temp == NULL) {
    printf("delete failed there has no bus");
    return;
  }
  temp->pre->next = temp->next;
  temp->next->pre = temp->pre;
  free(temp);
  printf("delete success");
  return;
}