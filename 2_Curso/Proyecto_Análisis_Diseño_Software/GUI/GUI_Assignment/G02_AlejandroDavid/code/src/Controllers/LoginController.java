package Controllers;

import java.awt.Container;
import java.awt.event.*;
import java.io.IOException;
import java.util.HashMap;
import java.awt.CardLayout;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import View.*;
import padsof.*;
import Exceptions.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages LoginPanel.
 * It implements ActionListener
 */
public class LoginController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private String filename;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;
	
	/**
	 * This constructor creates a new LoginController.
	 * It just stores all the information needed to control LoginPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param filename Name of the file where the applicatio ndata is going to be stored
	 * @param app The application (Model) run.
	 */
	public LoginController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, String filename, Application app) {
		this.app = app;
		this.window = window;
		this.card = (CardLayout) window.getLayout();
		this.filename = filename;
		this.panels = panels;
		this.controllers = controllers;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Login")) {
			String userId = ((LoginPanel)panels.get("LOGIN PANEL")).getUserIdText();
			String password = ((LoginPanel)panels.get("LOGIN PANEL")).getPasswordText();
			RegisteredUser user = app.login(userId, password);
			
			if(userId.equals("admin") && password.equals("admin")) {
				card.show(window, "MANAGER START PANEL");
			}
			else if(user == null) {
				JOptionPane.showMessageDialog(null, "USUARIO O CONTRASEÑA INCORRECTOS");
			}
			else{
				app.setLoggedUser(user);
				if(user.isBlocked()) {
					if(app.requestedCCNChange(app.getLoggedUser())) {
						JOptionPane.showMessageDialog(null, "Your credit card number is going to be checked by managers soon\nSorry for the delay");
					}
					else {
						((BlockedUserPanel)panels.get("BLOCKED USER PANEL")).clean();
						((BlockedUserPanel)panels.get("BLOCKED USER PANEL")).prepareButtons(user.getUserType());
						card.show(window, "BLOCKED USER PANEL");
					}
				}
				else {
					((StartPanel)panels.get("START PANEL")).showOffers(app.getOffersArray(), ((StartController)controllers.get("START CONTROLLER")));
					((StartPanel)panels.get("START PANEL")).prepareStartButtons(user.getUserType());
					card.show(window, "START PANEL");
				}
			}
		}
		else {
			try {
				((StartPanel)panels.get("START PANEL")).showOffers(app.getFreeOffers(null), ((StartController)controllers.get("START CONTROLLER")));
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to enter the application",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			((StartPanel)panels.get("START PANEL")).prepareStartButtons(null);
			card.show(window, "START PANEL");
			try {
				app.saveData(this.filename);
			}catch(IOException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to save the application",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			
		}
	}
	

}
