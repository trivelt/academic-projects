import java.io.PrintWriter;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.io.BufferedReader;
import java.io.InputStreamReader;

class Start
{

static String generujString(int ile)
{
String ciag="";
for(int i=0;i<ile;i++)
	{
	ciag+="a";
	}
return ciag;
}


public static void main(String args[])
{
double[] tabTime = new double[19];
if(args.length == 1) // Serwer 
	{
	int port = Integer.parseInt(args[0]);
	try 	{
		ServerSocket so = new ServerSocket(port);
		Socket s = so.accept();
		PrintWriter out = new PrintWriter(s.getOutputStream() );
		for(int i=100;i<=1000;i+=50)
			{
			for(int j=0;j<10000;j++) // ciag kazdego rozmiaru jest przesylany 1000 razy
				{
				out.println(generujString(i));
				out.flush();
				}
			}
		} catch(IOException e){System.out.println("Blad");}
	
	}

else if(args.length == 2) // Klient
	{
	String host = args[0];	
	int port = Integer.parseInt(args[1]);
	try	{
		Socket so = new Socket(host, port);
		BufferedReader br = new BufferedReader(new InputStreamReader( so.getInputStream() ) );
		String line;
		int licznik=0;
		int rozmiar=100;
		long start=0, stop=0; // do mierzenia czasu
		int przebieg=0;
		while( (line = br.readLine() ) != null) 
			{
			if(licznik==0)
				{
				start = System.currentTimeMillis();
				//System.out.println("Dostalem (pierwsza) linie numer "+licznik+" o rozmiarze "+rozmiar);
				}
			else if(licznik==9999)
				{
				stop = System.currentTimeMillis();
				//System.out.println("Dostalem (ostatnia) linie numer "+licznik+" o rozmiarze "+rozmiar);
				//System.out.println("\t\tZmierzylem "+(stop-start)+" milisekund");
				licznik=-1;
				rozmiar+=50;
				tabTime[przebieg]=stop-start;
				przebieg++;
				}
			licznik++;
			}
		} catch(Exception e){}
int rozmiar=100;
	for(int i=0;i<19;i++)
		{
		System.out.println("Dla rozmiaru "+rozmiar+" zmierzylem czas "+tabTime[i]+" milisekund");
		System.out.println("Oznacza to, ze dane sa przesylane z predkoscia " + (rozmiar*2*9999)/(tabTime[i]) + " bajtow/sekunde");
		rozmiar+=50;
		}
	}

}
}
