/**
 * 
 */
package padsof;

import java.io.*;
import Exceptions.*;

/**
 * @author Alejandro Santorum y David Cabornero
 * This class allows to create a new apartment of a Landlord, get and set its attributes 
 * (the postal code, the address, the description and the Landlord) and return this class as a string.
 *
 */
public class Apartment implements Serializable{
	private int pc;
	private String address;
	private String description;
	private RegisteredUser owner;
	
	/**
	 * This constructor creates a new Apartment
	 * @param pc The postal code of the apartment
	 * @param address The address of the apartment
	 * @param description The description of the apartment
	 * @param owner The Landlord who owns the apartment
	 * @throws UserException this user cannot register a property
	 */
	public Apartment(int pc, String address, String description, RegisteredUser owner) throws UserException{
		if(pc <= 0){
		      throw new IllegalArgumentException("PC is lower or equal than cero: " + pc); 
		}
		if(!owner.getUserType().canRegister()) {
			throw new InvalidUserTypeException("An user not Landlord type is trying to register an apartment");
		}
		this.pc = pc;
		this.address = address;
		this.description = description;
		this.owner = owner;
	}

	/**
	 * This getter gives the postal code of the apartment
	 * @return The postal code
	 */
	public int getPc() {
		return pc;
	}

	/**
	 * This getter gives the address of the apartment
	 * @return the address
	 */
	public String getAddress() {
		return address;
	}

	/**
	 * This getter gives the description of the apartment
	 * @return the description
	 */
	public String getDescription() {
		return description;
	}
	
	/**
	 * This getter gives the Landlord who owns the apartment
	 * @return the owner of the apartment
	 */
	public RegisteredUser getOwner() {
		return owner;
	}
	
	/**
	 * This toString returns a String that includes information about the nick of the landlord of the
	 * apartment, the address, the postal code and the description.
	 */
	public String toString() {
		String str;
		str = "-Apartment:\n";
		str = str + "\tOwner: "+owner.getNick()+"\n";
		str = str + "\tAddress: " + address + "\n";
		str = str + "\tPostal Code: " + pc + "\n";
		str = str + "\tDescription: " + description + "\n";
		return str;
	}
	
	/**
	 * This function compare our apartment with another apartment
	 * @param apart Apartment to be compared
	 * @return true if they are the same apartment (same postal code, same address, same description, same landlord),
	 * else false
	 */
	public Boolean equals(Apartment apart) {
		if(this.pc == apart.pc && this.address.equals(apart.address) 
				&& this.description.equals(apart.description) 
					&& this.owner.equals(apart.owner)) return true;
		return false;
	}

}
