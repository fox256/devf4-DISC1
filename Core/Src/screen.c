/*
 * screen.c
 *
 *  Created on: Aug 29, 2022
 *      Author: Alexander
 */

#include "ILI9341.h"
#include "ILI9341_GFX.h"
#include "ds3231.h"
#include "fonts.h"
#include "GUI.h"
#include <stdlib.h>

#define CLOCK_Y 285
#define HOUR0_X	0
#define HOUR1_X 30
#define MIN0_X	93
#define MIN1_X	123
#define SEC0_X	185
#define SEC1_X	215


	  //GUI_DispCharAt('1',0,285);
	  //GUI_DispCharAt('6',30,285);


int temp_sec = 0;
char s[2] = {0};
char temp_s[2] = {0};


int temp_min = 0;
char m[2] = {0};
char temp_m[2] = {0};


void LCD_home_screen(void)
{
	  ILI9341_Init();//initial driver setup to drive ili9341
	  ILI9341_Fill_Screen(BLACK);
	  ILI9341_Draw_Hollow_Rectangle_Coord(0,0,110,60,YELLOW);
	  ILI9341_Draw_Hollow_Rectangle_Coord(129,0,239,60,YELLOW);
	  ILI9341_Draw_Text("Temp data ( C ):", 10, 10, WHITE, 1, BLACK);
	  ILI9341_Draw_Text("25.11", 10, 30, WHITE, 3, BLACK);
	  ILI9341_Draw_Text("10 11" ,2, 280, WHITE, 5, BLACK);

}

void LCD_Print_Time(uint8_t data_h, uint8_t data_m, uint8_t data_s)
{
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontD32);

	if(data_s != temp_sec)
	{
		temp_sec = data_s;
		itoa((int)data_s,s,10);
		if (data_s < 10)
		{
			GUI_DispCharAt('0',SEC0_X,CLOCK_Y);
			GUI_DispCharAt(s[0],SEC1_X,CLOCK_Y);
		}
		else
		{
			if (s[0] != temp_s[0])
			{
			GUI_DispCharAt(s[0],SEC0_X,CLOCK_Y);
			temp_s[0] = s[0];
			}
			if (s[1] != temp_s[1])
			{
				GUI_DispCharAt(s[1],SEC1_X,CLOCK_Y);
				temp_s[1] = s[1];
			}

		}
	}
//-----------------------------------------------------//
	if(data_m != temp_min)
	{
		temp_min = data_m;
		itoa((int)data_m, m , 10);
		if (data_m < 10)
		{
			GUI_DispCharAt('0',MIN0_X,CLOCK_Y);
			GUI_DispCharAt(m[0],MIN1_X,CLOCK_Y);
		}
		else
		{
			if (m[0] != temp_m[0])
			{
				GUI_DispCharAt(m[0],MIN0_X,CLOCK_Y);
				temp_m[0] = m[0];
			}
			if (m[1] != temp_m[1])
			{
				GUI_DispCharAt(m[1],MIN1_X,CLOCK_Y);
				temp_m[1] = m[1];
			}
		}

	}
//-----------------------------------------------------//

}



/*void LCD_update_time(void)
{
	sec = DS3231_Get_Sec();

	if(sec != temp_sec)
	{
		temp_sec = sec;
		itoa(sec,s,10);
		if (sec < 10)
		{
			drawChar(190,295,'0',WHITE,BLACK,3);
			drawChar(220,295,s[0],WHITE,BLACK,3);
		}
		else
		{
			if ( s[0] != temp_s[0] )
			{
			drawChar(190,295,s[0],WHITE,BLACK,3);
			}	temp_s[0] = s[0];

			if(s[1] != temp_s[1])
			{
				drawChar(220,295,s[1],WHITE,BLACK,3);
				temp_s[1] = s[1];
			}
		}

	  }

	drawChar(100,100,'a',WHITE,BLACK,2);

}*/





