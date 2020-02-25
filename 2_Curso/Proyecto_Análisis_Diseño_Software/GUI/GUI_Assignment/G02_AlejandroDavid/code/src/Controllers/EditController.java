package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.*;
import java.util.GregorianCalendar;
import java.util.HashMap;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import padsof.*;
import View.*;
import Exceptions.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages EditPanel.
 * It implements ActionListener
 */
public class EditController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;
	
	/**
	 * This constructor creates a new EditController.
	 * It just stores all the information needed to control EditPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public EditController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			((EditPanel)panels.get("EDIT PANEL")).clean();
			((OwnOfferPanel)panels.get("OWN OFFER PANEL")).clearSelection();
			card.show(window, "OWN OFFER PANEL");
		}
		else if(arg.getActionCommand().equals("Edit Offer")){
			Offer selected = ((OwnOfferController)controllers.get("OWN OFFER CONTROLLER")).getSelectedOffer();
			if(selected.getStatus() != Status.WAITING) {
				JOptionPane.showMessageDialog(null, "Sorry, you can only edit offers pending to be approved",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			
			String price = ((EditPanel)panels.get("EDIT PANEL")).getPriceText();
			String iniDay = ((EditPanel)panels.get("EDIT PANEL")).getIniDayText();
			String iniMonth = ((EditPanel)panels.get("EDIT PANEL")).getIniMonthText();
			String iniYear = ((EditPanel)panels.get("EDIT PANEL")).getiniYearText();
			
			if(selected.getOfferType() == OfferType.SHORT) {
				String finDay = ((EditPanel)panels.get("EDIT PANEL")).getFinDayText();
				String finMonth = ((EditPanel)panels.get("EDIT PANEL")).getFinMonthText();
				String finYear = ((EditPanel)panels.get("EDIT PANEL")).getFinYearText();
				try {
					Float money;
					if(price.equals("") || price.equals(" ")) {
						money = null;
					}else {
						money = Float.parseFloat(price);
					}
					GregorianCalendar iniDate;
					if((iniDay.equals("") || iniDay.equals(" ")) && (iniMonth.equals("") || iniMonth.equals(" ")) && (iniYear.equals("") || iniYear.equals(" "))) {
						iniDate = null;
					}else {
						iniDate = new GregorianCalendar(Integer.parseInt(iniYear), Integer.parseInt(iniMonth), Integer.parseInt(iniDay));
					}
					GregorianCalendar finDate;
					if((finDay.equals("") || finDay.equals(" ")) && (finMonth.equals("") || finMonth.equals(" ")) && (finYear.equals("") || finYear.equals(" "))) {
						finDate = null;
					}else {
						finDate = new GregorianCalendar(Integer.parseInt(finYear), Integer.parseInt(finMonth), Integer.parseInt(finDay));
					}
					try{
						iniDate.setLenient(false);
						finDate.setLenient(false);
						iniDate.getTime();
						finDate.getTime();
					}catch(Exception ex) {
						JOptionPane.showMessageDialog(null, "Please, introduce correct dates",
								"ERROR", JOptionPane.ERROR_MESSAGE);
						return;
					}
					app.editOffer(selected, money, iniDate, finDate);
					JOptionPane.showMessageDialog(null, "Offer edited successfully");
				}catch(OfferException ex) {
					JOptionPane.showMessageDialog(null, "Error while trying to edit an offer",
							"ERROR", JOptionPane.ERROR_MESSAGE);
					return;
				}catch(NumberFormatException ex) {
					JOptionPane.showMessageDialog(null, "Please, introduce correct numeric values in all the fields");
					return;
				}
				
			}
			if(selected.getOfferType() == OfferType.LONG) {
				String nDays = ((EditPanel)panels.get("EDIT PANEL")).getDaysText();
				String Months = ((EditPanel)panels.get("EDIT PANEL")).getMonthsText();
				String Years = ((EditPanel)panels.get("EDIT PANEL")).getYearsText();
				
				try {
					Float money;
					if(price.equals("") || price.equals(" ")) {
						money = null;
					}else {
						money = Float.parseFloat(price);
					}
					Integer days;
					if(nDays.equals("") || nDays.equals(" ")) {
						days = null;
					}else {
						days = Integer.parseInt(nDays);
					}
					Integer months;
					if(Months.equals("") || Months.equals(" ")) {
						months = null;
					}else {
						months = Integer.parseInt(Months);
					}
					Integer years;
					if(Years.equals("") || Years.equals(" ")) {
						years = null;
					}else {
						years = Integer.parseInt(Years);
					}
					GregorianCalendar iniDate;
					if((iniDay.equals("") || iniDay.equals(" ")) && (iniMonth.equals("") || iniMonth.equals(" ")) && (iniYear.equals("") || iniYear.equals(" "))) {
						iniDate = null;
					}else {
						iniDate = new GregorianCalendar(Integer.parseInt(iniYear), Integer.parseInt(iniMonth), Integer.parseInt(iniDay));
					}
					days = Integer.parseInt(nDays);
					app.editOffer(selected, money, iniDate, days, months, years);
					JOptionPane.showMessageDialog(null, "Offer edited successfully");
				}catch(OfferException ex) {
					JOptionPane.showMessageDialog(null, "Error while trying to edit an offer",
							"ERROR", JOptionPane.ERROR_MESSAGE);
					return;
				}catch(NumberFormatException ex) {
					JOptionPane.showMessageDialog(null, "Please, introduce numeric values for the dates");
					return;
				}
			}
		}
		
	}

}
