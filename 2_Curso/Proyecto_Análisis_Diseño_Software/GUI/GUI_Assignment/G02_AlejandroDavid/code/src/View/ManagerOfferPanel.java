package View;

import java.awt.*;
import java.awt.event.ActionListener;
import java.util.Calendar;
import java.util.GregorianCalendar;

import padsof.*;
import padsof.Long;
import padsof.Short;

import javax.swing.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the manager can accept or reject
 * an offer
 */
public class ManagerOfferPanel extends JPanel{
	/* Buttons */
	private JButton goBackButton;
	private JButton acceptButton;
	private JButton rejectButton;
	/* Labels */
	private JLabel type;
	private JLabel pc;
	private JLabel address;
	private JLabel dateInfo1;
	private JLabel dateInfo2;
	private JLabel price;
	private JLabel ownerName;
	private JLabel ownerId;
	/* Auxiliary */
	JPanel offerPanel;
	
	/**
	 * This constructor creates a new ManagerOfferPanel.
	 * It help helped by 2 privated methods that just creates different smaller panels
	 */
	public ManagerOfferPanel() {
		JPanel top = buildTopPanel();
		JPanel down = buildDownPanel();
		
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
		acceptButton.addActionListener(al);
		rejectButton.addActionListener(al);
	}
	
	/**
	 * Sets up all the offer information to be examinated by the admin
	 * @param offer Offer to be shown
	 */
	public void prepareOfferInfo(Offer offer) {
		if(offerPanel != null) {
			this.remove(offerPanel);
		}
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(8,0));
		
		type = new JLabel("Offer type: "+offer.getOfferType().toString());
		type.setHorizontalAlignment(JLabel.CENTER);
		address = new JLabel("Address: "+offer.getApartment().getAddress());
		address.setHorizontalAlignment(JLabel.CENTER);
		pc = new JLabel("Postal code: "+offer.getApartment().getPc());
		pc.setHorizontalAlignment(JLabel.CENTER);
		if(offer.getOfferType() == OfferType.SHORT) {
			GregorianCalendar ini = ((Short)offer).getInitialDate();
			GregorianCalendar fin = ((Short)offer).getFinalDate();
			dateInfo1 = new JLabel("Initial date: "+ini.get(Calendar.DATE)+"-"+ini.get(Calendar.MONTH)+"-"+ini.get(Calendar.YEAR));
			dateInfo1.setHorizontalAlignment(JLabel.CENTER);
			dateInfo2 = new JLabel("Final date: "+fin.get(Calendar.DATE)+"-"+fin.get(Calendar.MONTH)+"-"+fin.get(Calendar.YEAR));
			dateInfo2.setHorizontalAlignment(JLabel.CENTER);
		}else if(offer.getOfferType() == OfferType.LONG){
			GregorianCalendar ini = ((Long)offer).getInitialDate();
			dateInfo1 = new JLabel("Initial date: "+ini.get(Calendar.DATE)+"-"+ini.get(Calendar.MONTH)+"-"+ini.get(Calendar.YEAR));
			dateInfo1.setHorizontalAlignment(JLabel.CENTER);
			dateInfo2 = new JLabel("Minimum Period: "+((Long)offer).getMinimumPeriod());
			dateInfo2.setHorizontalAlignment(JLabel.CENTER);
		}
		price = new JLabel("Price: "+offer.getPrice());
		price.setHorizontalAlignment(JLabel.CENTER);
		ownerName = new JLabel("Owner nick: "+offer.getOwner().getNick());
		ownerName.setHorizontalAlignment(JLabel.CENTER);
		ownerId = new JLabel("Owner ID: "+offer.getOwner().getId());
		ownerId.setHorizontalAlignment(JLabel.CENTER);
		
		panel.add(type);
		panel.add(address);
		panel.add(pc);
		panel.add(dateInfo1);
		panel.add(dateInfo2);
		panel.add(price);
		panel.add(ownerName);
		panel.add(ownerId);
		
		offerPanel = panel;
		this.add(BorderLayout.CENTER, panel);
	}
	
	private JPanel buildTopPanel() {
		JPanel top = new JPanel();
		goBackButton = new JButton("Go Back");
		top.add(goBackButton);
		return top;
	}
	
	private JPanel buildDownPanel() {
		JPanel downPanel = new JPanel();
		this.acceptButton = new JButton("Accept Offer");
		this.rejectButton = new JButton("Reject Offer");
		downPanel.add(acceptButton);
		downPanel.add(rejectButton);
		return downPanel;
	}

}
