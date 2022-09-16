/*
 * ILI9341.c
 *
 *  Created on: Aug 13, 2022
 *      Author: Alexander
 *
 *      Connection:
 *      SPI2_MOSI -> PB15
 *      SPI2_MISO -> PB14
 *      SPI2_SCK  -> PB13
 *      LCD_CS	  -> PB0
 *      LCD_DC	  -> PB1
 *      LCD_RESET -> PB4
 *      LCD_LED	  -> PB5
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "../../Drivers/ILI9341/inc/ILI9341.h"

/* Global Variables ------------------------------------------------------------------*/
volatile uint16_t LCD_HEIGHT = ILI9341_SCREEN_HEIGHT;
volatile uint16_t LCD_WIDTH	 = ILI9341_SCREEN_WIDTH;

//void ILI9341_SPI_Send(unsigned char TxData);

/* Initialize SPI */
void ILI9341_SPI_Init(void)
{
	  SPI2->CR2 |= SPI_CR2_SSOE;
	  SPI2->CR1 |= SPI_CR1_SPE; // Enable SPI1
	  LCD_CS_Disable;			//CS OFF
}
void ILI9341_SPI_Send16(uint16_t dat)
{
	while(!((SPI2->SR)&(SPI_SR_TXE)));

	dat = (((dat & 0x00FF) << 8) | ((dat & 0xFF00) >> 8));
	/**(uint16_t*)&(SPI2->DR) = dat;*/

	LL_SPI_TransmitData16(SPI2,dat);

	while(!((SPI2->SR)&(SPI_SR_TXE)));		//Check Tx Buffer Empty Flag
	(void)SPI2->SR; //Dummy read

}

/*Send data (char) to LCD*/
void ILI9341_SPI_Send(unsigned char TxData)
{
	while(!((SPI2->SR)&(SPI_SR_TXE))); 		//Check Tx Buffer Empty Flag
	//__IO uint8_t *spidr = ((__IO uint8_t *)&SPI2->DR);	//Put data to DR register
	//*spidr = TxData;
	*(uint8_t*)&(SPI2->DR) = TxData;
	//*(uint8_t*)&(SPIx->DR) = TxData;

	while(!((SPI2->SR)&(SPI_SR_TXE)));		//Check Tx Buffer Empty Flag
	//while (((SPI2->SR)&(SPI_SR_BSY)));		//Check SPI Not Busy Flag
	//Clear the Overrun flag by reading DR and SR
	//(void)SPI2->DR; //Dummy read
	(void)SPI2->SR; //Dummy read
	//while(!((SPI2->SR)&(SPI_SR_TXE)));		//Check Tx Buffer Empty Flag
}

/* Send command (char) to LCD */
void ILI9341_Write_Command(uint8_t Command)
{
	LCD_CS_Enable;
	LCD_DC_Com;
	ILI9341_SPI_Send(Command);
	LCD_CS_Disable;
}

/* Send Data (char) to LCD */
void ILI9341_Write_Data(uint8_t Data)
{
	LCD_CS_Enable;
	LCD_DC_Data;
	ILI9341_SPI_Send(Data);
	LCD_CS_Disable;
}

/* Set Address - Location block - to draw into */
void ILI9341_Set_Address(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	LCD_CS_Enable;

	LCD_DC_Com;
	ILI9341_SPI_Send(0x2A);
	LCD_DC_Data;
//	ILI9341_SPI_Send16(X1);
//	ILI9341_SPI_Send16(X2);
	ILI9341_SPI_Send(X1>>8);
	ILI9341_SPI_Send(X1);
	ILI9341_SPI_Send(X2>>8);
	ILI9341_SPI_Send(X2);

	LCD_DC_Com;
	ILI9341_SPI_Send(0x2B);
	LCD_DC_Data;
	ILI9341_SPI_Send(Y1>>8);
	ILI9341_SPI_Send(Y1);
	ILI9341_SPI_Send(Y2>>8);
	ILI9341_SPI_Send(Y2);


	LCD_DC_Com;
	ILI9341_SPI_Send(0x2C);

	LCD_CS_Disable;
}

/*HARDWARE RESET*/
void ILI9341_Reset(void)
{
	LCD_RESET_ON;
	HAL_Delay(200);
	LCD_CS_Enable;
	HAL_Delay(200);
	LCD_RESET_OFF;
}

/*Set rotation of the screen - changes x0 and y0*/
void ILI9341_Set_Rotation(uint8_t Rotation)
{
	uint8_t screen_rotation = Rotation;

	ILI9341_Write_Command(0x36);
	HAL_Delay(1);

	switch(screen_rotation)
	{
		case SCREEN_VERTICAL_1:
			ILI9341_Write_Data(0x40|0x08);
			LCD_WIDTH = 240;
			LCD_HEIGHT = 320;
			break;
		case SCREEN_HORIZONTAL_1:
			ILI9341_Write_Data(0x20|0x08);
			LCD_WIDTH  = 320;
			LCD_HEIGHT = 240;
			break;
		case SCREEN_VERTICAL_2:
			ILI9341_Write_Data(0x80|0x08);
			LCD_WIDTH  = 240;
			LCD_HEIGHT = 320;
			break;
		case SCREEN_HORIZONTAL_2:
			ILI9341_Write_Data(0x40|0x80|0x20|0x08);
			LCD_WIDTH  = 320;
			LCD_HEIGHT = 240;
			break;
		default:
			//EXIT IF SCREEN ROTATION NOT VALID!
			break;
	}
}

/*Enable LCD display*/
void ILI9341_Enable(void)
{
	LCD_RESET_OFF;
	//LCD_LED_ON;
}

/*Initialize LCD display*/
void ILI9341_Init(void)
{
	ILI9341_Enable();
	ILI9341_SPI_Init();
	ILI9341_Reset();

	//SOFTWARE RESET
	ILI9341_Write_Command(0x01);
	HAL_Delay(10);

	//POWER CONTROL A
	ILI9341_Write_Command(0xCB);
	ILI9341_Write_Data(0x39);
	ILI9341_Write_Data(0x2C);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x34);
	ILI9341_Write_Data(0x02);

	//POWER CONTROL B
	ILI9341_Write_Command(0xCF);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0xC1);
	ILI9341_Write_Data(0x30);

	//DRIVER TIMING CONTROL A
	ILI9341_Write_Command(0xE8);
	ILI9341_Write_Data(0x85);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x78);

	//DRIVER TIMING CONTROL B
	ILI9341_Write_Command(0xEA);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x00);

	//POWER ON SEQUENCE CONTROL
	ILI9341_Write_Command(0xED);
	ILI9341_Write_Data(0x64);
	ILI9341_Write_Data(0x03);
	ILI9341_Write_Data(0x12);
	ILI9341_Write_Data(0x81);

	//PUMP RATIO CONTROL
	ILI9341_Write_Command(0xF7);
	ILI9341_Write_Data(0x20);

	//POWER CONTROL,VRH[5:0]
	ILI9341_Write_Command(0xC0);
	ILI9341_Write_Data(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	ILI9341_Write_Command(0xC1);
	ILI9341_Write_Data(0x10);
	//ILI9341_Write_Data(0x11);

	//VCM CONTROL
	ILI9341_Write_Command(0xC5);
	//ILI9341_Write_Data(0x3E);
	//ILI9341_Write_Data(0x28);
	ILI9341_Write_Data(0x30);
	ILI9341_Write_Data(0x30);

	//VCM CONTROL 2
	ILI9341_Write_Command(0xC7);
	ILI9341_Write_Data(0x87);

	//MEMORY ACCESS CONTROL
	ILI9341_Write_Command(0x36);
	ILI9341_Write_Data(0x48);

	//Vertical Scrolling Start Address
	ILI9341_Write_Command(0x37);
	ILI9341_Write_Data(0x00);

	//PIXEL FORMAT
	ILI9341_Write_Command(0x3A);
	ILI9341_Write_Data(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	ILI9341_Write_Command(0xB1);
	LCD_DC_Data;
	LCD_CS_Enable;
	ILI9341_SPI_Send(0x00);
	//ILI9341_Write_Data(0x00);
	//ILI9341_Write_Data(0x1A);
	ILI9341_SPI_Send(0x18);
	LCD_CS_Disable;


	//DISPLAY FUNCTION CONTROL
	ILI9341_Write_Command(0xB6);
	ILI9341_Write_Data(0x08);
	ILI9341_Write_Data(0x82);
	ILI9341_Write_Data(0x27);

	//3GAMMA FUNCTION DISABLE
	ILI9341_Write_Command(0xF2);
	ILI9341_Write_Data(0x00);

	//GAMMA CURVE SELECTED
	ILI9341_Write_Command(0x26);
	ILI9341_Write_Data(0x01);

	//POSITIVE GAMMA CORRECTION
	ILI9341_Write_Command(0xE0);
	ILI9341_Write_Data(0x0F);
	ILI9341_Write_Data(0x31);
	ILI9341_Write_Data(0x2B);
	ILI9341_Write_Data(0x0C);
	ILI9341_Write_Data(0x0E);
	ILI9341_Write_Data(0x08);
	ILI9341_Write_Data(0x4E);
	ILI9341_Write_Data(0xF1);
	ILI9341_Write_Data(0x37);
	ILI9341_Write_Data(0x07);
	ILI9341_Write_Data(0x10);
	ILI9341_Write_Data(0x03);
	ILI9341_Write_Data(0x0E);
	ILI9341_Write_Data(0x09);
	ILI9341_Write_Data(0x00);

	//NEGATIVE GAMMA CORRECTION
	ILI9341_Write_Command(0xE1);
	ILI9341_Write_Data(0x00);
	ILI9341_Write_Data(0x0E);
	ILI9341_Write_Data(0x14);
	ILI9341_Write_Data(0x03);
	ILI9341_Write_Data(0x11);
	ILI9341_Write_Data(0x07);
	ILI9341_Write_Data(0x31);
	ILI9341_Write_Data(0xC1);
	ILI9341_Write_Data(0x48);
	ILI9341_Write_Data(0x08);
	ILI9341_Write_Data(0x0F);
	ILI9341_Write_Data(0x0C);
	ILI9341_Write_Data(0x31);
	ILI9341_Write_Data(0x36);
	ILI9341_Write_Data(0x0F);

	//EXIT SLEEP
	ILI9341_Write_Command(0x11);
	HAL_Delay(120);

	//TURN ON DISPLAY
	ILI9341_Write_Command(0x29);

	//STARTING ROTATION
	ILI9341_Set_Rotation(SCREEN_VERTICAL_1);
}

//INTERNAL FUNCTION OF LIBRARY, USAGE NOT RECOMENDED, USE Draw_Pixel INSTEAD
/*Sends single pixel colour information to LCD
void ILI9341_Draw_Colour(uint16_t Colour)
{
//SENDS COLOUR
unsigned char TempBuffer[2] = {Colour>>8, Colour};
HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
HAL_SPI_Transmit(HSPI_INSTANCE, TempBuffer, 2, 1);
HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}*/

//INTERNAL FUNCTION OF LIBRARY
/*Sends block colour information to LCD*/
void ILI9341_Draw_Colour_Burst(uint16_t Colour, uint32_t Size)
{
	//SENDS COLOUR
	uint32_t Buffer_Size = 0;
	if((Size*2) < BURST_MAX_SIZE)
	{
		Buffer_Size = Size;
	}
	else
	{
		Buffer_Size = BURST_MAX_SIZE;
	}

	LCD_DC_Data;//HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	LCD_CS_Enable;//HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

	unsigned char chifted = Colour>>8;;
	unsigned char burst_buffer[Buffer_Size];
	for(uint32_t j = 0; j < Buffer_Size; j+=2)
	{
		burst_buffer[j] = 	chifted;
		burst_buffer[j+1] = Colour;
	}

	uint32_t Sending_Size = Size * 2;
	uint32_t Sending_in_Block = Sending_Size / Buffer_Size;
	uint32_t Remainder_from_block = Sending_Size % Buffer_Size;

	if(Sending_in_Block != 0)
	{
		for(uint32_t j = 0; j < (Sending_in_Block); j++)
		{
		//HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Buffer_Size, 10);
			for (uint16_t i = 0; i < Buffer_Size; i++ )
			{
				ILI9341_SPI_Send(burst_buffer[i]);
			}
		}
	}
	//REMAINDER!
	//HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Remainder_from_block, 10);
	for (uint16_t r = 0; r < Remainder_from_block; r++)
	{
		ILI9341_SPI_Send(burst_buffer[r]);
	}
	LCD_CS_Disable;//HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

//FILL THE ENTIRE SCREEN WITH SELECTED COLOUR (either #define-d ones or custom 16bit)
/*Sets address (entire screen) and Sends Height*Width ammount of colour information to LCD*/
void ILI9341_Fill_Screen(uint16_t Colour)
{
	ILI9341_Set_Address(0,0,LCD_WIDTH,LCD_HEIGHT);
	ILI9341_Draw_Colour_Burst(Colour, LCD_WIDTH*LCD_HEIGHT);
}

//DRAW PIXEL AT XY POSITION WITH SELECTED COLOUR
//
//Location is dependant on screen orientation. x0 and y0 locations change with orientations.
//Using pixels to draw big simple structures is not recommended as it is really slow
//Try using either rectangles or lines if possible
//
void ILI9341_Draw_Pixel(uint16_t X,uint16_t Y,uint16_t Colour)
{
	if((X >=LCD_WIDTH) || (Y >=LCD_HEIGHT)) return;	//OUT OF BOUNDS!

	uint8_t bufferX[4] = {X>>8, X, (X+1)>>8, (X+1)};
	uint8_t bufferY[4] = {Y>>8, Y, (Y+1)>>8, (Y+1)};
	uint8_t bufferC[2] = {Colour>>8, Colour};

	//ADDRESS
	LCD_CS_Enable;

	LCD_DC_Com;
	ILI9341_SPI_Send(0x2A);

	LCD_DC_Data;
	ILI9341_SPI_Send(bufferX[0]);
	ILI9341_SPI_Send(bufferX[1]);
	ILI9341_SPI_Send(bufferX[2]);
	ILI9341_SPI_Send(bufferX[3]);

	//ADDRESS
	LCD_DC_Com;
	ILI9341_SPI_Send(0x2B);

	LCD_DC_Data;
	ILI9341_SPI_Send(bufferY[0]);
	ILI9341_SPI_Send(bufferY[1]);
	ILI9341_SPI_Send(bufferY[2]);
	ILI9341_SPI_Send(bufferY[3]);


	//ADDRESS
	LCD_DC_Com;
	ILI9341_SPI_Send(0x2C);

	//COLOUR
	LCD_DC_Data;

	ILI9341_SPI_Send(bufferC[0]);
	ILI9341_SPI_Send(bufferC[1]);
	//ILI9341_SPI_Send16(Colour);
	//ILI9341_SPI_Send16( (uint16_t)(bufferC[0]<<8) | (uint16_t)bufferC[1] );
	LCD_CS_Disable;

}

//DRAW RECTANGLE OF SET SIZE AND HEIGTH AT X and Y POSITION WITH CUSTOM COLOUR
//
//Rectangle is hollow. X and Y positions mark the upper left corner of rectangle
//As with all other draw calls x0 and y0 locations dependant on screen orientation
//
void ILI9341_Draw_Rectangle(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Height, uint16_t Colour)
{
	if((X >=LCD_WIDTH) || (Y >=LCD_HEIGHT)) return;
	if((X+Width-1)>=LCD_WIDTH)
		{
			Width=LCD_WIDTH-X;
		}
	if((Y+Height-1)>=LCD_HEIGHT)
		{
			Height=LCD_HEIGHT-Y;
		}
	ILI9341_Set_Address(X, Y, X+Width-1, Y+Height-1);
	ILI9341_Draw_Colour_Burst(Colour, Height*Width);
}
//DRAW LINE FROM X,Y LOCATION to X+Width,Y LOCATION
void ILI9341_Draw_Horizontal_Line(uint16_t X, uint16_t Y, uint16_t Width, uint16_t Colour)
{
	if((X >=LCD_WIDTH) || (Y >=LCD_HEIGHT)) return;
	if((X+Width-1)>=LCD_WIDTH)
		{
			Width=LCD_WIDTH-X;
		}
	ILI9341_Set_Address(X, Y, X+Width-1, Y);
	ILI9341_Draw_Colour_Burst(Colour, Width);
}

//DRAW LINE FROM X,Y LOCATION to X,Y+Height LOCATION
void ILI9341_Draw_Vertical_Line(uint16_t X, uint16_t Y, uint16_t Height, uint16_t Colour)
{
	if((X >=LCD_WIDTH) || (Y >=LCD_HEIGHT)) return;
	if((Y+Height-1)>=LCD_HEIGHT)
		{
			Height=LCD_HEIGHT-Y;
		}
	ILI9341_Set_Address(X, Y, X, Y+Height-1);
	ILI9341_Draw_Colour_Burst(Colour, Height);
}






