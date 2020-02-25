package padsof;

import Exceptions.*;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This enumeration indicates which kind of user is a certain
 * registered user (landlord, renter or both).
 */
public enum UserType {
	RENTER,
	LANDLORD,
	LANDLORD_RENTER;
	
	/**
	 * This function allows us to convert a certain 'code' to an element of the 
	 * enumeration.
	 * @param str 'O' to receive LANDLORD, 'D' to receive RENTER and 'OD'
	 * to receive LANDLORD_RENTER
	 * @return LANDLORD, RENTER or LANDLORD_RENTER, depending on the parameter.
	 * @throws UserException invalid user type
	 */
	public static UserType charToUserType(String str) throws UserException{
		if(str.equals("O")){
			return UserType.LANDLORD;
		}
		else if(str.equals("D")) {
			return UserType.RENTER;
		}
		else if(str.equals("OD")) {
			return UserType.LANDLORD_RENTER;
		}
		else {
			throw new InvalidUserTypeException("The read char is not a valid user identifier");
		}
	}
	
	/**
	 * This function allows to know if the type of user can rent apartments.
	 * @return true if UserType is RENTER or LANDLORD_RENTER, else false
	 */
	public Boolean canRent() {
		if(this == LANDLORD) return false;
		else return true;
	}
	
	/**
	 * This function indicates if a certain UserType can book an offer.
	 * @return true if UserType is RENTER or LANDLORD_RENTER, else false
	 */
	public Boolean canBook() {
		return this.canRent();
	}
	
	/**
	 * This function allows to know if a type of user can register apartments.
	 * @return true if UserType is LANDLORD or LANDLORD_RENTER, else false
	 */
	public Boolean canRegister() {
		if(this == RENTER) return false;
		else return true;
	}
	
	/**
	 * This function allows to know if a type of user can make an offer
	 * @return true if UserType is LANDLORD or LANDLORD_RENTER, else false
	 */
	public Boolean canOffer() {
		return this.canRegister();
	}
	
}
