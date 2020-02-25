package Filters;

import java.util.GregorianCalendar;

import padsof.Short;
import padsof.*;

/**
 * 
 * @author Alejandro Santorum and David Cabornero
 * This class implements the necessary methods to filter a short time stay in function of its specific
 * attributes.
 *
 */
public class ShortTimeFilter implements Filter{
	private GregorianCalendar initialDate;
	private GregorianCalendar finalDate;
	
	/**
	 * * This constructor allows to create a new LongTimeFilter
	 * @param initialDate The initial date of the offer has to be later than this
	 * @param finalDate The final date of the offer has to be earlier than this
	 */
	public ShortTimeFilter(GregorianCalendar initialDate, GregorianCalendar finalDate) {
		this.initialDate = initialDate;
		this.finalDate = finalDate;
	}
	
	/**
	 * Function that checks if certain offer pass the filter
	 * @param off Offer to be filtered
	 * @return true if the range of dates of the offer contains the range of dates of the filter, else false
	 */
	public Boolean check(Offer off) {
		if(off.getOfferType() != OfferType.SHORT) return false;
		
		GregorianCalendar ini = ((Short)off).getInitialDate();
		GregorianCalendar fin = ((Short)off).getFinalDate();
		if(ini.compareTo(initialDate) >= 0 && ini.compareTo(finalDate) < 0) {
			if(fin.compareTo(initialDate) > 0 && fin.compareTo(finalDate) <= 0) {
				return true;
			}
		}
		return false;
	}

}
