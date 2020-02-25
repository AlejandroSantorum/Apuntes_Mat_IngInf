package Controllers;

import java.awt.CardLayout;
import java.awt.event.*;
import java.awt.*;

import javax.swing.*;
import javax.swing.event.*;
import java.util.*;

import padsof.*;
import View.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages ManagerListUsersPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class ManagerListUsersController implements ActionListener, ListSelectionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private RegisteredUser selectedUser;
	
	/**
	 * This constructor creates a new ManagerListUsersController.
	 * It just stores all the information needed to control ManagerListUsersPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param app The application (Model) run.
	 */
	public ManagerListUsersController(Container window, HashMap<String, JPanel> panels, Application app) {
		this.app = app;
		this.window = window;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
	}
	
	@Override
	public void valueChanged(ListSelectionEvent arg) {
		JList<RegisteredUser> usersList = (JList<RegisteredUser>) arg.getSource();
		selectedUser = (RegisteredUser) usersList.getSelectedValue();
		if(selectedUser != null) {
			((ManagerUserPanel)panels.get("MANAGER USER PANEL")).prepareUserInfo(selectedUser, app);
		}
		card.show(window, "MANAGER USER PANEL");
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			((ManagerListUsersPanel)panels.get("MANAGER LIST USERS PANEL")).clearSelection();
			card.show(window, "MANAGER START PANEL");
		}
		
	}
	
	/**
	 * Gets the selected user
	 * @return The selected user
	 */
	public RegisteredUser getSelectedUser() {
		return selectedUser;
	}

}
