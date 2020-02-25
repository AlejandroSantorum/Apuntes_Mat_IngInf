package View;

import java.awt.*;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.*;
import javax.swing.event.ListSelectionListener;

import padsof.*;
import Exceptions.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can create
 *  a new long stay type offer
 */
public class CreateLongPanel extends JPanel{
	/* Buttons */
	private JButton createButton;
	private JButton goBackButton;
	/* Text Fields */
	private JTextField priceField;
	private JTextField iniDayField;
	private JTextField iniMonthField;
	private JTextField iniYearField;
	private JTextField daysField;
	private JTextField monthsField;
	private JTextField yearsField;
	/* Labels */
	private JLabel price;
	private JLabel iniDay;
	private JLabel iniMonth;
	private JLabel iniYear;
	private JLabel days;
	private JLabel months;
	private JLabel years;
	/* ComboBox */
	private JPanel apartmentsPanel;
	/* Auxiliary */
	Application app;
	
	/**
	 * This constructor creates a new CreateLongPanel.
	 * It help helped by 2 privated methods that just creates different smaller panels
	 * @param app The application (Model)
	 */
	public CreateLongPanel(Application app) {
		this.app = app;
		
		JPanel top = buildTopPanel();
		JPanel down = buildDownPanel();
		
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
		createButton.addActionListener(al);
	}
	
	public String getPriceText() {
		return this.priceField.getText();
	}
	
	public String getIniDayText() {
		return this.iniDayField.getText();
	}
	
	public String getIniMonthText() {
		return this.iniMonthField.getText();
	}
	
	public String getiniYearText() {
		return this.iniYearField.getText();
	}
	
	public String getDaysText() {
		return this.daysField.getText();
	}
	
	public String getMonthsText() {
		return this.monthsField.getText();
	}
	
	public String getYearsText() {
		return this.yearsField.getText();
	}
	
	/**
	 * It cleans the JTextFields
	 */
	public void clean() {
		this.priceField.setText("");
		this.iniDayField.setText("");
		this.iniMonthField.setText("");
		this.iniYearField.setText("");
		this.daysField.setText("");
		this.monthsField.setText("");
		this.yearsField.setText("");
	}
	
	/**
	 * Sets up the list of apartments owned by the logged user
	 * @param lsl ListSelectionListener
	 * @throws UserException they user might have not got apartments becuase of his type
	 */
	public void prepareApartments(ListSelectionListener lsl) throws UserException {
		if(apartmentsPanel!=null) {
			this.remove(apartmentsPanel);
		}
		JPanel apartments = new JPanel();
		DefaultListModel<Apartment> list = new DefaultListModel<Apartment>();
		ArrayList<Apartment> userAparts = app.getLoggedUser().getUserApartments();
		for(Apartment a: userAparts) {
			list.addElement(a);
		}
		
		JList<Apartment> apartList = new JList<Apartment>(list);
		apartList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		JScrollPane scroll = new JScrollPane(apartList);
		
		apartments.add(scroll);
		apartList.addListSelectionListener(lsl);
		
		apartmentsPanel = apartments;
		this.add(BorderLayout.CENTER, apartments);
	}
	
	private JPanel buildTopPanel() {
		JPanel topPanel = new JPanel();
		this.goBackButton = new JButton("Go Back");
		this.createButton = new JButton("Apply");
		topPanel.add(goBackButton);
		topPanel.add(createButton);
		return topPanel;
	}
	
	
	private JPanel buildDownPanel() {
		JPanel downPanel = new JPanel();
		downPanel.setLayout(new GridLayout(7,0));
		
		price = new JLabel("Price");
		price.setHorizontalAlignment(JLabel.CENTER);
		priceField = new JTextField(100);
		priceField.setHorizontalAlignment(JTextField.CENTER);
		
		iniDay = new JLabel("Initial day");
		iniDay.setHorizontalAlignment(JLabel.CENTER);
		iniDayField = new JTextField(100);
		iniDayField.setHorizontalAlignment(JTextField.CENTER);
		
		iniMonth = new JLabel("Initial month");
		iniMonth.setHorizontalAlignment(JLabel.CENTER);
		iniMonthField = new JTextField(100);
		iniMonthField.setHorizontalAlignment(JTextField.CENTER);
		
		iniYear = new JLabel("Initial year");
		iniYear.setHorizontalAlignment(JLabel.CENTER);
		iniYearField = new JTextField(100);
		iniYearField.setHorizontalAlignment(JTextField.CENTER);
		
		days = new JLabel("Minimum period (days)");
		days.setHorizontalAlignment(JLabel.CENTER);
		daysField = new JTextField(100);
		daysField.setHorizontalAlignment(JTextField.CENTER);
		
		months = new JLabel("Minimum period (months)");
		months.setHorizontalAlignment(JLabel.CENTER);
		monthsField = new JTextField(100);
		monthsField.setHorizontalAlignment(JTextField.CENTER);
		
		years = new JLabel("Minimum period (years)");
		years.setHorizontalAlignment(JLabel.CENTER);
		yearsField = new JTextField(100);
		yearsField.setHorizontalAlignment(JTextField.CENTER);
		
		downPanel.add(price);
		downPanel.add(priceField);
		downPanel.add(iniDay);
		downPanel.add(iniDayField);
		downPanel.add(iniMonth);
		downPanel.add(iniMonthField);
		downPanel.add(iniYear);
		downPanel.add(iniYearField);
		downPanel.add(days);
		downPanel.add(daysField);
		downPanel.add(months);
		downPanel.add(monthsField);
		downPanel.add(years);
		downPanel.add(yearsField);
		
		return downPanel;	
	}

}
