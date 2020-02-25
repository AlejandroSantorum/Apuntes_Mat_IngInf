package Exceptions;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This exception is thrown when a Register User cannot do some actions because of the type of the Offer.
 *
 */
public class InvalidOfferTypeException extends OfferException{
	
	/**
	 * Constructor of the exception InvalidOfferTypeException
	 * @param m Message sent to the console if the exception is thrown
	 */
	public InvalidOfferTypeException(String m) {
		super(m);
	}

}
