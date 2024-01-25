#include "bus.h"

#include "Base/kernel.h"

struct BUS_Node *bus_list = NULL;

void SystemBusInit(void) { /*	初始化双向链表  */
  bus_list = (struct BUS_Node *)malloc(sizeof(struct BUS_Node));
  if (bus_list == NULL) {
    CRAB_PRINTF("malloc failed");
  }
  bus_list->next = bus_list;
  bus_list->pre = bus_list;
  bus_list->data = NULL;  // 创建第一个节点 哨兵位置
}
void BusPrintfList() {
  struct BUS_Node *temp = bus_list->next;
  while (temp->data != NULL) {
    CRAB_PRINTF("%s", temp->data->name);
    temp = temp->next;
  }
}

void BusRegister(const struct BUS_Type *type) {
  assertptr(bus_list);
  struct BUS_Node *newnode = (struct BUS_Node *)malloc(sizeof(struct BUS_Node));
  if (newnode == NULL) {
    CRAB_PRINTF("malloc failed");
  }
  /*	在双向链表尾部插入节点*/
  newnode->data = type;                   // 新建节点
  struct BUS_Node *tail = bus_list->pre;  // 尾部节点为头结点的上一节点
  tail->next = newnode;      // 上一尾部节点的下一节点是新节点
  newnode->pre = tail;       // 新节点的上一节点是上一尾部节点
  newnode->next = bus_list;  // 新节点的下一节点是头结点
  bus_list->pre = newnode;   // 第一节点的前向节点为新节点
}

struct BUS_Node *BusCheck(const char *busname) {
  assertptr(bus_list);
  struct BUS_Node *temp = bus_list->next;
  if (temp == NULL) {
    return NULL;
  }
  do {
    if (strcmp(temp->data->name, busname) == 0) {
      return temp;
    }
    temp = temp->next;
  } while (temp->data != NULL);
  return NULL;
}

void BusDelete(char *busname) {
  assertptr(bus_list);
  struct BUS_Node *temp = BusCheck(busname);
  if (temp == NULL) {
    printf("delete failed there has no bus");
    return;
  }
  /*	删除节点 */
  temp->pre->next = temp->next;
  temp->next->pre = temp->pre;
  if (temp->data != NULL) {
    temp->data->unmount();  // 清空该总线上的设备
    free(temp->data->data);
  }
  free(temp);
  return;
}