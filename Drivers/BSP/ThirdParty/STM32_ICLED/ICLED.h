/*
 * ICLED.h
 *
 *  Created on: Mar 21, 2025
 *      Author: Simon
 */

#ifndef __ICLED_ICLED_H_
#define __ICLED_ICLED_H_

#include "led_symbol.h"

#define MAX_SCREEN_ROWS		7
#define MAX_SCREEN_COLOMNS		15

typedef enum
{
	ColorIdx_Green,
	ColorIdx_Red,
	ColorIdx_Blue,
	ColorIdx_MAX
}eColorIndex;

typedef struct
{
	union
	{
		uint8_t Color [3];
		struct
		{
			uint8_t G;
			uint8_t R;
			uint8_t B;
		};
	};
}sPixel_GRB;


typedef union
{
	uint8_t buf [12];
	struct
	{
		uint32_t ExpGreen;
		uint32_t ExpRed;
		uint32_t ExpBlue;
	};
	struct
	{
		uint8_t Msb_G01;
		uint8_t Msb_G23;
		uint8_t Msb_G45;
		uint8_t Msb_G67;
		uint8_t Msb_R01;
		uint8_t Msb_R23;
		uint8_t Msb_R45;
		uint8_t Msb_R67;
		uint8_t Msb_B01;
		uint8_t Msb_B23;
		uint8_t Msb_B45;
		uint8_t Msb_B67;
	};
}sExpandedPixel;

extern sPixel_GRB DisplayedScreen [MAX_SCREEN_ROWS * MAX_SCREEN_COLOMNS];

//void transfertOnePixel(uint8_t R, uint8_t G, uint8_t B);
//void SendLatchCommand();

void IcScreen_Clear();
void IcScreen_Draw();
bool IcScreen_SetPixelColor(uint8_t Row, uint8_t Col, uint8_t Red, uint8_t Green, uint8_t Blue);
void IcScreen_FillRectange(uint8_t Row, uint8_t Col,uint8_t Width, uint8_t Height, uint8_t Red, uint8_t Green, uint8_t Blue);
void IcScreen_FillColomn( uint8_t Col,  uint8_t Red, uint8_t Green, uint8_t Blue);
void IcScreen_DrawRectange(uint8_t Row, uint8_t Col,uint8_t Width, uint8_t Height, uint8_t Red, uint8_t Green, uint8_t Blue);
void IcScreen_DrawSymbol(const LED_Symbol* const pSymbol  , uint8_t Col, uint8_t Red, uint8_t Green, uint8_t Blue);
void IcScreen_DrawChar(char ascii, uint8_t Col, uint8_t Red, uint8_t Green, uint8_t Blue);
void IcScreen_DrawString(char * const pText, uint8_t Col, uint8_t Red, uint8_t Green, uint8_t Blue);
#endif /* THIRDPARTY_STM32_ICLED_ICLED_H_ */
