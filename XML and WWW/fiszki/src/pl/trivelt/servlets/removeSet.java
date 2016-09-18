package pl.trivelt.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.File;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

//import org.apache.tomcat.jni.File;

@WebServlet("/removeSet")
public class removeSet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       

    public removeSet() {
        super();
    }

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		 PrintWriter out = response.getWriter();
		 out.print("<html><head></head><body>");
		 String nameOfSet = request.getParameter("name");
		 
		 if(request.getParameter("remove") == null){
			 
			 out.println("Czy na pewno usunac zestaw " + nameOfSet + "?");
			 out.println("<a href='removeSet?name=" + nameOfSet + "&remove=True'>Tak</a>");
			 out.println(" <a href='index.jsp'>Nie</a>");
		 }
		 else {
			 File fileToRemove = new File("/home/maciej/workspace/fiszki/xmls/fiszki-zestaw-" + nameOfSet + ".xml");
			 fileToRemove.delete();
			 out.println("Usunieto zestaw '" + nameOfSet + "'. Wroc do <a href='index.jsp'>menu glownego</a>.");
		 }
		 out.print("</body></html>"); 	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
