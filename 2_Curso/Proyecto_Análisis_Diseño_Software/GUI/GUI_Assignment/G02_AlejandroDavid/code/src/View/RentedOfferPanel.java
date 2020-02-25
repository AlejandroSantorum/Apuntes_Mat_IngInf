package View;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionListener;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can see his/her rented offers
 */
public class RentedOfferPanel extends JPanel{
	/* Buttons */
	private JButton goBackButton;
	/* Auxiliary */
	private JPanel rentedOffersListPanel;
	
	/**
	 * This constructor creates a new RegisterPropertyPanel.
	 * It help helped by another privated method that just creates different smaller panels
	 */
	public RentedOfferPanel() {
		JPanel top = this.buildTopPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, top);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		goBackButton.addActionListener(al);
	}
	
	/**
	 * Sets up the list of the logged user rented offers
	 * @param rentedOffers list of rented offers
	 * @param lsl ListSelectionListener
	 */
	public void showRentedOffers(ArrayList<Offer> rentedOffers, ListSelectionListener lsl) {
		if(rentedOffersListPanel!=null) {
			this.remove(rentedOffersListPanel);
		}
		JPanel rentedOffersPanel = new JPanel();
		DefaultListModel<Offer> list = new DefaultListModel<Offer>();
		for(Offer off: rentedOffers) {
			list.addElement(off);
		}
		
		JList<Offer> offersList = new JList<Offer>(list);
		offersList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		JScrollPane scroll = new JScrollPane(offersList);
		
		rentedOffersPanel.add(scroll);
		offersList.addListSelectionListener(lsl);
		
		rentedOffersListPanel = rentedOffersPanel;
		this.add(BorderLayout.CENTER, rentedOffersPanel);
	}
	
	
	private JPanel buildTopPanel() {
		JPanel topPanel = new JPanel();
		this.goBackButton = new JButton("Go Back");
		topPanel.add(goBackButton);
		return topPanel;
	}
}
