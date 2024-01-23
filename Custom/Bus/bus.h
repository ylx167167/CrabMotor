#ifndef _BUS_H_
#define _BUS_H_
#include stdio.h

struct BUS_Type {
  char* name;
  void* data;
};

struct BUS_Node {
  struct BUS_Node* pre;
  struct BUS_Node* next;
  struct BUS_Type* data;
};

/**
 * @brief 系统总线初始化
 * @param
 * @retval
 **/
void SystemBusInit(void);

/**
 * @brief 注册总线
 * @param
 * @retval
 **/
void BusRegister(const struct BUS_Type* type);

/**
 * @brief 删除总线
 * @param
 * @retval
 **/
void BusDelete(const char* busname);

/**
 * @brief 查询是否存在总线
 * @param
 * @retval
 **/

void BusCheck(const char* busname);
#endif