package View;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.*;
import javax.swing.event.ListSelectionListener;

import padsof.Offer;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the manager can see all the pending offers
 */
public class ManagerListOffersPanel extends JPanel{
	private JButton goBackButton;
	/* Auxiliary */
	private JPanel offersListPanel;
	private JList theList;
	
	/**
	 * This constructor creates a new ManagerListOffersPanel.
	 * It help helped by another privated methods that just creates different smaller panels
	 */
	public ManagerListOffersPanel() {
		JPanel top = buildTopPanel();
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
	 * It cleans the JList selected item
	 */
	public void clearSelection() {
		theList.clearSelection();
	}
	
	/**
	 * Sets up the offers that the administrator has to manage
	 * @param offers List of pending offers
	 * @param lsl ListSelectionListener
	 */
	public void showOffers(ArrayList<Offer> offers, ListSelectionListener lsl) {
		if(offersListPanel!=null) {
			this.remove(offersListPanel);
		}
		JPanel offersPanel = new JPanel();
		DefaultListModel<Offer> list = new DefaultListModel<Offer>();
		for(Offer off: offers) {
			list.addElement(off);
		}
		
		JList<Offer> offersList = new JList<Offer>(list);
		offersList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		offersList.setPreferredSize(new Dimension(500, 300));
		JScrollPane scroll = new JScrollPane(offersList);
		
		offersPanel.add(scroll);
		offersList.addListSelectionListener(lsl);
		
		offersListPanel = offersPanel;
		this.add(BorderLayout.CENTER, offersPanel);
		theList = offersList;
	}
	
	
	private JPanel buildTopPanel() {
		JPanel top = new JPanel();
		goBackButton = new JButton("Go Back");
		top.add(goBackButton);
		return top;
	}

}
