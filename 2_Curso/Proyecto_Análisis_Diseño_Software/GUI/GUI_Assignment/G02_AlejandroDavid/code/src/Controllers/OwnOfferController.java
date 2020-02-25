package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import Exceptions.UserException;
import View.*;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages OwnOfferPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class OwnOfferController implements ActionListener, ListSelectionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;
	/* Auxiliary */
	private static Offer selectedOffer;

	/**
	 * This constructor creates a new OwnOfferController.
	 * It just stores all the information needed to control OwnOfferPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public OwnOfferController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}

	@Override
	public void valueChanged(ListSelectionEvent arg) {
		JList<Offer> offersList = (JList<Offer>) arg.getSource();
		selectedOffer = (Offer) offersList.getSelectedValue();
		if(selectedOffer == null) return;
		if(selectedOffer.getStatus() == Status.WAITING) {
			((EditPanel)panels.get("EDIT PANEL")).prepareButtons(selectedOffer.getOfferType());
			card.show(window, "EDIT PANEL");
		}
		else {
			((SeeOfferPanel)panels.get("SEE OFFER PANEL")).setPreviousPanel("OWN OFFER PANEL");
			((SeeOfferPanel)panels.get("SEE OFFER PANEL")).prepareOfferInfo(selectedOffer);
			card.show(window, "SEE OFFER PANEL");
		}
		
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			card.show(window, "START PANEL");
		}
		else if(arg.getActionCommand().equals("Create new short stay offer")) {
			try {
				((CreateShortPanel)panels.get("CREATE SHORT PANEL")).prepareApartments(((CreateShortController)controllers.get("CREATE SHORT CONTROLLER")));
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to create a new short offer",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			card.show(window, "CREATE SHORT PANEL");
		}
		else if(arg.getActionCommand().equals("Create new long stay offer")) {
			try {
				((CreateLongPanel)panels.get("CREATE LONG PANEL")).prepareApartments(((CreateLongController)controllers.get("CREATE LONG CONTROLLER")));
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to create a new long offer",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			card.show(window, "CREATE LONG PANEL");
		}
	}
	
	/**
	 * Gets the selected offer
	 * @return the selected offer
	 */
	public static Offer getSelectedOffer() {
		return selectedOffer;
	}
	
	/**
	 * Sets the selected offer
	 * @param off The selected offer
	 */
	public static void setSelectedOffer(Offer off) {
		selectedOffer = off;
	}

}