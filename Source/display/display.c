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
#include "stdlib.h"

#define WELCOME_SCREEN_TIMER_MS 3000

#define HEIGHT_BLOCKS 9
#define WIDTH_BLOCKS 18

#define GRID_SIZE 6
#define SNAKE_SIZE_PIXEL 	6
#define SNAKE_LENGTH_START 	3

#define WIDTH 	127
#define HEIGHT 	64

typedef enum
{
	LEFT, RIGHT, UP, DOWN
} snake_directions_t;

typedef struct
{
	uint8_t x;
	uint8_t y;
} snake_position_t;

typedef enum
{
	DISPLAY_STATE_INIT,
	DISPLAY_STATE_WELCOME,
	DISPLAY_STATE_START_GAME,
	DISPLAY_STATE_GAME,
	DISPLAY_STATE_SCORE
} display_states_t;

extern unsigned char snake_128x64[];

display_states_t display_state = DISPLAY_STATE_INIT;
display_states_t new_display_state = DISPLAY_STATE_INIT;

static xTimerHandle welcome_screen_timer = NULL;

static snake_directions_t snake_direction = LEFT;
static snake_position_t snake_body[136];

static uint16_t snake_body_size = 3;

static void display_screen_init()
{
	ssd1306_Init();
	new_display_state = DISPLAY_STATE_WELCOME;
}

static void display_welcome_screen()
{
	ssd1306_Fill(Black);
	ssd1306_DrawBitmap(0, 0, snake_128x64, 128, 64, White);
	ssd1306_UpdateScreen();
	xTimerStart(welcome_screen_timer, 0);
}

snake_position_t pos;

static void display_start_game_screen()
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(24, 20);
	ssd1306_WriteString("Press button", Font_7x10, White);
	ssd1306_SetCursor(36, 32);
	ssd1306_WriteString("to start", Font_7x10, White);
	ssd1306_UpdateScreen();

	snake_position_t pos =
	{ .x = GRID_SIZE * WIDTH_BLOCKS / 2 + 9 * 1 + 1, .y = GRID_SIZE * 4 + 4 * 1
			+ 1 };
	snake_body[0] = pos;
	pos.x += GRID_SIZE + 1;
	snake_body[1] = pos;
	pos.x += GRID_SIZE + 1;
	snake_body[2] = pos;

}

static void display_draw_apple()
{
	uint8_t block = rand() % (HEIGHT_BLOCKS*WIDTH_BLOCKS);
	uint8_t r = 2;
	uint8_t x = (block % WIDTH_BLOCKS)*GRID_SIZE + (block % WIDTH_BLOCKS)*1 + 3;
	uint8_t y = (block / WIDTH_BLOCKS) * GRID_SIZE + (block / WIDTH_BLOCKS)*1 + 3;
	ssd1306_DrawCircle(x, y, r, White);
	ssd1306_Line(x, y - r - 2, x, y - r, White);
}

static void display_draw_snake(uint8_t length, snake_directions_t direction)
{

	//snake_body[0] = {.x = 0, .y = GRID_SIZE*HEIGHT_BLOCKS/2 + HEIGHT_BLOCKS*1 + 1 + 1};
	switch (direction)
	{
	case LEFT:
		snake_body[2] = snake_body[1];
		snake_body[1] = snake_body[0];
		pos = snake_body[0];
		pos.x = pos.x - GRID_SIZE - 1;
		snake_body[0] = pos;
		break;
	case RIGHT:
		snake_body[2] = snake_body[1];
		snake_body[1] = snake_body[0];
		pos = snake_body[0];
		pos.x = pos.x + GRID_SIZE + 1;
		snake_body[0] = pos;
		break;
	case UP:
		snake_body[2] = snake_body[1];
		snake_body[1] = snake_body[0];
		pos = snake_body[0];
		pos.y = pos.y - GRID_SIZE - 1;
		snake_body[0] = pos;
		break;
	case DOWN:
		snake_body[2] = snake_body[1];
		snake_body[1] = snake_body[0];
		pos = snake_body[0];
		pos.y = pos.y + GRID_SIZE + 1;
		snake_body[0] = pos;
		break;

	}

	for (int i = 0; i < snake_body_size; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ssd1306_DrawRectangle(snake_body[i].x + j, snake_body[i].y + j,
					snake_body[i].x + GRID_SIZE - 1 - j,
					snake_body[i].y + GRID_SIZE - 1 - j, White);
		}

	}
	HAL_Delay(300);
	display_draw_apple();
}

static void display_game_screen()
{

	ssd1306_Fill(Black);
//	for (int i = 0; i <= WIDTH; i += 7)
//	{
//		ssd1306_Line(i, 0, i, HEIGHT - 1, White);
//	}
//
//	for (int i = 0; i <= HEIGHT; i += 7)
//	{
//		ssd1306_Line(0, i, WIDTH - 1, i, White);
//	}

	display_draw_snake(1, snake_direction);

	ssd1306_UpdateScreen();
}

static void display_highscore(uint8_t cnt)
{
	seven_seg_display_number(cnt);
}

void display_welcome_screen_timer_callback()
{
	new_display_state = DISPLAY_STATE_START_GAME;
}

static void display_state_machine_update()
{
	switch (display_state)
	{
	case DISPLAY_STATE_WELCOME:
		display_welcome_screen();
		break;
	case DISPLAY_STATE_START_GAME:
		display_start_game_screen();
		break;
	case DISPLAY_STATE_GAME:
		display_game_screen();
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
	display_screen_init();
	while (1)
	{
		if (display_state != new_display_state)
		{
			display_state = new_display_state;
			display_state_machine_update();
		}
		if (display_state == DISPLAY_STATE_GAME)
		{
			display_game_screen();
		}
		display_highscore(cnt);
	}
}

void display_button_pressed()
{
	if (display_state == DISPLAY_STATE_START_GAME)
	{
		new_display_state = DISPLAY_STATE_GAME;
	}
	if(display_state == DISPLAY_STATE_GAME)
	{
		if(snake_direction == UP)
		{
			snake_direction = RIGHT;
		}else if (snake_direction == RIGHT || snake_direction == LEFT){
			snake_direction = UP;
		}
	}
	cnt++;
}

void display_init()
{
	welcome_screen_timer = xTimerCreate((const char*) "welcome_screen_timer",
	WELCOME_SCREEN_TIMER_MS / portTICK_RATE_MS,
	pdFALSE, (void*) 0, display_welcome_screen_timer_callback);

	xTaskCreate(vDisplayTask, "display_task", configMINIMAL_STACK_SIZE, NULL,
			(tskIDLE_PRIORITY + 1UL), NULL);
}
