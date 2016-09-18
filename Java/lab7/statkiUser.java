import java.util.*;

class Para {
int a, b;
Para(){}
Para(int x) {a=b=x;}
Para(int x, int y) {a=x;b=y;}
}

class User implements UserInterface
{
int maxX, maxY, minX, minY;
Collection<Para> statki; //kolekcja zawierajaca wspolrzedne pol ze statkami
Collection<Para> puste;
GameInterface gra;

	String rysujPlansze(){return "";}

	public void registerGame(GameInterface g){
	maxX=maxY=g.MAX_INDEX;
	minX=minY=g.MIN_INDEX;
	gra = g;
	statki = new ArrayList<Para>();
	}

	Para losujPunkt()
	{
	return new Para(0,0);
	}


	public void start(){
	int zmWsp=0; //zmiana x - 1, zmiana y - 2
	int x=maxX,y=maxY;
	boolean swapped=false;
	do {
	try 	{
		gra.shot(x,y);
		statki.add(new Para(x,y));
		}
	catch(IndexTooSmallException e) {
		if(x!=y && swapped==false){
			int tmp = y;
			y=x;
			x=tmp;
			swapped=true;
			}
		else 	{
			
			}
	}
	catch(IndexTooLargeException e) {}
	catch(MissedException e) {}
	} while(true);
	} 


}
