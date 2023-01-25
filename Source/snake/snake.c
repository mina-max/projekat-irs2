/*
 * snake.c
 *
 *  Created on: Jan 24, 2023
 *      Author: mira
 */

#include "snake.h"
#include "project-irs2.h"

static grid_position_t apple_position = {
		.x_block = 5,
		.y_block = 2
};

static snake_t snake =
{
		.direction = INITIAL_DIRECTION,
		.body = {
			[0] = { .x_block = 9,  .y_block = 4 },
			[1] = { .x_block = 10, .y_block = 4 },
			[2] = { .x_block = 11, .y_block = 4 },
		},
		.body_size = INITIAL_SNAKE_BODY_SIZE
};


static void generate_new_apple_block()
{
	int i = 0;

	while (1)
	{
		if (i == snake.body_size)
		{
			return;
		}
		else
		{
			apple_position.x_block = rand() % WIDTH_BLOCKS;
			apple_position.y_block = rand() % HEIGHT_BLOCKS;
		}

		for (i = 0; i < snake.body_size; i++)
		{
			if (snake.body[i].x_block == apple_position.x_block &&
					snake.body[i].y_block == apple_position.y_block)
			{
				break;
			}
		}
	}
}

void move_snake()
{
	grid_position_t head = snake.body[0];

	switch (snake.direction)
	{
	case LEFT:
		if (head.x_block == 0)
		{
			head.x_block = WIDTH_BLOCKS - 1;
		}
		else
		{
			head.x_block -= 1;
		}
		break;
	case RIGHT:
		if (head.x_block == WIDTH_BLOCKS - 1)
		{
			head.x_block = 0;
		}
		else
		{
			head.x_block += 1;
		}
		break;
	case UP:
		if (head.y_block == 0)
		{
			head.y_block = HEIGHT_BLOCKS - 1;
		}
		else
		{
			head.y_block -= 1;
		}
		break;
	case DOWN:
		if (head.y_block == HEIGHT_BLOCKS - 1)
		{
			head.y_block = 0;
		}
		else
		{
			head.y_block += 1;
		}
		break;
	}


	if (head.x_block == apple_position.x_block &&
			head.y_block == apple_position.y_block)
	{
		snake.body_size++;
		game_increase_score();
		generate_new_apple_block();
	}

	for (int i = snake.body_size; i > 1; i--)
	{
		snake.body[i - 1] = snake.body[i - 2];
	}

	snake.body[0] = head;
}

void snake_change_direction(snake_directions_t direction)
{
	snake.direction = direction;
}

snake_t* get_snake()
{
	return &snake;
}

grid_position_t* get_apple_position()
{
	return &apple_position;
}
