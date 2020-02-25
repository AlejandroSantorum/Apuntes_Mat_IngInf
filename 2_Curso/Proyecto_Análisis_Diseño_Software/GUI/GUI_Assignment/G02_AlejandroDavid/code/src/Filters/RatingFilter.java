package Filters;

import padsof.*;
/**
 * 
 * @author Alejandro Santorum and David Cabornero
 * This class implements the necessary methods to filter a certain rating of an offer.
 *
 */
public class RatingFilter implements Filter{
	private int points;
	/**
	 * This constructor allows to create a new RatingFilter
	 * @param points The minimum rating to be filtered
	 */
	public RatingFilter(int points) {
		this.points = points;
	}
	
	/**
	 * Function that checks if certain offer pass the filter
	 * @param off Offer to be filtered
	 * @return true if  the offer has at least the minimum rating of the filter, else false
	 */
	public Boolean check(Offer off) {
		if(off.getRatingMedia() >= points) {
			return true;
		}
		return false;
	}
}
