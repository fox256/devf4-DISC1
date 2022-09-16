/*
 * ILI9341.h
 *
 *  Created on: Aug 13, 2022
 *      Author: Alexander
 */

#ifndef SRC_ILI9341_ILI9341_H_
#define SRC_ILI9341_ILI9341_H_

#include "config.h"
//#include "stm32f4xx_hal_spi.h"

//SPI INSTANCE
#define HSPI_INSTANCE	SPI2


#define ILI9341_SCREEN_HEIGHT	240
#define ILI9341_SCREEN_WIDTH	320

//0x0001 = port 0 PB0
#define LCD_CS_Disable	GPIOB->BSRR |= 0x0001		//1
#define LCD_CS_Enable	GPIOB->BSRR |= (0x0001<<16)	//0

//0x0002 = port 1 PB1
#define LCD_DC_Com		GPIOB->BSRR |= (0x0002<<16)	//DC = 0 command
#define LCD_DC_Data		GPIOB->BSRR |= 0x0002		//DC = 1 data

//0x0010 = port 4 PB4
#define	LCD_RESET_ON	GPIOB->BSRR |= (0x0010<<16) //0
#define	LCD_RESET_OFF	GPIOB->BSRR |= 0x0010		//1

//0x0020 = port 5 PB5
#define	LCD_LED_ON		GPIOB->BSRR |= 0x0020	    //1
#define	LCD_LEF_OFF		GPIOB->BSRR |= (0x0020<<16)	//0

#define BURST_MAX_SIZE 	500

#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F

#define SCREEN_VERTICAL_1		0
#define SCREEN_HORIZONTAL_1		1
#define SCREEN_VERTICAL_2		2
#define SCREEN_HORIZONTAL_2		3


void ILI9341_SPI_Init(void);
void ILI9341_SPI_Send16(uint16_t dat);
void ILI9341_Set_Rotation(uint8_t Rotation);
void ILI9341_Enable(void);
void ILI9341_Init(void);
void ILI9341_Write_Data(uint8_t Data);
void ILI9341_Write_Command(uint8_t Command);
void ILI9341_Fill_Screen(uint16_t Colour);
void ILI9341_Draw_Pixel(uint16_t X,uint16_t Y,uint16_t Colour);
void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size);

void ILI9341_Draw_Rectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour);
void ILI9341_Draw_Horizontal_Line(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Colour);
void ILI9341_Draw_Vertical_Line(uint16_t X, uint16_t Y, uint16_t Height, uint16_t Colour);

#endif /* SRC_ILI9341_ILI9341_H_ */
