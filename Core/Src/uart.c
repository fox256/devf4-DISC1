/*
 * uart.c
 *
 *  Created on: Aug 19, 2022
 *      Author: Alexander
 */

#include "uart.h"
#include "stm32f4xx_ll_usart.h"

//UART2 tx
void uart_tx(char data)
{
	USART2->DR = data;
	//while(((USART2->SR) &= (USART_SR_TC)) == SET);
	while (LL_USART_IsActiveFlag_TC(USART2) == RESET);
}

// print string
void send_str(char txdata[])
{
	for (int i = 0; i < strlen(txdata); i++)
	{
		uart_tx(txdata[i]);
	}
}

//print formated string
void send_strf(const char* str, ...)
{
	char stringArray[100];

	va_list args;
	va_start(args,str);
	vsprintf(stringArray, str, args);
	va_end(args);

	send_str(stringArray);
}

