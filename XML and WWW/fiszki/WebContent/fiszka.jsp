<html>
<head><title>Fiszki - Zestaw</title></head>
<body>
<%@ page import="java.util.ArrayList,java.util.HashMap,java.util.List" %>
<%@ page import="javax.xml.bind.annotation.*,javax.xml.bind.*,java.io.*" %>
<%@ page import="java.util.*" %>
<%@ page import="pl.fiszki.*" %>

<%
	String zestaw = request.getParameter("zestaw");
	int num = Integer.parseInt(request.getParameter("num"));
	String previousKnown = request.getParameter("prevKnown");
	if(previousKnown == null){
		//System.out.println("To jest pierwsza fiszka z zestawu, num=" + num);
	}
	else if(previousKnown.trim().equals("True")){
		int prevNum = Integer.parseInt(request.getParameter("numPrev"));
		//System.out.println("Poprzednia znana, jej numer=" + prevNum + ", num=" + num);
		Fiszki.setFiszkaAsLearned(zestaw, prevNum);
	}
	else if(previousKnown.trim().equals("False")){
		int prevNum = Integer.parseInt(request.getParameter("numPrev"));
		//System.out.println("Poprzednia nieznana, jej numer=" + prevNum + ", num=" + num);
	}

	Fiszki fiszkiSet = Fiszki.getFiszkiFromXml(zestaw);
	List<Fiszki.Fiszka> fiszki = fiszkiSet.getFiszki();
	int currentFiszkaNumber = -1;
	int unlearnedCounter = 0;
	int allCounter = 0;

	for(Iterator<Fiszki.Fiszka> it = fiszki.iterator(); it.hasNext(); ) {
	  		Fiszki.Fiszka fiszka = it.next();
	  		if(fiszka.isLearned().trim().equals("False")){
	  			if(unlearnedCounter == num){
	  				currentFiszkaNumber = allCounter;
	  			}
	  			unlearnedCounter++;
	  		}
	  		allCounter++;
	}
	int numberOfUnlearnedFiszki = unlearnedCounter;
	int numberOfFiszki = fiszki.size();
	
	if(currentFiszkaNumber == -1 && numberOfUnlearnedFiszki > 0){
		num = 0;
		for(int i=0; i<fiszki.size(); i++) {
	  		Fiszki.Fiszka fiszka = fiszki.get(i);
	  		if(fiszka.isLearned().trim().equals("False")){
				currentFiszkaNumber = i;
				break;
	  		}
		}
	}
%>

<h1>Zestaw "<%= zestaw  %>"</h1>

<%	
	if(previousKnown != null){
		int numOfPrevious = Integer.parseInt(request.getParameter("numPrev"));
		Fiszki.Fiszka previousFiszka = fiszki.get(numOfPrevious);
		String frontOfPrevious = previousFiszka.getFront();
		String backOfPrevious = previousFiszka.getBack();
%>		

	(<%= frontOfPrevious %> - <%= backOfPrevious %>)

<%	}
	

	if(numberOfUnlearnedFiszki == 0){ %>
		Gratulacje! Nauczyles sie wszystkiego z tego zestawu!. Wroc do <a href="index.jsp">menu glownego</a>,
		by wybrac inny zestaw, lub <a href="reset.jsp?&name=<%= zestaw %>">rozpocznij na nowo</a> nauke tego zestawu</a>.
<%	}else { 
		Fiszki.Fiszka fiszka = fiszki.get(currentFiszkaNumber);
		String textFront = fiszka.getFront();
		String linkAddress = "fiszka.jsp?zestaw=" + zestaw + "&num=" + (num+1) +
				"&numPrev=" + currentFiszkaNumber + "&prevKnown=";
%>
<br />Pozostalych do nauczenia: <%= numberOfUnlearnedFiszki %><br /><br />


<div id="fiszka-content">
	<%= textFront %>
</div>
<a href="<%= linkAddress %>True">Znam</a> <a href="<%= linkAddress %>False">Nie znam</a>
<%	} %>


</body>
</html>