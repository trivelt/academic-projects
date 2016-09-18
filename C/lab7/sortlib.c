#include <stdio.h>
#include <stdlib.h>

void BubbleSort(double *tab, int n)
{
double tmp;
int i,j;
for(i=0;i<n;i++)
    {
    for(j=0;j<=n-1;j++)
	{
	if(tab[i]<tab[j])
	    {
	    tmp=tab[i];
	    tab[i]=tab[j];
	    tab[j]=tmp;
	    }
	}
    }
}

void szybkie(double tab[], int p, int k)
{
double n=tab[(p+k)/2];
int i=p,j=k;
double tmp;

do
    {

    while(tab[i]<n) ++i;
    while(tab[j]>n) --j;

    if(i<=j)
        {
        tmp=tab[i];
        tab[i]=tab[j];
        tab[j]=tmp;
	++i; --j;
        }
    }while(i<j);
if(p<j) szybkie(tab,p,j);
if(k>i) szybkie(tab,i,k);
}

void babelkowe(double tab[],int n)
{
int i,zmiennik=1;
double tmp;
do
    {
    zmiennik=0;
    for(i=0;i<n-1;i++)
        {
        if(tab[i]>tab[i+1]) 
		{
		tmp=tab[i];
		tab[i]=tab[i+1];
		tab[i+1]=tmp;
		zmiennik++;
		}
        }
    }while(zmiennik);
}


