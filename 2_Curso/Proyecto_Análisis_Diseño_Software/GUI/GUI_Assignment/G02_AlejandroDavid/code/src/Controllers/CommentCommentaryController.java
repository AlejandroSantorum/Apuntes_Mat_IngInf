package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.GregorianCalendar;
import java.util.HashMap;

import javax.swing.JOptionPane;
import javax.swing.JPanel;

import padsof.*;
import Exceptions.*;
import View.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages CommentCommentaryPanel.
 * It implements ActionListener
 */
public class CommentCommentaryController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;

	/**
	 * This constructor creates a new CommentCommentaryController.
	 * It just stores all the information needed to control CommentCommentaryPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public CommentCommentaryController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.app = app;
		this.window = window;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			((SeeCommentPanel)panels.get("SEE COMMENT PANEL")).clearSelection();
			card.show(window, "SEE COMMENT PANEL");
			((CommentCommentaryPanel)panels.get("COMMENT COMMENTARY PANEL")).clean();
		}
		else if(arg.getActionCommand().equals("Comment textually")) {
			String text = ((CommentCommentaryPanel)panels.get("COMMENT COMMENTARY PANEL")).getCommentText();
			GregorianCalendar rightNow = new GregorianCalendar();
			Commentary theComment = ((SeeCommentController)controllers.get("SEE COMMENT CONTROLLER")).getComment();
			try {
				app.addCommentary(theComment, app.getLoggedUser(), rightNow, text);
				JOptionPane.showMessageDialog(null, "Commentary commented successfully");
				((CommentCommentaryPanel)panels.get("COMMENT COMMENTARY PANEL")).clean();
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to comment the offer. Try it later again",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}catch(OfferException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to comment the offer. Try it later again",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
		}
		else if(arg.getActionCommand().equals("Rate the commentary")) {
			String points = ((CommentCommentaryPanel)panels.get("COMMENT COMMENTARY PANEL")).getSelectedRateText();
			GregorianCalendar rightNow = new GregorianCalendar();
			Commentary theComment = ((SeeCommentController)controllers.get("SEE COMMENT CONTROLLER")).getComment();
			try {
				app.addCommentary(theComment, app.getLoggedUser(), rightNow, Integer.parseInt(points));
				JOptionPane.showMessageDialog(null, "Commentary rated successfully");
				((CommentCommentaryPanel)panels.get("COMMENT COMMENTARY PANEL")).clean();
			}catch(UserException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to comment the offer. Try it later again",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}catch(OfferException ex) {
				JOptionPane.showMessageDialog(null, "Error while trying to comment the offer. Try it later again",
						"ERROR", JOptionPane.ERROR_MESSAGE);
				return;
			}
		}
		
	}

}
