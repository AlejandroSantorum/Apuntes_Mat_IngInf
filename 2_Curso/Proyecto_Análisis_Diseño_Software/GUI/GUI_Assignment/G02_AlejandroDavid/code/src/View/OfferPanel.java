package View;

import java.awt.*;
import java.awt.event.ActionListener;
import java.util.Calendar;
import java.util.GregorianCalendar;

import javax.swing.*;
import padsof.UserType;
import padsof.*;
import padsof.Short;
import padsof.Long;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can see offer information
 */
public class OfferPanel extends JPanel{
	/* Renter buttons */
	private JButton rentOfferButton;
	private JButton bookOfferButton;
	private JButton commentOfferButton;
	/* General Buttons */
	private JButton goBackButton;
	private JButton seeCommentsButton;
	/* Labels of info */
	private JLabel offerType;
	private JLabel status;
	private JLabel postalCode;
	private JLabel rating;
	private JLabel dateInfo1;
	private JLabel dateInfo2;
	private JLabel price;
	/* Registered User */
	RegisteredUser user;
	/* Auxiliary */
	JPanel offerPanel;
	
	/**
	 * This constructor creates a new OfferPanel.
	 * It help helped by 2 privated methods that just creates different smaller panels
	 */
	public OfferPanel() {
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
		rentOfferButton.addActionListener(al);
		bookOfferButton.addActionListener(al);
		goBackButton.addActionListener(al);
		seeCommentsButton.addActionListener(al);
		commentOfferButton.addActionListener(al);
	}
	
	/**
	 * It sets up the buttons deppending on the user type
	 * @param ut logged user type
	 * @param flag Auxiliary flag that help us set visible some buttons depending on the situation
	 */
	public void prepareOfferButtons(UserType ut, int flag) {
		goBackButton.setVisible(true);
		seeCommentsButton.setVisible(true);
		if(ut==null || ut == UserType.LANDLORD || flag==1) {
			rentOfferButton.setVisible(false);
			bookOfferButton.setVisible(false);
		}
		else {
			commentOfferButton.setVisible(false);
			rentOfferButton.setVisible(true);
			bookOfferButton.setVisible(true);
			commentOfferButton.setVisible(true);
		}
	}
	
	/**
	 * Prepares all the offer information in the screen
	 * @param offer Offer to be shown
	 */
	public void prepareOfferInfo(Offer offer) {
		if(offerPanel != null) {
			this.remove(offerPanel);
		}
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(7,0));
		
		offerType = new JLabel("Type of stay: "+offer.getOfferType().toString());
		offerType.setHorizontalAlignment(JLabel.CENTER);
		status = new JLabel("Current status: "+offer.getStatus().toString());
		status.setHorizontalAlignment(JLabel.CENTER);
		postalCode = new JLabel("Postal code of the propety: "+offer.getApartment().getPc());
		postalCode.setHorizontalAlignment(JLabel.CENTER);
		rating = new JLabel("Rating: "+String.valueOf(offer.getRatingMedia()));
		rating.setHorizontalAlignment(JLabel.CENTER);
		price = new JLabel("Price: "+offer.getPrice());
		price.setHorizontalAlignment(JLabel.CENTER);
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
		
		panel.add(offerType);
		panel.add(status);
		panel.add(postalCode);
		panel.add(rating);
		panel.add(dateInfo1);
		panel.add(dateInfo2);
		panel.add(price);
		
		offerPanel = panel;
		this.add(BorderLayout.CENTER, panel);
	}
	
	private JPanel buildTopPanel() {
		JPanel topPanel = new JPanel();
		this.goBackButton = new JButton("Go Back");
		this.seeCommentsButton = new JButton("See Commentaries");
		topPanel.add(goBackButton);
		topPanel.add(seeCommentsButton);
		return topPanel;
	}
	
	private JPanel buildDownPanel() {
		JPanel downPanel = new JPanel();
		this.rentOfferButton = new JButton("Rent Offer");
		this.bookOfferButton = new JButton("Book Offer");
		this.commentOfferButton = new JButton("Comment Offer");
		downPanel.add(rentOfferButton);
		downPanel.add(bookOfferButton);
		downPanel.add(commentOfferButton);
		return downPanel;
	}
	

}
