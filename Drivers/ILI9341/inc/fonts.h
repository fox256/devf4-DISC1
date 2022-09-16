/*
 * fonts.h
 *
 *  Created on: Aug 29, 2022
 *      Author: Alexander
 */

#ifndef FONTS_H_
#define FONTS_H_


#include <stdint.h>
#include "ILI9341_GFX.h"
#include "../../Drivers/ILI9341/inc/FreeMono9pt7b.h"  // FF1 or FM9


#define FONT1	Arial_Narrow8x12
#define FONT2	Arial_Narrow10x13
#define FONT3	Arial_Narrow12x16
#define FONT4	Arial_Narrow15x19


extern const uint8_t Arial_Narrow8x12[];
extern const uint8_t Arial_Narrow10x13[];
extern const uint8_t Arial_Narrow12x16[];
extern const uint8_t Arial_Narrow15x19[];

typedef struct { // Data stored PER GLYPH
	uint32_t bitmapOffset;     // Pointer into GFXfont->bitmap
	uint8_t  width, height;    // Bitmap dimensions in pixels
	uint8_t  xAdvance;         // Distance to advance cursor (x axis)
	int8_t   xOffset, yOffset; // Dist from cursor pos to UL corner
} GFXglyph;

typedef struct { // Data stored for FONT AS A WHOLE:
	uint8_t  *bitmap;      // Glyph bitmaps, concatenated
	GFXglyph *glyph;       // Glyph array
	uint16_t  first, last; // ASCII extents
	uint8_t   yAdvance;    // Newline distance (y axis)
} GFXfont;




#endif /* FONTS_H_ */
