/*
 * arith_func.c
 *
 *  Created on: May 5, 2024
 *      Author: abdot
 */
#include "arith_func.h"

void ArithFunc(float num1, char op, float num2, int *Dicemal_Part_ptr, int *Floating_Part_ptr)
{
	float result, float_part;
	switch (op)
	{
		case '+' : // addition
		{
			result = num1 + num2;
			break;
		}

		case '-' : // subtraction
		{
			result = num1 - num2;
			break;
		}

		case '*' : // mul
		{
			result = num1 * num2;
			break;
		}

		case '/' : // div
		{
			result = num1 / num2;
			break;
		}
	}
	*Dicemal_Part_ptr = (int) result;
	float_part = (result-*Dicemal_Part_ptr);
	float_part = (float_part*1000);
	*Floating_Part_ptr = (int) float_part;

}
