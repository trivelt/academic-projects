package pl.trivelt.servlets;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import pl.fiszki.*;

@WebServlet("/createSet")
public class createSet extends HttpServlet {
	private static final long serialVersionUID = 1L;

    public createSet() {
        super();
    }

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		 PrintWriter out = response.getWriter();
		 		 
		 out.print("<html><head></head><body>");
		 out.print("<h1>Tworzenie nowego zestawu fiszek</h1>");
		 
		 if(request.getParameter("nameOfSet") != null){
			 String nameOfSet = request.getParameter("nameOfSet");
			 PrintWriter fileWriter = new PrintWriter("/home/maciej/"
	    		+ "workspace/fiszki/xmls/fiszki-zestaw-" + nameOfSet + 
	    		".xml", "UTF-8");
			 fileWriter.println("<?xml version='1.0' encoding='UTF-8' standalone='yes'?>");
			 fileWriter.println("<fiszki nazwa='" + nameOfSet + "'>");
			 fileWriter.println("</fiszki>");
			 fileWriter.close();
			 out.print("Utworzono zestaw '" + nameOfSet + "'. Wybierz go "
			 		+ "z <a href='index.jsp'>menu glownego</a>, aby nim zarzadzac.");

		 } else {
			 out.print("<form action='createSet' method='POST'>");
			 out.print("<input name='nameOfSet' />");
			 out.print("<input type='submit' name='accept' value='Dodaj' />");

			 out.print("</form>");
			 out.print("</body></html>"); 
		 }

	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
