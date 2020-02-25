package padsof;

import java.util.ArrayList;
import java.io.*;

import Exceptions.*;
/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This class allows us to create a new registered user. We can also save his data (nick, password,
 * comments, credit card...) or modify this personal values.
 *
 */
public class RegisteredUser implements Serializable{
	private String nick;
	private String id;
	private String password;
	private String creditCard;
	private Boolean blocked;
	private UserType userType;
	ArrayList<Apartment> apartments;
	ArrayList<Offer> offers;
	ArrayList<Offer> bookedOffers;
	ArrayList<Offer> rentedOffers;
	ArrayList<Commentary> comments;
	
	/**
	 * This constructor allows us to create a new RegisteredUser
	 * @param nick The name of the user in the application
	 * @param id ID (unique) of the user
	 * @param password User's secret password
	 * @param creditCard Credit card number of the user
	 * @param userChar 'O' if the user is LANDLORD, 'D' if the user is RENTER, 'OD' if the user is both
	 * @throws UserException invalid user
	 */
	public RegisteredUser(String nick, String id, String password, String creditCard, String userChar) throws UserException{
		this.nick = nick;
		this.id = id;
		this.password = password;
		this.creditCard = creditCard;
		this.blocked = false;
		this.userType = UserType.charToUserType(userChar);
		this.apartments = new ArrayList<Apartment>();
		this.offers = new ArrayList<Offer>();
		this.bookedOffers = new ArrayList<Offer>();
		this.rentedOffers = new ArrayList<Offer>();
		this.comments = new ArrayList<Commentary>();
	}

	/**
	 * This getter gives the nick of the user
	 * @return the nick
	 */
	public String getNick() {
		return nick;
	}

	/**
	 * This getter gives the id of the user
	 * @return the id
	 */
	public String getId() {
		return id;
	}

	/**
	 * This getter gives the password of the user
	 * @return the password
	 */
	public String getPassword() {
		return password;
	}

	/**
	 * This getter gives the credit card of the user
	 * @return the creditCard
	 */
	public String getCreditCard() {
		return creditCard;
	}
	
	/**
	 * This getter allows to know if the user is blocked
	 * @return true if blocked, otherwise false
	 */
	public Boolean isBlocked() {
		return blocked;
	}
	
	/**
	 * This getter gives the type of the user
	 * @return the user type
	 */
	public UserType getUserType() {
		return userType;
	}
	
	/**
	 * This getter gives the array of apartments registered by the user
	 * @return The array of apartments of the user
	 * @throws UserException this user cannot register a property
	 */
	public ArrayList<Apartment> getUserApartments() throws UserException{
		if(!userType.canRegister()) {
			throw new InvalidUserTypeException("An user not Landlord type hasn't got registered properties");
		}
		return apartments;
	}
	
	/**
	 * This getter gives the array of offers created by the user
	 * @return Array of offers created
	 * @throws UserException this user cannot offer a property
	 */
	public ArrayList<Offer> getUserOffers() throws UserException{
		if(!userType.canOffer()) {
			throw new InvalidUserTypeException("An user not Landlord type hasn't got registered offers");
		}
		return offers;
	}
	
	/**
	 * This getter gives the array of offers booked by the user
	 * @return Array of offers booked
	 * @throws UserException this user cannot book
	 */
	public ArrayList<Offer> getBookedOffers() throws UserException{
		if(!userType.canBook()) {
			throw new InvalidUserTypeException("An user not Renter type hasn't got booked offers");
		}
		return bookedOffers;
	}
	
	/**
	 * This getter gives the array of offers rented by the user
	 * @return Array of offers rented
	 * @throws UserException this user cannot rent
	 */
	public ArrayList<Offer> getUserRentedOffers() throws UserException{
		if(!userType.canRent()) {
			throw new InvalidUserTypeException("An user not Renter type hasn't got rented offers");
		}
		return rentedOffers;
	}
	
	/**
	 * This getter gives the array of comments created by the user
	 * @return Array of comments created
	 */
	public ArrayList<Commentary> getUserComments(){
		return comments;
	}
	
	/**
	 * This setter allows to set a new credit card number
	 * @param creditCard the creditCard to set
	 */
	public void setCreditCard(String creditCard) {
		this.creditCard = creditCard;
	}
	
	/**
	 * This function blocks the user
	 */
	public void setBlocked() {
		if(this.userType != UserType.RENTER) return; //we can only block an user if he is a renter
		if(this.blocked) this.blocked = false;
		else this.blocked = true;
	}
	
	/**
	 * This toString returns the nick of the user, the password, the id, the credit card number and
	 * shows if the user is blocked or not.
	 */
	public String toString() {
		String str;
		str = "== "+userType+" ==\n";
		str = "Nick: "+nick+"\n";
		str = str + "Password: "+password+"\n"; /* Only for testing */
		str = str + "Id: "+id+"\n";
		str = str + "Credit Card: "+creditCard+"\n";
		str = str + "Blocked: "+blocked+"\n";
		return str; 
	}
	
	/**
	 * This function compares our user with another user.
	 * @param user The user to be compared
	 * @return true if they are the same user (same id), else false
	 */
	public Boolean equals(RegisteredUser user) {
		if(this.id.equals(user.id)) return true;
		return false;
	}
	
	/**
	 * This function allows to add a new apartment to the list of apartments of the Landlord
	 * @param apart Apartment to be added
	 * @throws UserException this cannot book or its blocked
	 */
	public void addApartment(Apartment apart) throws UserException{
		if(blocked) {
			throw new BlockedUserException("A blocked user is trying to save a new apartment");
		}
		if(!userType.canRegister()) {
			throw new InvalidUserTypeException("An user not Landlord type is trying to save a new apartment");
		}
		apartments.add(apart);
	}
	
	/**
	 * This function allows to add a new offer to the list of offers of the Landlord
	 * @param off Offer to be added
	 * @throws UserException this cannot book or its blocked
	 */
	public void addOffer(Offer off) throws UserException{
		if(blocked) {
			throw new BlockedUserException("A blocked user is trying to save a rented offer");
		}
		if(!userType.canOffer()) {
			throw new InvalidUserTypeException("An user not Landlord type is trying to save a new offer");
		}
		offers.add(off);
	}
	
	/**
	 * This function allows to add a new offer to the list of booked offers of the Renter
	 * @param off Offer to be added
	 * @throws UserException this cannot book or its blocked
	 */
	public void addBookedOffer(Offer off) throws UserException{
		if(blocked) {
			throw new BlockedUserException("A blocked user is trying to save a booked offer");
		}
		if(!userType.canBook()) {
			throw new InvalidUserTypeException("An user not Renter type is trying to save a new booked offer");
		}
		bookedOffers.add(off);
	}
	
	/**
	 * This function allows to add a new offer to the list of rented offers of the Renter
	 * @param off Offer to be added
	 * @throws UserException the user is blocked or it cannot rent
	 */
	public void addRentedOffer(Offer off) throws UserException{
		if(blocked) {
			throw new BlockedUserException("A blocked user is trying to save a new rented offer");
		}
		if(!userType.canRent()) {
			throw new InvalidUserTypeException("An user not Renter type is trying to save a new rented offer");
		}
		
		if(bookedOffers.contains(off)) bookedOffers.remove(off);
		rentedOffers.add(off);
	}
	
	/**
	 * This function allows to add a new comment to the array of comments of the user
	 * @param comment The comment to be added
	 * @throws UserException the user is blocked
	 */
	public void addComment(Commentary comment) throws UserException{
		if(blocked) {
			throw new BlockedUserException("A blocked user is trying to save a new commentary");
		}
		comments.add(comment);
	}
}
