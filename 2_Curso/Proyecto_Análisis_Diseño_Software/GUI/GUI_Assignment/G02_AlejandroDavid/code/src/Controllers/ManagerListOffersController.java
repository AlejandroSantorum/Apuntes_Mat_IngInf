package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import padsof.*;
import View.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages ManagerListOffersPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class ManagerListOffersController implements ActionListener, ListSelectionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private Offer selectedOffer;
	
	/**
	 * This constructor creates a new ManagerListOffersController.
	 * It just stores all the information needed to control ManagerListOffersPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param app The application (Model) run.
	 */
	public ManagerListOffersController(Container window, HashMap<String, JPanel> panels, Application app) {
		this.app = app;
		this.window = window;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
	}

	@Override
	public void valueChanged(ListSelectionEvent arg) {
		JList<Offer> offersList = (JList<Offer>) arg.getSource();
		selectedOffer = (Offer) offersList.getSelectedValue();
		if(selectedOffer != null) {
			((ManagerOfferPanel)panels.get("MANAGER OFFER PANEL")).prepareOfferInfo(selectedOffer);
		}
		card.show(window, "MANAGER OFFER PANEL");
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			((ManagerListOffersPanel)panels.get("MANAGER LIST OFFERS PANEL")).clearSelection();
			card.show(window, "MANAGER START PANEL");
		}
	}
	
	/**
	 * Gets the selected offer
	 * @return The selected offer
	 */
	public Offer getSelectedOffer() {
		return selectedOffer;
	}

}
