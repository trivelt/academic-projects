class SimpleHTMLTableFormatter extends HTMLTableFormatter
{

SimpleHTMLTableFormatter(){}

private int grubosc = 0;
private int kolumny;
private boolean setCols=false;
private boolean getHeader=false;
private boolean getFooter=false;
String[] naglowki;

public void setCols( String[] names ) {
kolumny = names.length;
naglowki = names;
setCols=true;
}

public void setBorderWidth( int width ) {
grubosc = width;
}

public String getHeader() {
String txt="<table";
if(setCols==false || getHeader==true) return "";
if(grubosc!=0) txt+=" border=\"" + grubosc + "\"";
txt+=">";
txt+="\n<tr>\n";
for(int i=0;i<kolumny;i++)
	{
	txt+="<th>";
	txt+=naglowki[i];
	txt+="</th>\n";
	}

txt+="</tr>";
getHeader=true;
return txt;
}

public String getRow( String[] values ) {
String txt="";
if(values.length!=kolumny) return txt;
if(setCols==false || getHeader==false) return txt;
txt+="<tr>\n";
for(int i=0;i<kolumny;i++)
	{
	txt+="<td>";
	txt+=naglowki[i];
	txt+="</td>\n";
	}
txt+="</tr>";
return txt;
}

public String getFooter() {
String txt="";
if(getHeader==false || getFooter==true) return txt;
txt+="</table>";
getFooter=true;
return txt;
}

}
