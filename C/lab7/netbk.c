/* Maciej Michalec */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compar(const void* a, const void* b) /* funkcja porownujaca - potrzebna do sortowania*/
{
if( *(double*)a < *(double*)b ) return(-1);
else if( *(double*)a == *(double*)b ) return(0);
else if( *(double*)a > *(double*)b ) return (1);
}


int main()
{
clock_t start,end;
double czas;
double l[1000000];
int przedzialy[50];
int i;
srand48(431);
for(i=0;i<1000000;i++)
    {
    l[i]=drand48();
/*    printf("\nLiczba = %lf", l[i]);*/
    }
for(i=0;i<50;i++) /* zeruje tablice przedzialow */
    {
    przedzialy[i]=0;
    }
for(i=0;i<1000000;i++) /* uzupelniam przedzialy liczbami */
    {
    l[i]*=50;
    przedzialy[(int)l[i]]++;
    }
printf("\nROZKLAD LICZB LOSOWYCH W ROWNYCH PRZEDZIALACH:\n");
for(i=0;i<50;i++)
    {
    printf("Przedzial %d zawiera %d liczb\n",(i+1),przedzialy[i]);
    }


start=clock();

qsort(l,1000000,sizeof(*l),compar); /* sortowanie */

end=clock();
czas=((double)(end-start)/CLOCKS_PER_SEC);
printf("\n\nCzas zuzyty na sortowanie to %lf\n\n\n", czas);

for(i=0;i<10;i++) /* wypisuje 10 liczb - sprawdzanie czy zostaly posortowane */
{ 
printf("Liczba to %f\n",l[i]);
}

for(i=0;i<50;i++) /* zaruje przedzialy */
    {
    przedzialy[i]=0;
    }


for(i=0;i<=100000;i++) /* zliczanie roznic kolejnych liczb */
    {
    l[i]=(l[i+1]-l[i]);
    przedzialy[(int)(l[i]*100000)]++;
    }

printf("\n\nROZKLAD ROZNIC POSORTOWANYCH LICZB LOSOWYCH:\n");
for(i=0;i<50;i++)
    {
    printf("Przedzial %d zawiera %d liczb\n",(i+1),przedzialy[i]);
    }

}

