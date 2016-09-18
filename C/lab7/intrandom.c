/* Maciej Michalec */
#define RANDNUMS 1000000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compar(const void* a, const void* b) /* funkcja porownujaca - potrzebna do sortowania*/
{
if( *(int*)a < *(int*)b ) return(-1);
else if( *(int*)a == *(int*)b ) return(0);
else if( *(int*)a > *(int*)b ) return (1);
}


int main()
{
clock_t start,end;
double czas;
int l[RANDNUMS];
int przedzialy[50];
int i;
for(i=0;i<RANDNUMS;i++)
    {
    l[i]=random();
    }

for(i=0;i<50;i++) /* zeruje tablice przedzialow */
    {
    przedzialy[i]=0;
    }
for(i=0;i<RANDNUMS;i++) /* uzupelniam przedzialy liczbami */
    {
    /*l[i]=((double)l[i])/RAND_MAX*50;*/
    przedzialy[(int)(((double)l[i])/RAND_MAX*50)]++;
    }
printf("\nROZKLAD LICZB LOSOWYCH W ROWNYCH PRZEDZIALACH:\n");
for(i=0;i<50;i++)
    {
    printf("Przedzial %d zawiera %d liczb\n",(i+1),przedzialy[i]);
    }


start=clock();

qsort(l,RANDNUMS,sizeof(*l),compar); /* sortowanie */

end=clock();
czas=((double)(end-start)/CLOCKS_PER_SEC);
printf("\n\nCzas zuzyty na sortowanie to %lf\n\n\n", czas);

for(i=0;i<10;i++) /* wypisuje 10 liczb - sprawdzanie czy zostaly posortowane */
{ 
printf("Liczba to %d\n",l[i]);
}

for(i=0;i<50;i++) /* zeruje przedzialy */
    {
    przedzialy[i]=0;
    }


for(i=0;i<RANDNUMS;i++) /* zliczanie roznic kolejnych liczb */
    {
    przedzialy[(int)((double)(l[i+1]-l[i])/RAND_MAX)]++;
    }

printf("\n\nROZKLAD ROZNIC POSORTOWANYCH LICZB LOSOWYCH:\n");
for(i=0;i<50;i++)
    {
    printf("Przedzial %d zawiera %d liczb\n",(i+1),przedzialy[i]);
    }
}

