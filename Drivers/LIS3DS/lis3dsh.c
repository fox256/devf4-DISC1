/*
 * lis3dsh.c
 *
 *  Created on: Aug 23, 2022
 *      Author: Alexander
 */

#include "lis3dsh.h"
#include "spi.h"



/* SETUP CODE BEGIN  */

#define NSS_DISABLE() 	(GPIOE->ODR |= 0x0008)
#define NSS_ENABLE()	(GPIOE->ODR &= 0xFFF7)

void lis_tx_8b(uint8_t tx_data)
{
	spi1_tx_8b(tx_data);
}

uint8_t lis_rx_8b(void)
{
	uint8_t rx_data;
	rx_data = spi1_rx_8b();
	return	rx_data;
}
/* SETUP CODE END  */

// variables
uint8_t outx_l, outx_h, outy_l, outy_h, outz_l, outz_h, outt_l, outt_h, outt;
int16_t outx, outy, outz;

uint8_t LIS3DSH_Read(uint8_t addr)
{
	uint8_t data;
	addr |= 0x80;

	NSS_ENABLE();
	lis_tx_8b(addr);
	data = lis_rx_8b();
	NSS_DISABLE();
	return data;
}

void LIS3DSH_Write(uint16_t waddr, uint8_t wdata)
{
	NSS_ENABLE();
	lis_tx_8b(waddr);
	lis_tx_8b(wdata);
	NSS_DISABLE();
}


void LIS3DSH_Init(void)
{
	//***NORMAL mode***
	NSS_DISABLE();
	LIS3DSH_Write(CTRL_REG4_ADDR, 0b01101111); //ODR = 100Hz, BDU = 1, ZYX enabled
	LIS3DSH_Write(CTRL_REG1_ADDR, 0x00);
	LIS3DSH_Write(CTRL_REG2_ADDR, 0x00);
	LIS3DSH_Write(CTRL_REG3_ADDR, 0x00);
	LIS3DSH_Write(CTRL_REG5_ADDR, 0b00000000); //BW = 00 anti aliasing 800Hz, Scale +- 2g, Self test disabled, SPI 4 wire
	LIS3DSH_Write(CTRL_REG6_ADDR, 0x00);
}

void LIS3DSH_Measure(void)
{

	//if(wszystko_ok == 1){
	outx_l	= 	LIS3DSH_Read(OUT_X_L_ADDR);
	outx_h	= 	LIS3DSH_Read(OUT_X_H_ADDR); //XDA=0 after reading
	outx = ( outx_h << 8 ) | outx_l;
	//x = (float) outx * sensitivity; //FS=00 + Normal mode, SENSITIVITY = 0.06 mg // mg

	outy_l	= 	LIS3DSH_Read(OUT_Y_L_ADDR);
	outy_h	= 	LIS3DSH_Read(OUT_Y_H_ADDR);
	outy = ( outy_h << 8 ) | outy_l;
	//y = (float) outy * sensitivity; //FS=00 + Normal mode, SENSITIVITY = 0.06 mg // mg

	outz_l	= 	LIS3DSH_Read(OUT_Z_L_ADDR);
	outz_h	=	LIS3DSH_Read(OUT_Z_H_ADDR);
	outz = ( outz_h << 8 ) | outz_l;
	//z = (float) outz * sensitivity; //FS=00 + Normal mode, SENSITIVITY = 0.06 mg // mg

}


