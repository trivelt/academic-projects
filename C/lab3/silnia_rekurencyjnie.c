#include <stdio.h>

int silnia(int x)
{
/*int sil, i;
i=1;
i=i*(i+1);
while(i<=x)
    {
    silnia(i+1);
    }
*/
if(x==1) return 1;
else 
return x*silnia(x-1);


}

int main()
{
int n,w;
printf("Podaj n: ");
scanf("%d", &n);
printf("\nN wynosi %d\n", n);

if(n==0) printf("%d! wynosi 1\n", n);

else 
    {
    w=silnia(n);
    printf("Silnia wynosi %d\n", w);
    }
}

