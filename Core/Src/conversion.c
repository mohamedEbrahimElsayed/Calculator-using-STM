/*
 * converion.c
 *
 *  Created on: May 5, 2024
 *      Author: abdot
 */
#include"conversion.h"

int hex_to_dec(unsigned char dig_1,unsigned char dig_2,unsigned char dig_3)
{
    int dec_num;
    dig_1=(dig_1-'0');
    dig_2=(dig_2-'0');
    dig_3=(dig_3-'0');
    dec_num=(dig_1*100)+(dig_2*10)+dig_3;
    return dec_num;
}

void dec_to_hex(int dec,unsigned char *hex)
{
    unsigned char x;
    for(x=0;x<=2;x++)
    {
        hex[2-x]=(dec%10)+'0';
        dec/=10;
    }


}
void dec_to_hex_dec(int dec,unsigned char *hex,unsigned char *size)
{
    int s=dec;
    int cnt=0;
    while(s!=0)//cnt=number of digits
    {
        cnt++;
        s/=10;
    }
    unsigned char x;
    for(x=0;x<cnt;x++)
    {
        hex[cnt-x]=(dec%10)+'0';
        dec/=10;
    }
*size=cnt;

}
