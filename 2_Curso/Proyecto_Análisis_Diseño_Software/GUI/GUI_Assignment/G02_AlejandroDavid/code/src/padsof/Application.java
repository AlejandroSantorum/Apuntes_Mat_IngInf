package padsof;

import java.io.*;
import java.util.*;
import Exceptions.*;
import es.uam.eps.padsof.telecard.FailedInternetConnectionException;
import es.uam.eps.padsof.telecard.InvalidCardNumberException;
import es.uam.eps.padsof.telecard.OrderRejectedException;
import Filters.*;
/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This class manages the application of the system, where we are going to save all our registered users,
 * their apartments and offers and the appropriate comments.
 *
 */
public class Application {
	final ArrayList<RegisteredUser> usersArray;
	private ArrayList<Apartment> apartmentsArray;
	private ArrayList<Offer> offersArray;
	private ArrayList<Commentary> commentsArray;
	private Map<String, String> creditCardRequest;
	private RegisteredUser loggedUser;
	
	/**
	 * This constructor creates a new Application.
	 */
	public Application() {
		usersArray = new ArrayList<RegisteredUser>();
		apartmentsArray = new ArrayList<Apartment>();
		offersArray = new ArrayList<Offer>();
		commentsArray = new ArrayList<Commentary>();
		creditCardRequest = new HashMap<String, String>();
	}
	
	/**
	 * This method load the registered users of the file in our array or registered users.
	 * @param filename Path of the file with the data of the registered users
	 * @throws IOException error opening a file
	 * @throws UserException invalid user
	 */
	public void loadUsers(String filename) throws IOException, UserException{
		try(BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(filename)))){
			String line;
			String[] items = new String[]{};
			line = reader.readLine();
			while((line = reader.readLine()) != null) {
				items = line.split(";");
				
				if (items.length != 5) {
					throw new IOException("The read line has not got 5 fields when loading users.\n");
				}
				
				usersArray.add(new RegisteredUser(items[2], items[1], items[3], items[4], items[0]));
			}
		}catch(IOException ex) {
			throw ex;
		};
	}
	
	/**
	 * Logins an user given its name and password
	 * @param id Identifier of the user
	 * @param password password of the user
	 * @return the RegisteredUser if it exists or null otherwise
	 */
	public RegisteredUser login(String id, String password) {
		for(RegisteredUser user: usersArray) {
			if(user.getId().equals(id) && user.getPassword().equals(password)) {
				return user;
			}
		}
		return null;
	}

	/**
	 * This getter gives the array of registered users
	 * @return the usersArray
	 */
	public ArrayList<RegisteredUser> getUsersArray() {
		return usersArray;
	}

	/**
	 * This getter gives the array of apartments
	 * @return the apartmentsArray
	 */
	public ArrayList<Apartment> getApartmentsArray() {
		return apartmentsArray;
	}

	/**
	 * This getter gives the array of offers
	 * @return the offersArray
	 */
	public ArrayList<Offer> getOffersArray() {
		return offersArray;
	}
	
	public ArrayList<Offer> getFreeOffers(RegisteredUser user) throws UserException{
		int flag;
		ArrayList<Offer> allOffers = new ArrayList<Offer>();
		
		if(user != null) {
			if(user.getUserType() == UserType.LANDLORD) {
				allOffers.addAll(user.getUserOffers());
			}else if(user.getUserType() == UserType.RENTER) {
				allOffers.addAll(user.getUserBookedOffers());
				allOffers.addAll(user.getUserRentedOffers());
			}else if(user.getUserType() == UserType.LANDLORD_RENTER) {
				allOffers.addAll(user.getUserOffers());
				allOffers.addAll(user.getUserBookedOffers());
				allOffers.addAll(user.getUserRentedOffers());
			}
		}
		
		ArrayList<Offer> aux = new ArrayList<Offer>();
		for(Offer off: offersArray) {
			flag = 0;
			for(Offer off2: allOffers) {
				if(off2.equals(off)) {
					flag = 1;
					break;
				}
			}
			if(flag==0 && off.getStatus()!=Status.WAITING) {
				aux.add(off);
			}
		}
		return aux;
	}
	
	/**
	 * This getter gives the array of comments
	 * @return the commentsArray
	 */
	public ArrayList<Commentary> getCommentsArray(){
		return commentsArray;
	}
	
	/**
	 * This getter gives the user who has certain ID
	 * @param id The id of the user who we are searching
	 * @return The user that we want to find
	 */
	public RegisteredUser getUserById(String id) {
		for(RegisteredUser ru: usersArray) {
			if(ru.getId().equals(id)) return ru;
		}
		return null;
	}
	
	/**
	 * This getter gives the current logged user stored
	 * @return The current logged user, null if is nobody logged
	 */
	public RegisteredUser getLoggedUser() {
		return loggedUser;
	}
	
	/**
	 * Sets the logged user
	 * @param user Sets the logged user
	 */
	public void setLoggedUser(RegisteredUser user) {
		this.loggedUser = user;
	}
	
	/**
	 * Filter the application offers and returns the offers that are peding to be approved
	 * @return ArraList of offers that meet the condition
	 */
	public ArrayList<Offer> getWaitingOffers(){
		ArrayList<Offer> waitOffers = new ArrayList<>();
		
		for(Offer off: offersArray) {
			if(off.getStatus() == Status.WAITING) {
				waitOffers.add(off);
			}
		}
		return waitOffers;
	}
	
	/**
	 * Returns the map of the user and its new credit card number proposal
	 * @return The stored map
	 */
	public Map<String, String> getCreditCardRequest() {
		return creditCardRequest;
	}
	
	/**
	 * This adds an user and its new credit card to the map
	 * @param user The user changing its credit card
	 * @param ccn The new credit card number
	 */
	public void addCreditCardRequest(RegisteredUser user, String ccn) {
		creditCardRequest.put(user.getId(), ccn);
	}
	
	/**
	 * This removes an user and its new credit card from the map
	 * @param user The user changing its credit card
	 */
	public void removeCreditCardRequest(RegisteredUser user) {
		creditCardRequest.remove(user.getId());
	}
	
	/**
	 * This checks if an user has already claimed to change its credit card number
	 * @param user The user to check
	 * @return true if the user has already claimed to change its ccn, or false otherwise.
	 */
	public Boolean requestedCCNChange(RegisteredUser user) {
		return creditCardRequest.containsKey(user.getId());
	}
	
	/**
	 * Function that prints all registered users' data
	 */
	public void printAllUsers() {
		System.out.println("==== APPLICATION USERS ====");
		for(RegisteredUser ru: usersArray) {
			System.out.println(ru);
		}
		System.out.println("=====================================");
	}
	
	/**
	 * Function that prints all apartments' data
	 */
	public void printAllApartments() {
		System.out.println("==== USERS' APARTMENTS =====");
		for(Apartment apart: apartmentsArray) {
			System.out.println(apart);
		}
		System.out.println("=====================================");
	}
	
	/**
	 * Function that prints all offers' data
	 */
	public void printAllOffers() {
		System.out.println("==== USERS' OFFERS ====");
		for(Offer o: offersArray) {
			System.out.println(o);
		}
		System.out.println("=====================================");
	}
	
	/**
	 * Function that prints all comments' data
	 */
	public void printAllComments() {
		System.out.println("==== COMMENTARIES ====");
		for(Commentary c: commentsArray) {
			System.out.println(c);
		}
		System.out.println("=====================================");
	}
	
	/**
	 * This method creates and initializes a new Apartment and adds it to the array.
	 * @param pc Postal code of the apartment
	 * @param address Address of the apartment
	 * @param description Description of the apartment
	 * @param owner Landlord who owns the apartment
	 * @throws OfferException invalid offer
	 * @throws UserException this user cannot register a property or its blocked
	 */
	public void createApartment(int pc, String address, String description, 
			RegisteredUser owner) throws OfferException, UserException{
		
		Apartment apart;
		/* Trying to create the apartment */
		try {
			apart = new Apartment(pc, address, description, owner);
		}catch(InvalidUserTypeException ex) {
			/*System.err.println("InvalidUserTypeException: "+ex.getMessage());*/
			throw ex;
		}
		
		/* Trying to add this apartment (created) into the user's apartment list */
		try {
			owner.addApartment(apart);
		}catch(InvalidUserTypeException ex) {
			/*System.err.println("InvalidUserTypeException: "+ex.getMessage());*/
			throw ex;
		}catch(BlockedUserException ex) {
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
			throw ex;
		}
		/* Adding the apartment to the application's apartments list */
		apartmentsArray.add(apart);
	}
	
	/**
	 * This method creates and initializes a long stay offer and adds it to the array of offers
	 * @param price Price of the offer
	 * @param apartment Apartment of the offer
	 * @param owner Landlord who creates the offer
	 * @param initialDate First day that a renter can rent the apartment
	 * @param nDays The minimum number of days of the contract (you also have to introduce months and years)
	 * @param nMonths The minimum number of months of the contract (you also have to introduce days and years)
	 * @param nYears The minimum number of years of the contract (you also have to introduce months and days)
	 * @throws UserException this user cannot create an offer or its blocked
	 * @throws OfferException invalid offer operation
	 */
	public void createOffer(float price, Apartment apartment, 
			RegisteredUser owner, GregorianCalendar initialDate, int nDays, int nMonths, int nYears) throws UserException, OfferException{
		
		Long off;
		/* Trying to create the Long type Offer */
		try {
			off = new Long(price, apartment, owner, initialDate, nDays, nMonths, nYears);
		}catch(InvalidUserTypeException ex) {
			/*System.err.println("InvalidUserTypeException: "+ex.getMessage());*/
			throw ex;
		}
		
		/* Trying to add this offer (created) into the users' offer list */
		try {
			owner.addOffer(off);
		}catch(InvalidUserTypeException ex) {
			/*System.err.println("InvalidUserTypeException: "+ex.getMessage());*/
			throw ex;
		}catch(BlockedUserException ex) {
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
			throw ex;
		}
		/* Adding the offer to the application's offers list */
		offersArray.add(off);
	}
	
	/**
	 * This method creates and initializes a short stay offer and adds it to the array of offers
	 * @param price The price of the offer
	 * @param apartment The apartment that is going to be rented
	 * @param owner The Landlord who is going to rent the apartment
	 * @param initialDate Beginning of the range of dates of the stay
	 * @param finalDate End of the range of dates of the stay
	 * @throws OfferException invalid offer operation
	 * @throws UserException this user cannot create an offer or its blocked
	 */
	public void createOffer(float price, Apartment apartment, 
			RegisteredUser owner, GregorianCalendar initialDate, GregorianCalendar finalDate) throws OfferException, UserException{
		
		Short off;
		/* Trying to create the Short type Offer */
		try {
			off = new Short(price, apartment, owner, initialDate, finalDate);
		}catch(InvalidUserTypeException ex) {
			/*System.err.println("InvalidUserTypeException: "+ex.getMessage());*/
			throw ex;
		}
		
		/* Trying to add this offer (created) into the users' offer list */
		try {
			owner.addOffer(off);
		}catch(InvalidUserTypeException ex) {
			/*System.err.println("InvalidUserTypeException: "+ex.getMessage());*/
			throw ex;
		}catch(BlockedUserException ex) {
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
			throw ex;
		}
		/* Adding the offer to the application's offers list */
		offersArray.add(off);
	}
	
	/**
	 * This edits a short offer
	 * @param off Offer to be edited
	 * @param price Offer price
	 * @param initialDate the new initial date
	 * @param finalDate the new final date
	 * @throws OfferException only pending offers can be edited
	 */
	public void editOffer(Offer off, Float price, GregorianCalendar initialDate, GregorianCalendar finalDate) throws OfferException{
		if(off.getStatus() != Status.WAITING) {
			throw new InvalidStatusOfferException("Only Waiting status offers can be edited");
		}
		
		if(price != null) {
			off.setPrice(price);
		}
		if(initialDate != null) {
			((Short) off).setInitialDate(initialDate);
		}
		if(finalDate != null) {
			((Short) off).setFinalDate(finalDate);
		}
	}
	
	/**
	 * This edits a long offer
	 * @param off Offer to be edited
	 * @param price Offer price
	 * @param initialDate the new initial date
	 * @param nDays The minimum number of days of the contract (you also have to introduce months and years)
	 * @param nMonths The minimum number of months of the contract (you also have to introduce days and years)
	 * @param nYears The minimum number of years of the contract (you also have to introduce months and days) 
	 * @throws OfferException only pending offers can be edited
	 */
	public void editOffer(Offer off, Float price, GregorianCalendar initialDate, Integer nDays, Integer nMonths, Integer nYears) throws OfferException{
		if(off.getStatus() != Status.WAITING) {
			throw new InvalidStatusOfferException("Only Waiting status offers can be edited");
		}
		
		if(price != null) {
			off.setPrice(price);
		}
		if(initialDate != null) {
			((Long) off).setInitialDate(initialDate);
		}
		if(nDays==null && nMonths==null && nYears==null) return;
		
		int nDaysAux;
		if(nDays != null) {
			nDaysAux = nDays;
		}else {
			nDaysAux = 0;
		}
		
		int nMonthsAux;
		if(nMonths != null) {
			nMonthsAux = nMonths;
		}else {
			nMonthsAux = 0;
		}
		
		int nYearsAux;
		if(nYears != null) {
			nYearsAux = nYears;
		}else {
			nYearsAux = 0;
		}
		
		((Long) off).setMinimumPeriod(nDaysAux, nMonthsAux, nYearsAux);		
	}
	
	
	
	/**
	 * This method is used when a renter wants to book an offer
	 * @param offer Offer to be booked
	 * @param booker Renter who books the offer
	 * @throws OfferException invalid offer operation
	 * @throws UserException this user cannot book an offer or its blocked
	 */
	public void bookOffer(Offer offer, RegisteredUser booker) throws OfferException, UserException{
		/* Trying to book the offer */
		try {
			offer.bookOffer(booker);
		}catch(InvalidUserTypeException ex) {
			System.err.println("InvalidUserTypeException: "+ex.getMessage());
			return;
		}catch(BlockedUserException ex) {
			throw ex;
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
		}catch(OfferException ex) {
			throw ex;
			/*System.err.println("OfferException: "+ex.getMessage());*/
		}
		
		/* If the offer creation succeeds we try to add it to 
		 the user booked offers list */
		try {
			booker.addBookedOffer(offer);
		}catch(InvalidUserTypeException ex) {
			/*System.err.println("InvalidUserTypeException: "+ex.getMessage());*/
			/* We have to reverse the changes made above */
			offer.setStatus(Status.FREE);
			offer.unsetDemander();
			throw ex;
		}catch(BlockedUserException ex) {
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
			/* We have to reverse the changes made above */
			offer.setStatus(Status.FREE);
			offer.unsetDemander();
			throw ex;
		}
	}
	
	/**
	 * This method is used when a renter wants to rent an offer
	 * @param offer Offer to be rented
	 * @param renter Renter who rents the offer
	 * @throws OfferException invalid offer operation
	 * @throws UserException this user cannot rent or its blocked
	 * @throws OrderRejectedException internet connection lost or invalid credit card number
	 */
	public void rentOffer(Offer offer, RegisteredUser renter) throws OfferException, UserException, OrderRejectedException{
		/* Trying to rent the offer */
		try {
			offer.rentOffer(renter);
		}catch(InvalidUserTypeException ex) {
			/*System.err.println("InvalidUserTypeException: "+ex.getMessage());*/
			throw ex;
		}catch(BlockedUserException ex) {
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
			throw ex;
		}catch(InvalidStatusOfferException ex) {
			/*System.err.println("InvalidStatusOfferException: "+ex.getMessage());*/
			throw ex;
		}catch(InvalidDemanderOfferException ex) {
			/*System.err.println("InvalidDemanderOfferException: "+ex.getMessage());*/
			throw ex;
		}catch(InvalidCardNumberException ex) {
			/*System.err.println("InvalidCardNumberException: "+ex.getMessage()+"\nThe user has been BLOCKED");*/
			renter.setBlocked();
			throw ex;
		}catch(FailedInternetConnectionException ex) {
			/*System.err.println("FailedInternetConnectionException: "+ex.getMessage());*/
			throw ex;
		}
		
		/* If the offer creation succeeds we try to add it to 
		 the user rented offers list */
		try {
			renter.addRentedOffer(offer);
		}catch(InvalidUserTypeException ex) {
			/*System.err.println("InvalidUserTypeException: "+ex.getMessage());*/
			/* We have to reverse the changes made above */
			offer.setStatus(Status.FREE);
			offer.unsetDemander();
			throw ex;
		}catch(BlockedUserException ex) {
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
			/* We have to reverse the changes made above */
			offer.setStatus(Status.FREE);
			offer.unsetDemander();
			throw ex;
		}
		
	}
	
	/**
	 * This function adds a text comment in an offer.
	 * @param offer Offer to be commented
	 * @param user User who is going to comment
	 * @param date Date when the comment was released
	 * @param text Text of the comment
	 * @throws UserException the user is blocked
	 * @throws OfferException invalid offer operation
	 */
	public void addCommentary(Offer offer, RegisteredUser user, GregorianCalendar date, String text) throws UserException, OfferException {
		try {
			Commentary comment = new Textual(user, date, text);
			offer.commentOffer(comment);
			user.addComment(comment);
			commentsArray.add(comment);
		}catch(BlockedUserException ex) {
			throw ex;
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
		}
	}
	
	/**
	 * This function adds a numerical rating in an offer.
	 * @param offer Offer to be rated
	 * @param user User who is going to rate
	 * @param date Date when the comment was released
	 * @param points Numerical punctuation (integer) of the rating
	 * @throws UserException the user is blocked
	 * @throws OfferException invalid offer operation
	 */
	public void addCommentary(Offer offer, RegisteredUser user, GregorianCalendar date, int points) throws UserException, OfferException {
		try {
			Commentary comment = new Rating(user, date, points);
			offer.commentOffer(comment);
			user.addComment(comment);
			commentsArray.add(comment);
		}catch(BlockedUserException ex) {
			throw ex;
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
		}catch(InvalidStatusOfferException ex) {
			throw ex;
			/*System.err.println("InvalidStatusOfferException: "+ex.getMessage());*/
		}
	}
	
	/**
	 * This function adds a text comment in an comment.
	 * @param comment Comment to be commented
	 * @param user User who is going to comment
	 * @param date Date when the comment was released
	 * @param text Text of the comment
	 * @throws UserException the user is blocked
	 * @throws OfferException invalid offer operation
	 */
	public void addCommentary(Commentary comment, RegisteredUser user, GregorianCalendar date, String text) throws UserException, OfferException {
		try {
			Commentary commentAux = new Textual(user, date, text);
			comment.commentCommentary(commentAux);
			user.addComment(comment);
			commentsArray.add(comment);
		}catch(BlockedUserException ex) {
			throw ex;
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
		}
	}
	
	/**
	 * This function adds a numerical rating in an offer.
	 * @param comment Comment to be commented
	 * @param user User who is going to rate
	 * @param date Date when the comment was released
	 * @param points Numerical punctuation (integer) of the rating
	 * @throws UserException the user is blocked
	 * @throws OfferException invalid offer operation
	 */
	public void addCommentary(Commentary comment, RegisteredUser user, GregorianCalendar date, int points) throws UserException, OfferException {
		try {
			Commentary commentAux = new Rating(user, date, points);
			comment.commentCommentary(commentAux);
			user.addComment(comment);
			commentsArray.add(comment);
		}catch(BlockedUserException ex) {
			throw ex;
			/*System.err.println("BlockedUserException: "+ex.getMessage());*/
		}
	}
	
	
	/**
	 * Function that saves all the data of the application in a file
	 * @param filename Path of the file
	 * @throws IOException error opening a file
	 */
	public void saveData(String filename) throws IOException{
		PrintWriter pw = new PrintWriter(filename);
		pw.close();
		try {
			ObjectOutputStream fileData = 
					new ObjectOutputStream(
							new FileOutputStream(filename));
			
			fileData.writeObject(usersArray);
			fileData.writeObject(apartmentsArray);
			fileData.writeObject(offersArray);
			fileData.writeObject(commentsArray);
			fileData.writeObject(creditCardRequest);
			
			fileData.close();
		}catch(IOException ex) {
			throw ex;
		};
		
	}
	
	/**
	 * Function that loads all the information saved in the given file
	 * @param filename Path of the file
	 * @throws IOException error opening a file
	 * @throws ClassNotFoundException class not found
	 */ 
	public void readData(String filename) throws IOException, ClassNotFoundException{
		try {
			ObjectInputStream fileData = 
					new ObjectInputStream(
							new FileInputStream(filename));
			
			usersArray.clear();
			apartmentsArray.clear();
			offersArray.clear();
			commentsArray.clear();
			creditCardRequest.clear();
			
			usersArray.addAll((Collection<RegisteredUser>) fileData.readObject());
			apartmentsArray.addAll((Collection<Apartment>) fileData.readObject());
			offersArray.addAll((Collection<Offer>) fileData.readObject());
			commentsArray.addAll((Collection<Commentary>) fileData.readObject());
			creditCardRequest = (Map<String, String>)fileData.readObject();
			
			fileData.close();
		}catch(IOException ex) {
			throw ex;
		};
		
	}
	
	/**
	 * Function that filters the given offers using the given filters
	 * @param offers Array of all the offers to be filtered
	 * @param filters Array of all the filters to be used
	 * @return the array of offers that satisfy all the filters
	 */
	public ArrayList<Offer> search(ArrayList<Offer> offers, ArrayList<Filter> filters){
		ArrayList<Offer> temp = new ArrayList<Offer>();
		temp.addAll(offers);
		
		for(Filter fil: filters) {
			ArrayList<Offer> forAux = new ArrayList<Offer>();
			for(Offer off: temp) {
				if(fil.check(off)) {
					forAux.add(off);
				}
			}
			temp.clear();
			temp.addAll(forAux);
		}
		return temp;
	}
}
