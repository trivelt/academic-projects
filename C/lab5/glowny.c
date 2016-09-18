#include <stdio.h>

/*
Wyniki dzialania programu:
1. Przedzial: od 0 do 100, eps=1e-50:
a) metoda bisekcji: x0=2.0 w 58 krokach
b) metoda siecznych: x0=2.0 w 16 krokach
2. Przedzial: od 0 do 10, eps=1e-50
a) metoda bisekcji: x0=2.0, w 54 krokach
b) metoda siecznych: x0=2.0, w 8 krokach

*/

double f(double x);
double mzero(double xl, double xp, double eps, int* i, int flaga);

int main()
{
double x0, xl,xp, eps; /*m0, lewa i prawa granica przedzialu, dokladnosc oblicz.*/
int iter, flaga;
printf("Podaj przedzial: ");
scanf("%lf %lf", &xl, &xp);
printf("Podaj epsilon: ");
scanf("%lf", &eps);
printf("Z jakiej metody obliczen chcesz skorzystac?\n1.Metoda bisekcji\n2.Metoda siecznych\n: ");
scanf("%d", &flaga);

    if(f(xl)*f(xp)<0) /*Znakozmienna*/
    {
    x0=mzero(xl,xp,eps, &iter, flaga);
    }
    else
    {
    printf("\nBrak miejsc zerowych w tym przedziale\n");
    return 1;
    }
printf("\n %f %f w %d krokach\n", x0, f(x0), iter);
}

