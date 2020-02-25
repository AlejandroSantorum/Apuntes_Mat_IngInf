package padsof;


import java.util.Calendar;
import java.util.GregorianCalendar;

import Exceptions.OfferException;
import Exceptions.UserException;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This class allows us to create new long stay offers. These offers can specifically start in a certain day (or later)
 * and the renter has a minimum period of the contract, unlike the short stay offers.
 */
public class Long extends Offer{
	private GregorianCalendar initialDate;
	private int minimumPeriod;

	/**
	 * This constructor allows to create a new long stay Offer
	 * @param price The price of the offer
	 * @param apartment The apartment to be rented
	 * @param owner The Landlord of the apartment
	 * @param initialDate the initial date of the offer
	 * @param nDays The minimum number of days of the contract (you also have to introduce months and years)
	 * @param nMonths The minimum number of months of the contract (you also have to introduce days and years)
	 * @param nYears The minimum number of years of the contract (you also have to introduce months and days)
	 * @throws UserException this user cannot offer
	 * @throws OfferException invalid offer operation
	 */
	public Long(float price, Apartment apartment, RegisteredUser owner, GregorianCalendar initialDate, int nDays, int nMonths, int nYears) throws OfferException, UserException{
		super(price, apartment, owner);
		this.initialDate = initialDate;
		minimumPeriod = nDays + nMonths*30 + nYears*365;	
	}
	
	/**
	 * This getter gives the first day when the offer can be rented
	 * @return Initial date of the offer
	 */
	public GregorianCalendar getInitialDate() {
		return initialDate;
	}
	
	/**
	 * This getter gives the number of days of the contract (minimum)
	 * @return The minimum period
	 */
	public int getMinimumPeriod() {
		return minimumPeriod;
	}
	
	/**
	 * This getter gives the type of the offer (it always returns the type long)
	 * @return OfferType.LONG
	 */
	public OfferType getOfferType() {
		return OfferType.LONG;
	}

	/**
	 * This setter modifies the mimimum period of the contract
	 * @param nDays The minimum number of days of the contract (you also have to introduce months and years)
	 * @param nMonths The minimum number of months of the contract (you also have to introduce days and years)
	 * @param nYears The minimum number of years of the contract (you also have to introduce months and days)
	 */
	public void setMinimumPeriod(int nDays, int nMonths, int nYears) {
		this.minimumPeriod = nDays + nMonths*30 + nYears*365;
	}
	
	/**
	 * This toString returns a string with the minimum period of the contract in days and the data of the offer.
	 */
	public String toString() {
		String aux;
		aux = "== Long Offer ==\n";
		aux = aux + "Initial Date: "+initialDate.get(Calendar.DATE)+"-"+initialDate.get(Calendar.MONTH)+"-"+initialDate.get(Calendar.YEAR)+"\n";
		aux = aux + "Minimum period: "+minimumPeriod+" days\n";
		aux = aux + super.toString();
		return aux;
	}

}
