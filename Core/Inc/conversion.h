/*
 * conversion.h
 *
 *  Created on: May 5, 2024
 *      Author: abdot
 */

#ifndef INC_CONVERSION_H_
#define INC_CONVERSION_H_

int hex_to_dec(unsigned char dig_1,unsigned char dig_2,unsigned char dig_3);
void dec_to_hex(int dec,unsigned char *hex);
void dec_to_hex_dec(int dec,unsigned char *hex,unsigned char *size);

#endif /* INC_CONVERSION_H_ */
