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

#define WELCOME_SCREEN_TIMER_MS 3000

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

static uint16_t current_score = 0;
static uint16_t high_score = 0;

static bool grid = false;

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
//		case GAME_STATE_IN_PROGRESS:
//			display_update_screen();
//			break;
		//	case DISPLAY_STATE_SCORE:
		//		break;
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
}

void game_toogle_grid()
{
	grid = !grid;
}

void game_start()
{
	new_game_state = GAME_STATE_IN_PROGRESS;
}

void vGameTask()
{
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
			HAL_Delay(100);
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
