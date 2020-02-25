package Exceptions;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This exception is thrown when a certain action cannot be executed because of the Status of the offer.
 *
 */
public class InvalidStatusOfferException extends OfferException{
	
	/**
	 * Constructor of the exception InvalidStatusOfferException
	 * @param m Message sent to the console if the exception is thrown
	 */
	public InvalidStatusOfferException(String m) {
		super(m);
	}

}
