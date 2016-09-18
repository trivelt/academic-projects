#include <stdio.h>

int fibonacci(int x)
{
int w, k, i=0;
int j=1;
if(x==0) return 0;

    for(k=0;k<x-1;k++)
    {
    w=i;
    i=j;
    j=w;
    j+=i;
    
    }
return j;
}

int main()
{
int n, wynik;
printf("Podaj n: ");
scanf("%d", &n);
if(n<0) return 0;
wynik=fibonacci(n);
printf("\nWynik to %d\n", wynik);
}