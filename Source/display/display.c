/*
 * display.c
 *
 *  Created on: Nov 30, 2022
 *      Author: mira
 */

#include "display.h"
#include "ssd1306.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"
#include "seven_segment_display.h"


#define WELCOME_SCREEN_TIMER_MS 3000

extern unsigned char snake_128x64[];

display_states_t display_state = DISPLAY_STATE_WELCOME;
display_states_t new_display_state = DISPLAY_STATE_WELCOME;

static xTimerHandle welcome_screen_timer = NULL;

static void show_welcome_screen()
{
	ssd1306_Fill(Black);
	ssd1306_DrawBitmap(0, 0, snake_128x64, 128, 64, White);
	ssd1306_UpdateScreen();
	xTimerStart(welcome_screen_timer, 0);
}

static void show_start_game_screen()
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(24, 20);
	ssd1306_WriteString("Press button", Font_7x10, White);
	ssd1306_SetCursor(36, 32);
	ssd1306_WriteString("to start", Font_7x10, White);
	ssd1306_UpdateScreen();
}

static void show_game_screen()
{
	ssd1306_Fill(Black);
	ssd1306_UpdateScreen();
}

static void screen_init()
{
	ssd1306_Init();
}

void welcome_screen_timer_callback()
{
	new_display_state = DISPLAY_STATE_START_GAME;
}

static void state_machine_update()
{
	switch (display_state)
	{
	case DISPLAY_STATE_WELCOME:
		show_welcome_screen();
		break;
	case DISPLAY_STATE_START_GAME:
		show_start_game_screen();
		break;
	case DISPLAY_STATE_GAME:
		show_game_screen();
		break;
	case DISPLAY_STATE_SCORE:
		break;
	default:
		break;
	}
}

int cnt = 0;

void vDisplayTask()
{
	screen_init();
	state_machine_update();
	while (1)
	{
		if(display_state != new_display_state)
		{
			display_state = new_display_state;
			state_machine_update();
		}

		if(display_state == DISPLAY_STATE_GAME)
		{

		}

		display_number(cnt);

	}
}
void display_state_button_pressed()
{
	if(display_state == DISPLAY_STATE_START_GAME)
	{
		new_display_state = DISPLAY_STATE_GAME;
	}
	cnt++;
}


void display_init()
{
	welcome_screen_timer = xTimerCreate((const char*) "welcome_screen_timer",
		WELCOME_SCREEN_TIMER_MS / portTICK_RATE_MS,
		pdFALSE, (void*) 0, welcome_screen_timer_callback);

	xTaskCreate(vDisplayTask, "display_task", configMINIMAL_STACK_SIZE, NULL,
			(tskIDLE_PRIORITY + 1UL), NULL);

}
