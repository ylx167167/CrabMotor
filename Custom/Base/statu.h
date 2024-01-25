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

#ifndef _STATU_H_
#define _STATU_H_

enum SPI_BUS_FLAG {
  SPI_REGISTER_FAILE = -1,
  SPI_HAS_BEEN_REGISTER = 0,
  SPI_REGISTER_SUCCESS = 1,
  SPI_LIST_NULL,
  SPI_INIT_SUCCESS,
  SPI_INIT_NO_FIND,
  SPI_INIT_FAILE,
  SPI_WRITE_SUCCESS,
  SPI_WRITE_FAIL,
  SPI_WRITE_NO_FIND,
  SPI_READ_SUCCESS,
  SPI_READ_FAIL,
  SPI_READ_NO_FIND,
  SPI_DEVICE_UNREGISTER_SUCCESS,
  SPI_DEVICE_NO_FIND,

};

enum I2C_BUS_FLAG {
  I2C_REGISTER_FAILE = -1,
  I2C_HAS_BEEN_REGISTER = 0,
  I2C_REGISTER_SUCCESS = 1,
  I2C_LIST_NULL,
  I2C_INIT_SUCCESS,
  I2C_INIT_NO_FIND,
  I2C_INIT_FAILE,
  I2C_WRITE_SUCCESS,
  I2C_WRITE_FAIL,
  I2C_WRITE_NO_FIND,
  I2C_READ_SUCCESS,
  I2C_READ_FAIL,
  I2C_READ_NO_FIND,
  I2C_DEVICE_NO_FIND,
  I2C_DEVICE_UNREGISTER_SUCCESS,
};
#endif