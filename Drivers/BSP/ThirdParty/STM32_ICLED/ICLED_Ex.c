/*
 * ICLED.c
 *
 *  Created on: Mar 21, 2025
 *      Author: Simon
 */

#include "sarmfsw.h"
#include "ICLED.h"
#include "ICLED_Ex.h"


// Function to convert HSV to RGB with values scaled between 0 and 25
static void HSVtoRGB(float h, float s, float v, uint8_t *r, uint8_t *g, uint8_t *b) {
    float c = v * s;
    float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    float m = v - c;
    float r1, g1, b1;

    if (h >= 0 && h < 60) {
        r1 = c, g1 = x, b1 = 0;
    } else if (h >= 60 && h < 120) {
        r1 = x, g1 = c, b1 = 0;
    } else if (h >= 120 && h < 180) {
        r1 = 0, g1 = c, b1 = x;
    } else if (h >= 180 && h < 240) {
        r1 = 0, g1 = x, b1 = c;
    } else if (h >= 240 && h < 300) {
        r1 = x, g1 = 0, b1 = c;
    } else {
        r1 = c, g1 = 0, b1 = x;
    }

    // Scale RGB values to 0-25 range
    *r = (uint8_t)((r1 + m) * 255);
    *g = (uint8_t)((g1 + m) * 255);
    *b = (uint8_t)((b1 + m) * 255);
}


void IcScreenEx_FillHSV(float Min_Saturation, float Value)
{
	uint8_t R, G, B;
	for(int j = 0; j< MAX_SCREEN_COLOMNS; j++)
	{
		for(int i = 0; i< MAX_SCREEN_ROWS; i++)
		{
			HSVtoRGB(360.0f / (float)MAX_SCREEN_COLOMNS * (float)j, (1.0f - Min_Saturation) / 7.0f * (float)i + Min_Saturation, Value, &R, &G, &B);
			IcScreen_SetPixelColor(i, j, R, G, B);
		}
	}
}

