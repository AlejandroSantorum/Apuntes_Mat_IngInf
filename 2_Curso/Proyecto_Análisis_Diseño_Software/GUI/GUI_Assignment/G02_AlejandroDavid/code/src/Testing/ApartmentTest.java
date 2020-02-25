package Testing;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import padsof.*;
import Exceptions.*;

public class ApartmentTest {
	private RegisteredUser user;
	private RegisteredUser excepUser;
	private Apartment apart;
	
	@Before
	public void setUp() throws UserException{
		user = new RegisteredUser("example user", "123456789", "password", "1111222233334444", "OD");
		excepUser = new RegisteredUser("exception user", "987654321", "password2", "9999888877776666", "D");
		apart = new Apartment(25555, "Street 101", "Swimming-pool included", user);
	}

	@Test
	public void testGettersAndSetters() {
		assertEquals(25555, apart.getPc());
		assertEquals("Street 101", apart.getAddress());
		assertEquals("Swimming-pool included", apart.getDescription());
		assertSame(user, apart.getOwner());
	}
	
	@Test
	public void testEquals() throws UserException {
		Apartment apart2 = new Apartment(25555, "Street 101", "Swimming-pool included", user);
		assertTrue(apart.equals(apart2));
	}
	
	@Test (expected = UserException.class)
	public void testRenterUser() throws UserException{
		apart = new Apartment(30000, "Street 101", "Swimming-pool included", excepUser);
	}

}
