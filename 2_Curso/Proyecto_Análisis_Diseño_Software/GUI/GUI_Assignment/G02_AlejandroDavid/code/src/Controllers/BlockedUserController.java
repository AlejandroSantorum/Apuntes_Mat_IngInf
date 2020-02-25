package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.*;
import java.io.IOException;
import java.util.HashMap;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import Exceptions.UserException;
import View.*;
import padsof.Application;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages BlockedUserPanel.
 * It implements ActionListener
 */
public class BlockedUserController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private String filename;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;
	
	/**
	 * This constructor creates a new BlockedUserController.
	 * It just stores all the information needed to control BlockedUserPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param filename Name of the file where the application data is going to be stored
	 * @param app The application (Model) run.
	 */
	public BlockedUserController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, String filename, Application app) {
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
			((BlockedUserPanel)panels.get("BLOCKED USER PANEL")).clean();
			card.show(window, "LOGIN PANEL");
		}
		else if(arg.getActionCommand().equals("Continue without changes")) {
			try {
				((StartPanel)panels.get("START PANEL")).showOffers(app.getFreeOffers(app.getLoggedUser()), ((StartController)controllers.get("START CONTROLLER")));
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to login",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			((StartPanel)panels.get("START PANEL")).prepareStartButtons(app.getLoggedUser().getUserType());
			card.show(window, "START PANEL");
		}
		else if(arg.getActionCommand().equals("Change credit card number")) {
			String aux = ((BlockedUserPanel)panels.get("BLOCKED USER PANEL")).getCCNText();
			app.addCreditCardRequest(app.getLoggedUser(), aux);
			try {
				app.saveData(filename);
			} catch (IOException e) {
				JOptionPane.showMessageDialog(null, "Error while closing the application",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			card.show(window, "LOGIN PANEL");
		}
	}

}
