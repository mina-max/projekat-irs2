/*
 * display.h
 *
 *  Created on: Nov 30, 2022
 *      Author: mira
 */

#ifndef DISPLAY_DISPLAY_H_
#define DISPLAY_DISPLAY_H_

#include "stdbool.h"
#include "snake.h"

void display_init(void);
void display_update(void);
void display_welcome_screen(void);
void display_start_game_screen(void);
void display_draw_snake(bool grid, snake_t* snake);
void display_draw_apple(grid_position_t* pos);


#endif /* DISPLAY_DISPLAY_H_ */
