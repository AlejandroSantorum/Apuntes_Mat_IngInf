package padsof;

import java.util.*;

import Exceptions.*;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 *
 *This class allows us to create a Short stay offer. Specifically, it has an initial date
 *and a final date, indicating the maximum range of dates of the stay.
 */
public class Short extends Offer{
	private GregorianCalendar initialDate;
	private GregorianCalendar finalDate;
	
	/**
	 * This constructor allows to create a new Short offer.
	 * @param price The price of the offer
	 * @param apartment The apartment that is going to be rented
	 * @param owner The Landlord who is going to rent the apartment
	 * @param initialDate Beginning of the range of dates of the stay
	 * @param finalDate End of the range of dates of the stay
	 * @throws UserException invalid user
	 * @throws OfferException invalid offer operation
	 */
	public Short(float price, Apartment apartment, RegisteredUser owner, GregorianCalendar initialDate, GregorianCalendar finalDate) throws OfferException, UserException{
		super(price, apartment, owner);
		if(initialDate.compareTo(finalDate) >= 0){
		      throw new IllegalArgumentException("The initial date has to be previous than the final date"); 
		}
		this.initialDate = initialDate;
		this.finalDate = finalDate;
	}

	/**
	 * This getter gives us the initial date of the range of stays
	 * @return The initial date of the range of stays
	 */
	public GregorianCalendar getInitialDate() {
		return initialDate;
	}
	
	/**
	 * This getter gives us the type of the offer
	 * @return The type of the offer
	 */
	public OfferType getOfferType() {
		return OfferType.SHORT;
	}

	/**
	 * This getter gives us the final date of the range of stays
	 * @return The final date of the range of stays
	 */
	public GregorianCalendar getFinalDate() {
		return finalDate;
	}

	/**
	 * This setter modifies the initial date of the range of dates
	 * @param initialDate The initialDate to set
	 */
	public void setInitialDate(GregorianCalendar initialDate) {
		this.initialDate = initialDate;
	}

	/**
	 * This setter modifies the final date of the range of dates
	 * @param finalDate The finalDate to set
	 */
	public void setFinalDate(GregorianCalendar finalDate) {
		this.finalDate = finalDate;
	}
	
	
	/*
	public String toString() {
		String aux;
		aux = "== Short Offer ==\n";
		aux = aux + "Initial Date: "+initialDate.get(Calendar.DATE)+"-"+initialDate.get(Calendar.MONTH)+"-"+initialDate.get(Calendar.YEAR)+"\n";
		aux = aux + "Final Date: "+finalDate.get(Calendar.DATE)+"-"+finalDate.get(Calendar.MONTH)+"-"+finalDate.get(Calendar.YEAR)+"\n";
		aux = aux + super.toString();
		return aux;
	}*/
	
	/**
	 * This toString returns the range of dates of the short offer, the type of offer, the price,
	 * the apartment data and the nick of the Landlord.
	 */
	public String toString() {
		String aux;
		aux = "Short Stay | ";
		aux += super.toString();
		return aux;
	}
	
	/**
	 * This checks if two short stay type offers are equal or not
	 * @param off Offer to be compared with this
	 * @return true if they are equal, false otherwise
	 */
	public Boolean equals(Offer off) {
		if(this.getPrice() != off.getPrice()) return false;
		if(this.getOfferType() != off.getOfferType()) return false;
		if(this.getStatus() != off.getStatus()) return false;
		if(!this.getApartment().equals(off.getApartment())) return false;
		if(!this.getOwner().equals(off.getOwner())) return false;
		if(!this.initialDate.equals(((Short) off).getInitialDate())) return false;
		if(!this.finalDate.equals(((Short)off).getFinalDate())) return false;
		return true;
	}
	
	
}
