#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
double a,b,c,x,Delta,P_Delta;
a=atof(argv[1]);
b=atof(argv[2]);
c=atof(argv[3]);
Delta=b*b-4*a*c;

printf("Delta: %f\n", Delta);
P_Delta=sqrt(Delta);
(Delta>=0) ? printf("P_Delta %f\n", P_Delta) : printf(" ") ;



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
    printf("Pierwiastek z delty: %f\n", P_Delta);
    printf("Pierwiastki zespolone: %f + i %f , %f - i %f\n", -b/(2*a), P_Delta/(2*a), -b/(2*a), P_Delta/(2*a));
    }
    

}

