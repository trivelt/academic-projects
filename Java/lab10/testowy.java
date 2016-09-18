class Start {
public static void main(String[] args)
{
petle:
for(int i=0;i<5;i++)
	{
	for(int j=0;j<5;j++)
		{
		System.out.println(i + " " + j);
		if(i==2&&j==2){System.out.println("!!!!!!!!!!!");break petle;}
		}
	}
System.out.println("koniec");
}


}
