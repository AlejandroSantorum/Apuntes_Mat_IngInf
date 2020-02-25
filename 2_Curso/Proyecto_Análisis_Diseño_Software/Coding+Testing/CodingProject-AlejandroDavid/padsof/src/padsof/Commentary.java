package padsof;

import java.io.Serializable;
import java.util.*;

import Exceptions.*;

/**
 * @author Alejandro Santorum y David Cabornero
 * This class creates and allows us to work with commentaries
 * about other commentaries or offers.
 */
public abstract class Commentary implements Serializable{
	private GregorianCalendar date;
	private RegisteredUser commentator;
	private ArrayList<Commentary> commentsArray;
	
	/**
	 * This constructor allows us to create a new commentary.
	 * @param commentator The registered user who made this commentary
	 * @param date The date and time when the commentary was created
	 * @throws UserException the user is blocked
	 */
	public Commentary(RegisteredUser commentator, GregorianCalendar date) throws UserException{
		if(commentator.isBlocked()) {
			throw new BlockedUserException("A blocked user is trying to comment");
		}
		this.commentator = commentator;
		this.date = date;
		commentsArray = new ArrayList<Commentary>();
	}
	
	/**
	 * This getter gives the date when the commentary was created
	 * @return The date and time when the commentary was created
	 */
	public GregorianCalendar getDate() {
		return date;
	}
	
	/**
	 * This getter gives the registered user who comments the commentary
	 * @return Registered User who comments the commentary
	 */
	public RegisteredUser getCommentator() {
		return commentator;
	}
	
	/**
	 * This getter gives us the array of commentaries which comments this commentary.
	 * @return Array of commentaries which comments this commentary.
	 */
	public ArrayList<Commentary> getComments(){
		return commentsArray;
	}
	
	/**
	 * This function allows us to comment our commentary.
	 * @param comment The new commentary
	 */
	public void commentCommentary(Commentary comment) {
		commentsArray.add(comment);
	}
	
	/**
	 * This toString gives the information about the nick of the commentator
	 * and the date and time when the commentary was created.
	 */
	public String toString() {
		String aux = " --- Commentary ---\n";
		aux += "Commentator: "+commentator.getNick()+"\n";
		aux = aux + "Date: "+date.get(Calendar.DATE)+"-"+date.get(Calendar.MONTH)+"-"+date.get(Calendar.YEAR)+"\n";
		return aux;
	}
	
}
