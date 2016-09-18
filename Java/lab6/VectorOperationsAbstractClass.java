/**
 * Klasa bazaowa zawierajaca publiczna metode szablonowa prostych operacji
 * matematycznych na wektorach. 
 * <a href="http://pl.wikipedia.org/wiki/Metoda_szablonowa_(wzorzec_projektowy)">
 * Metoda szablonowa - wzorzec projektowy</a>
 * @author Piotr Oramus
 * @version 1.0
 */
public abstract class VectorOperationsAbstractClass {
	/**
	 * Uproszczona "normalizacja" wektora. Wszystkie elementy wektora dzielone są
	 * przez największy ze składników, w ten sposob wszystkie nie sa wieksze od 1.0
	 * @param v - wektor do "normalizacji"
	 */
	abstract protected void normalize( double[] v );
	
	/**
	 * Prezentuje elementy wektora na terminalu w postaci: 
	 * <pre>
	 * v[0]=wartosc0 v[1]=wartosc1 v[2]=wartosc2 itd.
	 * </pre>
	 * @param v - wektor do wyswietlenia na ekranie
	 */
	abstract protected void show( double[] v );
	
	/**
	 * Wykonuje obliczenia na wektorach. Wynik zapisywany jest w wektorze c.
	 * @param a - pierwszy argument operacji wektorowej
	 * @param b - drugi argument operacji wektorowej
	 * @param c - wynik operacji
	 */
	abstract protected void calc( double[] a, double[] b, double[] c );
	
	/**
	 * Metoda pomocnicza: prezentuje skladowe wektora przed i po normalizacji
	 * @param v - wektor do przetworzenia
	 */
	private void showNormalizeShow( double[] v ) {
		show(v);
		normalize(v);
		show(v);
	}
	
	/**
	 * Metoda odpowiedzialna za przetworzenie dwoch wektorow a i b do wyniku
	 * zapisanego w wektorze c i prezentacje etapow obliczen.
	 * @param a - pierwszy argument operacji wektorowej
	 * @param b - drugi argument operacji wektorowej
	 * @param c - wynik operacji wektorowej
	 */
	public void doIt( double[] a, double[] b, double[] c ) {
		showNormalizeShow( a );
		showNormalizeShow( b );
		calc( a, b, c );
		showNormalizeShow( c );
	}
}
