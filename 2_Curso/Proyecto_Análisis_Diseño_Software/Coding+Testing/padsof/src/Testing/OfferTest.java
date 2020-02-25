package Testing;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;
import java.util.*;

import padsof.*;
import padsof.Long;
import Exceptions.*;
import es.uam.eps.padsof.telecard.OrderRejectedException;

public class OfferTest {
	private RegisteredUser renter;
	private RegisteredUser landlord;
	private Apartment apart;
	private Offer offer;
	private Commentary comment1;
	private ArrayList<Commentary> comments;
	
	@Before
	public void setUp() throws UserException, OfferException{
		renter = new RegisteredUser("Renter user", "123456789", "pass1", "1234567890123456", "D");
		landlord =  new RegisteredUser("Landlord user", "987654321", "pass2", "987654321098", "O");
		apart = new Apartment(25555, "Street 101", "Swimming-pool included", landlord);
		offer = new Long(200.0f, apart, landlord, new GregorianCalendar(2018, 02, 02), 0, 1, 0);
		comment1 = new Textual(renter, new GregorianCalendar(2018, 02, 15), "Hi! We are testing Textual!");
		comments = new ArrayList<Commentary>(Arrays.asList(comment1));
	}

	@Test
	public void testGettersAndSetters() {
		assertEquals(200.0f, offer.getPrice(), 0);
		assertEquals(Status.WAITING, offer.getStatus());
		assertSame(apart, offer.getApartment());
		assertSame(landlord, offer.getOwner());
		offer.setStatus(Status.FREE);
		assertEquals(Status.FREE, offer.getStatus());
		offer.setDemander(renter);
		assertSame(renter, offer.getDemander());
		offer.setPrice(400.0f);
		assertEquals(400.0f, offer.getPrice(), 0);
	}
	
	@Test
	public void testBookOffer() throws UserException, OfferException{
		/* First, we have to set our example offer in Free Status,
		 * that means Manager has approved it and it enters the renting system.*/
		offer.setStatus(Status.FREE);
		
		offer.bookOffer(renter);
		assertEquals(Status.BOOKED, offer.getStatus());
		assertEquals(renter, offer.getDemander());
	}
	
	@Test
	public void testRentOffer() throws UserException, OfferException, OrderRejectedException{
		offer.setStatus(Status.FREE);
		
		offer.rentOffer(renter);
		assertEquals(Status.RENTED, offer.getStatus());
		assertEquals(renter, offer.getDemander());
	}
	
	@Test
	public void testCommentOffer() throws OfferException {
		offer.setStatus(Status.FREE);
		
		offer.commentOffer(comment1);
		assertEquals(comments, offer.getComments());
		
	}
	
	@Test (expected = UserException.class)
	public void testExBookOffer1() throws UserException, OfferException{
		offer.setStatus(Status.FREE);
		
		offer.bookOffer(landlord); /* A landlord cannot book */
	}
	
	@Test (expected = UserException.class)
	public void testExBookOffer2() throws UserException, OfferException{
		offer.setStatus(Status.FREE);
		renter.setBlocked();
		
		offer.bookOffer(renter); /* A blocked user cannot book */
	}
	
	@Test (expected = OfferException.class)
	public void testExBookOffer3() throws UserException, OfferException{
		offer.bookOffer(renter); /* Unable to book an offer that its Status is not equal than FREE */
	}
	
	@Test (expected = UserException.class)
	public void testExRentOffer1() throws UserException, OfferException, OrderRejectedException{
		offer.setStatus(Status.FREE);
		
		offer.rentOffer(landlord); /* A landlord cannot rent */
	}
	
	@Test (expected = UserException.class)
	public void testExRentOffer2() throws UserException, OfferException, OrderRejectedException{
		offer.setStatus(Status.FREE);
		renter.setBlocked();
		
		offer.rentOffer(landlord); /* A blocked user cannot rent */
	}
	
	@Test (expected = OfferException.class)
	public void testExRentOffer3() throws UserException, OfferException, OrderRejectedException{
		offer.rentOffer(renter); /* Unable to rent an offer that its Status is not equal than FREE */
	}
	
	@Test (expected = OfferException.class)
	public void testExRentOffer4() throws UserException, OfferException, OrderRejectedException{
		offer.setStatus(Status.FREE);
		RegisteredUser auxRenter = new RegisteredUser("Aux Renter user", "987654321", "passAux", "9876543210987654", "D");
		offer.bookOffer(auxRenter);
		
		offer.rentOffer(renter); /* Unable to rent an offer that is booked by ANOTHER user */
	}
	
	@Test (expected = OrderRejectedException.class)
	public void testExRentOffer5() throws UserException, OfferException, OrderRejectedException{
		offer.setStatus(Status.FREE);
		renter.setCreditCard("bad credit card number");
		
		offer.rentOffer(renter); /* The credit card is supposed to fail */
	}

}
