package Testing;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;
import java.util.*;

import padsof.*;
import padsof.Short;
import Exceptions.*;

public class ShortTest {
	private RegisteredUser user;
	private Apartment apart;
	private GregorianCalendar iniDate; 
	private GregorianCalendar finDate; 
	private GregorianCalendar newIniDate; 
	private GregorianCalendar newFinDate; 
	private Short shr;
	
	@Before
	public void setUp() throws UserException, OfferException{ /* UserException and OfferException will be checked later */
		user = new RegisteredUser("example user", "123456789", "password", "1111222233334444", "OD");
		apart = new Apartment(25550, "Street 45", "Two bathdrooms and four bedrooms", user);
		iniDate = new GregorianCalendar(2018, 02, 15);
		finDate = new GregorianCalendar(2018, 02, 18);	
		newIniDate = new GregorianCalendar(2018, 02, 17);
		newFinDate = new GregorianCalendar(2018, 02, 22);
		shr = new Short(150.0f, apart, user, iniDate, finDate);
	}
	
	@Test
	public void testGettersAndSetters() {
		assertEquals(iniDate, shr.getInitialDate());
		assertEquals(finDate, shr.getFinalDate());
		shr.setInitialDate(newIniDate);
		shr.setFinalDate(newFinDate);
		assertEquals(newIniDate, shr.getInitialDate());
		assertEquals(newFinDate, shr.getFinalDate());
		
	}

}
