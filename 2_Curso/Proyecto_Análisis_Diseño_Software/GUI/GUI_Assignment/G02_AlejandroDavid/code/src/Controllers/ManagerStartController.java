package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.HashMap;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import padsof.*;
import View.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages ManagerStartPanel.
 * It implements ActionListener
 */
public class ManagerStartController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private String filename;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;
	
	/**
	 * This constructor creates a new ManagertartController.
	 * It just stores all the information needed to control ManagerStartsPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param filename Name of the file where the application data is going to be stored
	 * @param app The application (Model) run.
	 */
	public ManagerStartController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, String filename, Application app) {
		this.app = app;
		this.window = window;
		this.card = (CardLayout) window.getLayout();
		this.filename = filename;
		this.panels = panels;
		this.controllers = controllers;
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Logout")) {
			((LoginPanel)panels.get("LOGIN PANEL")).clean();
			try {
				app.saveData(filename);
			}catch(IOException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to save application data",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			app.setLoggedUser(null);
			card.show(window, "LOGIN PANEL");
		}
		else if(arg.getActionCommand().equals("Offer Management")) {
			((ManagerListOffersPanel)panels.get("MANAGER LIST OFFERS PANEL")).showOffers(app.getWaitingOffers(), ((ManagerListOffersController)controllers.get("MANAGER LIST OFFERS CONTROLLER")));
			card.show(window, "MANAGER LIST OFFERS PANEL");
		}
		else if(arg.getActionCommand().equals("User Management")) {
			((ManagerListUsersPanel)panels.get("MANAGER LIST USERS PANEL")).showUsers(app.getCreditCardRequest().keySet(), ((ManagerListUsersController)controllers.get("MANAGER LIST USERS CONTROLLER")));
			card.show(window, "MANAGER LIST USERS PANEL");
		}
	}

}
