/* Maciej Michalec */

#include <stdio.h>
#include "biblioteka.h"

int main()
{
char znak;
int liczba, i,n;

printf("Podaj znak do zbadania: ");
scanf("%d",&liczba);

/*char znak, %c, def. fkcji*/


printf("\n");
n=8*sizeof(liczba);

    for(i=n-1;i>=0;i--)
    {
    printf("%d", printBit(liczba,i));
    }

printf("\n");
for(i=n-1;i>=0;i--)
    {
    printf("%d\n", flipBit(liczba,i));
    }

printf("\n");
for(i=n-1;i>=0;i--)
    {
    printf("%d", zeroBit(liczba,i));
    }

printf("\n");
for(i=n-1;i>=0;i--)
    {
    printf("%d", setBit(liczba,i));
    }
printf("\n");
}

