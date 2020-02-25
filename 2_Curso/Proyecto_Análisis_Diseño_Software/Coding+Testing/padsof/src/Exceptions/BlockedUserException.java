package Exceptions;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This exception is thrown when a Renter cannot do a certain action because this user is blocked.
 *
 */
public class BlockedUserException extends UserException{
	
	/**
	 * Constructor of the exception BlockedUserException
	 * @param m Message sent to the console if the exception is thrown
	 */
	public BlockedUserException(String m) {
		super(m);
	}

}
