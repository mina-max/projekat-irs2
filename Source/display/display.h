/*
 * display.h
 *
 *  Created on: Nov 30, 2022
 *      Author: mira
 */

#ifndef DISPLAY_DISPLAY_H_
#define DISPLAY_DISPLAY_H_

typedef enum
{
	DISPLAY_STATE_WELCOME,
	DISPLAY_STATE_START_GAME,
	DISPLAY_STATE_GAME,
	DISPLAY_STATE_SCORE
} display_states_t;

void display_init();
void display_state_button_pressed();

#endif /* DISPLAY_DISPLAY_H_ */
