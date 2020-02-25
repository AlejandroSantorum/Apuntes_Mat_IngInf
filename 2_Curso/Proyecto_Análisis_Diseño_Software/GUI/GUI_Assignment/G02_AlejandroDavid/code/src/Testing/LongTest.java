package Testing;

import static org.junit.Assert.*;

import java.util.GregorianCalendar;

import org.junit.Before;
import org.junit.Test;


import padsof.*;
import padsof.Long;
import Exceptions.*;

public class LongTest {
	private RegisteredUser user;
	private Apartment apart;
	private GregorianCalendar iniDate; 
	private Long lng;
	
	@Before
	public void setUp() throws UserException, OfferException{/* UserException and OfferException will be checked later */
		user = new RegisteredUser("example user", "123456789", "password", "1111222233334444", "OD");
		apart = new Apartment(25550, "Street 45", "Two bathdrooms and four bedrooms", user);
		iniDate = new GregorianCalendar(2018, 02, 15);
		lng = new Long(200.0f, apart, user, iniDate,0 , 1, 0);
	}

	@Test
	public void testGetterAndSetters() {
		assertEquals(30, lng.getMinimumPeriod());
		lng.setMinimumPeriod(20, 0, 0);
		assertEquals(20, lng.getMinimumPeriod());
		lng.setMinimumPeriod(0, 0, 1);
		assertEquals(365, lng.getMinimumPeriod());
		assertEquals(iniDate, lng.getInitialDate());
		lng.setMinimumPeriod(1, 1, 1);
		assertEquals(396, lng.getMinimumPeriod());
	}
	
}
