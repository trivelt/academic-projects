class MyRun implements Runnable {
 
    private int id;
 
    public MyRun(int id) {
        this.id = id;

    }
 
    public void run() {
        while(true) {
		try {if(id>5){throw new RuntimeException();}}catch(RuntimeException e){System.out.println("Przechwycony"); return;}
            System.out.println("Watek "+id);
            try {
                //usypiamy wątek na 100 milisekund
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        id++;}
    }
}


class Runner {
    public static void main(String[] args) throws Exception {
        Runnable runner1;
        Thread thread1 = new Thread();
 
            runner1 = new MyRun(1);
            thread1 = new Thread(runner1);
	System.out.println("Dostalem dane. Zaczynam jakies obliczenia...");
            thread1.start();
	for(int i=0;i<10;i++)
		{
		System.out.println("Obliczenie numer " + i);
		Thread.sleep(1000);
		}
	}
}
