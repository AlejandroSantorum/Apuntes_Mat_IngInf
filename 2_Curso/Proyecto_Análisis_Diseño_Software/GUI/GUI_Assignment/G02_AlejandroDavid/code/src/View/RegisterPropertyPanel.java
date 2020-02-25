package View;

import java.awt.*;
import java.awt.event.ActionListener;
import javax.swing.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can register a new property
 */
public class RegisterPropertyPanel extends JPanel{
	/* Buttons */
	private JButton registerButton;
	private JButton goBackButton;
	/* Text Fields */
	private JTextField pcField;
	private JTextField addressField;
	private JTextField descriptionField;
	/* Labels */
	private JLabel pc;
	private JLabel address;
	private JLabel description;
	
	/**
	 * This constructor creates a new RegisterPropertyPanel.
	 * It help helped by 3 privated methods that just creates different smaller panels
	 */
	public RegisterPropertyPanel() {
		JPanel top = buildTopPanel();
		JPanel mid = buildMidPanel();
		JPanel down = buildDownPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, top);
		this.add(BorderLayout.CENTER, mid);
		this.add(BorderLayout.SOUTH, down);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		goBackButton.addActionListener(al);
		registerButton.addActionListener(al);
	}
	
	public String getPCText() {
		return this.pcField.getText();
	}
	
	public String getAddressText() {
		return this.addressField.getText();
	}
	
	public String getDescriptionText() {
		return this.descriptionField.getText();
	}
	
	/**
	 * It clears the JTextFields
	 */
	public void clean() {
		this.pcField.setText("");
		this.addressField.setText("");
		this.descriptionField.setText("");
	}
	
	private JPanel buildTopPanel() {
		JPanel topPanel = new JPanel();
		this.goBackButton = new JButton("Go Back");
		topPanel.add(goBackButton);
		return topPanel;
	}
	
	private JPanel buildMidPanel() {
		JPanel midPanel = new JPanel();
		midPanel.setLayout(new GridLayout(3,0));
		
		pc = new JLabel("Postal code");
		pc.setHorizontalAlignment(JLabel.CENTER);
		pcField = new JTextField(100);
		pcField.setHorizontalAlignment(JTextField.CENTER);
		
		address = new JLabel("Address");
		address.setHorizontalAlignment(JLabel.CENTER);
		addressField = new JTextField(100);
		addressField.setHorizontalAlignment(JTextField.CENTER);
		
		description = new JLabel("Description");
		description.setHorizontalAlignment(JLabel.CENTER);
		descriptionField = new JTextField(100);
		descriptionField.setHorizontalAlignment(JTextField.CENTER);
		
		midPanel.add(pc);
		midPanel.add(pcField);
		midPanel.add(address);
		midPanel.add(addressField);
		midPanel.add(description);
		midPanel.add(descriptionField);
		
		return midPanel;	
	}
	
	private JPanel buildDownPanel() {
		JPanel downPanel = new JPanel();
		this.registerButton = new JButton("Register Property");
		downPanel.add(registerButton);
		return downPanel;
	}

}
