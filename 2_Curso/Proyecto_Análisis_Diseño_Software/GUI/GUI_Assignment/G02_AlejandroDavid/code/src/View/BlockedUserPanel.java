package View;

import java.awt.*;
import java.awt.event.ActionListener;
import javax.swing.*;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can introduce a new credit card
 * number in the case he is blocked
 */
public class BlockedUserPanel extends JPanel{
	/* Buttons */
	JButton logoutButton;
	JButton changeButton;
	JButton continueButton;
	/* Labels */
	JLabel warning;
	JLabel advice;
	JLabel ccn;
	/* Textfield */
	JTextField ccnField;
	
	/**
	 * This constructor creates a new BlockedUserPanel.
	 * It help helped by 3 privated methods that just creates different smaller panels
	 */
	public BlockedUserPanel() {
		JPanel top = buildTopPanel();
		JPanel mid = buildMidPanel();
		JPanel bot = buildDownPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, top);
		this.add(BorderLayout.CENTER, mid);
		this.add(BorderLayout.SOUTH, bot);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		logoutButton.addActionListener(al);
		changeButton.addActionListener(al);
		continueButton.addActionListener(al);
	}
	
	/**
	 * It sets up the buttons deppending on the user type
	 * @param ut logged user type
	 */
	public void prepareButtons(UserType ut) {
		logoutButton.setVisible(true);
		changeButton.setVisible(true);
		if(ut == UserType.RENTER) {
			continueButton.setVisible(false);
		}else {
			continueButton.setVisible(true);
		}
	}
	
	/**
	 * It cleans the JTextFields
	 */
	public void clean() {
		ccnField.setText("");
	}
	
	
	public String getCCNText() {
		return ccnField.getText();
	}
	
	private JPanel buildMidPanel() {
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(2,0));
		
		warning = new JLabel("WARNING: Your credit card number is wrong");
		warning.setHorizontalAlignment(JLabel.CENTER);
		warning.setForeground(Color.RED);
		advice = new JLabel("Please, change it as soon as possible");
		advice.setHorizontalAlignment(JLabel.CENTER);
		advice.setForeground(Color.RED);
		ccn = new JLabel("New credit card number --->");
		ccn.setHorizontalAlignment(JLabel.CENTER);
		ccnField = new JTextField(100);
		ccnField.setHorizontalAlignment(JTextField.CENTER);
		panel.add(warning);
		panel.add(advice);
		panel.add(ccn);
		panel.add(ccnField);
		
		return panel;
		
	}
	
	private JPanel buildTopPanel() {
		JPanel panel = new JPanel();
		logoutButton = new JButton("Logout");
		continueButton = new JButton("Continue without changes");
		panel.add(logoutButton);
		panel.add(continueButton);
		return panel;
	}
	
	private JPanel buildDownPanel() {
		JPanel panel = new JPanel();
		changeButton = new JButton("Change credit card number");
		panel.add(changeButton);
		return panel;
	}
}
