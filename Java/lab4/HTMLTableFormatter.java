/** Klasa abstrakcyjna do tworzenia klas odpowiedzialnych za generowanie
tabel w jezyku HTML. Ponizej fragment kodu HTML ze strony
http://www.w3schools.com/html/html_tables.asp, 
ktory podzielono za pomoca znakow {N*}{*N} na kilka sekcji. 
Poszczegolne sekcje HTML sa
generowane przez odpowiednie metody tej klasy. 
<b>Uwaga</b>: obiekty tej klasy sa
jednokrotnego uzytku - oznacza to, ze jeden obiekt pozwala na 
wygenerowanie kodu HTML tylko jednej tabeli.
<br>
<br>
<pre>
{1*}
&lt;table border="1">
&lt;tr>
&lt;th>Header 1&lt;/th>
&lt;th>Header 2&lt;/th>
&lt;/tr>
{*1}
{2*}
&lt;tr>
&lt;td>row 1, cell 1&lt;/td>
&lt;td>row 1, cell 2&lt;/td>
&lt;/tr>
{*2}
{2*}
&lt;tr>
&lt;td>row 2, cell 1&lt;/td>
&lt;td>row 2, cell 2&lt;/td>
&lt;/tr>
{*2}
{3*}
&lt;/table>
{*3}
</pre>

*/
abstract public class HTMLTableFormatter {
	/** 
	Metoda pozwala na przekazanie do obiektu informacji o ilosci
	kolumn w tabeli oraz ich nazwach. Moze zostac ponownie uzyta
	i nadpisac poprzednie wartosci 
	tylko jesli nie wykonono wczesniej metody getHeader.
	@param names Lista nazw kolumn tabeli
	*/
	abstract public void setCols( String[] names );
	
	/** 
	Metoda pozwala na przekazanie do obiektu informacji o grubosci
	obramowania tabeli. Metode mozna wykonac ponownie, o ile nie zaczeto juz
	generowac kodu HTML za pomoca getHeader(). Jesli metoda nie zostala
	wywolana dla danego obiektu, sekcja argument border nie jest ustawiany.
	@param width Grubosc ramki wokol tabeli
	*/
	abstract public void setBorderWidth( int width );
	
	/** 
	Metoda zwraca ciag znakow bedacych kodem HTML
	odpowidzialnym za rozpoczecie pracy z tabela i
	wyswietlenie nazw poszczegolnych kolumn - w 
	przykladowym kodzie odpowiada tekstowi od {1*}
	do {*1}. Ponowne wywolanie tej metody powoduje
	zwroceniem pustego ciagu znakow (nie null!).
	Wywolanie tej metody bez wczesniejszego wywolania
	metody setCols konczy sie zwroceniem
	pustego ciagu znakow.

	@return Zwraca kod HTML odpowiedzialny za rozpoczecie pracy z tabela
	i prezentacje nazw kolumn. Jesli nie wykonano wczesniej metody setCols
	metoda zwraca pusty ciag znakow.
	*/
	abstract public String getHeader();
	
	/** 
	Metoda przyjmuje informacje o zawartosci poszczegolnych
	pol tabeli w danym rzedzie i generuje stosownych kod
	HTML. W przykladowym kodzie tabeli,  praca tej metody
	zaczyna sie od {2*} a konczy na {*2} (aby uzyskac
	wynik zgodny z przykladem, metode getRow trzeba wywolac
	dwukrotnie). Jesli nie wykonano wczesniej metody setCols
	zwraca ona pusty ciag znakow. Podobnie, jesli nie wykonono
	metody getHeader zwracany jest pusty ciag znakow. W przypadku
	dostarczenia tablicy o rozmiarze innym niz liczba
	kolumn tabeli (rozmiar tabli przeslanej do metody setCols),
	zwracany jest pusty ciag znakow.
	
 	@param values Wartosci poszczegolnych kolumn tabeli
	@return Kod HTML, ktory spowoduje prawidlowe wyswietlenie
	jednego wiersza tabeli ze stosowna zawartoscia pol. Jesli
	nie wykonano wczesniej setCols lub getHeader zwraca pusty
	ciag znakow. Jesli przeslano tablice o rozmiarze niezgodnym
	z liczba kolumn przetwarzanej tabelki, zwraca pusty ciag znakow.
	*/
	abstract public String getRow( String[] values );
	
	/** 
	Metoda zwraca ciag znakow bedacych kodem HTML
	odpowidzialnym za zakonczenie pracy z tabela - w 
	przykladowym kodzie odpowiada tekstowi od {3*}
	do {*3}. Ponowne wywolanie kodu tej metody
	musi zakonczyc sie zwroceniem pustego ciagu znakow (nie null!).
	Jesli nie wykonono wczesniej metody getHeader zwraca pusty
	ciag znakow.
	@return Kod HTML konczacy prace z tabela, lub w gdy nie wykonano wczesniej
	getHeader - pusty ciag znakow.
	*/
	abstract public String getFooter();	
}


/*


Przklad ze strony: 
*/
