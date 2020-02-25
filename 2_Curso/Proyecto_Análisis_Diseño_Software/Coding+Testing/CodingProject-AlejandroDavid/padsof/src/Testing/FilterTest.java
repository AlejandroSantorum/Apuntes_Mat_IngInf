package Testing;

import static org.junit.Assert.*;

import org.junit.Test;
import java.util.*;
import org.junit.Before;

import Exceptions.OfferException;
import Exceptions.UserException;
import padsof.*;
import Filters.*;
import padsof.Long;
import padsof.Short;

public class FilterTest {
	RegisteredUser user;
	Apartment apart;
	private Offer shr1, shr2, lng1, lng2;
	private Set<Status> statusArray;

	@Before
	public void SetUp() throws UserException, OfferException {
		user = new RegisteredUser("example user", "123456789", "password", "1111222233334444", "OD");
		apart = new Apartment(25550, "Street 45", "Two bathdrooms and four bedrooms", user);
		shr1 = new Short(150.0f, apart, user, new GregorianCalendar(2018, 02, 15), new GregorianCalendar(2018, 02, 20));
		shr2 = new Short(300.0f, apart, user, new GregorianCalendar(2018, 03, 15), new GregorianCalendar(2018, 04, 15));
		lng1 = new Long(200.0f, apart, user, new GregorianCalendar(2018, 03, 15),0 , 1, 0);
		lng2 =  new Long(500.0f, apart, user, new GregorianCalendar(2018, 05, 15),0 , 1, 0);
		statusArray = new HashSet<Status>(Arrays.asList(Status.FREE, Status.WAITING));
	}
	
	@Test
	public void testTypeStayFilter() {
		TypeStayFilter fil = new TypeStayFilter(OfferType.SHORT);
		assertTrue(fil.check(shr1));
		assertTrue(fil.check(shr2));
		assertFalse(fil.check(lng1));
		assertFalse(fil.check(lng2));
	}
	
	@Test
	public void testPriceFilter() {
		PriceFilter fil = new PriceFilter(200, 400);
		assertFalse(fil.check(shr1));
		assertTrue(fil.check(shr2));
		assertTrue(fil.check(lng1));
		assertFalse(fil.check(lng2));
	}
	
	@Test
	public void testRatingFilter() {
		RatingFilter fil1 = new RatingFilter(2);
		RatingFilter fil2 = new RatingFilter(3);
		assertTrue(fil1.check(shr1));
		assertTrue(fil1.check(shr2));
		assertTrue(fil1.check(lng1));
		assertTrue(fil1.check(lng2));
		assertFalse(fil2.check(shr1));
		assertFalse(fil2.check(shr2));
		assertFalse(fil2.check(lng1));
		assertFalse(fil2.check(lng2));
	}
	
	@Test
	public void testPostalCodeFilter() {
		PostalCodeFilter fil1 = new PostalCodeFilter(25550);
		PostalCodeFilter fil2 = new PostalCodeFilter(25551);
		assertTrue(fil1.check(shr1));
		assertTrue(fil1.check(shr2));
		assertTrue(fil1.check(lng1));
		assertTrue(fil1.check(lng2));
		assertFalse(fil2.check(shr1));
		assertFalse(fil2.check(shr2));
		assertFalse(fil2.check(lng1));
		assertFalse(fil2.check(lng2));
	}
	
	@Test
	public void testStatusFilter() {
		StatusFilter fil1 = new StatusFilter(statusArray);
		assertTrue(fil1.check(shr1));
		assertTrue(fil1.check(shr2));
		assertTrue(fil1.check(lng1));
		assertTrue(fil1.check(lng2));
		shr1.setStatus(Status.BOOKED);
		assertFalse(fil1.check(shr1));
	}
	
	@Test
	public void testShortTimeFilter() {
		ShortTimeFilter fil = new ShortTimeFilter(new GregorianCalendar(2018, 01, 01), new GregorianCalendar(2019, 01, 01));
		assertTrue(fil.check(shr1));
		assertTrue(fil.check(shr2));
		assertFalse(fil.check(lng1));
		assertFalse(fil.check(lng2));
		ShortTimeFilter fil2 = new ShortTimeFilter(new GregorianCalendar(2018, 01, 01), new GregorianCalendar(2018, 03, 15));
		assertTrue(fil2.check(shr1));
		assertFalse(fil2.check(shr2));
		assertFalse(fil2.check(lng1));
		assertFalse(fil2.check(lng2));
	}
	
	@Test
	public void testLongTimeFilter() {
		LongTimeFilter fil = new LongTimeFilter(new GregorianCalendar(2018, 01, 01), 0, 2, 0);
		assertTrue(fil.check(lng1));
		assertTrue(fil.check(lng2));
		assertFalse(fil.check(shr1));
		assertFalse(fil.check(shr2));
		LongTimeFilter fil2 = new LongTimeFilter(new GregorianCalendar(2019, 01, 01), 0, 2, 0);
		assertFalse(fil2.check(shr1));
		assertFalse(fil2.check(shr2));
		assertFalse(fil2.check(lng1));
		assertFalse(fil2.check(lng2));
	}
	
	
}