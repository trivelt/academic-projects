class Brain implements BrainI, Runnable
{	public void run(){
	try {
		while( true ) {
			System.out.println( "Tu gadawka... " + Thread.currentThread().getName() );
			Thread.sleep( 70 );
			}
		}
	catch ( InterruptedException e ) {
		System.out.println( "Zlapalem wyjatek - koncze prace metody run" );
		return;
		}
	}
	public void setGameI( GameI gi ){}
	public void start(){
	Brain dzialo = new Brain();
	Thread t = new Thread(dzialo);
	t.setName("WaTeK1");
	t.start();
      System.out.println( "Wlasnie uruchomiony zostal odrebny watek" );
      try {
         System.out.println( "Tu metoda main - ide spac na 2 sekundy" );
         Thread.sleep( 1000 );
      }
      catch ( InterruptedException e ) {
         return;
      }     
      System.out.println( "Wywoluje wyjatek w watku" );
      t.interrupt();


      System.out.println( "Wlasnie uruchomiony zostal odrebny watek" );
      try {
         System.out.println( "Tu metoda main - ide spac na 2 sekundy" );
         Thread.sleep( 1000 );
      }
      catch ( InterruptedException e ) {
         return;
      }     
      System.out.println( "Wywoluje wyjatek w watku" );
      t.interrupt();

	}

}

class Start{
static public void main(String[] args){
Brain a = new Brain();
a.start();
}

}
