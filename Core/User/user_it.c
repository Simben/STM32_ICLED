/*
 * user_it.c
 *
 *  Created on: Mar 21, 2025
 *      Author: Simon
 */

#include "sarmfsw.h"
#include "user_it.h"

extern uint8_t State;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim10)
	{
		HAL_GPIO_TogglePin(GPIO(LD2));
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint32_t tick = 0;
	if(GPIO_Pin  == B1_Pin)
	{
		if(TPSSUP_MS(tick, 500)) // debounce
		{
			State ++;
		}
	}


}
