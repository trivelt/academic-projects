import java.util.*;
import java.io.*;

class Para {
public int x;
public int y;
Para(){}
Para(int a, int b){x=a; y=b;}
Para(int a){x=y=a;}
}

class ImageCompression implements ImageCompressionInterface {
int kolorTla;
int kolorPedzla;
int dlBoku;
int[][]tab;

	public void setBackgroundBrightness( int b ){
	kolorTla = b;
	tab=new int[dlBoku][dlBoku];
	for(int y=0;y<dlBoku;y++)
		{
		for(int x=0;x<dlBoku;x++)
			{
			tab[x][y]=kolorTla;
			System.out.println("Indeksy to ["+x+"]["+y+"]");
			}
		}
	}
	
	public void setSize( int s ){
	dlBoku = s;
	}

	public void setPenBrightness( int b ){
	kolorPedzla = b;
	}

	public void setPixel( int x, int y ){
	tab[x][y]=kolorPedzla;
	}
	public void saveImage( String file )
	{
	java.io.FileWriter wyjsciowy;
		try{
	wyjsciowy = new FileWriter(file);
	String tmp = Integer.toString(dlBoku) + "\n";
	wyjsciowy.write(tmp);	
	int prevKolor=tab[0][0];
	int licznikKol=0;
	for(int y=0;y<dlBoku;y++)
	{
	for(int x=0;x<dlBoku;x++)
		{
		System.out.println("Poczatek petli: kolorBiezacy="+tab[x][y]+" prevKolor="+prevKolor+" Licznik="+licznikKol);
		if(tab[x][y]==prevKolor)
			{
			licznikKol=licznikKol+1;
			}
		else
			{
			System.out.println(prevKolor+" "+licznikKol);
			tmp=(prevKolor+" "+licznikKol+"\n");
			wyjsciowy.write(tmp);
			licznikKol=1;
			}
//		System.out.println("Indeksy to ["+x+"]["+y+"]");
		prevKolor=tab[x][y];
		}

	}		System.out.println(prevKolor+" "+licznikKol);
			tmp=(prevKolor+" "+licznikKol);
			wyjsciowy.write(tmp);

	wyjsciowy.close();
		}
		catch(IOException e){}
	}
}

class Start
{
public static void main(String[] args){
ImageCompression obrazek = new ImageCompression();
obrazek.setSize(4);
obrazek.setBackgroundBrightness(101);

obrazek.setPenBrightness(255);
obrazek.setPixel(0,0);
obrazek.setPixel(1,0);

obrazek.setPenBrightness(100);
obrazek.setPixel(2,0);
obrazek.setPixel(3,0);
obrazek.setPixel(0,1);

obrazek.setPenBrightness(199);
obrazek.setPixel(2,1);
obrazek.setPixel(3,1);
obrazek.setPixel(0,2);

obrazek.setPenBrightness(200);
obrazek.setPixel(1,1);


obrazek.saveImage("testowy123.txt");
}
}
