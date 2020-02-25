package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import padsof.Application;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages PropertyPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class PropertyController implements ActionListener, ListSelectionListener{
	private Application app;
	private Container window;
	private CardLayout card;

	/**
	 * This constructor creates a new PropertyController.
	 * It just stores all the information needed to control PropertyPanel
	 * @param window Container of the application
	 * @param app The application (Model) run.
	 */
	public PropertyController(Container window, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
	}

	@Override
	public void valueChanged(ListSelectionEvent arg) {
		return;
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			card.show(window, "START PANEL");
		}
		else if(arg.getActionCommand().equals("Register New Property")) {
			card.show(window, "REGISTER PROPERTY PANEL");
		}
	}

}
