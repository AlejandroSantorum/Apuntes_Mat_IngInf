package Testing;

import java.io.*;

import java.util.*;

import Exceptions.*;
import es.uam.eps.padsof.telecard.OrderRejectedException;
import padsof.*;

public class InitialTester {

	public static void main(String[] args) throws IOException, ClassNotFoundException, OfferException, UserException, OrderRejectedException{
		Application app = new Application();
		
		app.loadUsers("users.txt");
		
		ArrayList<RegisteredUser> usersArray = app.getUsersArray();
		
		for(int i=0; i<usersArray.size(); i++) { /* We do it in this way to change
		 										  * some parameters in the apartment description */
			RegisteredUser aux = usersArray.get(i);
			if(!aux.getUserType().canRegister()) continue;
			app.createApartment(i+1000, "Street "+(100+i), "Number of bathrooms equal to "+(i+1), usersArray.get(i));
		}
		
		ArrayList<Apartment> apartmentsArray = app.getApartmentsArray();
		
		for(int i=0; i<apartmentsArray.size(); i++) {
			Apartment aux = apartmentsArray.get(i);
			RegisteredUser owner = aux.getOwner();
			
			if(!(owner.getUserType().canOffer())) continue;
			app.createOffer(100+10*i, aux, owner, new GregorianCalendar(2010+i, 1+i, 10+i),
					new GregorianCalendar(2010+i, 2+i, 15+i));
			app.createOffer(100+10*i,  aux,  owner, new GregorianCalendar(2010+i, 1+i, 10+i), 0, 1+i, 0);
		}
		
		app.saveData("prueba.txt");
		
		app.readData("prueba.txt");
		
		app.printAllUsers();
		
		app.printAllApartments();
		
		app.printAllOffers();
	}

}
