//package stats.java;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "numberOfBooks",
    "mostPopularLanguage",
    "oldestBook",
    "latestBook"
})
@XmlRootElement(name = "stats")
class Stats {

    @XmlElement()
    protected int numberOfBooks;
    
    @XmlElement()
    protected String mostPopularLanguage;
    
    @XmlElement()
    protected String oldestBook;
    
    @XmlElement()
    protected String latestBook;

    public int getNumberOfBooks() {
        return numberOfBooks;
    }

    public void setNumberOfBooks(int value) {
        this.numberOfBooks = value;
    }

    public String getMostPopularLanguage() {
        return mostPopularLanguage;
    }

    public void setMostPopularLanguage(String value) {
        this.mostPopularLanguage = value;
    }

    public String getOldestBook() {
        return oldestBook;
    }

    public void setOldestBook(String value) {
        this.oldestBook = value;
    }

    public String getLatestBook() {
        return latestBook;
    }

    public void setLatestBook(String value) {
        this.latestBook = value;
    }

}