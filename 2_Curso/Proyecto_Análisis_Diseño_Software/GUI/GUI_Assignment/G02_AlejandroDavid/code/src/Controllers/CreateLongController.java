package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.GregorianCalendar;
import java.util.HashMap;

import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import View.*;
import padsof.*;
import Exceptions.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages CreateLongPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class CreateLongController implements ActionListener, ListSelectionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	/* Auxiliary */
	private Apartment selected;
	
	/**
	 * This constructor creates a new CreateLongController.
	 * It just stores all the information needed to control CreateLongPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param app The application (Model) run.
	 */
	public CreateLongController(Container window, HashMap<String, JPanel> panels, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
	}

	@Override
	public void valueChanged(ListSelectionEvent arg) {
		JList<Apartment> apartList = (JList<Apartment>) arg.getSource();
		Apartment selectedApartment = (Apartment) apartList.getSelectedValue();
		selected = selectedApartment;
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			card.show(window, "OWN OFFER PANEL");
			selected = null;
			((CreateLongPanel)panels.get("CREATE LONG PANEL")).clean();
			OwnOfferPanel.clearSelection();
		}
		else if(arg.getActionCommand().equals("Apply")) {
			if(selected == null) {
				JOptionPane.showMessageDialog(null, "Please, select a property to offer");
			}
			else {
				String price = ((CreateLongPanel)panels.get("CREATE LONG PANEL")).getPriceText();
				String iniDay = ((CreateLongPanel)panels.get("CREATE LONG PANEL")).getIniDayText();
				String iniMonth = ((CreateLongPanel)panels.get("CREATE LONG PANEL")).getIniMonthText();
				String iniYear = ((CreateLongPanel)panels.get("CREATE LONG PANEL")).getiniYearText();
				String nDays = ((CreateLongPanel)panels.get("CREATE LONG PANEL")).getDaysText();
				String nMonths = ((CreateLongPanel)panels.get("CREATE LONG PANEL")).getMonthsText();
				String nYears = ((CreateLongPanel)panels.get("CREATE LONG PANEL")).getYearsText();
				RegisteredUser user = app.getLoggedUser();
				try {
					GregorianCalendar iniDate = new GregorianCalendar(Integer.parseInt(iniYear), Integer.parseInt(iniMonth), Integer.parseInt(iniDay));
					try{
						iniDate.setLenient(false);
						iniDate.getTime();
					}catch(Exception ex) {
						JOptionPane.showMessageDialog(null, "Please, introduce correct dates",
								"ERROR", JOptionPane.ERROR_MESSAGE);
						return;
					}
					app.createOffer(Float.parseFloat(price), selected, user, iniDate, Integer.parseInt(nDays), Integer.parseInt(nMonths), Integer.parseInt(nYears));
					JOptionPane.showMessageDialog(null, "The operation has been successfully performed");
					((CreateLongPanel)panels.get("CREATE LONG PANEL")).clean();
				}catch(UserException ex) {
					JOptionPane.showMessageDialog(null, "Error while trying to create a new offer",
							"ERROR", JOptionPane.ERROR_MESSAGE);
					return;
				}catch(OfferException ex) {
					JOptionPane.showMessageDialog(null, "Error while trying to create a new offer",
							"ERROR", JOptionPane.ERROR_MESSAGE);
					return;
				}catch(NumberFormatException ex) {
					JOptionPane.showMessageDialog(null, "Please, introduce numeric values for the dates");
					return;
				}catch(IllegalArgumentException ex) {
					JOptionPane.showMessageDialog(null, "The initial date has to be previous than the final date",
							"ERROR", JOptionPane.ERROR_MESSAGE);
					return;
				}
			}
		}
	}

}
