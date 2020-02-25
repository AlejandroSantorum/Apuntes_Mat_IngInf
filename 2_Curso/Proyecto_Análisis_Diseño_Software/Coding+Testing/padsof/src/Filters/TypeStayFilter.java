package Filters;

import padsof.*;

/**
 * 
 * @author Alejandro Santorum and David Cabornero
 * This class implements the necessary methods to filter the type of stay of an offer
 *
 */
public class TypeStayFilter implements Filter{
	private OfferType ot;
	
	/**
	 * This constructor allows to create a new OfferTypeFilter
	 * @param ot OfferType to be filtered
	 */
	public TypeStayFilter(OfferType ot) {
		this.ot = ot;
	}
	
	/**
	 * Function that checks if certain offer pass the filter
	 * @param off Offer to be filtered
	 * @return true if the type of the offer is the same that the type of the filter, else false
	 */
	public Boolean check(Offer off) {
		if(off.getOfferType() == ot) return true;
		return false;
	}

}
