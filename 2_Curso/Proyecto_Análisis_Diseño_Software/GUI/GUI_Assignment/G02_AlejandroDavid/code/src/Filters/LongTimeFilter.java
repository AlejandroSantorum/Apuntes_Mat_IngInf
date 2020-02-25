package Filters;

import java.util.*;

import padsof.Long;
import padsof.*;

/**
 * 
 * @author Alejandro Santorum and David Cabornero
 * This class implements the necessary methods to filter a long time stay in function of its specific
 * attributes.
 *
 */
public class LongTimeFilter implements Filter{
	private GregorianCalendar initialDate;
	private int minimumPeriod;
	
	/**
	 * This constructor allows to create a new LongTimeFilter
	 * @param initialDate The initial date of the offer has to be later than this
	 * @param nDays Days of the minimum period (the period can be shorter)
	 * @param nMonths Months of the minimum period (the period can be shorter)
	 * @param nYears Years of the minimum period (the period can be shorter)
	 */
	public LongTimeFilter(GregorianCalendar initialDate, int nDays, int nMonths, int nYears) {
		this.initialDate = initialDate;
		minimumPeriod = nDays + nMonths*30 + nYears*365;
	}
	
	/**
	 * Function that checks if certain offer pass the filter
	 * @param off Offer to be filtered
	 * @return true if  the offer starts the initial date after the filter's date and if the minimum period is
	 * shorter than the filter's period, else false
	 */
	public Boolean check(Offer off) {
		if(off.getOfferType() != OfferType.LONG) return false;
		if(((Long)off).getMinimumPeriod() <= minimumPeriod) {
			if(((Long)off).getInitialDate().compareTo(initialDate) >= 0) {
				return true;
			}
		}
		return false;
	}
}
