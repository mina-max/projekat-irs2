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

#define WIDTH 	127
#define HEIGHT 	64

extern unsigned char snake_128x64[];

void display_welcome_screen()
{
	ssd1306_Fill(Black);
	ssd1306_DrawBitmap(0, 0, snake_128x64, 128, 64, White);
	//ssd1306_UpdateScreen();
}

void display_start_game_screen()
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(24, 20);
	ssd1306_WriteString("Press button", Font_7x10, White);
	ssd1306_SetCursor(36, 32);
	ssd1306_WriteString("to start", Font_7x10, White);
	//ssd1306_UpdateScreen();
}

void display_draw_apple(grid_position_t* pos)
{
	uint8_t r = 3;
	uint8_t x = pos->x_block * GRID_SIZE + pos->x_block + 3;
	uint8_t y = pos->y_block * GRID_SIZE + pos->y_block + 3;
	ssd1306_DrawCircle(x, y, r, White);
}

void display_draw_snake(bool grid, snake_t* snake)
{
	ssd1306_Fill(Black);

	if(grid)
	{
		for (int i = 0; i <= WIDTH; i += 7)
		{
			ssd1306_Line(i, 0, i, HEIGHT - 1, White);
		}

		for (int i = 0; i <= HEIGHT; i += 7)
		{
			ssd1306_Line(0, i, WIDTH - 1, i, White);
		}
	}

	for (int i = 0; i < snake->body_size; i++)
	{
		uint8_t x1 = snake->body[i].x_block*GRID_SIZE + snake->body[i].x_block + 1;
		uint8_t x2 = snake->body[i].x_block*GRID_SIZE + snake->body[i].x_block + GRID_SIZE;
		uint8_t y1 = snake->body[i].y_block*GRID_SIZE + snake->body[i].y_block + 1;
		uint8_t y2 = snake->body[i].y_block*GRID_SIZE + snake->body[i].y_block + GRID_SIZE;
		for (int j = 0; j < 4; j++)
		{
			ssd1306_DrawRectangle(x1 + j, y1 + j, x2 - j, y2 - j, White);
		}
	}
}

void display_update()
{
	ssd1306_UpdateScreen();
}

void display_init()
{
	ssd1306_Init();
}
