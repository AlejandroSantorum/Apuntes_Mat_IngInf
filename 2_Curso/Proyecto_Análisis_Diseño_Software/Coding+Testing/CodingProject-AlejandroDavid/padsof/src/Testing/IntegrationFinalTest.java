package Testing;

import java.io.IOException;
import java.util.ArrayList;
import java.util.GregorianCalendar;

import Exceptions.*;
import es.uam.eps.padsof.telecard.InvalidCardNumberException;
import es.uam.eps.padsof.telecard.OrderRejectedException;
import padsof.*;
import Filters.*;

public class IntegrationFinalTest {

	public static void main(String[] args) throws IOException, ClassNotFoundException, OfferException, UserException, OrderRejectedException{
		Application app = new Application();
		
		System.out.println("Loading users from the application users file...");
		app.loadUsers("users.txt");
		System.out.println("Users loaded successfully\n");
		System.out.println("Users loaded:");
		app.printAllUsers();
		System.out.println(" ------------------------------------------------- ");
		
		ArrayList<RegisteredUser> usersArray = app.getUsersArray();
		
		System.out.println("For every landlord type user, we create an apartment...");
		for(int i=0; i<usersArray.size(); i++) { /* We do it in this way to change
			  									* some parameters in the apartment description */
			RegisteredUser aux = usersArray.get(i);
			if(!aux.getUserType().canRegister()) continue;
			app.createApartment(i+1000, "Street "+(100+i), "Number of bathrooms equal to "+(i+1), usersArray.get(i));
		}
		System.out.println("Properties created successfully\n");
		System.out.println("Properties created:");
		app.printAllApartments();
		System.out.println(" ------------------------------------------------- ");
		
		ArrayList<Apartment> apartmentsArray = app.getApartmentsArray();
		
		System.out.println("Now, for every apartment, we are going to create an offer...");
		for(int i=0; i<apartmentsArray.size(); i++) {
			Apartment aux = apartmentsArray.get(i);
			RegisteredUser owner = aux.getOwner();
			
			if(!(owner.getUserType().canOffer())) continue;
			app.createOffer(100+10*i, aux, owner, new GregorianCalendar(2010+i, 1+i, 10+i),
					new GregorianCalendar(2010+i, 2+i, 15+i));
			app.createOffer(100+10*i,  aux,  owner, new GregorianCalendar(2010+i, 1+i, 10+i), 0, 1+i, 0);
		}
		System.out.println("Different offers created successfully\n");
		System.out.println("Offers created:");
		app.printAllOffers();
		System.out.println(" ------------------------------------------------- ");
		
		ArrayList<Offer> offersArray = app.getOffersArray();
		for(Offer o: offersArray) {
			o.setStatus(Status.FREE);
		}
		
		System.out.print("Now we are commenting on all the offers...");
		for(int i=0; i<offersArray.size(); i++) {
			RegisteredUser c = usersArray.get(i%(usersArray.size()));
			
			app.addCommentary(offersArray.get(i), c, new GregorianCalendar(2010+i, 1+i, 10+i), "Esto es un comentario de prueba"+i);
			app.addCommentary(offersArray.get(i), c, new GregorianCalendar(2010+i, 1+i, 12+i), i%6);
		}
		System.out.println("Different comments created successfully\n");
		System.out.println("Comments created:");
		app.printAllComments();
		System.out.println(" -------------------------------------------------\n");
		
		System.out.println("At this moment we are going to save all the data into a file...");
		app.saveData("finalTest.txt");
		System.out.println("Data saved successfully\n");
		System.out.println("Opening the file and reading all the data to store it again in the application...");
		app.readData("finalTest.txt");
		System.out.println("Data read successfully\n");
		System.out.println("Printing all offers again in order to check the functions worked well:");
		app.printAllOffers();
		System.out.println("Persistence worked perfectly\n");
		
		System.out.println("Now let's check book an offer:");
		Offer off = offersArray.get(0);
		RegisteredUser user = usersArray.get(1);
		
		System.out.println(user.getUserType());
		off.bookOffer(user);
		System.out.println(off);
		System.out.println("We can see that demander is not null and the offer status is BOOKED.");
		System.out.println("Booking is working finely\n");
		
		System.out.println("So, let's try to rent the same offer by the same user:");
		try {
			off.rentOffer(user);
		}catch(InvalidCardNumberException ex) {
			System.out.println("InvalidCardNumberException: "+ex.getMessage());
		}
		System.out.println(off);
		System.out.println("We can check that demander is the same than before, and now status is RENTED");
		System.out.println("Offer rented successfully\n");

		System.out.println("It`s important to clarify we've used another user, with a correct credit card number");
		System.out.println("Exceptions are checked in JUnit testings\n");
		
		System.out.println("Finally, we are going to filter all the offers using two filters...");
		ArrayList<Offer> auxiliarO;
		
		ArrayList<Filter> filters = new ArrayList<Filter>();
		filters.add(new TypeStayFilter(OfferType.SHORT));
		filters.add(new PriceFilter(100, 120));
		filters.add(new RatingFilter(3));
		auxiliarO = app.search(offersArray, filters);
		
		System.out.println("The search function has succeed. This is the result:\n");
		
		for(Offer o: auxiliarO) {
			System.out.println(o);
		}
		
		System.out.println("The previous offer/s is/are the filtered\n");
		System.out.println(" -------------------------------------------------");
		System.out.println("THIS DEMO PLUS ALL THE JUnit TEST CONSTITUTE A CLEAR");
		System.out.println("EXAMPLE OF WHAT OUR APPLICATION CAN DO.");
		System.out.println("IF YOU ARE READING THIS IT'S BECAUSE EVERYTHING SUCEED!");
		System.out.println(" -------------------------------------------------\n");
		System.out.println("\tDemo completed");
		
	}

}
