<html>
<head><title>Fiszki - Start</title></head>
<body>
<%@ page import="java.util.ArrayList,java.util.HashMap,java.util.List" %>
<%@ page import="javax.xml.bind.annotation.*,javax.xml.bind.*,java.io.*" %>
<%@ page import="java.util.*" %>
<%@ page import="pl.fiszki.*" %>

 <%
 	List<String> fiszki = Fiszki.getFiszkiNames();
 	
 %>
<a href="createSet">Utworz nowy zestaw fiszek</a> lub wybierz istniejacy: 
<form action="set.jsp" method="POST">
  <select name="fiszkiSets">
	<% for(Iterator<String> it = fiszki.iterator(); it.hasNext(); ) {
	  		String fiszka = it.next();
	%>
    <option value="<%= fiszka %>"><%= fiszka %></option>
  <% } %>
  </select>
  <input type="submit" value="Ok" />
</form>

</body>
</html>