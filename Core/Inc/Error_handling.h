/*
 * Error_handling.h
 *
 *  Created on: May 5, 2024
 *      Author: abdot
 */

#ifndef INC_ERROR_HANDLING_H_
#define INC_ERROR_HANDLING_H_

unsigned char divByZeroError(unsigned char oprand2,unsigned char opration);
unsigned char invldOpr(unsigned char dig1,unsigned char dig2,unsigned char dig3);
unsigned char invldOpration(unsigned char oprator);
void DELAY(unsigned int time);

#endif /* INC_ERROR_HANDLING_H_ */
