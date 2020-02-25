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
 * This class implements the controller that manages CreateShortPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class CreateShortController implements ActionListener, ListSelectionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	/* Auxiliary */
	private Apartment selected;
	
	/**
	 * This constructor creates a new CreateShortController.
	 * It just stores all the information needed to control CreateShortPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param app The application (Model) run.
	 */
	public CreateShortController(Container window, HashMap<String, JPanel> panels, Application app) {
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
			((CreateShortPanel)panels.get("CREATE SHORT PANEL")).clean();
			OwnOfferPanel.clearSelection();
		}
		else if(arg.getActionCommand().equals("Apply")) {
			if(selected == null) {
				JOptionPane.showMessageDialog(null, "Please, select a property to offer");
			}
			else {
				String price = ((CreateShortPanel)panels.get("CREATE SHORT PANEL")).getPriceText();
				String iniDay = ((CreateShortPanel)panels.get("CREATE SHORT PANEL")).getIniDayText();
				String iniMonth = ((CreateShortPanel)panels.get("CREATE SHORT PANEL")).getIniMonthText();
				String iniYear = ((CreateShortPanel)panels.get("CREATE SHORT PANEL")).getiniYearText();
				String finDay = ((CreateShortPanel)panels.get("CREATE SHORT PANEL")).getFinDayText();
				String finMonth = ((CreateShortPanel)panels.get("CREATE SHORT PANEL")).getFinMonthText();
				String finYear = ((CreateShortPanel)panels.get("CREATE SHORT PANEL")).getFinYearText();
				RegisteredUser user = app.getLoggedUser();
				
				try {
					GregorianCalendar iniDate = new GregorianCalendar(Integer.parseInt(iniYear), Integer.parseInt(iniMonth), Integer.parseInt(iniDay));
					GregorianCalendar finDate = new GregorianCalendar(Integer.parseInt(finYear), Integer.parseInt(finMonth), Integer.parseInt(finDay));
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
					app.createOffer(Float.parseFloat(price), selected, user, iniDate, finDate);
					JOptionPane.showMessageDialog(null, "The operation has been successfully performed");
					((CreateShortPanel)panels.get("CREATE SHORT PANEL")).clean();
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
