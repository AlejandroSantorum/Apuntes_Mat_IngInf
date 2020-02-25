package View;

import java.awt.*;
import java.awt.event.ActionListener;
import javax.swing.*;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can edit a offer that
 * is still not evaluated by the manager
 */
public class EditPanel extends JPanel{
	private JButton goBackButton;
	private JButton editButton;
	/* Text Fields */
	private JTextField priceField;
	private JTextField iniDayField;
	private JTextField iniMonthField;
	private JTextField iniYearField;
	private JTextField finDayField;
	private JTextField finMonthField;
	private JTextField finYearField;
	private JTextField daysField;
	private JTextField monthsField;
	private JTextField yearsField;
	/* Labels */
	private JLabel price;
	private JLabel iniDay;
	private JLabel iniMonth;
	private JLabel iniYear;
	private JLabel finDay;
	private JLabel finMonth;
	private JLabel finYear;
	private JLabel days;
	private JLabel months;
	private JLabel years;

	/**
	 * This constructor creates a new EditPanel.
	 * It help helped by 3 privated methods that just creates different smaller panels
	 */
	public EditPanel() {
		JPanel top = buildTopPanel();
		JPanel mid = buildMidPanel();
		JPanel bot = buildDownPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, top);
		this.add(BorderLayout.CENTER, mid);
		this.add(BorderLayout.SOUTH, bot);
	}
	
	/**
	 * It sets up the buttons deppending on the user type
	 * @param ot logged user type
	 */
	public void prepareButtons(OfferType ot) {
		goBackButton.setVisible(true);
		editButton.setVisible(true);
		price.setVisible(true);
		priceField.setVisible(true);
		iniDay.setVisible(true);
		iniDayField.setVisible(true);
		iniMonth.setVisible(true);
		iniMonthField.setVisible(true);
		iniYear.setVisible(true);
		iniYearField.setVisible(true);
		if(ot == OfferType.SHORT) {
			finDay.setVisible(true);
			finDayField.setVisible(true);
			finMonth.setVisible(true);
			finMonthField.setVisible(true);
			finYear.setVisible(true);
			finYearField.setVisible(true);
			days.setVisible(false);
			daysField.setVisible(false);
			months.setVisible(false);
			monthsField.setVisible(false);
			years.setVisible(false);
			yearsField.setVisible(false);
		}
		else if(ot == OfferType.LONG) {
			days.setVisible(true);
			daysField.setVisible(true);
			months.setVisible(true);
			monthsField.setVisible(true);
			years.setVisible(true);
			yearsField.setVisible(true);
			finDay.setVisible(false);
			finDayField.setVisible(false);
			finMonth.setVisible(false);
			finMonthField.setVisible(false);
			finYear.setVisible(false);
			finYearField.setVisible(false);
		}
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		goBackButton.addActionListener(al);
		editButton.addActionListener(al);
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
	
	public String getFinDayText() {
		return this.finDayField.getText();
	}
	
	public String getFinMonthText() {
		return this.finMonthField.getText();
	}
	
	public String getFinYearText() {
		return this.finYearField.getText();
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
		this.finDayField.setText("");
		this.finMonthField.setText("");
		this.finYearField.setText("");
		this.daysField.setText("");
		this.monthsField.setText("");
		this.yearsField.setText("");
	}
	
	private JPanel buildTopPanel() {
		JPanel topPanel = new JPanel();
		this.goBackButton = new JButton("Go Back");
		topPanel.add(goBackButton);
		return topPanel;
	}
	
	private JPanel buildMidPanel() {
		JPanel mid = new JPanel();
		mid.setLayout(new GridLayout(10,1));
		
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
		
		finDay = new JLabel("Final day");
		finDay.setHorizontalAlignment(JLabel.CENTER);
		finDayField = new JTextField(100);
		finDayField.setHorizontalAlignment(JTextField.CENTER);
		
		finMonth = new JLabel("Final month");
		finMonth.setHorizontalAlignment(JLabel.CENTER);
		finMonthField = new JTextField(100);
		finMonthField.setHorizontalAlignment(JTextField.CENTER);
		
		finYear = new JLabel("Final year");
		finYear.setHorizontalAlignment(JLabel.CENTER);
		finYearField = new JTextField(100);
		finYearField.setHorizontalAlignment(JTextField.CENTER);
		
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
		
		mid.add(price);
		mid.add(priceField);
		mid.add(iniDay);
		mid.add(iniDayField);
		mid.add(iniMonth);
		mid.add(iniMonthField);
		mid.add(iniYear);
		mid.add(iniYearField);
		mid.add(finDay);
		mid.add(finDayField);
		mid.add(finMonth);
		mid.add(finMonthField);
		mid.add(finYear);
		mid.add(finYearField);
		mid.add(days);
		mid.add(daysField);
		mid.add(months);
		mid.add(monthsField);
		mid.add(years);
		mid.add(yearsField);
		
		return mid;
	}
	
	private JPanel buildDownPanel() {
		JPanel downPanel = new JPanel();
		this.editButton = new JButton("Edit Offer");
		downPanel.add(editButton);
		return downPanel;
	}
}
