/* Maciej Michalec */

#include <stdio.h>

/* ##### WERSJE BEZ WSKAZNIKOW ##### */

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
return a&(~maska);
}

int setBit(int a, int n) /* ustawia n-ty bit na 1 */
{
unsigned int maska=1<<n;
return a|maska;
}


/* ##### WERSJE WSKAZNIKOWE ##### */

int printBitwsk(int* c, int n)
{
unsigned int maska=1<<n;
return ((*c)&maska)>>n;
}

int setBitwsk(int*a, int n)
{
unsigned int maska=1<<n;
return (*a)|maska;
}

int zeroBitwsk(int* a, int n)
{
unsigned int maska=1<<n;
return (*a)&(~maska);
}

int flipBitwsk(int* a, int n)
{
unsigned int maska=1<<n;
return((*a)^maska);
}
