package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import View.*;
import es.uam.eps.padsof.telecard.*;
import padsof.*;
import Exceptions.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages OfferPanel.
 * It implements ActionListener
 */
public class OfferController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;
	/* Auxiliary */
	private static Offer theOffer;

	/**
	 * This constructor creates a new OfferController.
	 * It just stores all the information needed to control OfferPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public OfferController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.app = app;
		this.window = window;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			((StartPanel)panels.get("START PANEL")).clearSelection();
			card.show(window, "START PANEL");
		}
		else if(arg.getActionCommand().equals("See Commentaries")) {
			((SeeCommentPanel)panels.get("SEE COMMENT PANEL")).showCommentaries(theOffer.getComments(), ((SeeCommentController)controllers.get("SEE COMMENT CONTROLLER")));
			card.show(window, "SEE COMMENT PANEL");
		}
		else if(arg.getActionCommand().equals("Comment Offer")) {
			card.show(window, "COMMENT OFFER PANEL");
		}
		else if(arg.getActionCommand().equals("Rent Offer")) {
			try {
				app.rentOffer(theOffer, app.getLoggedUser());
				JOptionPane.showMessageDialog(null, "Offer rented successfully");
			}catch(OfferException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to rent the offer. Try it later again",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Sorry, you are blocked because your credit card is invalid. Fix it as soon as possible",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				((LoginPanel)panels.get("LOGIN PANEL")).clean();
				card.show(window, "LOGIN PANEL");
				return;
			}catch(InvalidCardNumberException ex) {
				JOptionPane.showMessageDialog(null, "Invalid credit card number. Try to change it as soon as possible",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}catch(FailedInternetConnectionException ex) {
				JOptionPane.showMessageDialog(null, "Sorry. Internet connection error. Try it later again",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}catch(OrderRejectedException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to rent the offer. Try it later again",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
		}
		else if(arg.getActionCommand().equals("Book Offer")) {
			try {
				app.bookOffer(theOffer, app.getLoggedUser());
			}catch(OfferException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to book the offer.",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Sorry, you are blocked because your credit card is invalid. Fix it as soon as possible",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			JOptionPane.showMessageDialog(null, "Offer booked successfully");
		}
	}
	
	/**
	 * Gets the selected offer
	 * @return the selected offer
	 */
	public static Offer getOffer() {
		return theOffer;
	}
	
	/**
	 * Sets the selected offer
	 * @param off The selected offer
	 */
	public static void setOffer(Offer off) {
		theOffer = off;
	}

}
