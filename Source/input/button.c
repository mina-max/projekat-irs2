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
#include "snake.h"
#include "project-irs2.h"

static xTimerHandle debouncing_timer = NULL;

static bool debouncing_time_passed = true;

static void button_pressed_start_game()
{
	game_start();
}

static void button_pressed_toggle_grid()
{
	game_toogle_grid();
}

static void button_pressed_change_snake_direction(snake_directions_t direction)
{
	snake_change_direction(direction);
}

static void debouncing_timer_callback()
{
	debouncing_time_passed = true;
}

static void button_callback(uint16_t pin)
{
	if(pin == SW2_Pin)
	{
		button_pressed_start_game();
	}
	else if(pin == SW1_Pin)
	{
		button_pressed_toggle_grid();
	}
	else if(pin == UP_Pin)
	{
		button_pressed_change_snake_direction(UP);
	}
	else if(pin == RIGHT_Pin)
	{
		button_pressed_change_snake_direction(RIGHT);
	}
	else if(pin == DOWN_Pin)
	{
		button_pressed_change_snake_direction(DOWN);
	}
	else if(pin == LEFT_Pin)
	{
		button_pressed_change_snake_direction(LEFT);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(debouncing_time_passed)
	{
		button_callback(GPIO_Pin);
		debouncing_time_passed = false;
		xTimerStartFromISR(debouncing_timer, 0);
	}
}

void button_init()
{
	debouncing_timer = xTimerCreate((const char*) "debouncing_timer",
			60 / portTICK_RATE_MS,
			pdFALSE, (void*) 0, debouncing_timer_callback);

}
