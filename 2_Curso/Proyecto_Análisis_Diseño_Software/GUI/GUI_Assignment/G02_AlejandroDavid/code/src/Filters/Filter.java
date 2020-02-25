package Filters;

import padsof.Offer;
/**
 * 
 * @author David Cabornero y Alejandro Santorum
 * 
 * Interface used to create all filters, which are going to filter the offers depending on certain criteria.
 */
public interface Filter {
	/**
	 * Function that checks if certain offer pass the filter
	 * @param off Offer to be filtered
	 * @return true if the the offer pass the filter, else false
	 */
	public Boolean check(Offer off);
}
