/*
 * button.c
 *
 *  Created on: Nov 30, 2022
 *      Author: mira
 */
#include "main.h"
#include "display.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "stdbool.h"

static xTimerHandle debouncing_timer = NULL;

static void debouncing_timer_callback()
{
	display_state_button_pressed();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	xTimerStartFromISR(debouncing_timer, 0);
}

void button_init()
{
	debouncing_timer = xTimerCreate((const char*) "debouncing_timer",
			80 / portTICK_RATE_MS,
			pdFALSE, (void*) 0, debouncing_timer_callback);

}
