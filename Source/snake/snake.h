/*
 * snake.h
 *
 *  Created on: Jan 24, 2023
 *      Author: mira
 */

#ifndef DISPLAY_SNAKE_H_
#define DISPLAY_SNAKE_H_

#include "stdlib.h"
#include "stdint.h"

#define HEIGHT_BLOCKS 9
#define WIDTH_BLOCKS 18
#define GRID_SIZE 6

#define INITIAL_DIRECTION 		LEFT
#define INITIAL_SNAKE_BODY_SIZE 3

typedef enum
{
	LEFT, RIGHT, UP, DOWN
} snake_directions_t;

typedef struct
{
	uint8_t x_block;
	uint8_t y_block;
} grid_position_t;

typedef struct
{
	snake_directions_t direction;
	grid_position_t body[WIDTH_BLOCKS*HEIGHT_BLOCKS];
	uint8_t body_size;
} snake_t;

void move_snake();
void snake_change_direction(snake_directions_t direction);
snake_t* get_snake();
grid_position_t* get_apple_position();

#endif /* DISPLAY_SNAKE_H_ */
