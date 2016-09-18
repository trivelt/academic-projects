#include <stdio.h>
#include <math.h>

double f(double x);
double mzero(double xl, double xp, double eps, int*i, int flaga)
{
(*i)=0;
double x0, f0, fp, fl;

fl=f(xl);
fp=f(xp);

printf("Dostalem %f %f \n", xl, xp);
printf("Ich wartosci to %f %f \n", fl, fp);

if (flaga==1) /*Obliczam metoda bisekcji*/
{


while(1)
{
(*i)++;
x0=(xl+xp)/2;
printf("Teraz x0 to %f \n", x0);
f0=f(x0);
printf("Wartosc x0 to %f \n", f0);

    if(fabs(f0)<eps)
    {
    return x0;
    }

    if(fl*f0<0)
    {
    xp=x0;
    fp=f0;
    }
    else 
    {
    xl=x0;
    fl=f0;
    }

}

}

else /*Obliczam metoda siecznych*/

{
while(fabs(xl-xp)>eps)
{
(*i)++;
x0=xl-fl*(xl-xp)/(fl-fp);
f0=f(x0);
if(fabs(f0)<eps) break;
xp=xl;
fp=fl;
xl=x0;
fl=f0;
}
return x0;
}



}