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

	//DS_I2C_start(); //repeated start

	//DS_I2C_write_add(DS3231_ADDRESS | 0x01);
	//uint8_t data = DS_I2C_read();

	DS_I2C_stop();	//stop
	//return data;
}


uint8_t DS3231_Get_Sec (void)
{
	uint8_t sec = 0;
	sec = B2D(DS3231_Read(0x00));

	return sec;
}

uint8_t DS3231_Get_Min (void)
{
	uint8_t min = 0;
	min = B2D(DS3231_Read(0x01));
	return min;

}

uint8_t DS3231_Get_Hours (void)
{
	uint8_t hours = 0;
	hours = B2D(DS3231_Read(0x02));
	return hours;
}

void DS3231_Set_12_24 (bool format)
{
	uint8_t reg = 0;
	if(format == RESET)
	{
		reg = DS3231_Read(0x02);

	}
	else
	{

	}
}




static uint8_t B2D(uint8_t bcd)
{
  return (bcd >> 4) * 10 + (bcd & 0x0F);
}

static uint8_t D2B(uint8_t decimal)
{
  return (((decimal / 10) << 4) | (decimal % 10));
}






