package Exceptions;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This exception is thrown when a user cannot do a certain action because this user has not enough permissons.
 *
 */
public class InvalidUserTypeException extends UserException{
	
	/**
	 * Constructor of the exception InvalidUserTypeException
	 * @param m Message sent to the console if the exception is thrown
	 */
	public InvalidUserTypeException(String m) {
		super(m);
	}

}
