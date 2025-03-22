/*
 * user_loop.c
 *
 *  Created on: Mar 21, 2025
 *      Author: Simon
 */

#include "sarmfsw.h"
#include "user_loop.h"
#include "ICLED.h"
#include "ICLED_Ex.h"

uint8_t State = 12;

uint8_t Animation_Step = 0;
bool Animation_Started = 0;

void user_loop()
{

	static uint32_t tick = 0;
	if(TPSSUP_MS(tick, 20))
	{
		tick = HAL_GetTick();

		switch(State)
		{
		case 0:
			IcScreen_Clear();
			IcScreen_SetPixelColor(3, 7, 0xFF, 0x00, 0x00);
			break;
		case 1:
			IcScreen_Clear();
			IcScreen_SetPixelColor(3, 7, 0x00, 0xFF, 0x00);
			break;
		case 2:
			IcScreen_Clear();
			IcScreen_SetPixelColor(3, 7, 0x00, 0x00, 0xFF);
			break;
		case 3:
			IcScreen_Clear();
			IcScreen_SetPixelColor(3, 7, 0xFF, 0xFF, 0xFF);
			break;
		case 4:
			IcScreen_Clear();
			IcScreen_SetPixelColor(3, 7, 0x00, 0xFF, 0xFF);
			break;
		case 5:
			IcScreen_Clear();
			IcScreen_SetPixelColor(3, 7, 0xFF, 0x00, 0xFF);
			break;
		case 6:
			IcScreen_Clear();
			IcScreen_SetPixelColor(3, 7, 0xFF, 0xFF, 0x00);
			break;
		case 7:
			IcScreen_Clear();
			IcScreen_DrawRectange(0,0,3,4,0x20,0x20,0x00);
			break;
		case 8:
			IcScreen_Clear();
			IcScreen_DrawString("led", 0, 0x00, 0x00, 0x20);
			break;
		case 9:
			IcScreen_Clear();
			IcScreenEx_FillHSV(0.8f, 0.05f);
			break;
		case 10:
			IcScreen_Clear();
			IcScreenEx_FillHSV(0.8f, 0.5f);
			break;
		case 11:
			IcScreen_Clear();
			IcScreenEx_FillHSV(0.0f, 1.0f);
			break;
		case 12:
			if(!Animation_Started)
			{
				Animation_Step = 0;
				Animation_Started = true;
			}
			IcScreen_Clear();
			if(Animation_Step >= 28)
			{
				Animation_Step = 0x00;
			}

			if(Animation_Step < 14)
			{
				IcScreen_FillColomn(Animation_Step, 0x7F, 0x00, 0x00);
			}
			else
			{
				IcScreen_FillColomn(14 - (Animation_Step % 14) , 0x7F, 0x00, 0x00);
			}


			break;
		default :
			Animation_Started = false;
			State = 0x00;
			break;

		}
		Animation_Step++;
		IcScreen_Draw();


	}


}
