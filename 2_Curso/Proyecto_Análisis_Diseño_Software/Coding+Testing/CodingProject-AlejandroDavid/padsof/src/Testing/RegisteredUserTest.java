package Testing;

import static org.junit.Assert.*;
import org.junit.Test;
import org.junit.Before;
import java.util.*;

import padsof.*;
import padsof.Long;
import Exceptions.*;


public class RegisteredUserTest {
	private RegisteredUser renter;
	private RegisteredUser landlord;
	private Apartment apart;
	private Offer offer;
	private Commentary comment1;
	private ArrayList<Offer> offers;
	private ArrayList<Apartment> apartments;
	private ArrayList<Commentary> comments;
	
	
	@Before
	public void setUp() throws UserException, OfferException{
		renter = new RegisteredUser("Renter user", "123456789", "pass1", "123456789012", "D");
		landlord =  new RegisteredUser("Landlord user", "987654321", "pass2", "987654321098", "O");
		apart = new Apartment(25555, "Street 101", "Swimming-pool included", landlord);
		offer = new Long(200.0f, apart, landlord, new GregorianCalendar(2018, 02, 02), 0, 1, 0);
		comment1 = new Textual(renter, new GregorianCalendar(2018, 02, 15), "Hi! We are testing Textual!");
		offers = new ArrayList<Offer>(Arrays.asList(offer));
		apartments = new ArrayList<Apartment>(Arrays.asList(apart));
		comments = new ArrayList<Commentary>(Arrays.asList(comment1));
	}

	@Test
	public void testGettersAndSetters() {
		assertEquals("Renter user", renter.getNick());
		assertEquals("987654321", landlord.getId());
		assertEquals("pass1", renter.getPassword());
		assertEquals("987654321098", landlord.getCreditCard());
		assertEquals(UserType.RENTER, renter.getUserType());
		assertEquals(false, landlord.isBlocked());
		renter.setBlocked();
		landlord.setBlocked(); // It should do nothing
		assertEquals(true, renter.isBlocked());
		assertEquals(false, landlord.isBlocked()); // We can only block renter users
		landlord.setCreditCard("1212121212121212");
		assertEquals("1212121212121212", landlord.getCreditCard());
	}
	
	@Test
	public void testArraysGettersAndSetters() throws UserException{
		landlord.addApartment(apart);
		landlord.addOffer(offer);
		
		renter.addBookedOffer(offer);
		assertEquals(offers, renter.getBookedOffers());
		renter.addRentedOffer(offer);
		
		renter.addComment(comment1);
		
		assertNotEquals(offers, renter.getBookedOffers());
		assertEquals(offers, renter.getUserRentedOffers());
		assertEquals(apartments, landlord.getUserApartments());
		assertEquals(comments, renter.getUserComments());
	}
	
	@Test (expected = UserException.class)
	public void testExAddApartment() throws UserException{
		renter.addApartment(apart);
	}
	
	@Test (expected = UserException.class)
	public void testExAddOffer() throws UserException{
		renter.addOffer(offer);
	}
	
	@Test (expected = UserException.class)
	public void testExAddBookedOffer() throws UserException{
		landlord.addBookedOffer(offer);
	}
	
	@Test (expected = UserException.class)
	public void testExAddRentedOffer() throws UserException{
		landlord.addRentedOffer(offer);
	}

}
