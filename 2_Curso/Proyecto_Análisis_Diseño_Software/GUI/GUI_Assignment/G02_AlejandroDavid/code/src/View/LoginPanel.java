package View;

import java.awt.*;
import java.awt.event.ActionListener;
import javax.swing.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can login the application
 */
public class LoginPanel extends JPanel{
	private JTextField idField;
	private JPasswordField passwordField;
	private JButton loginButton;
	private JButton guestButton;
	private JLabel id;
	private JLabel password;
	
	/**
	 * This constructor creates a new LoginPanel.
	 * It help helped by 2 privated methods that just creates different smaller panels
	 */
	public LoginPanel() {
		JPanel dataPanel = this.buildDataPanel();
		JPanel buttonsPanel = this.buildButtonsPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, dataPanel);
		this.add(BorderLayout.SOUTH, buttonsPanel);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		loginButton.addActionListener(al);
		guestButton.addActionListener(al);
	}
	
	public String getUserIdText() {
		return this.idField.getText();
	}
	
	public String getPasswordText() {
		return String.copyValueOf(this.passwordField.getPassword());
	}
	
	/**
	 * It cleans the JTextFields
	 */
	public void clean() {
		this.idField.setText("");
		this.passwordField.setText("");
	}
	
	private JPanel buildDataPanel() {
		JPanel dataPanel = new JPanel();
		dataPanel.setLayout(new GridLayout(2,0));
		
		id = new JLabel("User ID: ");
		idField = new JTextField(100);
		
		password = new JLabel("Password: ");
		passwordField = new JPasswordField(100);
		
		dataPanel.add(id);
		dataPanel.add(idField);
		
		dataPanel.add(password);
		dataPanel.add(passwordField);
		
		return dataPanel;
	}
	
	private JPanel buildButtonsPanel() {
		JPanel buttons= new JPanel();
		
		this.loginButton = new JButton("Login");
		this.guestButton = new JButton("Join as guest");
		
		buttons.add(this.loginButton);
		buttons.add(this.guestButton);
		
		return buttons;
	}
}
