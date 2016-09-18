import java.util.concurrent.*;

class Game implements GameI {

	public int getSize(){return 10;}
	
	public int getCannons(){return 2;}

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
private static final Semaphore sem = new Semaphore(1);
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
int liczbaStrzalow=0;

public obslugaArmaty(int x){id=x;}

public void run(){

while(zatopione<liczbaOkretow)
	{
	sem.acquireUninterruptibly();
	petle:
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
	sem.release();
	wynik = gra.shoot(id,x,y);
	liczbaStrzalow++;
	System.out.println("Jako armata " + id + " strzelam w " + x + ", " + y +". Wynik to " + wynik);
	if(wynik==false){	sem.acquireUninterruptibly(); plansza[x][y]=1; sem.release();} // w to miejsce juz nie warto strzelac
	if(wynik==true) // otwiera sie nam cale spektrum mozliwosci...
		{
		zatopioneDziala++;
		sem.acquireUninterruptibly();
		plansza[x][y]=1; // w to miejsce juz nie warto strzelac
		sem.release();
		if(zatopioneDziala<rozmiarOkretow)
			{
			aktualnyX[zatopioneDziala-1]=x;
			aktualnyY[zatopioneDziala-1]=y;
			ostrzeliwujemyStatek=true;
			
			}
		else if(zatopioneDziala==rozmiarOkretow) // wlasnie udalo nam sie zatopic statek!
			{
			aktualnyX[zatopioneDziala-1]=x;
			aktualnyY[zatopioneDziala-1]=y;
			aktualnyX = new int[rozmiarOkretow]; //czyscimy tablice
			aktualnyY = new int[rozmiarOkretow];
			zatopioneDziala=0; // zerujemy
			ostrzeliwujemyStatek = false; // wlasnie skonczylismy go ostrzeliwac
			zatopione++; // SYNCHONIZACJA!!!!!!!!
			}
		}//sem.release();
	}
System.out.println("(ID:)"+id+ " Wykonano " + liczbaStrzalow + " strzalow");
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
