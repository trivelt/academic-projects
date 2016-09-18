class Wateczek implements Runnable {

public void run(){
int i=0;
	while(true){
		System.out.println("hehe " + i);
            try {
                //usypiamy wątek na 100 milisekund
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
	i++;}//koniec while
	}//koniec run

}

class Start {
public static void main(String[] args) throws Exception {
Runnable watek = new Wateczek();
//Thread t1 = new Thread(watek);
//t1.start();
new Thread(watek).start();

System.out.println("Dostalem dane. Zaczynam jakies obliczenia...");
for(int i=0;i<10;i++)
	{
	System.out.println("Obliczenie numer " + i);
	Thread.sleep(1000);
	}
}
}
