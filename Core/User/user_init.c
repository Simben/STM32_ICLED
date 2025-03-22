/*
 * user_init.c
 *
 *  Created on: Mar 21, 2025
 *      Author: Simon
 */

#include "sarmfsw.h"
#include "user_init.h"

#include "TIM_ex.h"
#include "ICLED.h"


void user_init()
{
	init_TIM_Base(&htim10, 1);

	IcScreen_Clear();
	IcScreen_Draw();
}
