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

import View.SeeOfferPanel;
import padsof.Application;
import padsof.Offer;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages RentedOfferPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class RentedOfferController implements ActionListener, ListSelectionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private Offer selectedOffer;
	
	/**
	 * This constructor creates a new RentedOfferController.
	 * It just stores all the information needed to control RentedOfferPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param app The application (Model) run.
	 */
	public RentedOfferController(Container window, HashMap<String, JPanel> panels, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
	}
	
	@Override
	public void valueChanged(ListSelectionEvent arg) {
		JList<Offer> offersList = (JList<Offer>) arg.getSource();
		selectedOffer = (Offer) offersList.getSelectedValue();
		if(selectedOffer == null) return;
		((SeeOfferPanel)panels.get("SEE OFFER PANEL")).setPreviousPanel("RENTED OFFER PANEL");
		((SeeOfferPanel)panels.get("SEE OFFER PANEL")).prepareOfferInfo(selectedOffer);
		card.show(window, "SEE OFFER PANEL");
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			card.show(window, "START PANEL");
		}
	}

}
