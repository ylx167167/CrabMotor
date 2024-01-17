/**
 * Created by preference on 2024/01/17
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

#ifndef _HW_BASE_H_
#define _HW_BASE_H_

/* 2相四线GPIO--->TBH640	*/
#define HW_AP_GPIO_GROUP
#define HW_AP_PIN
#define HW_AM_GPIO_GROUP
#define HW_AM_PIN
#define HW_BP_GPIO_GROUP
#define HW_BP_PIN
#define HW_AM_GPIO_GROUP
#define HW_BM_PIN
/* A相PWM B相PWM --->TBH640	 */
#define HW_APWM_GPIO_GROUP
#define HW_APWM_PIN
#define HW_APWM_CHANNEL
#define HW_APWM_GPIO_GROUP
#define HW_APWM_PIN
#define HW_APWM_CHANNEL

// AS5047_SPI采集(GPIO)
#define AS5047_SPI_CS_GPIO_CLK_ENABLE()
#define AS5047_SPI_CS_GPIO_GROUP
#define AS5047_SPI_CS_PIN
// AS5047_SPI采集(AFIO & SPI)
#define AS5047_SPI_CLK_GPIO_CLK_ENABLE()
#define AS5047_SPI_CLK_GPIO_GROUP
#define AS5047_SPI_CLK_PIN
#define AS5047_SPI_MISO_GPIO_CLK_ENABLE()
#define AS5047_SPI_MISO_GPIO_GROUP
#define AS5047_SPI_MISO_PIN
#define AS5047_SPI_MOSI_GPIO_CLK_ENABLE()
#define AS5047_SPI_MOSI_GPIO_GROUP
#define AS5047_SPI_MOSI_PIN
#define AS5047_SPI_SPI_CLK_ENABLE()
#define AS5047_SPI_Get_SPI
#define AS5047_SPI_Get_HSPI
#define AS5047_SPI_AFIO_REMAP
#define AS5047_SPI_Prescaler

#endif