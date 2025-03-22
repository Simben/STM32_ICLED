/*
 * emoji_symbol.h
 *
 *  Created on: Mar 21, 2025
 *      Author: Simon
 */

#ifndef __EMOJI_SYMBOL_H_
#define __EMOJI_SYMBOL_H_

#include "led_symbol.h"
//#include "ICLED.h"

#define MAX_EMOJI_WIDTH 6


typedef enum
{
	 Emoji_Smile_Face,
	 Emoji_Frown_Face,
	 Emoji_Neutral_Face,
	 Emoji_Tongue_Face,
	 Emoji_Check_Mark,
	 Emoji_Heart,
	 Emoji_Droplet,
	 Emoji_Total_Count
}eSmileyType;

extern const LED_Symbol EMOJI_ARRAY[Emoji_Total_Count];

#endif /* THIRDPARTY_STM32_ICLED_EMOJI_SYMBOL_H_ */
