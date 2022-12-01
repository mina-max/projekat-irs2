/*
 * seven_segment_display.c
 *
 *  Created on: Nov 30, 2022
 *      Author: mira
 */

#include "main.h"

#define DELAY_PWM 			8
#define MAX_NUM_TWO_DIGITS	99

typedef enum
{
	ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, _NUM_OF_DIGITS
} digits_t;

typedef struct
{
	GPIO_PinState a;
	GPIO_PinState b;
	GPIO_PinState c;
	GPIO_PinState d;
	GPIO_PinState e;
	GPIO_PinState f;
	GPIO_PinState g;
} digit_to_gpio_t;

static const digit_to_gpio_t digits_to_gpios[_NUM_OF_DIGITS] =
{
		[ZERO] 	= { .a = GPIO_PIN_RESET, .b = GPIO_PIN_RESET, .c = GPIO_PIN_RESET, .d = GPIO_PIN_RESET, .e = GPIO_PIN_RESET, .f = GPIO_PIN_RESET, .g = GPIO_PIN_SET },
		[ONE] 	= { .a = GPIO_PIN_SET, 	 .b = GPIO_PIN_RESET, .c = GPIO_PIN_RESET, .d = GPIO_PIN_SET, 	.e = GPIO_PIN_SET, 	 .f = GPIO_PIN_SET,   .g = GPIO_PIN_SET },
		[TWO] 	= { .a = GPIO_PIN_RESET, .b = GPIO_PIN_RESET, .c = GPIO_PIN_SET,   .d = GPIO_PIN_RESET, .e = GPIO_PIN_RESET, .f = GPIO_PIN_SET,   .g = GPIO_PIN_RESET },
		[THREE] = { .a = GPIO_PIN_RESET, .b = GPIO_PIN_RESET, .c = GPIO_PIN_RESET, .d = GPIO_PIN_RESET, .e = GPIO_PIN_SET,   .f = GPIO_PIN_SET,   .g = GPIO_PIN_RESET },
		[FOUR] 	= { .a = GPIO_PIN_SET, 	 .b = GPIO_PIN_RESET, .c = GPIO_PIN_RESET, .d = GPIO_PIN_SET, 	.e = GPIO_PIN_SET,	 .f = GPIO_PIN_RESET, .g = GPIO_PIN_RESET },
		[FIVE] 	= { .a = GPIO_PIN_RESET, .b = GPIO_PIN_SET,   .c = GPIO_PIN_RESET, .d = GPIO_PIN_RESET, .e = GPIO_PIN_SET, 	 .f = GPIO_PIN_RESET, .g = GPIO_PIN_RESET },
		[SIX] 	= { .a = GPIO_PIN_RESET, .b = GPIO_PIN_SET,   .c = GPIO_PIN_RESET, .d = GPIO_PIN_RESET, .e = GPIO_PIN_RESET, .f = GPIO_PIN_RESET, .g = GPIO_PIN_RESET },
		[SEVEN] = { .a = GPIO_PIN_RESET, .b = GPIO_PIN_RESET, .c = GPIO_PIN_RESET, .d = GPIO_PIN_SET, 	.e = GPIO_PIN_SET, 	 .f = GPIO_PIN_SET,   .g = GPIO_PIN_SET },
		[EIGHT] = { .a = GPIO_PIN_RESET, .b = GPIO_PIN_RESET, .c = GPIO_PIN_RESET, .d = GPIO_PIN_RESET, .e = GPIO_PIN_RESET, .f = GPIO_PIN_RESET, .g = GPIO_PIN_RESET },
		[NINE] 	= { .a = GPIO_PIN_RESET, .b = GPIO_PIN_RESET, .c = GPIO_PIN_RESET, .d = GPIO_PIN_RESET, .e = GPIO_PIN_SET, 	 .f = GPIO_PIN_RESET, .g = GPIO_PIN_RESET },
};

static void set_digit_gpios(digits_t digit)
{
	digit_to_gpio_t digit_to_gpio = digits_to_gpios[digit];
	HAL_GPIO_WritePin(SA_GPIO_Port, SA_Pin, digit_to_gpio.a);
	HAL_GPIO_WritePin(SB_GPIO_Port, SB_Pin, digit_to_gpio.b);
	HAL_GPIO_WritePin(SC_GPIO_Port, SC_Pin, digit_to_gpio.c);
	HAL_GPIO_WritePin(SD_GPIO_Port, SD_Pin, digit_to_gpio.d);
	HAL_GPIO_WritePin(SE_GPIO_Port, SE_Pin, digit_to_gpio.e);
	HAL_GPIO_WritePin(SF_GPIO_Port, SF_Pin, digit_to_gpio.f);
	HAL_GPIO_WritePin(SG_GPIO_Port, SG_Pin, digit_to_gpio.g);
}

static void set_select_ones_digit()
{
	HAL_GPIO_WritePin(SEL1_GPIO_Port, SEL1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEL2_GPIO_Port, SEL2_Pin, GPIO_PIN_RESET);
}

static void set_select_tens_digit()
{
	HAL_GPIO_WritePin(SEL1_GPIO_Port, SEL1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEL2_GPIO_Port, SEL2_Pin, GPIO_PIN_SET);
}

void seven_seg_display_number(uint8_t num)
{
	uint8_t ones_digit = 0;
	uint8_t tens_digit = 0;

	if (num > MAX_NUM_TWO_DIGITS)
	{
		num = MAX_NUM_TWO_DIGITS;
	}

	ones_digit = num % 10;
	tens_digit = num / 10;

	set_select_ones_digit();
	set_digit_gpios(ones_digit);
	HAL_Delay(DELAY_PWM);
	if(num > 9)
	{
		set_select_tens_digit();
		set_digit_gpios(tens_digit);
		HAL_Delay(DELAY_PWM);
	}
}
