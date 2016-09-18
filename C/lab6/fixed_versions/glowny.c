#include <stdio.h>
#include "biblioteka.h"

int main()
{
char znak;
int liczba, i,n,g;

printf("Podaj znak do zbadania: ");
scanf("%d",&liczba);

/*char znak, %c, def. fkcji*/


printf("\n");
n=8*sizeof(liczba);

    for(i=n-1;i>=0;i--)
    {
    printf("%ld", printBit(liczba,i));
    }

printf("\n");
for(i=n-1;i>=0;i--)
    {
/*    g=flipBit(liczba,i);*/
    printf("%ld\n", flipBit(liczba,i));
    }

printf("\n");
for(i=n-1;i>=0;i--)
    {
    g=zeroBit(liczba,i);
    printf("%ld", printBit(g,i));
    }

printf("\n");
for(i=n-1;i>=0;i--)
    {
    g=setBit(liczba,i);
    printf("%ld", printBit(g,i));
    }
printf("\n");
}

