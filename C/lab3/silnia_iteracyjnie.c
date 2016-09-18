#include <stdio.h>


int main()
{
int n, i, silnia =1;
printf("Podaj n: ");
scanf("%d", &n);
printf("\nN wynosi %d\n", n);

    for (i=2; i<=n;i++)
    {
    silnia=silnia*i;
    }
    
printf("Silnia wynosi %d\n", silnia);
}

/*
Dla int: poprawne wyniki aż do 16! włącznie, od 34! jest 0
dla float: poprawne wyniki do 34!
Dla double: poprawne wyniki do 170!, potem jest "inf"
*/
