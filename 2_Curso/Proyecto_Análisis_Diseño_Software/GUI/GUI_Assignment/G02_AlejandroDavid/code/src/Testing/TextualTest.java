package Testing;

import static org.junit.Assert.*;

import java.util.*;
import org.junit.Before;
import org.junit.Test;

import Exceptions.*;
import padsof.*;

public class TextualTest {
	private RegisteredUser user;
	public Textual comment1;
	
	@Before
	public void setUp() throws UserException{ /* UserException will be checked later */
		user = new RegisteredUser("example user", "123456789", "password", "1111222233334444", "OD");
		comment1 = new Textual(user, new GregorianCalendar(2018, 02, 15), "Hi! We are testing Textual!");
	}
	
	@Test
	public void testGetters() {
		assertEquals("Hi! We are testing Textual!", comment1.getText());
	}
	
}
