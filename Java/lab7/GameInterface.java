public interface GameInterface {
	/**
	 * Najmniejszy indeks, pod ktorym mozna szukac planszy z okretami.
	 */
	int MIN_INDEX = -100;
	/**
	 * Najwiekszy indeks, pod ktorym mozna szukac planszy z okretami.
	 */
	int MAX_INDEX = 100;

	/**
	 * Strzal do celu. Jesli metoda nie zwraca wyjatku to oznacza, ze strzal byl
	 * celny.
	 * 
	 * @param x
	 *            wspolrzedna x
	 * @param y
	 *            wspolrzedna y
	 * @throws IndexTooSmallException
	 *             jeden z indeksow jest poza granica planszy do gry i jest zbyt
	 *             maly
	 * @throws IndexTooLargeException
	 *             jeden z indeksow jest poza granica planszy do gry i jest zbyt
	 *             duzy
	 * @throws MissedException
	 *             strzal w plasze, ale zaden statek nie zostal trafiony
	 */
	void shot(int x, int y) throws IndexTooSmallException,
			IndexTooLargeException, MissedException;
}
