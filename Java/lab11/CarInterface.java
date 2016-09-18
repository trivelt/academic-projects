
public interface CarInterface {
	/**
	 * Auto jedzie szybciej.
	 */
	public void faster();
	
	/**
	 * Auto jedzie wolniej lub zatrzymuje sie.
	 */
	public void slower();
	
	/**
	 * Auto zmienia kierunek ruchu
	 */
	public void oppositeDirection();
	
	/**
	 * Auto sie natychmiast zatrzymuje.
	 */
	public void stop();
	
	/**
	 * Podaje aktualna predkosc auta
	 * @return - predkosc auta w MPH
	 */
    public int getVelocity();
    
    /**
     * Prezentuje na ekranie predkosc auta (wystarczy liczba), 
     * ale tylko wtedy, gdy 
     * jej wartosc jest inna niz w chwili ostatniej prezentacji.
     * Czyli, jesli wyswietlona zostala predkosc 10, to 10 nie moze
     * pojawic sie ponownie. Metoda ma eliminowac prezentacje tych samych
     * wartosci predkosci, nawet jesli stan auta ulegal zmianie.
     */
    public void showVelocity();
}
