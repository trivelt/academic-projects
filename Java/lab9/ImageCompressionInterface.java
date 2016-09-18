/**
 * Interfejs pozwala na stworzenie kwadratowego, czarno-bialego
 * obrazu i jego zapisanie w pliku w postaci skompresowanej.
 * 
 * @author Piotr Oramus
 *
 */
public interface ImageCompressionInterface {
	/**
	 * Ustala kolor tla. Wszystkie piksele obrazu zostaja
	 * nadpisane tym kolorem. Uzycie metody rownoznaczne
	 * jest z wypelnieniem calego obrazu pikselami o
	 * podanej jasnosci.
	 * @param b - jasnosc tla obrazu. Od 0 (czarny) do 255 (bialy).
	 */
	void setBackgroundBrightness( int b );
	
	/**
	 * Ustala rozmiar obrazu. Obraz zawsze jest kwadratowy.
	 * Podawana jest dlugosc boku w plikelach.
	 * @param s - dlugosc boku w pikselach.
	 */
	void setSize( int s );
	
	/**
	 * Ustala jasnosc piora. 
	 * @param b - jasnosc piora. Od 0 do 255.
	 */
	void setPenBrightness( int b );
	
	/** Piksel o wskazanych koordynatach zmienia jasnosc
	 * na jasnosc piora. Wsporzedna 0, 0 oznacza gorny-lewy rog
	 * obrazka. Znaczenie wspolrzednych x i y jak w standardowym
	 * ukladzie spolrzednych.
	 * @param x - wspolrzedna x obrazu
	 * @param y - wspolrzedna y obrazu
	 */
	void setPixel( int x, int y );
	
	/** Zapisuje obraz na dysku we wskazanym pliku. Obraz zapisywany 
	 * jest w pliku tekstowym w nastepujacym formacie:
	 * <br>pierwsza linijka - rozmiar boku obrazu w pikselach
	 * <br>w kolejnych linijkach - jasnosc i liczba kolejnych pikseli o tej
	 * samej jasnosci. 
	 * <br><br>Pierwszy zakodowany piksel ma pozycje 0,0. Obraz kodowany
	 * jest rzedami. W obrebie jednego rzedu od lewej do prawej strony.
	 * Po zakodowaniu calego rzedu przetwarzany jest rzad kolejny.
	 * Przyklad: obraz o nastepujacych poziomach jasnosci pikseli:
	 * <pre>
	 * 255 255 100 100
     * 100 200 199 199
     * 199 101 101 101
     * 101 101 101 101
     * </pre>
     * Zostanie zapisany tak:
     * <pre>
     * 4
     * 255 2
     * 100 3
     * 200 1
     * 199 3
     * 101 7
     * </pre>
     * 
	 * @param file - nazwa pliku w ktorym ma zostac zapisany obraz. Moze
	 * zawierac pelna sciezke z nazwa pliku, jesli plik ma zostac zapisany
	 * w katalogu innym niz biezacy.
	 */
	void saveImage( String file );
}
