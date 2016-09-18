/* Maciej Michalec */

#include <stdio.h>

int printBit(int a, int n)
{
unsigned int maska=1<<n;
return (a&maska)>>n; /*iloczyn bitowy*/
}

int flipBit(int a, int n)
{
unsigned int maska=1<<n;
return(a^maska);
/*
return(a^maska)?1:0;
sprobowac jako char
*/
}

int zeroBit(int a, int n)
{
unsigned int maska=1<<n;
return 0&(~maska);
}

int setBit(int a, int n)
{
unsigned int maska=1<<n;
return (a|maska)>>n;
}

int printBitwsk(int* c, int n)
{
unsigned int maska=1<<n;
return ((*c)&maska)>>n;
}

