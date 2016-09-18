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
		}
	}

	public void south(){
	if(setStep==true){
		posY=posY-krok;
		licznik++;
		}
	}

	public void east(){
	if(setStep==true){
		posX=posX+krok;
		licznik++;
		}
	}

	public void west(){
	if(setStep==true){
		posX=posX-krok;
		licznik++;
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
