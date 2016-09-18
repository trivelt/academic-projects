/*
Maciej Michalec
Zadanie 2
17.10.2013
*/

class Game {
int rozmiar = 0;
int poprz = 0; // poprzedni ruch: 1-kolko, 2-krzyzyk
String[][] tab; // tablica pol planszy

	public void setSize( int size ) {
	if(size<3){
		System.out.println("Plansza do gry musi mieć wymiary co najmniej 3x3");
		}
	else if(size>30){
		System.out.println("Nie mozna utworzyc planszy o tak duzych rozmiarach (max:30)");
		}
	else 	{ // gdy podane rozmiary sa odpowiednie
		if(rozmiar == 0) { // tworzenie nowej planszy
			rozmiar = size;
			tab = new String[size][size];
			for(int i=0;i<size;i++) // uzupelnianie tablicy pol spacjami
				{
				for(int j=0;j<size;j++)
					{
					tab[i][j]=" ";
					}
				} // koniec for
			} // koniec if
		else if(size > rozmiar) { // powiekszanie planszy
			String[][] tempTab = new String[rozmiar][rozmiar]; // kopia starej planszy
			tempTab = tab;
			tab = new String[size][size];
			for(int i=0;i<size;i++) // uzupelnianie powiekszonej planszy
				{
				for(int j=0;j<size;j++)
					{
					if(i<rozmiar && j<rozmiar) tab[i][j]=tempTab[i][j];
					else tab[i][j] = " ";
					}
				}
			rozmiar = size;
			}
		else if(size < rozmiar) { // zmniejszanie planszy
			int diff = rozmiar-size;
			for(int i=0;i<rozmiar;i++) // sprawdzanie czy mozna dokonac operacji
				{
				for(int j=size;j<size+diff;j++)
					{
					if(tab[i][j] != " ") return; // kontrola wierszy POD nowa plansza
					else if(tab[j][i] != " ") return; // kontrola kolumn na prawo od nowej planszy
					/*System.out.println("[" + i + "][" + j + "]");
					System.out.println("[" + j + "][" + i + "]"); */
					}
				}
			String[][] tempTab = new String[rozmiar][rozmiar]; // kopia starej planszy
			tempTab = tab;
			tab = new String[size][size];
			for(int i=0;i<size;i++)
				{
				for(int j=0;j<size;j++)
					{
					tab[i][j] = tempTab[i][j];
					}
				}
			rozmiar = size;
			}
		} // koniec else
	}

   public void setO( int x, int y ) {
	if(rozmiar == 0) return; // rozmiar planszy nie jest ustawiony
	if(x>=rozmiar || y>=rozmiar || x<0 || y<0) return; // sprawdzenie zakresu
	if(tab[x][y] == "O" || tab[x][y] == "X") return; // zajetosc pola
	if(poprz == 1) return;
	tab[x][y] = "O";
	poprz = 1;
	} 

   public void setX( int x, int y ) {
	if(rozmiar == 0) return; // rozmiar planszy nie jest ustawiony
	if(x>=rozmiar || y>=rozmiar || x<0 || y<0) return; // sprawdzenie zakresu
	if(tab[x][y] == "O" || tab[x][y] == "X") return; // zajetosc pola
	if(poprz == 2) return;
	tab[x][y] = "X";
	poprz = 2;
	}

   public String toString() {
	if(rozmiar == 0) return null;
	String plansza = new String();
	int k=0; // licznik dla indeksu tablicy
	for(int i=0;i<=2*rozmiar;i++) // ilosc wierszy
		{
		if(i%2 == 0) // wyswietlanie wierszy pomiedzy polami
			{
			plansza+="+";
			for(int j=0;j<rozmiar;j++)
				{
				plansza+="-+";
				}
			plansza+="\n";
			}
		else
			{
			for(int j=0;j<=rozmiar;j++) // wyswietlanie wierszy z polami 
				{
				plansza+="|";
				if(j<rozmiar) plansza+=tab[j][k];
				}
			plansza+="\n";
			k++;
			}
		}
	return plansza;
	}

	public boolean anyEmpty() { 
	if(rozmiar == 0) return false;
	for(int i=0;i<rozmiar;i++) // uzupelnianie tablicy pol spacjami
		{
		for(int j=0;j<rozmiar;j++)
			{ // jesli ktorekolwiek z pol jest puste to plansza nie jest zapelniona
			if(tab[i][j] == " ") return true;
			}
		}
	return false;
	}
}
