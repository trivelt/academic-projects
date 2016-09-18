
enum CarStates implements CarInterface {
	STOPPED {
		public void faster()
		{
		currentState=PLUS_10MPH;
		}
		public void slower()
		//wolniej sie nie da 
		{
		}
		public void oppositeDirection()
		{
		//przeciez stoimy
		}
		public void stop()
		{
		//juz stoimy
		}
		public int getVelocity()
		{
		return 0;
		}
		public void showVelocity()
		{
		if(displayedVelocity!=0)
			{
			System.out.println("Aktualna predkosc to 0");
			displayedVelocity=0;
			}
		}
	},

	PLUS_10MPH {
		public void faster()
		{
		currentState=PLUS_20MPH;
		}
		public void slower()
		{
		currentState=STOPPED;
		}
		public void oppositeDirection()
		{
		currentState=MINUS_10MPH;
		}
		public void stop()
		{
		currentState=STOPPED;
		}
		public int getVelocity()
		{
		return 10;
		}
		public void showVelocity()
		{
		if(displayedVelocity!=10)
			{
			System.out.println("Aktualna predkosc to 10");
			displayedVelocity=10;
			}
		}
	},

	PLUS_20MPH {
		public void faster()
		{
		currentState=PLUS_30MPH;
		}
		public void slower()
		{
		currentState=PLUS_10MPH;
		}
		public void oppositeDirection()
		{
		currentState=MINUS_20MPH;
		}
		public void stop()
		{
		currentState=STOPPED;
		}
		public int getVelocity()
		{
		return 20;
		}
		public void showVelocity()
		{
		if(displayedVelocity!=20)
			{
			System.out.println("Aktualna predkosc to 20");
			displayedVelocity=20;
			}
		}
	},

	PLUS_30MPH {
		public void faster()
		{
		//szybciej sie nie da 
		}
		public void slower()
		{
		currentState=PLUS_20MPH;
		}
		public void oppositeDirection()
		{
		currentState=MINUS_30MPH;
		}
		public void stop()
		{
		currentState=STOPPED;
		}
		public int getVelocity()
		{
		return 30;
		}
		public void showVelocity()
		{
		if(displayedVelocity!=30)
			{
			System.out.println("Aktualna predkosc to 30");
			displayedVelocity=30;
			}
		}
	},

	MINUS_10MPH {
		public void faster()
		{
		currentState=MINUS_20MPH;
		}
		public void slower()
		{
		currentState=STOPPED;
		}
		public void oppositeDirection()
		{
		currentState=PLUS_10MPH;
		}
		public void stop()
		{
		currentState=STOPPED;
		}
		public int getVelocity()
		{
		return(-10);
		}
		public void showVelocity()
		{
		if(displayedVelocity!=-10)
			{
			System.out.println("Aktualna predkosc to -10");
			displayedVelocity=-10;
			}
		}
	},

	MINUS_20MPH {
		public void faster()
		{
		currentState=MINUS_30MPH;
		}
		public void slower()
		{
		currentState=MINUS_10MPH;
		}
		public void oppositeDirection()
		{
		currentState=PLUS_20MPH;
		}
		public void stop()
		{
		currentState=STOPPED;
		}
		public int getVelocity()
		{
		return(-20);
		}
		public void showVelocity()
		{
		if(displayedVelocity!=-20)
			{
			System.out.println("Aktualna predkosc to -20");
			displayedVelocity=-20;
			}
		}
	},

	MINUS_30MPH {
		public void faster()
		{
		//szybciej sie nie da 
		}
		public void slower()
		{
		currentState=MINUS_20MPH;
		}
		public void oppositeDirection()
		{
		currentState=PLUS_30MPH;
		}
		public void stop()
		{
		currentState=STOPPED;
		}
		public int getVelocity()
		{
		return(-30);
		}
		public void showVelocity()
		{
		if(displayedVelocity!=-30)
			{
			System.out.println("Aktualna predkosc to -30");
			displayedVelocity=-30;
			}
		}
	};
	private static int displayedVelocity=1;
	public static CarStates currentState = STOPPED;
}

class Start {
static public void main(String[] args) {
CarStates.currentState.faster();
CarStates.currentState.showVelocity();
CarStates.currentState.faster();
CarStates.currentState.showVelocity();
CarStates.currentState.stop();
CarStates.currentState.faster();
CarStates.currentState.faster();
CarStates.currentState.showVelocity();
CarStates.currentState.oppositeDirection();
CarStates.currentState.stop();
CarStates.currentState.oppositeDirection();
CarStates.currentState.slower();
CarStates.currentState.showVelocity();
}
}
