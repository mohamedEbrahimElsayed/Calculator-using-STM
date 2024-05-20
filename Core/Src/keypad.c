/*
 * keypad.c
 *
 *  Created on: May 4, 2024
 *      Author: Adnan
 */
#include "keypad.h"

GPIO_TypeDef* rows_port= GPIOA;
uint16_t row_pins[KEYPAD_ROWS]= {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3};

GPIO_TypeDef* cols_port= GPIOA;
uint16_t col_pins[KEYPAD_COLS]= {GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};

uint8_t keypad_buttons[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'c', '0', '=', '+'}
};

void KeypadInit(void)
{
	// Initialize GPIO pins for keypad rows as outputs
	for (int row = 0; row < KEYPAD_ROWS; row++)
	{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = row_pins[row];
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(rows_port, &GPIO_InitStruct);
	}

	// Initialize GPIO pins for keypad columns as inputs with pull-up resistors
	for (int col = 0; col < KEYPAD_COLS; col++)
	{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Pin = col_pins[col];
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(cols_port, &GPIO_InitStruct);
	}
}

uint8_t Keypad_GetVal(void)
{
	uint8_t rows_counter= 0;
	uint8_t columns_counter= 0;
	uint8_t counter= 0;
	GPIO_PinState keypad_state;
	uint8_t ret_val= 0;
while(ret_val==0)
{
	for(rows_counter= 0; rows_counter < KEYPAD_ROWS; rows_counter++)
	{
		for(counter= 0; counter < KEYPAD_ROWS; counter++)
		{
			HAL_GPIO_WritePin(GPIOA, row_pins[counter], GPIO_PIN_RESET);
		}
		HAL_GPIO_WritePin(GPIOA, row_pins[rows_counter], GPIO_PIN_SET);

		for(columns_counter= 0; columns_counter < KEYPAD_COLS; columns_counter++)
		{
			keypad_state= HAL_GPIO_ReadPin(GPIOA, col_pins[columns_counter]);
			if(keypad_state == GPIO_PIN_SET)
			{
				ret_val= keypad_buttons[rows_counter][columns_counter];
			}
		}
	}
	DELAY(8);
}
	return ret_val;
}

