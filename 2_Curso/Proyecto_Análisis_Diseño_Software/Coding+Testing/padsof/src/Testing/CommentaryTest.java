package Testing;

import static org.junit.Assert.*;

import java.util.*;
import org.junit.Before;
import org.junit.Test;

import padsof.*;
import Exceptions.*;

public class CommentaryTest {
	private RegisteredUser user;
	private GregorianCalendar date;
	private Commentary comment1;
	private Commentary comment2;
	private ArrayList<Commentary> array;
	
	@Before
	public void setUp() throws UserException{ /* UserException will be checked later */
		user = new RegisteredUser("example user", "123456789", "password", "1111222233334444", "OD");
		date = new GregorianCalendar(2018, 02, 15);
		comment1 = new Rating(user, date, 4);
		comment2 = new Textual(user, date, "Hi! We are testing Commentary!");
		array = new ArrayList<Commentary>(Arrays.asList(comment2));
	}

	@Test
	public void testGetters() {
		assertSame(date, comment1.getDate());
		assertSame(date, comment2.getDate());
		assertSame(user, comment1.getCommentator());
		assertSame(user, comment2.getCommentator());
	}
	
	@Test
	public void testCommentCommenratyAndGetComments() {
		comment1.commentCommentary(comment2);
		assertEquals(array, comment1.getComments());
	}

}
