package Exceptions;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This exception is thrown when we can do some actions on one offer because of some
 *  attribute/s of the user.
 *
 */
public class UserException extends Exception{
	
	/**
	 * Constructor of the exception UserException
	 * @param m Message sent to the console if the exception is thrown
	 */
	public UserException(String m) {
		super(m);
	}

}
