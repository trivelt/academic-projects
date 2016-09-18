/* Maciej Michalec */

#include <stdio.h>
#include "biblioteka.h"

int main()
{

union {
double d;
float f[2];
int z[2];
} moja_unia;

int i,n,a;

printf("Podaj liczbe rzeczywista: ");
scanf("%f",moja_unia.f);
printf("Podales %f", moja_unia.f[0]);


printf("\n");
n=8*sizeof(i);

    for(i=n-1;i>=0;i--)
    {
    printf("%d", printBit(moja_unia.z[0],i));
    }

printf("\n");

    for(i=n-1;i>=0;i--)
    {
    a=setBitwsk(moja_unia.z,i); /* uzywam wskaznikowej wersji funkcji */
    printf("%d", printBit(a,i));
    }

printf("\n");

    for(i=n-1;i>=0;i--)
    {
    a=zeroBitwsk(moja_unia.z,i); 
    printf("%d", printBit(a,i));
    }

printf("\n");

    for(i=n-1;i>=0;i--)
    {
    a=flipBit(moja_unia.z[0],i); /* uzywam wersji funkcji bez wskaznikow */
    printf("%d", printBit(a,i));
    }

printf("\n");
}

