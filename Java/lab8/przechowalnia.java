import java.util.*;

class Przechowalnia implements PrzechowalniaInterface
{
List<Paczka> al;

	//konstruktor
	Przechowalnia(){al = new ArrayList<Paczka>();}

	public void przechowajPaczke( Paczka p ){
	System.out.println("Dodaje paczke");
	al.add(p);
	}

	public List<Paczka> paczkiPosortowaneWgObjetosci(){
	Collections.sort( al, new SortowanieWgObjetosci() );
	return al;
	}
	
	public List<Paczka> paczkiPosortowaneWgCiezaru(){
	Collections.sort( al, new SortowanieWgCiezaru() );
	return al;
	}
	
	public List<Paczka> paczkiPosortowaneWgPolaPowierzchniPodstawy(){
	Collections.sort( al, new SortowanieWgPola() );
	return al;
	}

}

class SortowanieWgObjetosci implements Comparator<Paczka>
{
	public int compare(Paczka a, Paczka b){
	int objA = a.dlugosc * a.szerokosc * a.wysokosc;
	int objB = b.dlugosc * b.szerokosc * b.wysokosc;
	if ( objA < objB ) return -1;
	if ( objA > objB ) return 1;
	return 0;
	}
}

class SortowanieWgCiezaru implements Comparator<Paczka>
{
	public int compare(Paczka a, Paczka b){
	if ( a.masa < b.masa ) return -1;
	if ( a.masa > b.masa ) return 1;
	return 0;
	}
}

class SortowanieWgPola implements Comparator<Paczka>
{
	public int compare(Paczka a, Paczka b){
	int poleA = a.dlugosc * a.szerokosc;
	int poleB = b.dlugosc * b.szerokosc;
	if ( poleA < poleB ) return -1;
	if ( poleA > poleB ) return 1;
	return 0;
	}
}

class Start{

   private static void show( Iterator<Paczka> it, String komentarz ) {
       System.out.println( komentarz );
       while( it.hasNext() ) {
	Paczka p = it.next();
	System.out.println("Dlugosc: " + p.dlugosc + ", Szerokosc: " + p.szerokosc + ", Wysokosc: " + p.wysokosc + ", Masa: " + p.masa);
       }
   }



	static public void main(String[] args){
	Przechowalnia przech = new Przechowalnia();
	Paczka p1 = new Paczka();
	Paczka p2 = new Paczka();
	Paczka p3 = new Paczka();
	List<Paczka> listka;


	p1.dlugosc=1;
	p1.szerokosc=7;
	p1.wysokosc=5;
	p1.masa=4;

	p2.dlugosc=6;
	p2.szerokosc=1;
	p2.wysokosc=2;
	p2.masa=7;

	p3.dlugosc=12;
	p3.szerokosc=2;
	p3.wysokosc=1;
	p3.masa=3;

	przech.przechowajPaczke(p1);
	przech.przechowajPaczke(p2);
	przech.przechowajPaczke(p3);

	listka = przech.paczkiPosortowaneWgObjetosci();	
	show(listka.iterator(), "Wg. objetosci");
	listka = przech.paczkiPosortowaneWgPolaPowierzchniPodstawy();
	show(listka.iterator(), "Wg. pola");
	listka = przech.paczkiPosortowaneWgCiezaru();
	show(listka.iterator(), "Wg. ciezaru");
	}

}
