
class Game implements GameI {

	public int getSize(){return 10;}
	
	public int getCannons(){return 1;}

	public int getShips(){return 3;}

	public int getShipSize(){return 3;}

	public void start(){}
	
	public boolean shoot( int cannonID, int x, int y ){
	if( (x==1&&y==1) || (x==2&&y==1) || (x==3&&y==1) || (x==0&&y==8) || (x==1&&y==8)
	|| (x==2&&y==8) || (x==5&&y==3) || (x==5&&y==4) || (x==5&&y==5)) return true;
	else { return false;}
	}

	public void stop(){}
}



class Brain implements BrainI {
private GameI gra;
private int liczbaDzial;
private int liczbaOkretow;
private int rozmiarOkretow;
private int rozmiarPlanszy;
int[][] plansza; // wypelniona 0 w miejscach, gdzie warto oddac strzal
int zatopione; // liczba zatopionych okretow



class obslugaArmaty implements Runnable {
int id;
int[] aktualnyX = new int[rozmiarOkretow]; // przechowuje wspolrzedne aktualnie
int[] aktualnyY = new int[rozmiarOkretow]; // ostrzeliwanego okretu
int x,y; // wspolrzedne strzalu
boolean wynik, ostrzeliwujemyStatek=false;
int zatopioneDziala; // liczba zatopionych dzial z aktualnie ostrzeliwanego statku;

public obslugaArmaty(int x){id=x;}

public void run(){

while(zatopione<liczbaOkretow)
	{
	petle:
	if(ostrzeliwujemyStatek==false)
		{
		for(int i=0;i<rozmiarPlanszy;i++) //poszukiwanie wspolrzednych do strzalu
			{
			for(int j=0;j<rozmiarPlanszy;j++)
				{
				if(plansza[i][j]==0)
					{
					x=i;
					y=j;
					break petle;
					}
				}
			}
		} // koniec ifa
	else // poszukiwanie wspolrzednych do strzalu w okret, ktory zaczelismy zatapiac
		{
		if(zatopioneDziala==1) // jeszcze nie wiemy czy okret jest w pionie czy poziomie
			{
			boolean znalezionyPunkt = false;
			// szukamy ktorego z punktu wokol, w ktory warto strzelac
			int tmpX = aktualnyX[0];
			int tmpY = aktualnyY[0];
			if(x>0)
				{
				if(plansza[tmpX-1][tmpY]==0) // tu mozna strzelac!
					{
					znalezionyPunkt = true;
					x=tmpX-1;
					y=tmpY;
					}
				}
			if(x >= 0 && x < (rozmiarPlanszy-1) && znalezionyPunkt == false)
				{
				if(plansza[tmpX+1][tmpY]==0) // tu mozna strzelac!
					{
					znalezionyPunkt = true;
					x = tmpX+1;
					y= tmpY;
					}
				}
			if(y>0 && znalezionyPunkt == false)
				{
				if(plansza[tmpX][tmpY-1]==0) // tu mozna strzelac!
					{
					znalezionyPunkt = true;
					x = tmpX;
					y = tmpY-1;
					}
				}
			if(y>=0 && y < (rozmiarPlanszy-1) && znalezionyPunkt == false)
				{
				if(plansza[tmpX][tmpY+1]==0) // tu mozna strzelac!
					{
					znalezionyPunkt = true;
					x = tmpX;
					y = tmpY+1;
					}
				}
			}
		else
			{
			boolean poziomo=false;
			boolean znalezionyPunkt = false;
			int min,max; // minimalny i maksymalny element naszego okretu
			int plaszczyzna; // Y lub X
			if(aktualnyY[0]==aktualnyY[1]) // nasz okret jest ustawiony poziomo
				{
				poziomo=true;
				plaszczyzna = aktualnyY[0];
				min=max=aktualnyX[0];
				for(int i=0;i<zatopioneDziala;i++)
					{
					if(min > aktualnyX[i]) min=aktualnyX[i];
					if(max < aktualnyX[i]) max=aktualnyX[i];
					}
				if(x<0)
					{
					if(plansza[min-1][plaszczyzna]==0) // tu mozna strzelac!
						{
						znalezionyPunkt = true;
						x = min-1;
						y = plaszczyzna;
						}
					}
				if(x < (rozmiarPlanszy-1) && znalezionyPunkt == false)
					{
					if(plansza[max+1][plaszczyzna]==0) // tu mozna strzelac!
						{
						znalezionyPunkt = true;
						x = max+1;
						y = plaszczyzna;
						}
					}
				}
			else // wyszukujemy elementy min i max w pionie
				{
				plaszczyzna = aktualnyX[0];
				min=max=aktualnyY[0];
				for(int i=0;i<zatopioneDziala;i++)
					{
					if(min > aktualnyY[i]) min=aktualnyY[i];
					if(max < aktualnyY[i]) max=aktualnyY[i];
					System.out.println("[petla] min = " + min);
					}
				System.out.println("Max to " + max + " a min to " + min );
				if(y>0)
					{
					if(plansza[plaszczyzna][min-1]==0) // tu mozna strzelac!
						{
						znalezionyPunkt = true;
						x = plaszczyzna;
						y = min-1;
						}
					}
				if(y < (rozmiarPlanszy-1) && znalezionyPunkt == false)
					{
					if(plansza[plaszczyzna][max+1]==0) // tu mozna strzelac!
						{
						znalezionyPunkt = true;
						x = plaszczyzna;
						y = max+1;
						}
					}
				}
			}
		}
	wynik = gra.shoot(id,x,y);
	System.out.println("Jako armata " + id + " strzelam w " + x + ", " + y +". Wynik to " + wynik);
	if(wynik==false){plansza[x][y]=1;} // w to miejsce juz nie warto strzelac
	if(wynik==true) // otwiera sie nam cale spektrum mozliwosci...
		{
		zatopioneDziala++;
		plansza[x][y]=1; // w to miejsce juz nie warto strzelac
		if(zatopioneDziala<rozmiarOkretow)
			{
			aktualnyX[zatopioneDziala-1]=x;
			aktualnyY[zatopioneDziala-1]=y;
			ostrzeliwujemyStatek=true;
			}
		else if(zatopioneDziala==rozmiarOkretow) // wlasnie udalo nam sie zatopic statek!
			{
			//margines!!!!!!
			aktualnyX = new int[rozmiarOkretow]; //czyscimy tablice
			aktualnyY = new int[rozmiarOkretow];
			zatopioneDziala=0; // zerujemy
			ostrzeliwujemyStatek = false; // wlasnie skonczylismy go ostrzeliwac
			zatopione++; // SYNCHONIZACJA!!!!!!!!
			}
		}
	}
}
}

public void start(){
	int zatopione=0;
	liczbaDzial = gra.getCannons();
	liczbaOkretow = gra.getShips();
	rozmiarOkretow = gra.getShipSize();
	rozmiarPlanszy = gra.getSize();
	plansza = new int[rozmiarPlanszy][rozmiarPlanszy];
	for(int i=0;i<liczbaDzial;i++)
		{
		new Thread(new obslugaArmaty(i)).start();
		System.out.println("@@@@@@@@@@@@@@@@@@");
		}	
	}

public void setGameI(GameI gi){
	gra = gi;
	}
}

class Start {
static public void main(String[] args){
BrainI bi = new Brain();
GameI gi = new Game();
bi.setGameI(gi);
bi.start();
}

}
