package Controllers;

import java.awt.Container;
import java.awt.event.*;
import java.io.IOException;
import java.util.HashMap;
import java.awt.CardLayout;
import javax.swing.*;
import javax.swing.event.*;
import Exceptions.UserException;
import View.*;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages StartPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class StartController implements ActionListener, ListSelectionListener{
	private Application app;
	private Container window;
	private String filename;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;

	/**
	 * This constructor creates a new StartController.
	 * It just stores all the information needed to control StartPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param filename Name of the file where the application data is going to be stored
	 * @param app The application (Model) run.
	 */
	public StartController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, String filename, Application app) {
		this.app = app;
		this.window = window;
		this.filename = filename;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Logout")) {
			((LoginPanel)panels.get("LOGIN PANEL")).clean();
			
			try {
				app.saveData(filename);
			}catch(IOException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to save application data",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			app.setLoggedUser(null);
			card.show(window, "LOGIN PANEL");
		}
		else if(arg.getActionCommand().equals("Properties")) {
			try {
				((PropertyPanel)panels.get("PROPERTY PANEL")).showProperties(app.getLoggedUser().getUserApartments(), ((PropertyController)controllers.get("PROPERTY CONTROLLER")));
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to show your properties",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			card.show(window, "PROPERTY PANEL");
		}
		else if(arg.getActionCommand().equals("Offers")) {
			try {
				((OwnOfferPanel)panels.get("OWN OFFER PANEL")).showOwnOffers(app.getLoggedUser().getUserOffers(), ((OwnOfferController)controllers.get("OWN OFFER CONTROLLER")));
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to show your own offers",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			card.show(window, "OWN OFFER PANEL");
		}
		else if(arg.getActionCommand().equals("Rented offers")) {
			try {
				((RentedOfferPanel)panels.get("RENTED OFFER PANEL")).showRentedOffers(app.getLoggedUser().getUserRentedOffers(), ((RentedOfferController)controllers.get("RENTED OFFER CONTROLLER")));
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to show your rented offers",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			card.show(window, "RENTED OFFER PANEL");
		}
		else if(arg.getActionCommand().equals("Booked offers")) {
			try {
				((BookedOfferPanel)panels.get("BOOKED OFFER PANEL")).showBookedOffers(app.getLoggedUser().getUserBookedOffers(), ((BookedOfferController)controllers.get("BOOKED OFFER CONTROLLER")));
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to show your booked offers",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			card.show(window, "BOOKED OFFER PANEL");
		}
		else if(arg.getActionCommand().equals("Search")) {
			((SearchPanel)panels.get("SEARCH PANEL")).prepareIniButtons(app.getLoggedUser());
			card.show(window, "SEARCH PANEL");
		}
	}
	
	@Override
	public void valueChanged(ListSelectionEvent arg) {
		JList<Offer> offersList = (JList<Offer>) arg.getSource();
		Offer selectedOffer = (Offer) offersList.getSelectedValue();
		if(app.getLoggedUser() != null) {
			((OfferPanel)panels.get("OFFER PANEL")).prepareOfferButtons(app.getLoggedUser().getUserType(), 0);
		}else {
			((OfferPanel)panels.get("OFFER PANEL")).prepareOfferButtons(null, 0);
		}
		if(selectedOffer!=null) {
			((OfferPanel)panels.get("OFFER PANEL")).prepareOfferInfo(selectedOffer);
		}
		OfferController.setOffer(selectedOffer);
		card.show(window, "OFFER PANEL");
	}
	
	
}
