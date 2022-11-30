/*
 * button.c
 *
 *  Created on: Nov 30, 2022
 *      Author: mira
 */
#include "main.h"
#include "display.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if(GPIO_Pin == SW2_Pin)
	{
		display_state_button_pressed();
	}
	else if(GPIO_Pin == SW1_Pin)
	{
		display_state_button_pressed();
	}
}

void button_init()
{

}
