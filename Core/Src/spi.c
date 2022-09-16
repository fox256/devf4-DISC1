/*
 * spi.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Alexander
 */


#include "spi.h"




/*SPI1 Tx*/
void spi1_tx_8b(uint8_t TxData)
{
	while(!((SPI1->SR)&(SPI_SR_TXE))); 		//Check Tx Buffer Empty Flag
	__IO uint8_t *spidr = ((__IO uint8_t *)&SPI1->DR);	//Put data to DR register
	*spidr = TxData;
	while(!((SPI1->SR)&(SPI_SR_TXE)));		//Check Tx Buffer Empty Flag
	while (((SPI1->SR)&(SPI_SR_BSY)));		//Check SPI Not Busy Flag
	//Clear the Overrun flag by reading DR and SR
	(void)SPI1->DR; //Dummy read
	(void)SPI1->SR;	//Dummy read
}


/*SPI1 Rx*/
uint8_t spi1_rx_8b(void)
{
	while (((SPI1->SR)&(SPI_SR_BSY)));//Check SPI Not Busy Flag

	__IO uint8_t *spirdr = ((__IO uint8_t *)&SPI1->DR);	//Put data to DR register
	*spirdr = 0xFF; // Dummy write

	while (!((SPI1->SR) &(SPI_SR_RXNE)));//Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
	uint8_t data =  (uint8_t)(SPI1->DR);
	return data;
}

