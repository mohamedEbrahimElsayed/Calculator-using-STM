/*
 * Error_handling.c
 *
 *  Created on: May 5, 2024
 *      Author: abdot
 */
#include"Error_handling.h"
unsigned char divByZeroError(unsigned char oprand2,unsigned char opration)
{
    if (opration =='/' && oprand2 == 0)
    {
        return 10;
    }
    return 0;
}
unsigned char invldOpr(unsigned char dig1,unsigned char dig2,unsigned char dig3)
{
    if (dig1<0x30 || dig2<0x30 || dig3<0x30 || dig1>0x39 || dig2>0x39 || dig3>0x39)
    {
        return 10;
    }
    else
    return 0;

}
unsigned char invldOpration(unsigned char oprator)
{
    if (oprator<'*'|| oprator>'/')
    {
        return 10;
    }
    else
    return 0;

}
void DELAY(unsigned int time)
{
    unsigned int I,J;
    for(I=0;I<time;I++)
    for(J=0;J<1275;J++);
}

