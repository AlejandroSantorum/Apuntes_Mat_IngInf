package View;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Set;

import javax.swing.*;
import javax.swing.event.ListSelectionListener;

import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the manager can manage
 * all the credit card number changes, requested by blocked users
 */
public class ManagerListUsersPanel extends JPanel{
	private Application app;
	private JButton goBackButton;
	/* Auxiliary */
	private JPanel offersListPanel;
	private JList theList;
	
	/**
	 * This constructor creates a new ManagerListUsersPanel.
	 * It help helped by another privated methods that just creates different smaller panels
	 * @param app The application (Model)
	 */
	public ManagerListUsersPanel(Application app) {
		this.app = app;
		JPanel top = buildTopPanel();
		this.setLayout(new BorderLayout());
		this.add(BorderLayout.NORTH, top);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		goBackButton.addActionListener(al);
	}
	
	/**
	 * It cleans the JList selected item
	 */
	public void clearSelection() {
		theList.clearSelection();
	}
	
	/**
	 * Sets up the users that the administrator has to manage
	 * @param usersIDS List of blocked users
	 * @param lsl ListSelectionListener
	 */
	public void showUsers(Set<String> usersIDS, ListSelectionListener lsl) {
		if(offersListPanel!=null) {
			this.remove(offersListPanel);
		}
		JPanel usersPanel = new JPanel();
		
		ArrayList<RegisteredUser> users = new ArrayList<RegisteredUser>();
		for(String str: usersIDS) {
			users.add(app.getUserById(str));
		}
		DefaultListModel<RegisteredUser> list = new DefaultListModel<RegisteredUser>();
		for(RegisteredUser usr: users) {
			list.addElement(usr);
		}
		
		JList<RegisteredUser> usersList = new JList<RegisteredUser>(list);
		usersList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		usersList.setPreferredSize(new Dimension(500, 300));
		JScrollPane scroll = new JScrollPane(usersList);
		
		usersPanel.add(scroll);
		usersList.addListSelectionListener(lsl);
		
		offersListPanel = usersPanel;
		this.add(BorderLayout.CENTER, usersPanel);
		theList = usersList;
	}
	
	private JPanel buildTopPanel() {
		JPanel top = new JPanel();
		goBackButton = new JButton("Go Back");
		top.add(goBackButton);
		return top;
	}
}
