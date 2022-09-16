/*
 * ds3231.h
 *
 *  Created on: Aug 25, 2022
 *      Author: Alexander
 */

#ifndef DS3231_DS3231_H_
#define DS3231_DS3231_H_

#define DS3231_ADDRESS			(0x68<<1)

#define DS3231_REG_TIME             0x00
#define DS3231_REG_SECONDS          0x00
#define DS3231_REG_MINUTES          0x01
#define DS3231_REG_HOURS          	0x02
#define DS3231_REG_DAY              0x03
#define DS3231_REG_DATE             0x04
#define DS3231_REG_MONTH            0x05
#define DS3231_REG_YEAR             0x06
#define DS3231_REG_ALARM_1          0x07
#define DS3231_REG_ALARM_2          0x0B
#define DS3231_REG_CONTROL          0x0E
#define DS3231_REG_STATUS           0x0F
#define DS3231_REG_MSB_TEMP      	0x11
#define DS3231_REG_LSB_TEMP			0x12

uint8_t DS3231_Read(uint8_t addr);
uint8_t DS3231_Get_Sec(void);
uint8_t DS3231_Get_Min(void);
uint8_t DS3231_Get_Hours(void);

#endif /* DS3231_DS3231_H_ */
