package Testing;

import static org.junit.Assert.*;

import java.io.IOException;
import java.util.GregorianCalendar;

import org.junit.Before;
import org.junit.Test;

import padsof.*;
import padsof.Long;
import padsof.Short;
import Exceptions.*;
import es.uam.eps.padsof.telecard.OrderRejectedException;

public class ApplicationTest {
	private Application app;
	private RegisteredUser renter1;
	private RegisteredUser renter2;
	private RegisteredUser landlord;
	private Apartment apart;
	private Short shr;
	private Long lng;
	private Textual text;
	private GregorianCalendar iniDate;
	private GregorianCalendar finDate;
	private GregorianCalendar newIniDate;
	private GregorianCalendar newFinDate;
	
	
	@Before
	public void setUp() throws UserException, OfferException{
		app = new Application();
		renter1 = new RegisteredUser("Renter user", "123456789", "pass1", "1234567890123456", "D");
		renter2 = new RegisteredUser("Renter user 2", "135798642", "pass12", "1111222233334444", "D");
		landlord =  new RegisteredUser("Landlord user", "987654321", "pass2", "9876543210987654", "O");
		apart = new Apartment(25555, "Street 101", "Swimming-pool included", landlord);
		lng = new Long(200.0f, apart, landlord, new GregorianCalendar(2018, 02, 02), 0, 1, 0);
		iniDate = new GregorianCalendar(2018, 02, 15);
		finDate = new GregorianCalendar(2018, 02, 20);	
		newIniDate = new GregorianCalendar(2018, 02, 17);
		newFinDate = new GregorianCalendar(2018, 02, 22);
		shr = new Short(150.0f, apart, landlord, iniDate, finDate);
		text = new Textual(renter1, new GregorianCalendar(2018, 02, 15), "Hi! We are testing Textual!");
	}
	
	@Test
	public void testLoadUsersAndGetUserById() throws IOException, UserException {
		app.loadUsers("users.txt");
		assertNotNull(app.getUsersArray());
		assertEquals(9, app.getUsersArray().size());
		assertNotNull(app.getUserById("51999111X"));
	}
	
	@Test
	public void testCreateApartmentAndGetter() throws UserException, OfferException {
		app.createApartment(25555, "Street 101", "Swimming-pool included", landlord);
		assertNotNull(app.getApartmentsArray());
		assertEquals(1, app.getApartmentsArray().size());
	}
	
	@Test
	public void testCreateOffer1AndGetter() throws UserException, OfferException {
		app.createOffer(200.0f, apart, landlord, new GregorianCalendar(2018, 02, 02),0,1,0);
		assertNotNull(app.getOffersArray());
		assertEquals(1, app.getOffersArray().size());
	}
	
	@Test
	public void testCreateOffer2AndGetter() throws OfferException, UserException {
		app.createOffer(300.0f, apart, landlord, iniDate, finDate);
		assertNotNull(app.getOffersArray());
		assertEquals(1, app.getOffersArray().size());
	}
	
	@Test
	public void testBookOffer() throws OfferException, UserException {
		shr.setStatus(Status.FREE);
		app.bookOffer(shr, renter1);
		assertEquals(Status.BOOKED, shr.getStatus());
	}
	
	@Test
	public void testRentOffer() throws OfferException, UserException, OrderRejectedException {
		lng.setStatus(Status.FREE);
		app.rentOffer(lng, renter2);
		assertEquals(Status.RENTED, lng.getStatus());
	}
	
	@Test
	public void testAddCommentary1() throws UserException, OfferException {
		app.addCommentary(text, renter1, newFinDate, 2);
		assertNotNull(app.getCommentsArray());
		assertEquals(1, app.getCommentsArray().size());
	}
	
	@Test
	public void testAddCommentary2() throws UserException, OfferException {
		shr.setStatus(Status.RENTED);
		app.addCommentary(shr, renter2, newIniDate, "Very  good");
		assertNotNull(app.getCommentsArray());
		assertEquals(1, app.getCommentsArray().size());
	}
	
	@Test (expected = IOException.class)
	public void testLoadUsersException() throws IOException, UserException {
		app.loadUsers("trash_name.txt");
	}

}
