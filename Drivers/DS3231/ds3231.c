/*
 * ds3231.c
 *
 *  Created on: Aug 25, 2022
 *      Author: Alexander
 */

#include "i2c.h"
#include "ds3231.h"
#include "stm32f407xx.h"
#include <stdint.h>


static uint8_t B2D(uint8_t bcd);
static uint8_t D2B(uint8_t decimal);

rtc_time_t rtc;

/* SETUP CODE BEGIN	*/
void DS_I2C_start (void)
{
	//i2c_start(I2C1,10);
	i2c1_start();
}

void DS_I2C_stop (void)
{
	//i2c_stop(I2C1);
	i2c1_stop();
}

void DS_I2C_write (uint8_t i2c_data)
{
	i2c1_write (i2c_data);
}

uint8_t DS_I2C_read (void)
{
	uint8_t dsdata = i2c1_read();
	return dsdata;
}

void DS_I2C_write_add (uint8_t addr)
{
	i2c1_write_adress (addr);
}

/* SETUP CODE END	*/

uint8_t DS3231_Read (uint8_t addr)
{
	DS_I2C_start(); // start

	DS_I2C_write_add(DS3231_ADDRESS);
	DS_I2C_write(addr);

	DS_I2C_start(); //repeated start

	DS_I2C_write_add(DS3231_ADDRESS | 0x01);
	uint8_t data = DS_I2C_read();

	DS_I2C_stop();	//stop
	return data;
}

void DS3231_Write (uint8_t addr, uint8_t data)
{
	DS_I2C_start(); // start

	DS_I2C_write_add(DS3231_ADDRESS);
	DS_I2C_write(addr);
	DS_I2C_write(data);

	//DS_I2C_start(); //repeated start

	//DS_I2C_write_add(DS3231_ADDRESS | 0x01);
	//uint8_t data = DS_I2C_read();

	DS_I2C_stop();	//stop
	//return data;
}


uint8_t DS3231_Get_Sec (void)
{
	uint8_t sec = 0;
	sec = B2D(DS3231_Read(DS3231_REG_SECOND));
	return sec;
}

uint8_t DS3231_Get_Min (void)
{
	uint8_t min = 0;
	min = B2D(DS3231_Read(DS3231_REG_MINUTE));
	return min;
}

uint8_t DS3231_Get_Hours (void)
{
	uint8_t hours = 0;
	hours = B2D(DS3231_Read(DS3231_REG_HOUR));
	return hours;
}


uint8_t DS3231_Get_Week (void)
{
	uint8_t week = 0;
	week = DS3231_Read(DS3231_REG_WEEK);
	return week;
}

//----------set functions--------------------------//
void DS3231_Set_Hours (uint8_t h)
{
	DS3231_Write(DS3231_REG_HOUR,D2B(h));
}

void DS3231_Set_Min (uint8_t m)
{

	DS3231_Write(DS3231_REG_MINUTE,D2B(m));
}


void rtc_time_init(void)
{
	//default values
	rtc.sec = 0;
	rtc.min = 0;
	rtc.hours = 12;
	rtc.weekday = 4; 	// Thursday
	rtc.day = 23;
	rtc.month = 11; 	// November
	rtc.year = 89;

	//write data to DS3231
	DS3231_Write(DS3231_REG_SECOND, D2B	(rtc.sec));
	DS3231_Write(DS3231_REG_MINUTE,	D2B	(rtc.min));
	DS3231_Write(DS3231_REG_HOUR,	D2B	(rtc.hours));
	DS3231_Write(DS3231_REG_WEEK,	D2B	(rtc.weekday));
	DS3231_Write(DS3231_REG_DATE,	D2B	(rtc.day));
	DS3231_Write(DS3231_REG_MONTH,	D2B	(rtc.month));
	DS3231_Write(DS3231_REG_YEAR,	D2B	(rtc.year));
}



static uint8_t B2D(uint8_t bcd)
{
  return (bcd >> 4) * 10 + (bcd & 0x0F);
}

static uint8_t D2B(uint8_t decimal)
{
  return (((decimal / 10) << 4) | (decimal % 10));
}






