package Filters;

import padsof.*;

/**
 * 
 * @author Alejandro Santorum and David Cabornero
 * This class implements the necessary methods to filter a certain postal code of an offer.
 *
 */
public class PostalCodeFilter implements Filter{
	private int pc;
	
	/**
	 * This constructor allows to create a new PostalCodeFilter
	 * @param pc The postal code to be filtered
	 */
	public PostalCodeFilter(int pc) {
		if(pc <= 0){
		      throw new IllegalArgumentException("PC is lower or equal than cero: " + pc); 
		}
		this.pc = pc;
	}
	
	/**
	 * Function that checks if certain offer pass the filter
	 * @param off Offer to be filtered
	 * @return true if  the offer has the postal code of the filter, else false
	 */
	public Boolean check(Offer off) {
		if(off.getApartment().getPc() == pc) return true;
		return false;
	}
}
