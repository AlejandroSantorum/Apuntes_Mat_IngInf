package View;

import java.awt.*;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.*;
import javax.swing.event.ListSelectionListener;
import padsof.UserType;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the initial panel of the application once the user (guest or not)
 * has logged in.
 */
public class StartPanel extends JPanel{
	/* Landlord buttons */
	private JButton propertiesButton;
	private JButton offersButton;
	/* Renter buttons */
	private JButton rentedButton;
	private JButton bookedButton;
	/* General buttons */
	private JButton logoutButton;
	private JButton searchButton;
	/* User */
	private RegisteredUser user;
	
	/* Auxiliary */
	private JPanel offersListPanel;
	private JList theList;
	
	/**
	 * This constructor creates a new StartPanel.
	 * It help helped by 2 privated methods that just creates different smaller panels
	 */
	public StartPanel() {
		JPanel generalButtons = this.buildGeneralButtonsPanel();
		JPanel userButtons = this.buildUserButtonsPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, userButtons);
		this.add(BorderLayout.SOUTH, generalButtons);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		logoutButton.addActionListener(al);
		searchButton.addActionListener(al);
		propertiesButton.addActionListener(al);
		offersButton.addActionListener(al);
		rentedButton.addActionListener(al);
		bookedButton.addActionListener(al);
	}
	
	/**
	 * It sets up the buttons deppending on the user type
	 * @param ut logged user type
	 */
	public void prepareStartButtons(UserType ut) {
		logoutButton.setVisible(true);
		searchButton.setVisible(true);
		if(ut==null) {
			propertiesButton.setVisible(false);
			offersButton.setVisible(false);
			rentedButton.setVisible(false);
			bookedButton.setVisible(false);
		}
		else if(ut == UserType.RENTER) {
			propertiesButton.setVisible(false);
			offersButton.setVisible(false);
			rentedButton.setVisible(true);
			bookedButton.setVisible(true);
		}
		else if(ut == UserType.LANDLORD) {
			propertiesButton.setVisible(true);
			offersButton.setVisible(true);
			rentedButton.setVisible(false);
			bookedButton.setVisible(false);
		}
		else {
			/* By default all buttons are visible, but maybe they have been unseen
			 * and now we have to restore its visibility due to a Landlord-Renter user type
			 */
			propertiesButton.setVisible(true);
			offersButton.setVisible(true);
			rentedButton.setVisible(true);
			bookedButton.setVisible(true);
		}
	}
	
	/**
	 * It cleans the JList selected item
	 */
	public void clearSelection() {
		theList.clearSelection();
	}
	
	/**
	 * Sets up the list of offers
	 * @param offers List of offers to be shown
	 * @param lsl ListSelectionListener
	 */
	public void showOffers(ArrayList<Offer> offers, ListSelectionListener lsl) {
		if(offersListPanel!=null) {
			this.remove(offersListPanel);
		}
		JPanel offersPanel = new JPanel();
		DefaultListModel<Offer> list = new DefaultListModel<Offer>();
		for(Offer off: offers) {
			list.addElement(off);
		}
		
		JList<Offer> offersList = new JList<Offer>(list);
		offersList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		offersList.setPreferredSize(new Dimension(500, 300));
		JScrollPane scroll = new JScrollPane(offersList);
		
		offersPanel.add(scroll);
		offersList.addListSelectionListener(lsl);
		
		offersListPanel = offersPanel;
		this.add(BorderLayout.CENTER, offersPanel);
		theList = offersList;
	}
	
	
	private JPanel buildUserButtonsPanel() {
		JPanel userButtonsPanel = new JPanel();
		
		this.propertiesButton = new JButton("Properties");
		this.offersButton = new JButton("Offers");
		
		this.rentedButton = new JButton("Rented offers");
		this.bookedButton = new JButton("Booked offers");
		
		userButtonsPanel.add(propertiesButton);
		userButtonsPanel.add(offersButton);
		userButtonsPanel.add(rentedButton);
		userButtonsPanel.add(bookedButton);
		
		return userButtonsPanel;
	}
	
	
	private JPanel buildGeneralButtonsPanel() {
		JPanel generalButtonsPanel = new JPanel();
		
		this.searchButton = new JButton("Search");
		this.logoutButton = new JButton("Logout");
		
		generalButtonsPanel.add(searchButton);
		generalButtonsPanel.add(logoutButton);
		
		return generalButtonsPanel;	
	}

}
