package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import View.*;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages ManagerOfferPanel.
 * It implements ActionListener
 */
public class ManagerOfferController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;

	/**
	 * This constructor creates a new ManagerOfferController.
	 * It just stores all the information needed to control ManagerOfferPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public ManagerOfferController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			((ManagerListOffersPanel)panels.get("MANAGER LIST OFFERS PANEL")).showOffers(app.getWaitingOffers(), ((ManagerListOffersController)controllers.get("MANAGER LIST OFFERS CONTROLLER")));
			card.show(window, "MANAGER LIST OFFERS PANEL");
		}
		else if(arg.getActionCommand().equals("Accept Offer")) {
			Offer off = ((ManagerListOffersController)controllers.get("MANAGER LIST OFFERS CONTROLLER")).getSelectedOffer();
			off.setStatus(Status.FREE);
			JOptionPane.showMessageDialog(null, "Offer accepted successfully");
		}
		else if(arg.getActionCommand().equals("Reject Offer")) {
			Offer off = ((ManagerListOffersController)controllers.get("MANAGER LIST OFFERS CONTROLLER")).getSelectedOffer();
			off.setStatus(Status.DENIED);
			JOptionPane.showMessageDialog(null, "Offer rejected successfully");
		}
	}

}
