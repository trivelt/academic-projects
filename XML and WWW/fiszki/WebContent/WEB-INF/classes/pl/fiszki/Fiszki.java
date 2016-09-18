package pl.fiszki;
// javac -sourcepath . -d . Fiszki.java 

import java.util.*;
import javax.xml.bind.annotation.*;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.StringReader;
import java.io.StringWriter;


@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "fiszka"
})
@XmlRootElement(name = "fiszki")
public class Fiszki {
	
	public static void main(String args[]) throws JAXBException
	{
		getFiszkiNames();
		System.out.println("Hej");
	}
	
	public static List<String> getFiszkiNames()
	{
		List<String> fiszkiSets = new ArrayList<String>();
		String directory = "/home/maciej/workspace/fiszki/xmls/";
		File folder = new File(directory);
		File[] listOfFiles = folder.listFiles();

		for (File file : listOfFiles) {
		    if (file.isFile() 
		    		&& file.getName().startsWith("fiszki-zestaw-") 
		    		&& file.getName().endsWith(".xml")) {
		    	String name = file.getName();
		    	name = name.substring(14, name.length()-4);
		    	fiszkiSets.add(name);
		    }
		}
		return fiszkiSets;
	}

	
	public static Fiszki getFiszkiFromXml(String name)  throws JAXBException
	{		
		String xmlPath = "/home/maciej/workspace/fiszki/xmls/fiszki-zestaw-" + name + ".xml";
        final JAXBContext jaxbContext = JAXBContext.newInstance(Fiszki.class);
        StringBuilder sb = new StringBuilder();
        try {
        	BufferedReader br = new BufferedReader(new FileReader(xmlPath));
        	String sCurrentLine = br.readLine();
        	while(sCurrentLine != null)
        	{
        		sb.append(sCurrentLine);
        		sCurrentLine = br.readLine();
        	}
        } catch(Exception e) {
        	System.out.println("Cannot read XML file " + xmlPath);
        	return new Fiszki();
        }        
        
        final Fiszki fiszki =
                (Fiszki) jaxbContext.createUnmarshaller().unmarshal(
                    new StringReader(sb.toString()));
		
		//System.out.println("Pobieram fiszki z xmla " + xmlPath);
		return fiszki;
	}
	
	public static void setFiszkaAsLearned(String name, int num) throws JAXBException {
		Fiszki fiszkiSet = getFiszkiFromXml(name);
		List<Fiszki.Fiszka> fiszki = fiszkiSet.getFiszki();
		Fiszki.Fiszka fiszka = fiszki.get(num);
		fiszka.setLearned("True");
		final JAXBContext jaxbContext = JAXBContext.newInstance(Fiszki.class);
		StringWriter writer = new StringWriter();
		jaxbContext.createMarshaller().marshal(fiszkiSet, writer);
		System.out.println(writer.toString());		
	    try
	    {
	    	PrintWriter pWriter = new PrintWriter("/home/maciej/"
	    		+ "workspace/fiszki/xmls/fiszki-zestaw-" + name + ".xml", "UTF-8");
	        pWriter.println(writer.toString());
	        pWriter.close();	
	    } catch(Exception e) {
	    	System.out.println("Cannot save XML");
	    	return;
	    }		
	}
	
	public static void resetLearning(String name) throws JAXBException {
		Fiszki fiszkiSet = getFiszkiFromXml(name);
		List<Fiszki.Fiszka> fiszki = fiszkiSet.getFiszki();		
		for(int i=0; i<fiszki.size(); i++){
			Fiszki.Fiszka fiszka = fiszki.get(i);
			fiszka.setLearned("False");;
		}
		final JAXBContext jaxbContext = JAXBContext.newInstance(Fiszki.class);
		StringWriter writer = new StringWriter();
		jaxbContext.createMarshaller().marshal(fiszkiSet, writer);
		System.out.println(writer.toString());		
	    try
	    {
	    	PrintWriter pWriter = new PrintWriter("/home/maciej/"
	    		+ "workspace/fiszki/xmls/fiszki-zestaw-" + name + ".xml", "UTF-8");
	        pWriter.println(writer.toString());
	        pWriter.close();	
	    } catch(Exception e) {
	    	System.out.println("Cannot save XML");
	    	return;
	    }				
	}
	
	public static void removeFiszka(String nameOfSet, int num) throws JAXBException {
		Fiszki fiszkiSet = getFiszkiFromXml(nameOfSet);
		List<Fiszki.Fiszka> fiszki = fiszkiSet.getFiszki();		
		fiszki.remove(num);
		final JAXBContext jaxbContext = JAXBContext.newInstance(Fiszki.class);
		StringWriter writer = new StringWriter();
		jaxbContext.createMarshaller().marshal(fiszkiSet, writer);
		System.out.println(writer.toString());		
	    try
	    {
	    	PrintWriter pWriter = new PrintWriter("/home/maciej/"
	    		+ "workspace/fiszki/xmls/fiszki-zestaw-" + nameOfSet + ".xml", "UTF-8");
	        pWriter.println(writer.toString());
	        pWriter.close();	
	    } catch(Exception e) {
	    	System.out.println("Cannot save XML");
	    	return;
	    }	
	}
	
	public static void addFiszka(String nameOfSet, String front, String back) throws JAXBException {
		Fiszki fiszkiSet = getFiszkiFromXml(nameOfSet);
		List<Fiszki.Fiszka> fiszki = fiszkiSet.getFiszki();		
		
		Fiszki.Fiszka nowa = new Fiszki.Fiszka();
		nowa.setFront(front);
		nowa.setBack(back);
		nowa.setLearned("False");
		fiszki.add(nowa);
		
		final JAXBContext jaxbContext = JAXBContext.newInstance(Fiszki.class);
		StringWriter writer = new StringWriter();
		jaxbContext.createMarshaller().marshal(fiszkiSet, writer);
		System.out.println(writer.toString());		
	    try
	    {
	    	PrintWriter pWriter = new PrintWriter("/home/maciej/"
	    		+ "workspace/fiszki/xmls/fiszki-zestaw-" + nameOfSet + ".xml", "UTF-8");
	        pWriter.println(writer.toString());
	        pWriter.close();	
	    } catch(Exception e) {
	    	System.out.println("Cannot save XML");
	    	return;
	    }	
	}	
	
	
    @XmlElement(required = true)
    protected List<Fiszki.Fiszka> fiszka;
    @XmlAttribute
    protected String nazwa;


    public List<Fiszki.Fiszka> getFiszki() {
        if (fiszka == null) {
            fiszka = new ArrayList<Fiszki.Fiszka>();
        }
        return this.fiszka;
    }

    public String getNazwa() {
        return nazwa;
    }

    public void setNazwa(String value) {
        this.nazwa = value;
    }

    @XmlAccessorType(XmlAccessType.FIELD)
    @XmlType(name = "", propOrder = {
        "front",
        "back",
        "learned"
    })
    public static class Fiszka {

        @XmlElement(required = true)
        protected String front;
        
        @XmlElement(required = true)
        protected String back;
        
        @XmlElement(required = true)
        protected String learned;

        public String getFront() {
            return front;
        }

        public void setFront(String value) {
            this.front = value;
        }

        public String getBack() {
            return back;
        }

        public void setBack(String value) {
            this.back = value;
        }

        public String isLearned() {
            return learned;
        }

        public void setLearned(String value) {
            this.learned = value;
        }

    }

}