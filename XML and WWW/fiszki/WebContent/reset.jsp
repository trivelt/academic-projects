<html>
<head><title>Fiszki</title></head>
<body>
<%@ page import="java.util.ArrayList,java.util.HashMap,java.util.List" %>
<%@ page import="javax.xml.bind.annotation.*,javax.xml.bind.*,java.io.*" %>
<%@ page import="java.util.*" %>
<%@ page import="pl.fiszki.*" %>

<%
	String zestaw = request.getParameter("name");
	Fiszki.resetLearning(zestaw);

%>

	Zresetowano zestaw "<%= zestaw %>". Wroc do <a href="fiszka.jsp?zestaw=<%= zestaw %>&num=0"">nauki</a> lub 
	do <a href="index.jsp">menu glownego</a>.

</body>
</html>