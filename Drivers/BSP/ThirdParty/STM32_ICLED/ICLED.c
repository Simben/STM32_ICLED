/*
 * ICLED.c
 *
 *  Created on: Mar 21, 2025
 *      Author: Simon
 */

#include "sarmfsw.h"
#include "ICLED.h"
#include "ASCII_character.h"
#include <string.h>

#define MAX_SCREEN_ROWS		7
#define MAX_SCREEN_COLOMNS		15

//Spi clock Speed Set at 3.2Mhz == following patern works for what ever reason

#define ZEROPATTERN 0x08 // 4-bits
#define ONEPATTERN 0x0E //0x0C(if clock set at 2.8mhz)  // 4-bits

#define ZEROZEROPATTERN ((ZEROPATTERN << 4) | ZEROPATTERN) // 10001000
#define ZEROONEPATTERN ((ZEROPATTERN << 4) | ONEPATTERN)   // 10001100
#define ONEZEROPATTERN ((ONEPATTERN << 4) | ZEROPATTERN)   // 11001000
#define ONEONEPATTERN ((ONEPATTERN << 4) | ONEPATTERN)     // 11001100


#define ICLED_LATCHBYTECOUNT 100 // ~= 212 Microsecond latch
uint8_t SpiBufferLatch [ICLED_LATCHBYTECOUNT] = {0};

sPixel_GRB DisplayedScreen [MAX_SCREEN_ROWS * MAX_SCREEN_COLOMNS] = {0};

sExpandedPixel DisplayedScreenBufExp [MAX_SCREEN_ROWS * MAX_SCREEN_COLOMNS]; // 1 Color Byte expanded into 4 Bytes to spi


static void SendLatchCommand()
{
	HAL_SPI_Transmit(&hspi2, &SpiBufferLatch[0], ICLED_LATCHBYTECOUNT, 100);
}

//Static Functions
static void SendCompleteScreen()
{
	//allows need color for screnn
	SendLatchCommand();
	//shaould take aroud 1.5us per bit so 36us per pixel so 3.780ms per screen so 5ms time should be fine
	HAL_SPI_Transmit(&hspi2, &DisplayedScreenBufExp[0].buf[0], sizeof(DisplayedScreenBufExp), 5);
}


static void ColorByteToExpandedByte(uint8_t Value, uint8_t * const ptrPixelColor, uint8_t colorIdx)
{
	for (uint8_t bitIdx = 0; bitIdx < 4; bitIdx++)
	{
		switch ((Value << (2 * bitIdx)) & 0xC0)
		{ // mask upper two bit
		case 0x00:
			ptrPixelColor[4 * colorIdx + bitIdx] = ZEROZEROPATTERN;
			break;
		case 0x40:
			ptrPixelColor[4 * colorIdx + bitIdx] = ZEROONEPATTERN;
			break;
		case 0x80:
			ptrPixelColor[4 * colorIdx + bitIdx] = ONEZEROPATTERN;
			break;
		case 0xC0:
			ptrPixelColor[4 * colorIdx + bitIdx] = ONEONEPATTERN;
			break;
		}
	}
}

static void ComputeBufExpFromScreen()
{
	for(int col = 0; col < MAX_SCREEN_COLOMNS; col++ )
	{
		for(int row = 0; row < MAX_SCREEN_ROWS; row++)
		{
			for(int color = 0; color < ColorIdx_MAX; color++)
			{
				ColorByteToExpandedByte(
						DisplayedScreen[col * MAX_SCREEN_ROWS + row].Color[color],
						&DisplayedScreenBufExp[(col * MAX_SCREEN_ROWS + row)].buf[0],
						color
				);
			}
		}
	}
}







void transfertOnePixel(uint8_t R, uint8_t G, uint8_t B)
{
	//1 color = 8bits -> 4 Bytes expanded

	uint8_t PixelBuffer [4*3];
	ColorByteToExpandedByte(R,&PixelBuffer[0],ColorIdx_Red);
	ColorByteToExpandedByte(G,&PixelBuffer[0],ColorIdx_Green);
	ColorByteToExpandedByte(B,&PixelBuffer[0],ColorIdx_Blue);

	HAL_SPI_Transmit(&hspi2, &PixelBuffer[0], 12, 100);
	//HAL_SPI_Transmit(&hspi2, &PixelBuffer[0], 12, 100);
}




void IcScreen_Clear()
{
	//Clear the Display screen
	memset(DisplayedScreen, 0, sizeof(DisplayedScreen));
	//Clear the Bufexp by setting every values to 00
	//memset(DisplayedScreenBufExp, ZEROZEROPATTERN ,sizeof(DisplayedScreenBufExp));
}

void IcScreen_Draw()
{
	ComputeBufExpFromScreen();
	SendCompleteScreen();
}

bool IcScreen_SetPixelColor(uint8_t Row, uint8_t Col, uint8_t Red, uint8_t Green, uint8_t Blue)
{
	if(Row > MAX_SCREEN_ROWS) return false;
	if(Col > MAX_SCREEN_COLOMNS) return false;


	DisplayedScreen[Col * MAX_SCREEN_ROWS + Row] = (sPixel_GRB){.R =Red,.G =Green, .B =Blue };
	return true;
}

void IcScreen_FillRectange(uint8_t Row, uint8_t Col,uint8_t Width, uint8_t Height, uint8_t Red, uint8_t Green, uint8_t Blue)
{
	for(int j = Col; j < MIN(Col + Width, MAX_SCREEN_COLOMNS);j++)
	{
		for(int i = Row; i< MIN (Row + Height, MAX_SCREEN_ROWS); i++)
		{
			DisplayedScreen[j * MAX_SCREEN_ROWS + i] = (sPixel_GRB){.R =Red,.G =Green, .B =Blue };
		}
	}
}

void IcScreen_FillColomn( uint8_t Col,  uint8_t Red, uint8_t Green, uint8_t Blue)
{
	for(int i = 0; i< MAX_SCREEN_ROWS; i++)
	{
		DisplayedScreen[Col * MAX_SCREEN_ROWS + i] = (sPixel_GRB){.R =Red,.G =Green, .B =Blue };
	}
}

void IcScreen_DrawRectange(uint8_t Row, uint8_t Col,uint8_t Width, uint8_t Height, uint8_t Red, uint8_t Green, uint8_t Blue)
{
	uint8_t EndRow = MIN (Row + Height, MAX_SCREEN_ROWS) -1;
	uint8_t EndCol = MIN(Col + Width, MAX_SCREEN_COLOMNS) - 1;

	//Draw Left line
	//Draw Right line
	for(int i = Row; i< EndRow + 1; i++)
	{
		DisplayedScreen[Col * MAX_SCREEN_ROWS + i] = (sPixel_GRB){.R =Red,.G =Green, .B =Blue };
		DisplayedScreen[EndCol * MAX_SCREEN_ROWS + i] = (sPixel_GRB){.R =Red,.G =Green, .B =Blue };
	}

	for(int i = Col + 1; i< EndCol ; i++)
	{
		DisplayedScreen[i * MAX_SCREEN_ROWS + Row] = (sPixel_GRB){.R =Red,.G =Green, .B =Blue };
		DisplayedScreen[i * MAX_SCREEN_ROWS + EndRow] = (sPixel_GRB){.R =Red,.G =Green, .B =Blue };
	}
}

void IcScreen_DrawSymbol(const LED_Symbol* const pSymbol  , uint8_t Col, uint8_t Red, uint8_t Green, uint8_t Blue)
{
	for(int i = 0; i< MAX_PIXELS_PER_SYMBOL; i++)
	{
		if(pSymbol->pixel_locations[i].x == 0xFF && pSymbol->pixel_locations[i].y == 0xFF)
			return;
		if((Col + pSymbol->pixel_locations[i].x) < MAX_SCREEN_COLOMNS)
		{
			DisplayedScreen[(Col + pSymbol->pixel_locations[i].x) * MAX_SCREEN_ROWS + pSymbol->pixel_locations[i].y] = (sPixel_GRB){.R =Red,.G =Green, .B =Blue };
		}
	}
}

void IcScreen_DrawChar(char ascii, uint8_t Col, uint8_t Red, uint8_t Green, uint8_t Blue)
{
	IcScreen_DrawSymbol(&ASCII_CHARACTERS_ARRAY[(uint8_t)ascii], Col, Red, Green, Blue);
}

void IcScreen_DrawString(char * const pText, uint8_t Col, uint8_t Red, uint8_t Green, uint8_t Blue)
{
	uint8_t colOffset = 0;
	for(int i = 0; i< strlen(pText); i++)
	{
		IcScreen_DrawChar(pText[i], Col + colOffset, Red, Green, Blue);
		colOffset += ASCII_CHARACTERS_ARRAY[(uint8_t)pText[i]].symbol_width + 1;
	}
}





