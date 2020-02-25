package Filters;

import java.util.*;
import padsof.*;

/**
 * 
 * @author Alejandro Santorum and David Cabornero
 * This class implements the necessary methods to filter certain status of an offer.
 *
 */
public class StatusFilter implements Filter{
	private Set<Status> statusArray;
	
	/**
	 * This constructor allows to create a new PostalCodeFilter
	 * @param statusArray The set of status to be filtered
	 */
	public StatusFilter(Set<Status> statusArray) {
		this.statusArray = statusArray;
	}
	
	/**
	 * Function that checks if certain offer pass the filter
	 * @param off Offer to be filtered
	 * @return true if the status is one of the status of the filter, else false
	 */
	public Boolean check(Offer off) {
		return statusArray.contains(off.getStatus());
	}

}
