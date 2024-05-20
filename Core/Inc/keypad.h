/*
 * keypad.h
 *
 *  Created on: May 4, 2024
 *      Author: Adnan
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

/* -------------------------------- Includes -------------------------------- */
#include "stm32f1xx_hal.h"

/* -------------------------------- Macros -------------------------------- */
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4


/* -------------------------------- Software Interfaces -------------------------------- */
void KeypadInit(void);

uint8_t Keypad_GetVal(void);

#endif /* KEYPAD_H_ */
