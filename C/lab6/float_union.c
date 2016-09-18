/* maciej Michalec */

#include <stdio.h>
#include "biblioteka.h"

int main()
{

typedef union a{
int z;
int g[2];
float f;
double d;
}b;
b a;

int* wsk;


int i,n;

printf("Podaj liczbe rzeczywista: ");
scanf("%d",&a.z);

/*char znak, %c, def. fkcji*/


printf("\n");
n=8*sizeof(a.z);

    for(i=n-1;i>=0;i--)
    {
    printf("%d", printBit(a.z,i));
    }

printf("\n");
}

