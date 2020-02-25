package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import Exceptions.UserException;
import View.*;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages SeeOfferPanel.
 * It implements ActionListener
 */
public class SeeOfferController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;
	
	/**
	 * This constructor creates a new SeeOfferController.
	 * It just stores all the information needed to control SeeOfferPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public SeeOfferController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			if(((SeeOfferPanel)panels.get("SEE OFFER PANEL")).getPreviousPanel().equals("OWN OFFER PANEL")) {
				try {
					((OwnOfferPanel)panels.get("OWN OFFER PANEL")).showOwnOffers(app.getLoggedUser().getUserOffers(), ((OwnOfferController)controllers.get("OWN OFFER CONTROLLER")));
				}catch(UserException ex) {
					JOptionPane.showMessageDialog(null, "Error while trying to show your own offers",
							"ERROR", JOptionPane.ERROR_MESSAGE);
					return;
				}
				card.show(window, "OWN OFFER PANEL");
			}
			else if(((SeeOfferPanel)panels.get("SEE OFFER PANEL")).getPreviousPanel().equals("RENTED OFFER PANEL")){
				try {
					((RentedOfferPanel)panels.get("RENTED OFFER PANEL")).showRentedOffers(app.getLoggedUser().getUserRentedOffers(), ((RentedOfferController)controllers.get("RENTED OFFER CONTROLLER")));
				}catch(UserException ex) {
					JOptionPane.showMessageDialog(null, "Error while trying to show your rented offers",
							"ERROR", JOptionPane.ERROR_MESSAGE);
					return;
				}
				card.show(window, "RENTED OFFER PANEL");
			}
			else if(((SeeOfferPanel)panels.get("SEE OFFER PANEL")).getPreviousPanel().equals("BOOKED OFFER PANEL")) {
				try {
					((BookedOfferPanel)panels.get("BOOKED OFFER PANEL")).showBookedOffers(app.getLoggedUser().getUserBookedOffers(), ((BookedOfferController)controllers.get("BOOKED OFFER CONTROLLER")));
				}catch(UserException ex) {
					JOptionPane.showMessageDialog(null, "Error while trying to show your booked offers",
							"ERROR", JOptionPane.ERROR_MESSAGE);
					return;
				}
				card.show(window, "BOOKED OFFER PANEL");
			}
		}
	}

}
