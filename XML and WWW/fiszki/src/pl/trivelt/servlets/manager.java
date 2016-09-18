package pl.trivelt.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.bind.JAXBException;

import pl.fiszki.*;


@WebServlet("/manager")
public class manager extends HttpServlet {
	private static final long serialVersionUID = 1L;
       

    public manager() {
        super();
    }


	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		 PrintWriter out = response.getWriter();
		 String nameOfSet = request.getParameter("name");
		 
		 out.print("<html><head></head><body>");
		 out.print("<h1>Edytowanie zestawu " + nameOfSet + "</h1>");
		 
		try {
			Fiszki fiszkiSet = Fiszki.getFiszkiFromXml(nameOfSet);
			List<Fiszki.Fiszka> fiszki = fiszkiSet.getFiszki();
			
			if(request.getParameter("dodaj") != null){
				out.print("<form action='manager' method='POST'>");
				out.print("<input type='hidden' name='name' value='" + nameOfSet + "' />");
				out.print("<input type='hidden' name='dodajFiszke' value='True' />");				
				out.print("<input name='front' />");
				out.print("<input name='back' />");
				out.print("<input type='submit' value='dodaj' />");
			}
			else if(request.getParameter("usun") != null){
				int num = Integer.parseInt(request.getParameter("usun"));
				Fiszki.removeFiszka(nameOfSet, num);
				out.print("Fiszka zostala usunieta z zestawu.");
				out.print(" <a href='manager?name=" + nameOfSet + "'>Wroc do managera</a>");
			}
			else if(request.getParameter("dodajFiszke") != null){
				String front = request.getParameter("front");
				String back = request.getParameter("back");
				Fiszki.addFiszka(nameOfSet, front, back);
				out.print("Fiszka zostala dodana do zestawu.");
				out.print(" <a href='manager?name=" + nameOfSet + "'>Wroc do managera</a>");
			}
			else {
					out.print("<form action='manager' method='POST'>");
					out.print("<input type='hidden' name='name' value='" + nameOfSet + "' />");
					
					for(int i=0; i<fiszki.size(); i++){
						Fiszki.Fiszka fiszka = fiszki.get(i);
						String front = fiszka.getFront();
						String back = fiszka.getBack();
						out.print("<input name='front' value='" + front + "' disabled />");
						out.print("<input name='back' value='" + back + "' disabled />");
						out.print("<a href='manager?usun=" + i + "&name=" + nameOfSet + "'>usun</a><br />");
					}
					
					out.print("<a href='manager?dodaj=True&name=" + nameOfSet + "'>dodaj</a><br />");
					out.print(" <a href='index.jsp'>Wroc do menu glownego</a>");
					out.print("</form>");				
			}


		} catch (JAXBException e) {
			out.print("<br />Blad podczas ladowania pliku XML.");
			e.printStackTrace();
		}
		 
		 out.print("</body></html>"); 
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
