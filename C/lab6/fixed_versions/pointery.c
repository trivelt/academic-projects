/* Maciej Michalec */

#include <stdio.h>
#include "biblioteka.h"

int main()
{
double d;
int* wsk;
int i,n,g,*h;
int liczba;
h=(int*)&d;
wsk=&liczba;
printf("Podaj liczbe rzeczywista: ");
scanf("%d",&liczba);

/*printf("%d", *(&(*(&(*(&(*(&(*(&(*(&(*(&(*(&(*(&(*(&(*(&(*(&i))))))))))))))))))))))));*/

printf("\n");
n=8*sizeof(i);

    for(i=n-1;i>=0;i--)
    {
    printf("%d", printBitwsk((int*)&liczba,i)); 
    }
    
printf("\n");

    for(i=n-1;i>=0;i--)
    {
    g=setBitwsk(&liczba,i);
     printf("%d", printBit(g,i));
    }

printf("\n");

    for(i=n-1;i>=0;i--)
    {
    g=zeroBitwsk(&liczba,i);
     printf("%d", printBitwsk(&g,i));
    }

printf("\n");

    for(i=n-1;i>=0;i--)
    {
     printf("%d\n", flipBitwsk(&liczba,i));
    }

printf("\n");
}

