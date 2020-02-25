package View;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.util.ArrayList;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionListener;

import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can see comments
 */
public class SeeCommentPanel extends JPanel{
	/* Buttons */
	private JButton returnOfferButton;
	private JButton seeCommentsButton;
	private JButton commentCommentButton;
	/* Auxiliary */
	private JPanel commentariesListPanel;
	private JList theList;
	private JScrollPane theScroll;
	
	/**
	 * This constructor creates a new SeeCommentPanel.
	 * It help helped by 2 privated methods that just creates different smaller panels
	 */
	public SeeCommentPanel() {
		JPanel top = this.buildTopPanel();
		JPanel bot = this.buildDownPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, top);
		this.add(BorderLayout.SOUTH, bot);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		returnOfferButton.addActionListener(al);
		seeCommentsButton.addActionListener(al);
		commentCommentButton.addActionListener(al);
	}
	
	
	public void prepareButtons(RegisteredUser user) {
		seeCommentsButton.setVisible(true);
		returnOfferButton.setVisible(true);
		if(user==null) {
			commentCommentButton.setVisible(false);
		}
		else {
			commentCommentButton.setVisible(true);
		}
	}
	
	/**
	 * Sets up all the commentaries
	 * @param commentaries List of commentaries to be shown
	 * @param lsl ListSelectionListener
	 */
	public void showCommentaries(ArrayList<Commentary> commentaries, ListSelectionListener lsl) {
		if(theScroll != null) {
			theScroll.setVisible(false);
		}
		if(commentariesListPanel!=null) {
			this.remove(commentariesListPanel);
		}
		JPanel commentariesPanel = new JPanel();
		DefaultListModel<Commentary> list = new DefaultListModel<Commentary>();
		for(Commentary com: commentaries) {
			list.addElement(com);
		}
		
		JList<Commentary> commentariesList = new JList<Commentary>(list);
		commentariesList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		JScrollPane scroll = new JScrollPane(commentariesList);
		
		commentariesPanel.add(scroll);
		theScroll = scroll;
		commentariesList.addListSelectionListener(lsl);
		commentariesList.setVisible(true);
		
		commentariesListPanel = commentariesPanel;
		this.add(BorderLayout.CENTER, commentariesPanel);
		theList = commentariesList;
	}
	
	/**
	 * It cleans the JList selected item
	 */
	public void clearSelection() {
		theList.clearSelection();
	}
	
	private JPanel buildTopPanel() {
		JPanel topPanel = new JPanel();
		this.returnOfferButton = new JButton("Return to the selected offer");
		topPanel.add(returnOfferButton);
		return topPanel;
	}
	
	private JPanel buildDownPanel() {
		JPanel panel = new JPanel();
		this.commentCommentButton = new JButton("Comment commentary");
		this.seeCommentsButton = new JButton("See comment's commentaries");
		panel.add(commentCommentButton);
		panel.add(seeCommentsButton);
		return panel;
	}

}
