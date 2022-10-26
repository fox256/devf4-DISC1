/*
 * sht20.h
 *
 *  Created on: Sep 6, 2022
 *      Author: Alexander
 */

#include <stdint.h>

#ifndef SHT20_SHT20_H_
#define SHT20_SHT20_H_


#define	SHT20_ADDR_W 		0x80
#define	SHT20_ADDR_R 		0x81

#define SHT20_READ_REG  	0XE7
#define SHT20_WRITE_REG		0XE6
#define SHT20_SOFT_RESET	0XFE

#define TRIG_T_MEASUREMENT_HM  0xE3
#define TRIG_H_MEASUREMENT_HM  0xE5

uint8_t SHT20_SoftReset(void);
uint8_t SHT20_ReadUserRegister(void);
float SHT20_GetTemp(void);
float SHT20_GetHum(void);

#endif /* SHT20_SHT20_H_ */
