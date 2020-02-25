package View;

import java.awt.*;
import java.awt.event.ActionListener;

import javax.swing.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the manager can choose
 * between manage offers, credit card changes and logout
 */
public class ManagerStartPanel extends JPanel{
	private JButton logoutButton;
	private JButton offerManagementButton;
	private JButton userManagementButton;
	
	/**
	 * This constructor creates a new ManagerStartPanel.
	 */
	public ManagerStartPanel() {
		this.setLayout(new GridLayout(3, 0));
		logoutButton = new JButton("Logout");
		offerManagementButton = new JButton("Offer Management");
		userManagementButton = new JButton("User Management");
		this.add(logoutButton);
		this.add(offerManagementButton);
		this.add(userManagementButton);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		logoutButton.addActionListener(al);
		offerManagementButton.addActionListener(al);
		userManagementButton.addActionListener(al);
	}

}
