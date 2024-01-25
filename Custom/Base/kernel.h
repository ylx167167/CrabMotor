
/**
 * Created by preference on 2024/01/23
 * This program is for learning purposes only and may not be used for any other
 *purpose without the author's permission
 ******
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******
 * Author   : WayneYao
 * Author-QQ: 417838124
 */

#ifndef _KERNEL_H_
#define _KERNEL_H_

/*  C基本库   */
#include <stdbool.h>  //Bool数据类型
#include <stddef.h>
#include <stdint.h>  //基本数据类型
#include <stdio.h>   //变量类型,宏,输入输出函数
#include <stdlib.h>  //变量类型,宏,通用工具函数
#include <string.h>  //变量类型,宏,字符数组函数

/*	 应用相关头文件   */
#include "hw_base.h"
#include "sin_map.h"
#include "statu.h"
/*  判断是不是为空指针	*/
#define assertptr(ptr)                     \
  do {                                     \
    if ((ptr) == NULL) {                   \
      printf("Error Pointer is NULL\r\n"); \
      return;                              \
    }                                      \
  } while (0)

/**
 * @brief 自定义打印
 * @param1打开打印 0关闭所有打印
 *  #define DBG(format,...)  printf("[%s][%05d]:"format, __func__, __LINE__,
    ##__VA_ARGS__) //打印函数名，行号 #define DBG(format,...)
    printf("["__FILE__"][%s][%05d]: "format, __func__, __LINE__,
    ##__VA_ARGS__)//打印文件名，函数名，行号
 * @retval
 **/
#define DEBUG 1
#if DEBUG
#define CRAB_PRINTF(format, ...)   \
  {                                \
    printf(format, ##__VA_ARGS__); \
    printf("\r\n");                \
  }  // 正常打印

#else
#define CRAB_PRINTF(format, ...)
#endif

#endif
