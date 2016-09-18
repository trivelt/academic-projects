class Move2D implements Move2DInterface {

	double krok;
	int licznik=0;
	double posX=0;
	double posY=0;
	boolean setStep=false;

	public void setStep( double step ){
	krok = step;	
	setStep=true;
	}

	public void north(){
	if(setStep==true){
		posY=posY+krok;
		licznik++;
		System.out.println("[NORTH] Aktualne wspolrzedne to X:" + posX + " Y:" + posY);
		}
	}

	public void south(){
	if(setStep==true){
		posY=posY-krok;
		licznik++;
		System.out.println("[SOUTH] Krok to " + krok + " Aktualne wspolrzedne to X:" + posX + " Y:" + posY);
		}
	}

	public void east(){
	if(setStep==true){
		posX=posX+krok;
		licznik++;
		System.out.println("[EAST] Aktualne wspolrzedne to X:" + posX + " Y:" + posY);
		}
	}

	public void west(){
	if(setStep==true){
		posX=posX-krok;
		licznik++;
		System.out.println("[WEST] Aktualne wspolrzedne to X:" + posX + " Y:" + posY);
		}
	}
	
	public int getSteps(){
	return licznik;
	}
	
	public double getDistance(){
	return Math.sqrt((Math.pow(posX,2) + Math.pow(posY,2)));
	}
	
	public double getSumAbsDistance(){
	return Math.abs(posX)+Math.abs(posY);
	}
}

class Start
{
public static void main(String[] args){

Move2DInterface ref = new Move2D();
ref.setStep(1);
ref.north();
ref.east();
ref.east();
ref.north();
ref.east();
ref.north();
ref.north();
System.out.println("Liczba krokow to " + ref.getSteps());
System.out.println("Distance sqrt: " + ref.getDistance());
System.out.println("Distance abs: " + ref.getSumAbsDistance());
}
}
