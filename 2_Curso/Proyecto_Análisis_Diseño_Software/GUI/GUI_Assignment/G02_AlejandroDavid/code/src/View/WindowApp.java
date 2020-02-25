package View;

import java.awt.CardLayout;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import Controllers.*;
import Exceptions.UserException;
import padsof.*;

/**
 * 
 * @author David Cabornero and Alejandro Santorum
 * This is only one Jframe of the Graphical user interface.
 * Its mission is to sep up everything and prepare the application
 * to run.
 */
public class WindowApp extends JFrame{
	private HashMap<String, JPanel> panels = new HashMap<String, JPanel>();
	private HashMap<String, ActionListener> controllers = new HashMap<String, ActionListener>();
	
	private Application app;
	private LoginPanel loginPanel;
	private StartPanel startPanel;
	private OfferPanel offerPanel;
	private PropertyPanel properPanel;
	private OwnOfferPanel ownOffPanel;
	private RentedOfferPanel rentedOffPanel;
	private BookedOfferPanel bookedOffPanel;
	private SeeCommentPanel seeCommentPanel;
	private RegisterPropertyPanel registerProperPanel;
	private CreateShortPanel createShortPanel;
	private CreateLongPanel createLongPanel;
	private CommentOfferPanel commentOffPanel;
	private CommentCommentaryPanel commCommPanel;
	private ManagerStartPanel managerStartPanel;
	private ManagerListOffersPanel manListOffersPanel;
	private ManagerListUsersPanel manListUsersPanel;
	private ManagerOfferPanel manOfferPanel;
	private ManagerUserPanel manUserPanel;
	private EditPanel editPanel;
	private SearchPanel searchPanel;
	private BlockedUserPanel blockedUserPanel;
	private SeeOfferPanel seeOffPanel;
	
	/**
	 * This constructor builds up the JFram next to all the JPanels and Controllers
	 * @param filename Name of the file where all the data is going to be stored
	 * @param app Application (logic part of the programming assignment)=
	 */
	public WindowApp(Application app, String filename){
		super("Photohouse");
		
		this.setLayout(new CardLayout());
		
		/* Panels */
		startPanel = new StartPanel();
		loginPanel = new LoginPanel();
		offerPanel = new OfferPanel();
		properPanel = new PropertyPanel();
		ownOffPanel = new OwnOfferPanel();
		rentedOffPanel = new RentedOfferPanel();
		bookedOffPanel = new BookedOfferPanel();
		seeCommentPanel = new SeeCommentPanel();
		registerProperPanel = new RegisterPropertyPanel();
		createShortPanel = new CreateShortPanel(app);
		createLongPanel = new CreateLongPanel(app);
		commentOffPanel = new CommentOfferPanel();
		commCommPanel = new CommentCommentaryPanel();
		managerStartPanel = new ManagerStartPanel();
		manListOffersPanel = new ManagerListOffersPanel();
		manListUsersPanel = new ManagerListUsersPanel(app);
		manOfferPanel = new ManagerOfferPanel();
		manUserPanel = new ManagerUserPanel();
		editPanel = new EditPanel();
		searchPanel = new SearchPanel();
		blockedUserPanel = new BlockedUserPanel();
		seeOffPanel = new SeeOfferPanel();
		
		/* Adding Panels to the MAP */
		panels.put("LOGIN PANEL", loginPanel);
		panels.put("START PANEL", startPanel);
		panels.put("OFFER PANEL", offerPanel);
		panels.put("PROPERTY PANEL", properPanel);
		panels.put("OWN OFFER PANEL", ownOffPanel);
		panels.put("RENTED OFFER PANEL", rentedOffPanel);
		panels.put("BOOKED OFFER PANEL", bookedOffPanel);
		panels.put("SEE COMMENT PANEL", seeCommentPanel);
		panels.put("REGISTER PROPERTY PANEL", registerProperPanel);
		panels.put("CREATE SHORT PANEL", createShortPanel);
		panels.put("CREATE LONG PANEL", createLongPanel);
		panels.put("COMMENT OFFER PANEL", commentOffPanel);
		panels.put("COMMENT COMMENTARY PANEL", commCommPanel);
		panels.put("MANAGER START PANEL", managerStartPanel);
		panels.put("MANAGER LIST OFFERS PANEL", manListOffersPanel);
		panels.put("MANAGER LIST USERS PANEL", manListUsersPanel);
		panels.put("MANAGER OFFER PANEL", manOfferPanel);
		panels.put("MANAGER USER PANEL", manUserPanel);
		panels.put("EDIT PANEL", editPanel);
		panels.put("SEARCH PANEL", searchPanel);
		panels.put("BLOCKED USER PANEL", blockedUserPanel);
		panels.put("SEE OFFER PANEL", seeOffPanel);
		
		
		/* Adding Panels to the CONTAINER */
		this.getContentPane().add(this.loginPanel, "LOGIN PANEL");
		this.getContentPane().add(this.startPanel, "START PANEL");
		this.getContentPane().add(this.offerPanel, "OFFER PANEL");
		this.getContentPane().add(this.properPanel, "PROPERTY PANEL");
		this.getContentPane().add(this.ownOffPanel, "OWN OFFER PANEL");
		this.getContentPane().add(this.rentedOffPanel, "RENTED OFFER PANEL");
		this.getContentPane().add(this.bookedOffPanel, "BOOKED OFFER PANEL");
		this.getContentPane().add(this.seeCommentPanel, "SEE COMMENT PANEL");
		this.getContentPane().add(this.registerProperPanel, "REGISTER PROPERTY PANEL");
		this.getContentPane().add(this.createShortPanel, "CREATE SHORT PANEL");
		this.getContentPane().add(this.createLongPanel, "CREATE LONG PANEL");
		this.getContentPane().add(this.commentOffPanel, "COMMENT OFFER PANEL");
		this.getContentPane().add(this.commCommPanel, "COMMENT COMMENTARY PANEL");
		this.getContentPane().add(this.managerStartPanel, "MANAGER START PANEL");
		this.getContentPane().add(this.manListOffersPanel, "MANAGER LIST OFFERS PANEL");
		this.getContentPane().add(this.manListUsersPanel, "MANAGER LIST USERS PANEL");
		this.getContentPane().add(this.manOfferPanel, "MANAGER OFFER PANEL");
		this.getContentPane().add(this.manUserPanel, "MANAGER USER PANEL");
		this.getContentPane().add(this.editPanel, "EDIT PANEL");
		this.getContentPane().add(this.searchPanel, "SEARCH PANEL");
		this.getContentPane().add(this.blockedUserPanel, "BLOCKED USER PANEL");
		this.getContentPane().add(this.seeOffPanel, "SEE OFFER PANEL");
		
		/* Setting CONTROLLERS */
		ManagerListUsersController manListUsersControl = new ManagerListUsersController(this.getContentPane(), panels, app);
		ManagerListOffersController manListOffersControl = new ManagerListOffersController(this.getContentPane(), panels, app);
		controllers.put("MANAGER LIST USERS CONTROLLER", manListUsersControl);
		controllers.put("MANAGER LIST OFFERS CONTROLLER", manListOffersControl);
		ManagerUserController manUserControl = new ManagerUserController(this.getContentPane(), panels, controllers, app);
		ManagerOfferController manOffControl = new ManagerOfferController(this.getContentPane(), panels, controllers, app);
		controllers.put("MANAGER USER CONTROLLER", manUserControl);
		controllers.put("MANAGER OFFER CONTROLLER", manOffControl);
		ManagerStartController managerStartControl = new ManagerStartController(this.getContentPane(), panels, controllers, filename, app);
		CreateShortController createShortControl = new CreateShortController(this.getContentPane(), panels, app);
		CreateLongController createLongControl = new CreateLongController(this.getContentPane(), panels, app);
		controllers.put("MANAGER START CONTROLLER", managerStartControl);
		controllers.put("CREATE SHORT CONTROLLER", createShortControl);
		controllers.put("CREATE LONG CONTROLLER", createLongControl);
		OwnOfferController ownOffControl = new OwnOfferController(this.getContentPane(), panels, controllers, app);
		controllers.put("OWN OFFER CONTROLLER", ownOffControl);
		EditController editControl = new EditController(this.getContentPane(), panels, controllers, app);
		PropertyController properControl = new PropertyController(this.getContentPane(), app);
		RentedOfferController rentedOffControl = new RentedOfferController(this.getContentPane(), panels, app);
		BookedOfferController bookedOffControl = new BookedOfferController(this.getContentPane(), panels, app);
		controllers.put("EDIT OFFER CONTROLLER", editControl);
		controllers.put("PROPERTY CONTROLLER", properControl);
		controllers.put("RENTED OFFER CONTROLLER", rentedOffControl);
		controllers.put("BOOKED OFFER CONTROLLER", bookedOffControl);
		StartController startControl = new StartController(this.getContentPane(), panels, controllers, filename, app);
		controllers.put("START CONTROLLER", startControl);
		LoginController loginControl = new LoginController(this.getContentPane(), panels, controllers, filename, app);
		SeeCommentController seeCommentControl = new SeeCommentController(this.getContentPane(), panels, controllers, app);
		controllers.put("SEE COMMENT CONTROLLER", seeCommentControl);
		controllers.put("LOGIN CONTROLLER", loginControl);
		OfferController offerControl = new OfferController(this.getContentPane(), panels, controllers, app);
		RegisterPropertyController registerProperControl = new RegisterPropertyController(this.getContentPane(), panels, controllers, app);
		controllers.put("OFFER CONTROLLER", offerControl);
		CommentOfferController commentOffControl = new CommentOfferController(this.getContentPane(), panels, app);
		controllers.put("COMMENT OFFER CONTROLLER", commentOffControl);
		CommentCommentaryController commentCommentaryControl = new CommentCommentaryController(this.getContentPane(), panels, controllers, app);
		controllers.put("COMMENT COMMENTARY CONTROLLER", commentCommentaryControl);
		SearchController searchControl = new SearchController(this.getContentPane(), panels, controllers, app);
		controllers.put("SEARCH CONTROLLER", searchControl);
		BlockedUserController blockedUserControl = new BlockedUserController(this.getContentPane(), panels, controllers, filename, app);
		SeeOfferController seeOffControl = new SeeOfferController(this.getContentPane(), panels, controllers, app);
		controllers.put("SEE OFFER CONTROLLER", seeOffControl);
		loginPanel.setController(loginControl);
		startPanel.setController(startControl);
		offerPanel.setController(offerControl);
		properPanel.setController(properControl);
		rentedOffPanel.setController(rentedOffControl);
		bookedOffPanel.setController(bookedOffControl);
		ownOffPanel.setController(ownOffControl);
		seeCommentPanel.setController(seeCommentControl);
		registerProperPanel.setController(registerProperControl);
		createShortPanel.setController(createShortControl);
		createLongPanel.setController(createLongControl);
		commentOffPanel.setController(commentOffControl);
		commCommPanel.setController(commentCommentaryControl);
		managerStartPanel.setController(managerStartControl);
		manListOffersPanel.setController(manListOffersControl);
		manListUsersPanel.setController(manListUsersControl);
		manOfferPanel.setController(manOffControl);
		manUserPanel.setController(manUserControl);
		editPanel.setController(editControl);
		searchPanel.setController(searchControl, searchControl);
		blockedUserPanel.setController(blockedUserControl);
		seeOffPanel.setController(seeOffControl);
		
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setVisible(true);
		this.setSize(800, 600);
	}

}
