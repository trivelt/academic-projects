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

