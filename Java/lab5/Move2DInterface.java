/**
 * Interfejs sterowania ruchem punktu w dwu-wymiarowej przestrzeni liczb
 * rzeczywistych. Ruch mozliwy jest w 4-ech podstawowych kierunkach o zadany krok.
 * Dlugosc kroku moze ulegac zmianie. Interfejs pozwala na uzyskanie
 * informacji o liczbie wykonanych krokow i odleglosci od punktu
 * startowego, ktorym jest poczatek ukladu wspolrzednych. 
 * 
 * @author Piotr Oramus
 * @version 1.0
 */
public interface Move2DInterface {
	/**
	 * Ustala dlugosc pojedynczego kroku. Jak dlugo dlugosc kroku nie zostanie
	 * podana, punktu nie mozna przesunac. Dlugosc kroku moze ulagac zmianie w trakcie
	 * pracy programu. 
	 * @param step Dlugosc kroku
	 */
	void setStep( double step );
	
	/**
	 * Przesuniecie punktu w gore ukladu wspolrzednych.
	 */
	void north();
	/**
	 * Przesuniecie punktu w dol ukladu wspolrzednych.
	 */
	void south();
	/**
	 * Przesuniecie punktu w prawo ukladu wspolrzednych
	 */
	void east();
	/**
	 * Przesuniecie punktu w lewo ukladu wspolrzednych
	 */
	void west();
	
	/**
	 * Zwraca liczbe wykonanych krokow
	 * @return liczba wykonanych krokow
	 */
	int getSteps();
	
	/**
	 * Zwraca odleglosc od punktu startowego wyznaczona jako
	 * pierwiastek z sumy kwadratow wspolrzednych czyli
	 * sqrt( x^2 + y^2 )
	 * @return odleglosc od punktu startowego
	 */
	double getDistance();
	
	/** Zwraca odleglosc od punktu startowego wyznaczona jako 
	 * suma wartosci bezwzglednych wspolrzednych punktu, czyli
	 * |x|+|y|
	 * @return odleglosc od punktu startowego
	 */
	double getSumAbsDistance();
}
