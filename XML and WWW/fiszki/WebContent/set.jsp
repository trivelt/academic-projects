<html>
<head><title>Fiszki - Zestaw</title></head>
<body>
<%@ page import="java.util.ArrayList,java.util.HashMap,java.util.List" %>
<%@ page import="javax.xml.bind.annotation.*,javax.xml.bind.*,java.io.*" %>
<%@ page import="java.util.*" %>
<%@ page import="pl.fiszki.*" %>

<%
	String zestaw = request.getParameter("fiszkiSets");
	Fiszki fiszkiSet = Fiszki.getFiszkiFromXml(zestaw);
	List<Fiszki.Fiszka> fiszki = fiszkiSet.getFiszki();
	int numberOfKnownFiszki = 0;
	for(Iterator<Fiszki.Fiszka> it = fiszki.iterator(); it.hasNext(); ) {
	  		Fiszki.Fiszka fiszka = it.next();
	  		if(fiszka.isLearned().trim().equals("True")){
	  			numberOfKnownFiszki++;
	  		}
	}
	int numberOfFiszki = fiszki.size();
%>

<h1>Zestaw "<%= zestaw  %>"</h1>
Liczba fiszek: <%= numberOfFiszki %> (tym nauczonych: <%= numberOfKnownFiszki %>)

<ul>
	<li><a href="manager?name=<%= zestaw %>">Modyfikuj</a></li>
	<li><a href="removeSet?name=<%= zestaw %>">Usun zestaw</a></li>
	<li><a href="fiszka.jsp?zestaw=<%= zestaw %>&num=0">Ucz sie</a></li>
</ul>

</body>
</html>