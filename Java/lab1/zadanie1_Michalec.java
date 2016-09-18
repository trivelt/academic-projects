/*
Maciej Michalec
Zadanie 1
12.10.2013
*/

class Start
{
public static void main(String[] args)
	{
	final double MAX = 10.0, MIN = -5.0, STEP = 0.5;
	int numerLinii=0;

	for(double i=MIN;i<=MAX;i+=STEP)
		{
		numerLinii++;
		System.out.println(i + "\t" + Math.sin(i) + "\t" + Math.abs(i));
		if(i>0) System.out.println("\t" + Math.log(i));
		if(numerLinii>=10 && numerLinii%2==0) System.out.println("----------------");
		}
	}

}
