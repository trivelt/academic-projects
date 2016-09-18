#include <stdio.h>
#include <math.h>

int main()
{
double a,b,c,x,Delta;
double P_Delta;
a=1;b=7;c=9;


printf("Podaj a: ");
scanf("%lf", &a);
printf("A wynosi %f\n", a);

printf("Podaj b ");
scanf("%lf", &b);
printf("B wynosi %f\n", b);

printf("Podaj c ");
scanf("%lf", &c);
printf("C wynosi %f\n", c);

Delta=b*b-4*a*c;
printf("Delta: %f\n", Delta);

P_Delta=sqrt(Delta);
(Delta>=0) ? printf("Pierwiastek z delty: %f\n", P_Delta) : printf("") ;

    if(Delta>0)
    {
    printf("Dwa pierwiastki rzeczywiste: %f i %f\n", ((-b)-P_Delta)/(2*a),((-b)+P_Delta)/(2*a) );
    }
    
    else if(Delta==0)
    {
    printf("Pierwiastek podwojny %f\n", -b/(2*a));
    }
    
    else
    {
    P_Delta=sqrt(-Delta);
    printf("Pierwiastki zespolone: %f + i %f , %f - i %f\n", -b/(2*a), P_Delta/(2*a), -b/(2*a), P_Delta/(2*a));
    }
    

}

