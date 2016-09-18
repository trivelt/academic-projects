
public interface UserInterface {
	/**
	 * Pozwala na dostep do obiektu gry poprzez GameInterface.
	 * @param g referencja do obiektu zgodnego z interfejsem 
	 * GameInterface
	 */
	void registerGame( GameInterface g );
	
	/**
	 * Zacznij gre. Metoda konczy sie z chwila zniszczenia
	 * wszystkich okretow na planszy.
	 */
	void start();
}
