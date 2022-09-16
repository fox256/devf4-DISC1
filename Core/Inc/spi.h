/*
 * spi.h
 *
 *  Created on: Aug 23, 2022
 *      Author: Alexander
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f4xx.h"

void spi1_tx_8b(uint8_t TxData);
uint8_t spi1_rx_8b(void);

#endif /* INC_SPI_H_ */
