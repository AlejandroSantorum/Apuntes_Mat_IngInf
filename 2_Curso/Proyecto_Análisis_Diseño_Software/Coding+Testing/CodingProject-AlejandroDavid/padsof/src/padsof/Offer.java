/**
 * 
 */
package padsof;

import java.io.*;
import java.util.*;

import Exceptions.*;
import es.uam.eps.padsof.telecard.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class allows us to create new offers, modify and get its attributes (like the price or the
 * apartment offered) or change its state (booked, rented, free...)
 */

public abstract class Offer implements Serializable{
	private float price;
	private Status status;
	private Apartment apartment;
	private RegisteredUser owner;
	private RegisteredUser demander;
	private ArrayList<Commentary> comments;
	
	/**
	 * This constructor creates a new offer
	 * @param price Price of the offer
	 * @param apartment Apartment to be offered
	 * @param owner Landlord who is going to offer the apartment
	 * @throws UserException this user cannot offer
	 */
	public Offer(float price, Apartment apartment, RegisteredUser owner) throws UserException{
		if(price <= 0.0f){
		      throw new IllegalArgumentException("Price is lower or equal than cero: " + price); 
		}
		if(!owner.getUserType().canOffer()) {
			throw new InvalidUserTypeException("An user not Landlord type is trying to create an offer");
		}
		this.price = price;
		this.status = Status.WAITING;
		this.apartment = apartment;
		this.owner = owner;
		this.demander = null;
		this.comments = new ArrayList<Commentary>();
	}
	
	/**
	 * This getter gives the price of the offer
	 * @return the price
	 */
	public float getPrice() {
		return price;
	}
	
	/**
	 * This getter gives the status of the offer (rented, booked...)
	 * @return the status
	 */
	public Status getStatus() {
		return status;
	}
	
	/**
	 * This getter gives the apartment offered
	 * @return the apartment
	 */
	public Apartment getApartment() {
		return apartment;
	}
	
	/**
	 * This getter gives the Landlord who did the offer
	 * @return the owner of the offer's apartment.
	 */
	public RegisteredUser getOwner() {
		return owner;
	}
	
	/**
	 * This getter gives the Renter who booked or rented the offer
	 * @return the client(demander) of the offer.
	 */
	public RegisteredUser getDemander() {
		return demander;
	}
	
	/**
	 * This getter gives the array of comments of the offer
	 * @return The array of comments
	 */
	public ArrayList<Commentary> getComments(){
		return comments;
	}
	
	/**
	 * This getter gives the media of the numerical comments
	 * @return The media of ratings
	 */
	public float getRatingMedia() {
		int sumat = 0;
		int n = 0;
		for(Commentary com: comments) {
			if(com instanceof Rating) {
				sumat += ((Rating) com).getPoints();
				n += 1;
			}
		}
		if(n==0) return 2.5f;
		return (sumat/n);
	}
	
	/**
	 * This function gives the type of stay (short or long)
	 * @return The type of stay
	 */
	public abstract OfferType getOfferType();
	
	/**
	 * This setter allows to set the status of the offer (free, rented, booked...)
	 * @param status the status to set
	 */
	public void setStatus(Status status) {
		this.status = status;
	}
	
	/**
	 * This setter allows to set the Renter who is going to rent or book the offer
	 * @param demander the demander to set
	 */
	public void setDemander(RegisteredUser demander) {
		this.demander = demander;
	}
	
	/**
	 * This function initializes the demander to null. It happens when, for example,
	 * the time of booking expires.
	 */
	public void unsetDemander() {
		this.demander = null;
	}
	
	/**
	 * This setter allows to set a new price 
	 * @param price The new price
	 */
	public void setPrice(float price) {
		this.price = price;
	}
	
	/**
	 * This toString returns the price of the offer, the status (free, booked...) the data of the apartment
	 * and the nick of the demander.
	 */
	public String toString() {
		String aux;
		aux = "Price: "+price+"\n";
		aux = aux + "Status: "+status+"\n";
		aux = aux + apartment;
		if(demander != null) aux=aux+"Demander: "+demander.getNick()+"\n";
		return aux;
	}
	
	/**
	 * This function allows to book the offer
	 * @param user The renter who is going to book the offer
	 * @throws UserException this user cannot book or it is blocked
	 * @throws OfferException this offer cannot be booked right now
	 */
	public void bookOffer(RegisteredUser user) throws UserException, OfferException{
		if(!user.getUserType().canBook()) {
			throw new InvalidUserTypeException("An user not Renter type is trying to book an offer");
		}
		if(user.isBlocked()) {
			throw new BlockedUserException("A blocked user is trying to book an offer");
		}
		if(this.getStatus() != Status.FREE) {
			throw new InvalidStatusOfferException("Trying to book an offer that is "+this.getStatus());
		}
		
		this.setStatus(Status.BOOKED);
		this.demander = user;
	}
	
	/**
	 * This function allows to rent an offer
	 * @param user The renter who is going to rent the offer
	 * @throws OfferException this offer cannot be rented right now
	 * @throws UserException this user is blocked or it cannot rent right now
	 * @throws OrderRejectedException the credit card number is wrong or the internet connection failed
	 */
	public void rentOffer(RegisteredUser user) throws OfferException, UserException, OrderRejectedException{
		if(!user.getUserType().canRent()) {
			throw new InvalidUserTypeException("An user not Renter type is trying to rent an offer");
		}
		if(user.isBlocked()) {
			throw new BlockedUserException("A blocked user is trying to rent an offer");
		}
		if(this.getStatus() != Status.FREE && this.getStatus() != Status.BOOKED) {
			throw new InvalidStatusOfferException("Trying to rent an offer that is "+this.getStatus());
		}
		if(this.getStatus()==Status.BOOKED && !this.demander.equals(user)) {
			throw new InvalidDemanderOfferException("Trying to rent a booked offer by a different demander");
		}
		
		for(int i=0, ntimes=5; i<ntimes; i++) {
			try {
				TeleChargeAndPaySystem.charge(user.getCreditCard(), "PhotoHouse renting", price);
				this.demander = user;
				this.setStatus(Status.RENTED);
			}catch(InvalidCardNumberException ccnex) {
				throw ccnex;
			}catch(FailedInternetConnectionException ficex) {
				throw ficex;
			}
		}
	}
	
	/**
	 * This function allows to add a new comment to the offer
	 * @param comment Comment to be added to the list of comments.
	 * @throws OfferException this offer cannot be commented right now
	 */
	public void commentOffer(Commentary comment) throws OfferException{
		if(this.getStatus()==Status.WAITING) {
			throw new InvalidStatusOfferException("Trying to comment an offer that is still pending to be approved");
		}
		comments.add(comment);
	}
}
