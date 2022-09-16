/*
 * i2c.c
 *
 *  Created on: Aug 22, 2022
 *      Author: Alexander
 *
 *      I2C1_SCL - PB6
 *      I2C1_SDA - PB9
 */


#include "i2c.h"
#include "stm32f407xx.h"


void i2c1_init(void)
{
	//configure PB6 and PB9
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; 	//enable GPIOB CLOCK
	GPIOB->MODER |= GPIO_MODER_MODER6_1 | GPIO_MODER_MODER9_1;	//10: Alternate function mode
	GPIOB->OTYPER |= GPIO_OTYPER_OT6 | GPIO_OTYPER_OT9;	//Output open-drain
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED6 | GPIO_OSPEEDR_OSPEED9;	//Very high speed
//	GPIOB->PUPDR |= GPIO_PUPDR_PUPDR6_0 | GPIO_PUPDR_PUPDR9_0;	//Pull-up
	GPIOB->PUPDR &= ~(1<<12); //no-pull
	GPIOB->PUPDR &= ~(1<<18); //no-pull
	GPIOB->AFR[0] |= 4 << 24;	//AF4 for pin PB6
	GPIOB->AFR[1] |= 4 << 4; 	//AF4 for pin PB9

	//configure I2C
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;	//enable I2C CLOCK
	I2C1->CR1 |= I2C_CR1_SWRST; 		// reset the I2C
	I2C1->CR1 &= ~(I2C_CR1_SWRST);  	// normal operation
	I2C1->CR1 |= I2C_CR1_ACK;			//Enable acknowledge

	I2C1->CR2 |= (42<<0); 				//set peripheral clock frequency to 42MHz

	I2C1->CCR |= I2C_CCR_FS; 			// 1: Fast Mode I2C
	I2C1->CCR &= ~(I2C_CCR_DUTY); 		//0: Fm mode tlow/thigh = 2

/*	CCR value calculation formula
 If DUTY=0 that means the Tlow is 2 times the Thigh, then use the below formulas:
 Thigh = CCR x TPCLK1
 Tlow = 2 x CCR x TPCLK1
 Therefore, CCR = FPCLK1 / 3 x FSCL

 CCR = 42HMz / 3* 0.4MHz = 42/1.2 = 35
*/
	//I2C1->CCR = (50<<0); 	// Configure the clock control registers:measured 378kHz
	I2C1->CCR = (60<<0);
	I2C1->TRISE = (0<<0);
	I2C1->CR1 |= (1<<0);  // Enable I2C
}

void i2c1_start (void)

{

	I2C1->CR1 &= ~(I2C_CR1_POS); // Disable POS
	I2C1->CR1 |= I2C_CR1_START;	//Generate START
	while (!(I2C1->SR1 & (1<<0)));	//wait for SB bite to set
	(void)I2C1->SR1; //read SR1 for clear SB bit
}

void i2c1_write (uint8_t data)
{

	I2C1->DR = data;
	while(!(I2C1->SR1 & (I2C_SR1_TXE)));

}

void i2c1_write_adress (uint8_t address)
{
	I2C1->DR = address;
	while (!(I2C1->SR1 & (I2C_SR1_ADDR)));  // wait for ADDR bit to set  1: Received address matched.
	//read SR1 and SR2 to clear the ADDR bit
	(void)I2C1->SR1;
	(void)I2C1->SR2;

}

uint8_t i2c1_read(void)
{

	while(!(I2C1->SR1 &= (I2C_SR1_RXNE)));
	uint8_t rxdata = I2C1->DR;
	return rxdata;
}

 void i2c1_stop(void)
 {
	 I2C1->CR1 &= ~(I2C_CR1_ACK);	//Disable ACK
	 I2C1->CR1 |= I2C_CR1_STOP;		//Stop generation
 }

uint8_t i2c1_test(void)
{
	i2c1_start();

	i2c1_write_adress(0xD0);

	i2c1_write(0x0E);

	i2c1_start();

	i2c1_write_adress(0xD1);

	uint8_t get = i2c1_read();

	i2c1_stop();

	return get;

}
//-------------------- new implementation -----------------//

uint8_t i2c_start(I2C_TypeDef *I2Cx, uint32_t timeout)
{
	uint32_t tick_start = HAL_GetTick();
	I2Cx->CR1 |= I2C_CR1_ACK;		//Enable acknowledge
	I2Cx->CR1 &= ~(I2C_CR1_POS); 	// Disable POS
	I2Cx->CR1 |= I2C_CR1_START;		//Generate START
	while (!(I2Cx->SR1 & (1<<0)))	//wait for SB bite to set
	{
	     if (((HAL_GetTick() - tick_start) > timeout) || (timeout == 0U))
	     {
	    	 return ERROR;
	     }
	}
	(void)I2Cx->SR1; 				//read SR1 for clear SB bit
	return SUCCESS;
}

uint8_t i2c_write_adress(I2C_TypeDef *I2Cx, uint8_t address, uint32_t timeout)
{

	uint32_t tick_start = HAL_GetTick();

	I2Cx->DR = address;

	while (!(I2C1->SR1 & (I2C_SR1_ADDR)))  // wait for ADDR bit to set  1: Received address matched.
	{
	     if (((HAL_GetTick() - tick_start) > timeout) || (timeout == 0U))
	     {
	    	return ERROR;
	     }
	}
	//read SR1 and SR2 to clear the ADDR bit
	(void)I2Cx->SR1;
	(void)I2Cx->SR2;
	return SUCCESS;
}

uint8_t i2c_write_data(I2C_TypeDef *I2Cx, uint8_t data, uint32_t timeout)
{
	uint32_t tick_start = HAL_GetTick();

	I2Cx->DR = data;

	while(!(I2C1->SR1 & (I2C_SR1_TXE)))
	{
		if (((HAL_GetTick() - tick_start) > timeout) || (timeout == 0U))
		{
			return ERROR;
		}
	}
	return SUCCESS;
}

uint8_t i2c_read_data(I2C_TypeDef *I2Cx, uint32_t timeout)
{
	uint32_t tick_start = HAL_GetTick();

	while(!(I2Cx->SR1 &= (I2C_SR1_RXNE)))
	{
		if (((HAL_GetTick() - tick_start) > timeout) || (timeout == 0U))
		{
			break;
		}
	}
	uint8_t rxdata = I2Cx->DR;
	return rxdata;
}

void i2c_stop(I2C_TypeDef *I2Cx)
{
	 I2Cx->CR1 &= ~(I2C_CR1_ACK);	//Disable ACK
	 I2Cx->CR1 |= I2C_CR1_STOP;		//Stop generation
}

void i2c_en_ack(I2C_TypeDef *I2Cx)
{
	I2Cx->CR1 |= I2C_CR1_ACK;
}

void i2c_dis_ack(I2C_TypeDef *I2Cx)
{
	I2C1->CR1 &= ~(I2C_CR1_ACK);
}




