/*
 * i2c.h
 *
 *  Created on: Aug 22, 2022
 *      Author: Alexander
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "config.h"





void i2c1_start (void);
uint8_t i2c1_read(void);
void i2c1_write (uint8_t data);
void i2c1_stop(void);

void i2c1_write_adress (uint8_t address);
void i2c1_init(void);
uint8_t i2c1_test(void);

//new implementation
uint8_t i2c_start(I2C_TypeDef *I2Cx, uint32_t timeout);
uint8_t i2c_write_adress(I2C_TypeDef *I2Cx, uint8_t address, uint32_t timeout);
uint8_t i2c_write_data(I2C_TypeDef *I2Cx, uint8_t data, uint32_t timeout);
uint8_t i2c_read_data(I2C_TypeDef *I2Cx, uint32_t timeout);
void i2c_dis_ack(I2C_TypeDef *I2Cx);
void i2c_stop(I2C_TypeDef *I2Cx);



#endif /* INC_I2C_H_ */
