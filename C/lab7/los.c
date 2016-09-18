/* Maciej Michalec */

#include <stdio.h>
#include <stdlib.h>

int main()
{
double l[1000000];
int i;
srand48(432);
for(i=0;i<100;i++)
    {
    l[i]=drand48();
/*    printf("\nLiczba = %lf", l[i]);*/
    }
}