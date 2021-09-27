#include "function.h"

int pow (int num, int p)
{
    if (p==0) return 1;
    if (p==1) return num;
    else if ((p % 2) == 0) return pow(num*num, p/2);
    else return num*pow(num*num, (p-1)/2);
}

void decToHex(int number, char hex[4])
{
    int rest, quo = number, i = 3;
    while (quo !=0)
    {
        rest = quo%16;
        if (rest > 9)
        {
            hex[i--] = 55 + rest;
        } else {
            hex[i--] = 48 + rest;
        }
        quo /= 16;
    }
}

int hexToDec(char hex[4])
{
    int dec;
    int val, len;
    dec = 0;
    len = 3;
    for(int i=0; hex[i]!='\0'; i++)
    {
        if(hex[i]>='0' && hex[i]<='9')
        {
            val = hex[i] - 48;
        } else if(hex[i]>='A' && hex[i]<='F')
        {
            val = hex[i] - 65 + 10;
        }
        dec += val * pow(16, len);
        len--;
    }
    return dec;
}
