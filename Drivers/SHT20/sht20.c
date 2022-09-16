/*
 * sht20.c
 *
 *  Created on: Sep 6, 2022
 *      Author: Alexander
 *
 *	MCU connectiom:
 *	SDA - PB9
 *	SCL - PB6
 *
 */

#include "sht20.h"
#include "i2c.h"



uint8_t SHT20_SoftReset(void)
{
	uint8_t err = 0;

	err = i2c_start(I2C1,10);
	err = i2c_write_adress(I2C1,SHT20_ADDR_W,10);
	err = i2c_write_data(I2C1,SHT20_SOFT_RESET,10);
	i2c_stop(I2C1);
	HAL_Delay(15);
	return err;
}

uint8_t SHT20_ReadUserRegister(void)
{
	uint8_t data = 0;

	i2c_start(I2C1,10);
	i2c_write_adress(I2C1,SHT20_ADDR_W,10);
	i2c_write_data(I2C1,SHT20_READ_REG,10);

	//read
	i2c_start(I2C1,10);
	I2C1->CR1 &= ~(I2C_CR1_ACK);
	i2c_write_adress(I2C1,SHT20_ADDR_R,10);
	data = i2c_read_data(I2C1,10);

	i2c_stop(I2C1);

	return data;
}


float SHT20_GetTemp(void)
{
    uint8_t data[3] = {0, 0, 0};
    uint16_t sT = 0;			//sensor Temperature raw data
    float temperatureC = 0;  	//variable for result

	i2c_start(I2C1,10);
	i2c_write_adress(I2C1,SHT20_ADDR_W,10);			//write address
	i2c_write_data(I2C1,TRIG_T_MEASUREMENT_HM,10);	//command

	//read
	i2c_start(I2C1,10); //repeated start
	i2c_write_adress(I2C1,SHT20_ADDR_R,10);	//read address
	data[0] = i2c_read_data(I2C1,100);		//timeout 100ms for temperature measuring
	data[1] = i2c_read_data(I2C1,10);
	i2c_dis_ack(I2C1); 						//disable ACK for reading last byte with NACK
	data[2] = i2c_read_data(I2C1,10);
	i2c_stop(I2C1);

	sT = ((uint16_t)data[0] << 8) | data[1];
	sT &= ~0x0003; 							//clear bits [1..0] (status bits)
	temperatureC = -46.85 + (((float)sT/65536)* 175.72);

	return temperatureC;
}


float SHT20_GetHum(void)
{
	uint8_t read_data[3] = {0, 0, 0};
	float humRh = 0;  	//variable for result

	i2c_start(I2C1,10);
	i2c_write_adress(I2C1,SHT20_ADDR_W,10);
	i2c_write_data(I2C1,TRIG_H_MEASUREMENT_HM,10); // Trigger RH measurement hold master

	//read
	i2c_start(I2C1,10); //repeated start
	i2c_write_adress(I2C1,SHT20_ADDR_R,10);
	read_data[0] = i2c_read_data(I2C1,50);	//timeout 50ms for humidity measuring
	read_data[1] = i2c_read_data(I2C1,10);
	i2c_dis_ack(I2C1); // disable ACK for reading last byte with NACK
	read_data[2] = i2c_read_data(I2C1,10);



	return humRh;
}


