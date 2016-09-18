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
List<Para> al;

	void wypiszListe()
	{
	ListIterator<Para> it = al.listIterator();
	Para wsk = null;
	int i=0;
	System.out.println("\n========== Wypisywacz listy ==========");
	while(it.hasNext())
		{
		wsk = it.next();
		System.out.println("Element numer " + i + ": " + wsk.x + ", " + wsk.y);
		i++;
		}
	}

	public void setBackgroundBrightness( int b ){
	kolorTla = b;
	al = new ArrayList<Para>();
	al.add( new Para(b,dlBoku*dlBoku) );
		wypiszListe();
	}
	
	public void setSize( int s ){
	dlBoku = s;
	}

	public void setPenBrightness( int b ){
	kolorPedzla = b;
	}

	public void setPixel( int x, int y ){
	int i=0;
	int odlOdPoczatku = dlBoku*y+x;
	int suma=0;
	ListIterator<Para> it = al.listIterator();
	Para wsk = null;
	wypiszListe();
	while(it.hasNext())
		{
		wsk = it.next();
		suma=suma+wsk.y;
		i++;
		if(suma>odlOdPoczatku) {break;}
		}
System.out.println("GDZIE JA JESTEM?!!!!!!!!!!\nSuma to " + suma + ", a kolor biezacy to " + wsk.x);	
	if(wsk.x==kolorPedzla) // czy poprzedni kolor jest taki sam jak aktualny
		{
		System.out.println("Jestem w pierwszym ifie: Poprzedni kolor jest taki sam");	
		if(wsk.y!=suma) wsk.y=wsk.y+1; // zapobiega zwiekszeniu rozmiaru obrazka 
		if( it.hasNext()) // czy nastepny kolor jest taki sam jak poprzedni i aktualny
			{
			wsk = it.next();
			if(wsk.x == kolorPedzla)
				{
				int tmp=wsk.y;
				wsk.y=0;
				wsk=it.previous();
				wsk.y=wsk.y+tmp;
				System.out.println("Kolejny i poprzedni kolor jest taki sam");
				}
			}
		}
	else if( it.hasNext()) // czy nastepny kolor jest taki sam jak aktualny
		{
		System.out.println("Jestem w drugim ifie - jest nastepny kolor");
		if(wsk.y==1) //jestesmy w obszarze o rozmiarze 1
			{
			System.out.println("To pole ma tylko 1 ");
			wsk=it.next();
			if(wsk.x==kolorPedzla){
				int tmp=wsk.y;
				it.remove();
				wsk=it.previous();
				it.remove();
				wsk=it.previous();
				wsk.y=wsk.y+tmp+1;
				}
			else
				{
				wsk=it.previous();
				wsk=it.previous();
				wsk.x=kolorPedzla;
				}
			}
		else {
			wsk = it.next();
			if(wsk.x == kolorPedzla)
				{
				wsk.y=wsk.y+1;
				wsk=it.previous();
				wsk.y=wsk.y-1;
				wsk=it.next();
				System.out.println("Kolejny kolor jest taki sam");
				}
			else
				{
				wsk = it.previous();
//				wsk.y=wsk.y-1;
				al.add( new Para(kolorPedzla,1) );
				}
			}
		}
	else // kolor piksela jest rozny od koloru poprzedzajacego i nastepujacego 
		{
		System.out.println("ssSuma to " + suma);	
		// musimy podzielic zakolorowany obszar na dwa i wstawic pomiedzy piksel 
		int diff=suma-odlOdPoczatku-1;
		int poczatekPrevKoloru = suma-wsk.y;
		wsk.y=odlOdPoczatku-poczatekPrevKoloru;
		al.add( new Para(kolorPedzla,1) );
		al.add( new Para(wsk.x,diff) );
		}
		wypiszListe();
	}
	public void saveImage( String file )
	{
	java.io.FileWriter wyjsciowy;
		try{
	wyjsciowy = new FileWriter(file);
	String tmp = Integer.toString(dlBoku) + "\n";
	wyjsciowy.write(tmp);	


	ListIterator<Para> it = al.listIterator();
	Para wsk = null;
	while(it.hasNext())
		{
		wsk = it.next();
		tmp = (wsk.x + " " + wsk.y + "\n");
		System.out.println(tmp);
		if(wsk.y!=0)
			{
			wyjsciowy.write(tmp);
			}
		}


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
obrazek.setPixel(0,1);

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
