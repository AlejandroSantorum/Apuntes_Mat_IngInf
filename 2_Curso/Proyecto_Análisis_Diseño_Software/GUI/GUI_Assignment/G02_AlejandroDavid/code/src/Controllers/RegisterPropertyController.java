package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import View.*;
import padsof.*;
import Exceptions.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages RegisterPropertyPanel.
 * It implements ActionListener
 */
public class RegisterPropertyController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;

	/**
	 * This constructor creates a new RegisterPropertyController.
	 * It just stores all the information needed to control RegisterPropertyPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public RegisterPropertyController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			try {
				((PropertyPanel)panels.get("PROPERTY PANEL")).showProperties(app.getLoggedUser().getUserApartments(), ((PropertyController)controllers.get("PROPERTY CONTROLLER")));
			} catch (UserException e) {
				JOptionPane.showMessageDialog(null, "Error while trying to go back. if this error persists, please close the application",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			card.show(window, "PROPERTY PANEL");
			((RegisterPropertyPanel)panels.get("REGISTER PROPERTY PANEL")).clean();
		}
		if(arg.getActionCommand().equals("Register Property")) {
			String pc = ((RegisterPropertyPanel)panels.get("REGISTER PROPERTY PANEL")).getPCText();
			String address = ((RegisterPropertyPanel)panels.get("REGISTER PROPERTY PANEL")).getAddressText();
			String description = ((RegisterPropertyPanel)panels.get("REGISTER PROPERTY PANEL")).getDescriptionText();
			RegisteredUser user = app.getLoggedUser();
			if(address.equals("") || description.equals("")) {
				JOptionPane.showMessageDialog(null, "Please, introduce address and/or description",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
			try {
				app.createApartment(Integer.parseInt(pc), address, description, user);
				JOptionPane.showMessageDialog(null, "Property registered successfully");
				((RegisterPropertyPanel)panels.get("REGISTER PROPERTY PANEL")).clean();
			}catch(OfferException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to register the new property",
												"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to register the new property",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}catch(NumberFormatException ex) {
				JOptionPane.showMessageDialog(null, "Please, introduce a numeric value for postal code");
				return;
			}
			
		}
	}
}
