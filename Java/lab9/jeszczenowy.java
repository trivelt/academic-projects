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
	while(it.hasNext())
		{
		wsk = it.next();
		suma=suma+wsk.y;
		i++;
		if(suma>=odlOdPoczatku) {break;}
		}
	if(wsk.x==kolorPedzla)
		{System.out.println("Tu estem");
		//nothing to do 
		wsk.y=wsk.y+1;
		wsk=it.next();
		wsk.y=wsk.y-1;
		}
	else if(it.hasNext())
		{
		if(wsk.x==1) // pole o rozmiarze 1
			{
			if(it.hasPrevious())
				{
				wsk = it.previous(); //poprzedni kolor
				if(wsk.x == kolorPedzla)
					{
					wsk = it.next(); //biezacy kolor
					wsk = it.next(); //nastepny
					if(wsk.x==kolorPedzla)	//scalanie z oboma
						{
						int tmp=wsk.y;
						it.remove();
						wsk=it.previous();
						it.remove();
						wsk=it.previous();
						wsk.y=wsk.y+tmp+1;
						}
					else 	//scalanie z poprzednim
						{
						wsk = it.previous();
						it.remove();
						wsk = it.previous();
						wsk.y=wsk.y+1;
						}
					}
				}
			if((wsk=it.next()).y==kolorPedzla)
				{
				wsk=it.previous();
				wsk=it.previous();
				if(wsk.x!=kolorPedzla) //scalanie z nastepnym
					{
					wsk=it.next();
					wsk=it.next();
					int tmp=wsk.y;
					it.remove();
					wsk=it.previous();
					wsk.y=tmp+1;
					}
				}
			else 	{
				wsk=it.previous();
				wsk=it.previous();
				if(wsk.x!=kolorPedzla)	//podmiana koloru
					{
					wsk=it.next();
					wsk.y=kolorPedzla;
					}
				}
			}
		else
			{
			if(suma==odlOdPoczatku+1)
				{
				wsk=it.next(); // nastepny kolor
				if(wsk.x==kolorPedzla) //zmniejszanie i scalanie
					{
					wsk.y=wsk.y+1;
					wsk=it.previous();
					wsk=it.previous();
					wsk.y=wsk.y-1;
					}
				else 	//zmniejszanie
					{
					wsk=it.previous();
					wsk.y=wsk.y-1;
					it.add(new Para(kolorPedzla,1));
					}
				}
			else 	//dzielenie obszaru
				{
				int diff=suma-odlOdPoczatku-1;
				System.out.println("Diff="+odlOdPoczatku);
				int poczatekPrevKoloru = suma-wsk.y;
				wsk.y=odlOdPoczatku-poczatekPrevKoloru;
				al.add( new Para(wsk.x,diff) );
				al.add( new Para(kolorPedzla,1) );
				}
			}
		}
	else
		{
		if(suma==odlOdPoczatku) //zmniejszanie
			{
			wsk.y=wsk.y-1;
			al.add( new Para(kolorPedzla,1) );
			}
		else //dzielenie obszaru
			{
			if(suma-odlOdPoczatku==wsk.y)
				{
				//System.out.println("Tu jestem");
				int tmp1=wsk.y-1;
				int tmp2=wsk.x;
				wsk.y=1;
				wsk.x=kolorPedzla;
				al.add( new Para(tmp2,tmp1) );
				}
			else
				{

				System.out.println("Suma="+suma+", wskOdPocz="+odlOdPoczatku+", wsk.y="+wsk.y);

				int diff=suma-odlOdPoczatku-1;
				int poczatekPrevKoloru = suma-wsk.y;
				wsk.y=odlOdPoczatku-poczatekPrevKoloru;
				al.add( new Para(kolorPedzla,1) );
				if(diff!=0) al.add( new Para(wsk.x,diff) );
				}
			}
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
obrazek.setPixel(1,0);

obrazek.setPenBrightness(100);
obrazek.setPixel(2,0);
/*obrazek.setPixel(3,0);
obrazek.setPixel(0,1);

obrazek.setPenBrightness(199);
obrazek.setPixel(2,1);
obrazek.setPixel(3,1);
obrazek.setPixel(0,2);

obrazek.setPenBrightness(200);
obrazek.setPixel(1,1);


obrazek.saveImage("testowy123.txt");
*/

}
}
