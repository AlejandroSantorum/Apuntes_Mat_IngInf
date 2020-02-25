package padsof;

import java.util.*;
import Exceptions.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * 
 *This class is a type of commentary which has 
 * a numerical rating of a commentary/offer.
 */
public class Rating extends Commentary{
	private int points;

	/**
	 * This constructor creates a new Rating class
	 * @param user Registered user who rates
	 * @param date Date and time when the commentary/offer is rated
	 * @param stars Number of points given to the commentary/offer
	 * @throws UserException invalid user
	 */
	public Rating(RegisteredUser user, GregorianCalendar date, int stars) throws UserException{
		super(user, date);
		if(stars < 0){
		      throw new IllegalArgumentException("The given points are lower than zero: " + stars); 
		}
		this.points = stars;
	}
	
	/**
	 * This getter gives us the rating of the commentary/offer
	 * @return Punctuation of the commentary/offer
	 */
	public int getPoints() {
		return points;
	}
	
	
	/*
	public String toString() {
		String aux = super.toString();
		aux += "Punctuation: "+points;
		return aux;
	}*/
	
	/**
	 * This toString gives us the information about the commentary and the punctuation
	 * given by the commentary.
	 */
	public String toString() {
		String aux = super.toString();
		aux += " | Rate = "+points;
		return aux;
	}
}
