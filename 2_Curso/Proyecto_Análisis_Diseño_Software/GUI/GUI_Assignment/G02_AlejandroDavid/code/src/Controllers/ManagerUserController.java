package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import View.ManagerListUsersPanel;
import padsof.Application;
import padsof.Offer;
import padsof.RegisteredUser;
import padsof.Status;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages ManagerUserPanel.
 * It implements ActionListener 
 */
public class ManagerUserController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;

	/**
	 * This constructor creates a new ManagerUserController.
	 * It just stores all the information needed to control ManagerUserPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public ManagerUserController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			((ManagerListUsersPanel)panels.get("MANAGER LIST USERS PANEL")).showUsers(app.getCreditCardRequest().keySet(), (ManagerListUsersController)controllers.get("MANAGER LIST USERS CONTROLLER"));
			card.show(window, "MANAGER LIST USERS PANEL");
		}
		else if(arg.getActionCommand().equals("Accept")) {
			RegisteredUser user = ((ManagerListUsersController)controllers.get("MANAGER LIST USERS CONTROLLER")).getSelectedUser();
			user.setCreditCard(app.getCreditCardRequest().get(user.getId()));
			JOptionPane.showMessageDialog(null, "User credit card number changed successfully");
			app.removeCreditCardRequest(user);
			user.setUnBlocked();
		}
		else if(arg.getActionCommand().equals("Reject")) {
			RegisteredUser user = ((ManagerListUsersController)controllers.get("MANAGER LIST USERS CONTROLLER")).getSelectedUser();
			app.removeCreditCardRequest(user);
			JOptionPane.showMessageDialog(null, "The user credit card number has been rejected");
		}
	}
}
