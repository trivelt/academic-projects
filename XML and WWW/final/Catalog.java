import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.annotation.*;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.PrintWriter;
import java.io.StringReader;
import java.io.StringWriter;

@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "book"
})
@XmlRootElement(name = "catalog")
public class Catalog {
	
	public static void main(String args[]) throws JAXBException
	{		
        final JAXBContext jaxbContext = JAXBContext.newInstance(Catalog.class);
        
        String path = "/home/maciej/prog/XML/cw7/booksCatalog.xml";
        StringBuilder sb = new StringBuilder();
        try {
        	BufferedReader br = new BufferedReader(new FileReader(path));
        	String sCurrentLine = br.readLine();
        	while(sCurrentLine != null)
        	{
        		sb.append(sCurrentLine);
        		sCurrentLine = br.readLine();
        	}
        } catch(Exception e) {
        	System.out.println("Cannot read XML file");
        	System.exit(1);
        }        
        
        final Catalog booksCatalog =
                (Catalog) jaxbContext.createUnmarshaller().unmarshal(
                    new StringReader(sb.toString()));
        
        
        int oldestBookYear = -1;
        String oldestBookTitle = "";
        
        int latestBookYear = -1;
        String latestBookTitle = "";
               
        List<Catalog.Book> books = booksCatalog.getBook();
        String[] languages = new String[books.size()];

        int counter = 0;
        for(Book book : books)
        {
        	int year = book.getDate();
        	if(counter == 0)
        	{
        		oldestBookTitle = book.getTitle();
        		oldestBookYear = year;
        		latestBookTitle = book.getTitle();
        		latestBookYear = year;
        	}
        	if(year >= latestBookYear)
        	{
        		latestBookYear = year;
        		latestBookTitle = book.getTitle();
        	}
        	if(year <= oldestBookYear)
        	{
        		oldestBookYear = year;
        		oldestBookTitle = book.getTitle();
        	}
        	languages[counter] = book.getLanguage();
        	counter++;
        }
                
        final JAXBContext jaxbStatsContext = JAXBContext.newInstance(Stats.class);
        Stats catalogStats = new Stats();
        
        catalogStats.setNumberOfBooks(books.size());
        catalogStats.setOldestBook(oldestBookTitle);
        catalogStats.setLatestBook(latestBookTitle);
        catalogStats.setMostPopularLanguage(mode(languages));
        
        StringWriter writer = new StringWriter();
        jaxbStatsContext.createMarshaller().marshal(catalogStats, writer);
        System.out.println(writer.toString());
        
        try
        {
            PrintWriter pWriter = new PrintWriter("statisticsOfBooksCatalog.xml", "UTF-8");
            pWriter.println(writer.toString());
            pWriter.close();	
        } catch(Exception e) {
        	System.out.println("Cannot save stats XML");
        	System.exit(-1);
        }
	}	
	

    @XmlElement(required = true)
    protected List<Catalog.Book> book;

    public List<Catalog.Book> getBook() {
        if (book == null) {
            book = new ArrayList<Catalog.Book>();
        }
        return this.book;
    }

    @XmlAccessorType(XmlAccessType.FIELD)
    @XmlType(name = "", propOrder = {
        "title",
        "author",
        "date",
        "language"
    })
    public static class Book {

        /**
         * Title of the book
         */
        @XmlElement(required = true)
        protected String title;
        
        /**
         * Name of the author
         */    
        @XmlElement(required = true)
        protected String author;
        
        /**
         * Publication date
         */    
        @XmlElement(required = true)
        protected int date;
        
        /**
         * Original language
         */    
        @XmlElement(required = true)
        protected String language;

        public String getTitle() {
            return title;
        }

        public void setTitle(String value) {
            this.title = value;
        }

        public String getAuthor() {
            return author;
        }

        public void setAuthor(String value) {
            this.author = value;
        }

        public int getDate() {
            return date;
        }

        public void setDate(int value) {
            this.date = value;
        }

        public String getLanguage() {
            return language;
        }

        public void setLanguage(String value) {
            this.language = value;
        }

    }

    public static String mode(String []array)
    {HashMap<String,Integer> hm=new HashMap<String,Integer>();
    int max=1;
    String temp = "-1";
    for(int i=0;i<array.length;i++)
        {
            if(hm.get(array[i])!=null)
            {int count=hm.get(array[i]);
            count=count+1;
            hm.put(array[i],count);
            if(count>max)
                {max=count;
                 temp=array[i];}
            }
            else
            {hm.put(array[i],1);}
        }
        return temp;
    }    
}


