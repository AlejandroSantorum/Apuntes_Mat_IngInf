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
 * This class implements the panel where the user can book an offer
 */
public class BookedOfferPanel extends JPanel{
	/* Buttons */
	private JButton goBackButton;
	/* Auxiliary */
	private JPanel bookedOffersListPanel;
	
	/**
	 * This constructor creates a new BookedOfferPanel.
	 * It help helped by another privated method that just creates a different smaller panel
	 */
	public BookedOfferPanel() {
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
	 * It sets up the shown offers deppending on the user
	 * @param bookedOffers List of the user booked offers
	 * @param lsl ListSelectionListener
	 */
	public void showBookedOffers(ArrayList<Offer> bookedOffers, ListSelectionListener lsl) {
		if(bookedOffersListPanel!=null) {
			this.remove(bookedOffersListPanel);
		}
		JPanel bookedOffersPanel = new JPanel();
		DefaultListModel<Offer> list = new DefaultListModel<Offer>();
		for(Offer off: bookedOffers) {
			list.addElement(off);
		}
		
		JList<Offer> offersList = new JList<Offer>(list);
		offersList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		JScrollPane scroll = new JScrollPane(offersList);
		
		bookedOffersPanel.add(scroll);
		offersList.addListSelectionListener(lsl);
		
		bookedOffersListPanel = bookedOffersPanel;
		this.add(BorderLayout.CENTER, bookedOffersPanel);
	}
	
	
	private JPanel buildTopPanel() {
		JPanel topPanel = new JPanel();
		this.goBackButton = new JButton("Go Back");
		topPanel.add(goBackButton);
		return topPanel;
	}
}