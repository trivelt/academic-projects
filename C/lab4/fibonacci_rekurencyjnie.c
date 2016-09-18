#include <stdio.h>

int fibonacci(int x)
{
if(x==0) return x;
else if(x==1) return x;
x=fibonacci(x-1)+fibonacci(x-2);
}

int main()
{
int n, w;
printf("Podaj n: ");
scanf("%d", &n);
if(n<0) return 0;
w=fibonacci(n);
printf("\nWynik to %d\n", w);
}

/*
Dla 3GB RAM program liczy:
n=10	0.84
n=20	1,07
n=30	0,94
n=40	2,08
n=43	6,88
n=45	13,25
n=46	19,60
*/