 /*
 * project-irs2.c
 *
 *  Created on: Nov 29, 2022
 *      Author: mira
 */

#include "stdbool.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include "main.h"
#include "display.h"
#include "seven_segment_display.h"
#include "snake.h"
#include "button.h"
#include "em_flash.h"
#include "string.h"

#define WELCOME_SCREEN_TIMER_MS 3000
#define START_SPEED				250

typedef enum {
	GAME_STATE_INIT,
	GAME_STATE_WELCOME_SCREEN,
	GAME_STATE_START_GAME,
	GAME_STATE_IN_PROGRESS,
	GAME_STATE_GAME_OVER
} game_states_t;

static xTimerHandle welcome_screen_timer = NULL;

static game_states_t game_state = GAME_STATE_INIT;
static game_states_t new_game_state = GAME_STATE_WELCOME_SCREEN;

static uint8_t current_score = 0;
static uint64_t high_score = 0;

static bool grid = false;
static bool new_highscore = false;

static uint16_t speed = START_SPEED;

static void game_state_machine_update()
{
	switch (game_state)
	{
	case GAME_STATE_WELCOME_SCREEN:
		display_welcome_screen();
		xTimerStart(welcome_screen_timer, 0);
		break;
	case GAME_STATE_START_GAME:
		display_start_game_screen();
		break;
	case GAME_STATE_GAME_OVER:
		display_game_over(new_highscore);
		new_highscore = false;
		current_score = 0;
		speed = START_SPEED;
		snake_reset();
		break;
	default:
		break;
	}
}

static void display_welcome_screen_timer_callback()
{
	new_game_state = GAME_STATE_START_GAME;
}

void game_increase_score()
{
	current_score++;
	speed-=5;
}

void game_toogle_grid()
{
	if(game_state == GAME_STATE_IN_PROGRESS)
	{
		grid = !grid;
	}
}

void game_start()
{
	if(game_state == GAME_STATE_START_GAME || game_state == GAME_STATE_GAME_OVER)
	{
		new_game_state = GAME_STATE_IN_PROGRESS;
	}
}

void game_over()
{
	new_game_state = GAME_STATE_GAME_OVER;
	if(current_score > high_score)
	{
		new_highscore = true;
		high_score = current_score;
		flash_write(high_score);
	}
}

uint8_t game_get_score()
{
	return current_score;
}

uint8_t game_get_highscore()
{
	return (uint8_t)high_score;
}

void vGameTask()
{
	memcpy(&high_score, (void*)ADDR_FLASH_PAGE_511, 8);
	if(high_score == 0xffffffffffffffff)
	{
		high_score = 0;
	}
	while(1)
	{
		if (game_state != new_game_state)
		{
			game_state = new_game_state;
			game_state_machine_update();
		}
		if(game_state == GAME_STATE_IN_PROGRESS)
		{
			move_snake();
			display_draw_snake(grid, get_snake());
			display_draw_apple(get_apple_position());
			vTaskDelay(speed);
		}
		display_update();
	}
}

void vDisplayScoreTask()
{
	while (1)
	{
		if(game_state == GAME_STATE_IN_PROGRESS)
		{
			seven_seg_display_number(current_score);
		}
		else
		{
			seven_seg_display_number(high_score);
		}

	}
}

void project_main(void)
{
	display_init();
	button_init();

	welcome_screen_timer = xTimerCreate((const char*) "welcome_screen_timer",
		WELCOME_SCREEN_TIMER_MS / portTICK_RATE_MS,
		pdFALSE, (void*) 0, display_welcome_screen_timer_callback);

	xTaskCreate(vGameTask, "game_task", configMINIMAL_STACK_SIZE, NULL,
				(tskIDLE_PRIORITY + 1UL), NULL);
	xTaskCreate(vDisplayScoreTask, "display_score_task", configMINIMAL_STACK_SIZE, NULL,
					(tskIDLE_PRIORITY + 1UL), NULL);
}
