package Testing;

import static org.junit.Assert.*;

import java.util.*;
import org.junit.Before;
import org.junit.Test;

import Exceptions.*;
import padsof.*;

public class RatingTest {
	private RegisteredUser user;
	public Rating comment1;
	
	@Before
	public void setUp() throws UserException{ /* UserException will be checked later */
		user = new RegisteredUser("example user", "123456789", "password", "1111222233334444", "OD");
		comment1 = new Rating(user, new GregorianCalendar(2018, 02, 15), 4);
	}
	
	@Test
	public void testGetters() {
		assertEquals(4,  comment1.getPoints());
	}
	
}
