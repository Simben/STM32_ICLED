/*
 * led_symbols.h
 *
 *  Created on: Mar 21, 2025
 *      Author: Simon
 */

#ifndef __LED_SYMBOL_H_
#define __LED_SYMBOL_H_

#define MAX_PIXELS_PER_SYMBOL ((7 * 6) + 1) // 7 rows * 6 columns + 1 for pixel end

#define PIXEL_LOCATION_END \
    {                      \
        0xFF, 0XFF         \
    }

typedef struct
{
    struct
    {
        uint8_t x;
        uint8_t y;
    } pixel_locations[MAX_PIXELS_PER_SYMBOL];
    uint8_t symbol_width;
} LED_Symbol;


#endif /* __THIRDPARTY_STM32_ICLED_LED_SYMBOLS_H_ */
