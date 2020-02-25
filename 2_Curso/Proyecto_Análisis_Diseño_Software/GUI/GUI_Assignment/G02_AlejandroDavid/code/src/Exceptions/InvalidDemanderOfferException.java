package Exceptions;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This exception is thrown when a Renter cannot rent a certain offer.
 *
 */
public class InvalidDemanderOfferException extends OfferException{
	
	/**
	 * Constructor of the exception InvalidDemanderOfferException
	 * @param m Message sent to the console if the exception is thrown
	 */
	public InvalidDemanderOfferException(String m) {
		super(m);
	}

}
