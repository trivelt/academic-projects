import java.lang.reflect.*;
import java.lang.annotation.*;

/*
@Retention(RetentionPolicy.RUNTIME)
@interface Version{
    int revision();
    boolean testPassed();
}*/

class Start
{

public static void main(String args[]) throws java.lang.ClassNotFoundException
{
String klasaOK="";
int wersjaOK=0;
for(int i=0;i<args.length;i++)
	{
	String nazwaKlasy=args[i];
	Class<?> klasa = Class.forName(nazwaKlasy);
	Annotation ans[] = klasa.getAnnotations();
	for(Annotation a : ans)
		{
		if(a instanceof Version)
			{
			Version ci = (Version)a;
			if( ci.revision() >= wersjaOK && ci.testPassed() )
				{
				klasaOK=nazwaKlasy;
				wersjaOK=ci.revision();
				}
			}
		}
	}
Class<?> klasa = Class.forName(klasaOK);

try {
	Constructor<?> c2str1i = klasa.getConstructor(java.lang.String.class, java.lang.String.class, Integer.TYPE);
	Object instancja = c2str1i.newInstance("foo", "bar", 1);
	try{
		Method me = klasa.getMethod("show", (java.lang.Class<?>[])null);
		me.invoke(instancja);		
		} catch(Exception e2){}
		
	try{
		Method me = klasa.getMethod("print", (java.lang.Class<?>[])null);
		me.invoke(instancja);		
		} catch(Exception e2){}
	}
	catch(Exception e){}

try {

	Constructor<?> c2str = klasa.getConstructor(java.lang.String.class, java.lang.String.class);
	Object instancja = c2str.newInstance("foo", "bar");
	try{
		Method me = klasa.getMethod("show", (java.lang.Class<?>[])null);
		me.invoke(instancja);		
		} catch(Exception e2){}
		
	try{
		Method me = klasa.getMethod("print", (java.lang.Class<?>[])null);
		me.invoke(instancja);		
		} catch(Exception e2){}
	}
	catch(Exception e){}

try {
	Constructor<?> c1i = klasa.getConstructor(Integer.TYPE);
	Object instancja = c1i.newInstance(2);
	try{
		Method me = klasa.getMethod("show", (java.lang.Class<?>[])null);
		me.invoke(instancja);		
		} catch(Exception e2){}
		
	try{
		Method me = klasa.getMethod("print", (java.lang.Class<?>[])null);
		me.invoke(instancja);		
		} catch(Exception e2){}
	}
	catch(Exception e){}
}
}
