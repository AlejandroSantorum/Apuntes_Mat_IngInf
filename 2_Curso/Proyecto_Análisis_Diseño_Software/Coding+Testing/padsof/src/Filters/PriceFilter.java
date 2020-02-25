package Filters;

import padsof.*;
/**
 * 
 * @author Alejandro Santorum and David Cabornero
 * This class implements the necessary methods to filter a certain range of prices of an offer.
 *
 */
public class PriceFilter implements Filter{
	private int min;
	private int max;
	
	/**
	 * This constructor allows to create a new PriceFilter
	 * @param min Minimum price allowed by the filter
	 * @param max Maximum price allowed by the filter
	 */
	public PriceFilter(int min, int max) {
		this.min = min;
		this.max = max;
	}
	
	/**
	 * Function that checks if certain offer pass the filter
	 * @param off Offer to be filtered
	 * @return true if the price of the offer is in the range of prices, else false
	 */
	public Boolean check(Offer off) {
		float p = off.getPrice();
		
		if(min <= p && p <= max) {
			return true;
		}
		return false;
	}

}
