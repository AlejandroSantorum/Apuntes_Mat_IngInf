package Exceptions;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This exception is thrown when we can do some actions on one offer because of some
 *  attribute/s of the offer.
 *
 */
public class OfferException extends Exception{
	
	/**
	 * Constructor of the exception OfferException
	 * @param m Message sent to the console if the exception is thrown
	 */
	public OfferException(String m) {
		super(m);
	}

}
