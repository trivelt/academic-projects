import java.lang.annotation.*;

@Retention(RetentionPolicy.RUNTIME)
@interface Version{
    int revision();
    boolean testPassed();
}

@Version (
  revision = 3,
  testPassed = false
)
class Testowa1 {
public Testowa1(String a, String b){}
}

@Version (
  revision = 2,
  testPassed = true
)
class Testowa2 {
//public Testowa2(String a, String b){System.out.println("Zostalem wywolany!");}
public Testowa2(int a, int b, int c){}
public Testowa2(String a,String b, int c){System.out.println("Zostalem wywolany!");}
public int show(){System.out.println("Pracuje");return 1;}
}


@Version (
  revision = 5,
  testPassed = true
)

class Testowa3 {
public Testowa3(int a){}
public void print(){System.out.println("Drukuje");}
}

@Version (
  revision = 6,
  testPassed = false
)
class Testowa4 {}
