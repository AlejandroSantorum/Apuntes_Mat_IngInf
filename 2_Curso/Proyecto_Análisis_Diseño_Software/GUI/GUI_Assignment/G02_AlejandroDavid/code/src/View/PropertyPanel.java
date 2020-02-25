package View;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.*;
import javax.swing.event.ListSelectionListener;

import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can see their properties
 */
public class PropertyPanel extends JPanel{
	/* Buttons */
	private JButton addPropertyButton;
	private JButton goBackButton;
	/* Auxiliary */
	private JPanel propertiesListPanel;
	
	/**
	 * This constructor creates a new PropertyPanel.
	 * It help helped by 2 privated methods that just creates different smaller panels
	 */
	public PropertyPanel() {
		JPanel top = this.buildTopPanel();
		JPanel down = this.buildDownPanel();
		
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
		addPropertyButton.addActionListener(al);
	}
	
	/**
	 * Sets up the list of properties
	 * @param properties List of the logged user properties
	 * @param lsl ListSelectionListener
	 */
	public void showProperties(ArrayList<Apartment> properties, ListSelectionListener lsl) {
		if(propertiesListPanel!=null) {
			this.remove(propertiesListPanel);
		}
		JPanel propertiesPanel = new JPanel();
		DefaultListModel<Apartment> list = new DefaultListModel<Apartment>();
		for(Apartment apart: properties) {
			list.addElement(apart);
		}
		
		JList<Apartment> propertiesList = new JList<Apartment>(list);
		propertiesList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		JScrollPane scroll = new JScrollPane(propertiesList);
		
		propertiesPanel.add(scroll);
		propertiesList.addListSelectionListener(lsl);
		
		propertiesListPanel = propertiesPanel;
		this.add(BorderLayout.CENTER, propertiesPanel);
	}
	
	
	private JPanel buildTopPanel() {
		JPanel topPanel = new JPanel();
		this.goBackButton = new JButton("Go Back");
		topPanel.add(goBackButton);
		return topPanel;
	}
	
	private JPanel buildDownPanel() {
		JPanel downPanel = new JPanel();
		this.addPropertyButton = new JButton("Register New Property");
		downPanel.add(addPropertyButton);
		return downPanel;
	}

}
