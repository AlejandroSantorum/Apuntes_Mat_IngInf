package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;

import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import View.OfferPanel;
import View.SeeCommentPanel;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages SeeCommentPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class SeeCommentController implements ActionListener, ListSelectionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private Commentary selectedComment;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;
	
	/**
	 * This constructor creates a new SeeCommentController.
	 * It just stores all the information needed to control SeeCommentPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public SeeCommentController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.window = window;
		this.app = app;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}
	
	@Override
	public void valueChanged(ListSelectionEvent arg) {
		JList<Commentary> commentList = (JList<Commentary>) arg.getSource();
			selectedComment = (Commentary) commentList.getSelectedValue();
			//card.show(window, "COMMENT COMMENTARY PANEL");
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Return to the selected offer")) {
			((OfferPanel)panels.get("OFFER PANEL")).prepareOfferInfo(OfferController.getOffer());
			card.show(window, "OFFER PANEL");
		}
		else if(arg.getActionCommand().equals("See comment's commentaries")) {
			if(selectedComment != null) {
				((SeeCommentPanel)panels.get("SEE COMMENT PANEL")).showCommentaries(selectedComment.getComments(), ((SeeCommentController)controllers.get("SEE COMMENT CONTROLLER")));
				((SeeCommentPanel)panels.get("SEE COMMENT PANEL")).clearSelection();
				((SeeCommentPanel)panels.get("SEE COMMENT PANEL")).revalidate();
				((SeeCommentPanel)panels.get("SEE COMMENT PANEL")).repaint();
				selectedComment = null;
				card.show(window, "SEE COMMENT PANEL");
			}
			else {
				JOptionPane.showMessageDialog(null, "Please, select a commentary");
			}	
		}
		else if(arg.getActionCommand().equals("Comment commentary")) {
			if(selectedComment != null) {
				card.show(window, "COMMENT COMMENTARY PANEL");
			}
			else {
				JOptionPane.showMessageDialog(null, "Please, select a commentary");
			}
		}
	}
	
	/**
	 * Gets the selected comment
	 * @return the selected comment
	 */
	public Commentary getComment() {
		return selectedComment;
	}
	
	/**
	 * Sets the selected comment
	 * @param comm The selected comment
	 */
	public void setCommentary(Commentary comm) {
		selectedComment = comm;
	}

}
