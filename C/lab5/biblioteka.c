#include <stdio.h>

int printBit(int a, int n)
{
unsigned int maska=1<<n;
return (a&maska)>>n; /*iloczyn bitowy*/
}


