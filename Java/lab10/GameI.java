
public interface GameI {

	/**
	 * Zwraca rozmiar planszy 
	 * @return rozmiar planszy
	 */
	public int getSize();
	
	/**
	 * Zwraca liczbe dostepnych dzial
	 * @return liczba dostepnych dzial
	 */
	public int getCannons();
	
	/**
	 * Zwraca liczbe okretow przeciwnika
	 * @return liczba okretow przeciwnika
	 */
	public int getShips();
	
	/**
	 * Zwraca rozmiar okretu przeciwnika. Wszystkie okrety sa tego samego rozmiaru.
	 * @return rozmiar okretu przeciwnika
	 */
	public int getShipSize();
	
	/**
	 * Rozpoczyna pomiar czasu. Przed wywolaniem tej metody nie wolno strzelac.
	 */
	public void start();
	
	/**
	 * Zleca wykonanie strzalu dzialem o podanym identyfikatorze i zwraca wynik. TRUE - trafienie, FALSE - pudlo.
	 * 
	 * @param cannonID identyfikator dziala, ktore ma oddac strzal
	 * @param x koordynata x celu
	 * @param y koordynata y celu
	 * @return informacja o wyniku strzelania. TRUE - trafienie, FALSE - pudlo
	 */
	public boolean shoot( int cannonID, int x, int y );
	
	/** 
	 * Konczy gre i pomiar czasu. Przed wywolaniem tej metody wszystkie okrety przeciwnika musza
	 * juz byc zatopione
	 */
	public void stop();
}
