import java.util.List;

public interface PrzechowalniaInterface {
	
	/**
	 * Przesyla do przechowalni paczke reprezentowana
	 * przez obiekt.
	 * @param p - obiekt do przechowania w systemie
	 */
	void przechowajPaczke( Paczka p );

	/**
	 * Zwraca paczki posortowane wg. ich objetosci 
	 * (dlugosc * szerokosc * wysokosc ).
	 * @return posortowana wg objetosci lista paczek. 
	 */
	List<Paczka> paczkiPosortowaneWgObjetosci();
	
	/**
	 * Zwraca paczki posortowane wg. ciezaru (masy)
	 * @return posortowana wg ciezaru (masy) lista paczek
	 */
	List<Paczka> paczkiPosortowaneWgCiezaru();
	
	/**
	 * Zwraca paczki posortowane wg. pola powierzchni podstawy 
	 * (dlugosc * szerokosc)
	 * @return posortowana wg. pola powierzchni podstawy lista paczek
	 */
	List<Paczka> paczkiPosortowaneWgPolaPowierzchniPodstawy();
}
