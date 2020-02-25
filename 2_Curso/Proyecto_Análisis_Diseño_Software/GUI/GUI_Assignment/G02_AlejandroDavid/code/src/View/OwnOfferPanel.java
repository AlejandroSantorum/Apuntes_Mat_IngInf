package View;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.*;
import javax.swing.event.ListSelectionListener;

import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can see his/her offers information
 */
public class OwnOfferPanel extends JPanel{
	/* Buttons */
	private JButton addShortOfferButton;
	private JButton addLongOfferButton;
	private JButton goBackButton;
	/* Auxiliary */
	private JPanel ownOffersListPanel;
	private static JList theList;
	
	/**
	 * This constructor creates a new OwnOfferPanel.
	 * It help helped by 2 privated methods that just creates different smaller panels
	 */
	public OwnOfferPanel() {
		JPanel top = this.buildTopPanel();
		JPanel down = this.buildDownPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, top);
		this.add(BorderLayout.SOUTH, down);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		goBackButton.addActionListener(al);
		addShortOfferButton.addActionListener(al);
		addLongOfferButton.addActionListener(al);
	}
	
	/**
	 * It cleans the JList selected item
	 */
	public static void clearSelection() {
		theList.clearSelection();
	}
	
	/**
	 * Sets up the list of offers
	 * @param ownOffers List of user offers
	 * @param lsl ListSelectionListener
	 */
	public void showOwnOffers(ArrayList<Offer> ownOffers, ListSelectionListener lsl) {
		if(ownOffersListPanel!=null) {
			this.remove(ownOffersListPanel);
		}
		JPanel ownOffersPanel = new JPanel();
		DefaultListModel<Offer> list = new DefaultListModel<Offer>();
		for(Offer off: ownOffers) {
			list.addElement(off);
		}
		
		JList<Offer> ownOffersList = new JList<Offer>(list);
		ownOffersList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		JScrollPane scroll = new JScrollPane(ownOffersList);
		
		ownOffersPanel.add(scroll);
		ownOffersList.addListSelectionListener(lsl);
		
		ownOffersListPanel = ownOffersPanel;
		this.add(BorderLayout.CENTER, ownOffersPanel);
		theList = ownOffersList;
	}
	
	
	private JPanel buildTopPanel() {
		JPanel topPanel = new JPanel();
		this.goBackButton = new JButton("Go Back");
		topPanel.add(goBackButton);
		return topPanel;
	}
	
	private JPanel buildDownPanel() {
		JPanel downPanel = new JPanel();
		this.addShortOfferButton = new JButton("Create new short stay offer");
		this.addLongOfferButton = new JButton("Create new long stay offer");
		downPanel.add(addShortOfferButton);
		downPanel.add(addLongOfferButton);
		return downPanel;
	}

}
