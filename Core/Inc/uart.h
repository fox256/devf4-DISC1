/*
 * uart.h
 *
 *  Created on: Aug 19, 2022
 *      Author: Alexander
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "config.h"

void send_strf(const char* str, ...);
void uart_tx(char data);
#endif /* INC_UART_H_ */
