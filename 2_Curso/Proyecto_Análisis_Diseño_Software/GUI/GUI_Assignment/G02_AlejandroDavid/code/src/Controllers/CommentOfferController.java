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
 * This class implements the controller that manages CommentOfferPanel.
 * It implements ActionListener
 */
public class CommentOfferController implements ActionListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	
	/**
	 * This constructor creates a new CommentOfferController.
	 * It just stores all the information needed to control CommentOfferPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param app The application (Model) run.
	 */
	public CommentOfferController(Container window, HashMap<String, JPanel> panels, Application app) {
		this.app = app;
		this.window = window;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
	}

	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			((OfferPanel)panels.get("OFFER PANEL")).prepareOfferInfo(OfferController.getOffer());
			card.show(window, "OFFER PANEL");
			((CommentOfferPanel)panels.get("COMMENT OFFER PANEL")).clean();
		}
		else if(arg.getActionCommand().equals("Comment textually")) {
			String text = ((CommentOfferPanel)panels.get("COMMENT OFFER PANEL")).getCommentText();
			GregorianCalendar rightNow = new GregorianCalendar();
			Offer theOffer = OfferController.getOffer();
			try {
				app.addCommentary(theOffer, app.getLoggedUser(), rightNow, text);
				JOptionPane.showMessageDialog(null, "Offer commented successfully");
				((CommentOfferPanel)panels.get("COMMENT OFFER PANEL")).clean();
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
		else if(arg.getActionCommand().equals("Rate offer")) {
			String points = ((CommentOfferPanel)panels.get("COMMENT OFFER PANEL")).getSelectedRateText();
			GregorianCalendar rightNow = new GregorianCalendar();
			Offer theOffer = OfferController.getOffer();
			try {
				app.addCommentary(theOffer, app.getLoggedUser(), rightNow, Integer.parseInt(points));
				JOptionPane.showMessageDialog(null, "Offer rated successfully");
				((CommentOfferPanel)panels.get("COMMENT OFFER PANEL")).clean();
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
