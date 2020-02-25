package padsof;

import java.util.*;
import Exceptions.*;

/**
* @author Alejandro Santorum and David Cabornero
* This class is a type of commentary which has 
* a textual review of a commentary/offer.
*/
public class Textual extends Commentary{
	private String text;

	/**
	* This constructor creates a new Textual class
	* @param user The registered user that made the Commentary
	* @param date The date and time when the commentary was made
	* @param text Text of the textual commentary
	* @throws UserException invalid user
	*/
	public Textual(RegisteredUser user, GregorianCalendar date, String text) throws UserException{
		super(user, date);
		this.text = text;
	}

	/**
	* This getter gives us the text of the textual commentary
	* @return The text of the textual commentary
	*/
	public String getText() {
		return text;
	}
	/**
	 * This toString gives us the information about the commentary and the text
	 * of the textual commentary.
	 */
	public String toString() {
		String aux = super.toString();
		aux += "Text: "+text;
		return aux;
	}
}
