/*
 * ds3231.h
 *
 *  Created on: Aug 25, 2022
 *      Author: Alexander
 */

#ifndef DS3231_DS3231_H_
#define DS3231_DS3231_H_

#define DS3231_ADDRESS			(0x68<<1)


/**
 * @brief chip register definition
 */
#define DS3231_REG_SECOND               0x00        /**< second register */
#define DS3231_REG_MINUTE               0x01        /**< minute register */
#define DS3231_REG_HOUR                 0x02        /**< hour register */
#define DS3231_REG_WEEK                 0x03        /**< week register */
#define DS3231_REG_DATE                 0x04        /**< date register */
#define DS3231_REG_MONTH                0x05        /**< month register */
#define DS3231_REG_YEAR                 0x06        /**< year register */
#define DS3231_REG_ALARM1_SECOND        0x07        /**< alarm1 second register */
#define DS3231_REG_ALARM1_MINUTE        0x08        /**< alarm1 minute register */
#define DS3231_REG_ALARM1_HOUR          0x09        /**< alarm1 hour register */
#define DS3231_REG_ALARM1_WEEK          0x0A        /**< alarm1 week register */
#define DS3231_REG_ALARM2_MINUTE        0x0B        /**< alarm2 minute register */
#define DS3231_REG_ALARM2_HOUR          0x0C        /**< alarm2 hour register */
#define DS3231_REG_ALARM2_WEEK          0x0D        /**< alarm2 week register */
#define DS3231_REG_CONTROL              0x0E        /**< control register */
#define DS3231_REG_STATUS               0x0F        /**< status register */
#define DS3231_REG_XTAL                 0x10        /**< xtal register */
#define DS3231_REG_TEMPERATUREH         0x11        /**< temperature high register */
#define DS3231_REG_TEMPERATUREL         0x12        /**< temperature low register */

typedef struct {
    uint8_t	sec;
    uint8_t min;
    uint8_t hours;
    uint8_t	weekday;
    uint8_t day;
    uint8_t month;
    uint8_t year;
}rtc_time_t;

extern rtc_time_t rtc;

uint8_t DS3231_Read(uint8_t addr);
uint8_t DS3231_Get_Sec(void);
uint8_t DS3231_Get_Min(void);
uint8_t DS3231_Get_Hours(void);
uint8_t DS3231_Get_Week (void);

void DS3231_Set_Hours (uint8_t h);
void DS3231_Set_Min (uint8_t m);




#endif /* DS3231_DS3231_H_ */
