package View;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionListener;

import javax.swing.*;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the manager can accept or reject
 * a credit card number change, requested by a blocked user
 */
public class ManagerUserPanel extends JPanel{
	/* Buttons */
	private JButton goBackButton;
	private JButton acceptButton;
	private JButton rejectButton;
	/* Labels */
	private JLabel name;
	private JLabel id;
	private JLabel type;
	private JLabel oldccn;
	private JLabel newccn;
	/* Auxiliary */
	JPanel userPanel;

	/**
	 * This constructor creates a new ManagerUserPanel.
	 * It help helped by 2 privated methods that just creates different smaller panels
	 */
	public ManagerUserPanel() {
		JPanel top = buildTopPanel();
		JPanel down = buildDownPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, top);
		this.add(BorderLayout.SOUTH, down);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		goBackButton.addActionListener(al);
		acceptButton.addActionListener(al);
		rejectButton.addActionListener(al);
	}

	/**
	 * Sets up all the user information to be examinated by the admin
	 * @param user Registered user whose information is going to be shown
	 * @param app Application
	 */
	public void prepareUserInfo(RegisteredUser user, Application app) {
		if(userPanel != null) {
			this.remove(userPanel);
		}
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(5,0));
		
		name = new JLabel("User nick: "+user.getNick());
		name.setHorizontalAlignment(JLabel.CENTER);
		id = new JLabel("User ID: "+user.getId());
		id.setHorizontalAlignment(JLabel.CENTER);
		type = new JLabel("User type: "+user.getUserType().toString());
		type.setHorizontalAlignment(JLabel.CENTER);
		oldccn = new JLabel("Current credit card number: "+user.getCreditCard());
		oldccn.setHorizontalAlignment(JLabel.CENTER);
		newccn = new JLabel("Requested credit card number: "+app.getCreditCardRequest().get(user.getId()));
		newccn.setHorizontalAlignment(JLabel.CENTER);
		
		panel.add(name);
		panel.add(id);
		panel.add(type);
		panel.add(oldccn);
		panel.add(newccn);
		
		userPanel = panel;
		this.add(BorderLayout.CENTER, panel);
	}
	
	
	private JPanel buildTopPanel() {
		JPanel top = new JPanel();
		goBackButton = new JButton("Go Back");
		top.add(goBackButton);
		return top;
	}
	
	private JPanel buildDownPanel() {
		JPanel downPanel = new JPanel();
		this.acceptButton = new JButton("Accept");
		this.rejectButton = new JButton("Reject");
		downPanel.add(acceptButton);
		downPanel.add(rejectButton);
		return downPanel;
	}

}
