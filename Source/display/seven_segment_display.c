/*
 * seven_segment_display.c
 *
 *  Created on: Nov 30, 2022
 *      Author: mira
 */

#include "main.h"

static void reset_seven_segment_display()
{
	HAL_GPIO_WritePin(SEL1_GPIO_Port, SEL1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SEL2_GPIO_Port, SEL2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SA_GPIO_Port, SA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SB_GPIO_Port, SB_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SC_GPIO_Port, SC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SD_GPIO_Port, SD_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SE_GPIO_Port, SE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SF_GPIO_Port, SF_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SG_GPIO_Port, SG_Pin, GPIO_PIN_RESET);
}

void display_number(uint8_t num)
{
	uint8_t digit = 0;

	if (num > 99)
	{
		num = 99;
	}

	int i = 0;
	if(num == 0)
	{
		HAL_GPIO_WritePin(SEL2_GPIO_Port, SEL2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SEL1_GPIO_Port, SEL1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SG_GPIO_Port, SG_Pin, GPIO_PIN_SET);
	}
	else
	{
		while (num)
		{
			reset_seven_segment_display();
			if(i == 0)
			{
				HAL_GPIO_WritePin(SEL2_GPIO_Port, SEL2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SEL1_GPIO_Port, SEL1_Pin, GPIO_PIN_SET);
				i++;
			}
			else
			{
				HAL_GPIO_WritePin(SEL1_GPIO_Port, SEL1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(SEL2_GPIO_Port, SEL2_Pin, GPIO_PIN_SET);
			}

			digit = num % 10;
			num /= 10;

			switch (digit)
			{
			case 0:
				HAL_GPIO_WritePin(SG_GPIO_Port, SG_Pin, GPIO_PIN_SET);
				break;
			case 1:
				HAL_GPIO_WritePin(SA_GPIO_Port, SA_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SD_GPIO_Port, SD_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SE_GPIO_Port, SE_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SF_GPIO_Port, SF_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SG_GPIO_Port, SG_Pin, GPIO_PIN_SET);
				break;
			case 2:
				HAL_GPIO_WritePin(SC_GPIO_Port, SC_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SF_GPIO_Port, SF_Pin, GPIO_PIN_SET);
				break;
			case 3:
				HAL_GPIO_WritePin(SE_GPIO_Port, SE_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SF_GPIO_Port, SF_Pin, GPIO_PIN_SET);
				break;
			case 4:
				HAL_GPIO_WritePin(SA_GPIO_Port, SA_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SD_GPIO_Port, SD_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SE_GPIO_Port, SE_Pin, GPIO_PIN_SET);
				break;
			case 5:
				HAL_GPIO_WritePin(SB_GPIO_Port, SB_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SE_GPIO_Port, SE_Pin, GPIO_PIN_SET);
				break;
			case 6:
				HAL_GPIO_WritePin(SB_GPIO_Port, SB_Pin, GPIO_PIN_SET);
				break;
			case 7:
				HAL_GPIO_WritePin(SD_GPIO_Port, SD_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SE_GPIO_Port, SE_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SF_GPIO_Port, SF_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(SG_GPIO_Port, SG_Pin, GPIO_PIN_SET);
				break;
			case 8:
				break;
			case 9:
				HAL_GPIO_WritePin(SE_GPIO_Port, SE_Pin, GPIO_PIN_SET);
				break;
			default:
				break;
			}
			HAL_Delay(10);
		}
	}

}
