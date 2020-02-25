package View;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.awt.event.ItemListener;

import javax.swing.*;

import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can search and filter through offers
 */
public class SearchPanel extends JPanel{
	/* Buttons */
	private JButton goBackButton;
	private JButton searchButton;
	/* JRadioButtons */
	private JRadioButton offerType[] = new JRadioButton[3];
	private JRadioButton rating[] = new JRadioButton[6];
	private JCheckBox offerStatus[] = new JCheckBox[3];
	/* JLabels */
	private JLabel type;
	private JLabel rate;
	private JLabel status;
	private JLabel minPrice;
	private JLabel maxPrice;
	private JLabel pc;
	private JLabel iniDay;
	private JLabel iniMonth;
	private JLabel iniYear;
	private JLabel finDay;
	private JLabel finMonth;
	private JLabel finYear;
	private JLabel nDays;
	private JLabel nMonths;
	private JLabel nYears;
	/* JTextFields */
	private JTextField minPriceField;
	private JTextField maxPriceField;
	private JTextField pcField;
	private JTextField iniDayField;
	private JTextField iniMonthField;
	private JTextField iniYearField;
	private JTextField finDayField;
	private JTextField finMonthField;
	private JTextField finYearField;
	private JTextField nDaysField;
	private JTextField nMonthsField;
	private JTextField nYearsField;

	/**
	 * This constructor creates a new SearchPanel.
	 * It help helped by 3 privated methods that just creates different smaller panels
	 */
	public SearchPanel() {
		JPanel bot = buildBotPanel();
		JPanel mid = buildMidPanel();
		JPanel top = buildTopPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, bot);
		this.add(BorderLayout.SOUTH, top);
		this.add(BorderLayout.CENTER, mid);
	}
	
	/**
	 * Sets up all the buttons and fields at its initial state
	 * @param user Logged user
	 */
	public void prepareIniButtons(RegisteredUser user) {
		goBackButton.setVisible(true);
		searchButton.setVisible(true);
		type.setVisible(true);
		for(JRadioButton rad: offerType) {
			rad.setVisible(true);
		}
		pc.setVisible(true);
		pcField.setVisible(true);
		iniDay.setVisible(false);
		iniDayField.setVisible(false);
		iniMonth.setVisible(false);
		iniMonthField.setVisible(false);
		iniYear.setVisible(false);
		iniYearField.setVisible(false);
		
		finDay.setVisible(false);
		finDayField.setVisible(false);
		finMonth.setVisible(false);
		finMonthField.setVisible(false);
		finYear.setVisible(false);
		finYearField.setVisible(false);
		
		nDays.setVisible(false);
		nDaysField.setVisible(false);
		nMonths.setVisible(false);
		nMonthsField.setVisible(false);
		nYears.setVisible(false);
		nYearsField.setVisible(false);
		
		if(user == null) {
			minPrice.setVisible(false);
			minPriceField.setVisible(false);
			maxPrice.setVisible(false);
			maxPriceField.setVisible(false);
			rate.setVisible(false);
			for(JRadioButton rad: rating) {
				rad.setVisible(false);
			}
			status.setVisible(false);
			for(JCheckBox rad: offerStatus) {
				rad.setVisible(false);
			}
		}
		else {
			minPrice.setVisible(true);
			minPriceField.setVisible(true);
			maxPrice.setVisible(true);
			maxPriceField.setVisible(true);
			rate.setVisible(true);
			for(JRadioButton rad: rating) {
				rad.setVisible(true);
			}
			status.setVisible(true);
			for(JCheckBox rad: offerStatus) {
				rad.setVisible(true);
			}
		}
	}
	
	/**
	 * Sets up all the buttons and fields if short offers are selected
	 * @param user Logged user
	 */
	public void prepareShortButtons(RegisteredUser user) {
		goBackButton.setVisible(true);
		searchButton.setVisible(true);
		type.setVisible(true);
		for(JRadioButton rad: offerType) {
			rad.setVisible(true);
		}
		pc.setVisible(true);
		pcField.setVisible(true);
		iniDay.setVisible(true);
		iniDayField.setVisible(true);
		iniMonth.setVisible(true);
		iniMonthField.setVisible(true);
		iniYear.setVisible(true);
		iniYearField.setVisible(true);
		
		finDay.setVisible(true);
		finDayField.setVisible(true);
		finMonth.setVisible(true);
		finMonthField.setVisible(true);
		finYear.setVisible(true);
		finYearField.setVisible(true);
		
		nDays.setVisible(false);
		nDaysField.setVisible(false);
		nMonths.setVisible(false);
		nMonthsField.setVisible(false);
		nYears.setVisible(false);
		nYearsField.setVisible(false);
		
		if(user == null) {
			minPrice.setVisible(false);
			minPriceField.setVisible(false);
			maxPrice.setVisible(false);
			maxPriceField.setVisible(false);
			rate.setVisible(false);
			for(JRadioButton rad: rating) {
				rad.setVisible(false);
			}
			status.setVisible(false);
			for(JCheckBox rad: offerStatus) {
				rad.setVisible(false);
			}
		}
		else {
			minPrice.setVisible(true);
			minPriceField.setVisible(true);
			maxPrice.setVisible(true);
			maxPriceField.setVisible(true);
			rate.setVisible(true);
			for(JRadioButton rad: rating) {
				rad.setVisible(true);
			}
			status.setVisible(true);
			for(JCheckBox rad: offerStatus) {
				rad.setVisible(true);
			}
		}
	}
	
	/**
	 * Sets up all the buttons and fields if long offers are selected
	 * @param user Logged user
	 */
	public void prepareLongButtons(RegisteredUser user) {
		goBackButton.setVisible(true);
		searchButton.setVisible(true);
		type.setVisible(true);
		for(JRadioButton rad: offerType) {
			rad.setVisible(true);
		}
		pc.setVisible(true);
		pcField.setVisible(true);
		iniDay.setVisible(true);
		iniDayField.setVisible(true);
		iniMonth.setVisible(true);
		iniMonthField.setVisible(true);
		iniYear.setVisible(true);
		iniYearField.setVisible(true);
		
		finDay.setVisible(false);
		finDayField.setVisible(false);
		finMonth.setVisible(false);
		finMonthField.setVisible(false);
		finYear.setVisible(false);
		finYearField.setVisible(false);
		
		nDays.setVisible(true);
		nDaysField.setVisible(true);
		nMonths.setVisible(true);
		nMonthsField.setVisible(true);
		nYears.setVisible(true);
		nYearsField.setVisible(true);
		
		if(user == null) {
			minPrice.setVisible(false);
			minPriceField.setVisible(false);
			maxPrice.setVisible(false);
			maxPriceField.setVisible(false);
			rate.setVisible(false);
			for(JRadioButton rad: rating) {
				rad.setVisible(false);
			}
			status.setVisible(false);
			for(JCheckBox rad: offerStatus) {
				rad.setVisible(false);
			}
		}
		else {
			minPrice.setVisible(true);
			minPriceField.setVisible(true);
			maxPrice.setVisible(true);
			maxPriceField.setVisible(true);
			rate.setVisible(true);
			for(JRadioButton rad: rating) {
				rad.setVisible(true);
			}
			status.setVisible(true);
			for(JCheckBox rad: offerStatus) {
				rad.setVisible(true);
			}
		}
	}
	
	/**
	 * Resets the buttons and fields initial status
	 */
	public void resetOptions() {
		rating[0].setSelected(true);
		for(JCheckBox rad: offerStatus) {
			rad.setSelected(false);
		}
		offerType[2].setSelected(true);
	}
	
	/**
	 * It clears all the JTextFields
	 */
	public void clean() {
		this.pcField.setText("");
		this.minPriceField.setText("");
		this.maxPriceField.setText("");
		this.iniDayField.setText("");
		this.iniMonthField.setText("");
		this.iniYearField.setText("");
		this.finDayField.setText("");
		this.finMonthField.setText("");
		this.finYearField.setText("");
		this.nDaysField.setText("");
		this.nMonthsField.setText("");
		this.nYearsField.setText("");
		
	}
	
	public String getSelectedOfferTypeText() {
		for(JRadioButton rad: offerType) {
			if(rad.isSelected()) {
				return rad.getText();
			}
		}
		return null;
	}
	
	public String getSelectedRatingText() {
		for(JRadioButton rad: rating) {
			if(rad.isSelected()) {
				return rad.getText();
			}
		}
		return null;
	}
	
	public String getMinPriceText() {
		return this.minPriceField.getText();
	}
	
	public String getMaxPriceText() {
		return this.maxPriceField.getText();
	}
	
	public String getPCText() {
		return this.pcField.getText();
	}
	
	public String getIniDayText() {
		return this.iniDayField.getText();
	}
	
	public String getIniMonthText() {
		return this.iniMonthField.getText();
	}
	
	public String getIniYearText() {
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
	
	public String getNDaysText() {
		return this.nDaysField.getText();
	}
	
	public String getNMonthsText() {
		return this.nMonthsField.getText();
	}
	
	public String getNYearsText() {
		return this.nYearsField.getText();
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 * @param il ItemListener
	 */
	public void setController(ActionListener al, ItemListener il) {
		goBackButton.addActionListener(al);
		searchButton.addActionListener(al);
		for(JRadioButton rad: offerType) {
			rad.addActionListener(al);
		}
		for(JRadioButton rad: rating) {
			rad.addActionListener(al);
		}
		for(JCheckBox rad: offerStatus) {
			rad.addItemListener(il);
		}
	}
	
	private JPanel buildMidPanel() {
		JPanel mid = new JPanel();
		mid.setLayout(new GridLayout(12,1));
		
		pc = new JLabel("Postal code");
		pc.setHorizontalAlignment(JLabel.CENTER);
		pcField = new JTextField(100);
		pcField.setHorizontalAlignment(JTextField.CENTER);
		
		minPrice = new JLabel("Minimum price");
		minPrice.setHorizontalAlignment(JLabel.CENTER);
		minPriceField = new JTextField(100);
		minPriceField.setHorizontalAlignment(JTextField.CENTER);
		
		maxPrice = new JLabel("Maximum price");
		maxPrice.setHorizontalAlignment(JLabel.CENTER);
		maxPriceField = new JTextField(100);
		maxPriceField.setHorizontalAlignment(JTextField.CENTER);
		
		iniDay = new JLabel("Day initial date");
		iniDay.setHorizontalAlignment(JLabel.CENTER);
		iniDayField = new JTextField(100);
		iniDayField.setHorizontalAlignment(JTextField.CENTER);
		
		iniMonth = new JLabel("Month initial date");
		iniMonth.setHorizontalAlignment(JLabel.CENTER);
		iniMonthField = new JTextField(100);
		iniMonthField.setHorizontalAlignment(JTextField.CENTER);
		
		iniYear = new JLabel("Year initial date");
		iniYear.setHorizontalAlignment(JLabel.CENTER);
		iniYearField = new JTextField(100);
		iniYearField.setHorizontalAlignment(JTextField.CENTER);
		
		finDay = new JLabel("Day final date");
		finDay.setHorizontalAlignment(JLabel.CENTER);
		finDayField = new JTextField(100);
		finDayField.setHorizontalAlignment(JTextField.CENTER);
		
		finMonth = new JLabel("Month final date");
		finMonth.setHorizontalAlignment(JLabel.CENTER);
		finMonthField = new JTextField(100);
		finMonthField.setHorizontalAlignment(JTextField.CENTER);
		
		finYear = new JLabel("Year final date");
		finYear.setHorizontalAlignment(JLabel.CENTER);
		finYearField = new JTextField(100);
		finYearField.setHorizontalAlignment(JTextField.CENTER);
		
		nDays = new JLabel("Minimum period (days)");
		nDays.setHorizontalAlignment(JLabel.CENTER);
		nDaysField = new JTextField(100);
		nDaysField.setHorizontalAlignment(JTextField.CENTER);
		
		nMonths = new JLabel("Minimum period (months)");
		nMonths.setHorizontalAlignment(JLabel.CENTER);
		nMonthsField = new JTextField(100);
		nMonthsField.setHorizontalAlignment(JTextField.CENTER);
		
		nYears = new JLabel("Minimum period (years)");
		nYears.setHorizontalAlignment(JLabel.CENTER);
		nYearsField = new JTextField(100);
		nYearsField.setHorizontalAlignment(JTextField.CENTER);
		
		mid.add(pc);
		mid.add(pcField);
		mid.add(minPrice);
		mid.add(minPriceField);
		mid.add(maxPrice);
		mid.add(maxPriceField);
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
		mid.add(nDays);
		mid.add(nDaysField);
		mid.add(nMonths);
		mid.add(nMonthsField);
		mid.add(nYears);
		mid.add(nYearsField);
		
		return mid;
	}
	
	private JPanel buildTopPanel() {
		JPanel mid = new JPanel();
		mid.setLayout(new BorderLayout());
		
		JPanel bot1 = buildSubTop1();
		JPanel bot2 = buildSubTop2();
		JPanel bot3 = buildSubTop3();
		
		mid.add(BorderLayout.NORTH, bot1);
		mid.add(BorderLayout.CENTER, bot2);
		mid.add(BorderLayout.SOUTH, bot3);
		
		return mid;
	}
	
	private JPanel buildBotPanel() {
		JPanel top = new JPanel();
		this.goBackButton = new JButton("Go Back");
		this.searchButton = new JButton("Search");
		top.add(goBackButton);
		top.add(searchButton);
		return top;
	}
	
	private JPanel buildSubTop1() {
		JPanel mid = new JPanel();
		mid.setLayout(new GridLayout(1, 0));
		
		type = new JLabel("TYPE OF STAY FILTER ->");
		type.setHorizontalAlignment(JLabel.CENTER);
		mid.add(type);
		offerType[0] = new JRadioButton("Short stay");
		offerType[0].setHorizontalAlignment(JRadioButton.CENTER);
		offerType[1] = new JRadioButton("Long stay");
		offerType[1].setHorizontalAlignment(JRadioButton.CENTER);
		offerType[2] = new JRadioButton("Both");
		offerType[2].setHorizontalAlignment(JRadioButton.CENTER);
		offerType[2].setSelected(true);
		ButtonGroup typeGroup = new ButtonGroup();
		typeGroup.add(offerType[0]);
		typeGroup.add(offerType[1]);
		typeGroup.add(offerType[2]);
		mid.add(offerType[0]);
		mid.add(offerType[1]);
		mid.add(offerType[2]);
		
		return mid;
	}
	
	private JPanel buildSubTop2() {
		JPanel mid = new JPanel();
		mid.setLayout(new GridLayout(1, 0));
		
		rate = new JLabel("RATING FILTER ->");
		rate.setHorizontalAlignment(JLabel.CENTER);
		mid.add(rate);
		for(int i=0; i<6; i++) {
			rating[i] = new JRadioButton(Integer.toString(i));
			rating[i].setHorizontalAlignment(JRadioButton.CENTER);
		}
		rating[0].setSelected(true);
		ButtonGroup rateGroup = new ButtonGroup();
		for(JRadioButton rad: rating) {
			rateGroup.add(rad);
			mid.add(rad);
		}
		return mid;
	}
	
	private JPanel buildSubTop3() {
		JPanel mid = new JPanel();
		mid.setLayout(new GridLayout(1, 0));
		
		status = new JLabel("STATUS FILTER ->");
		status.setHorizontalAlignment(JLabel.CENTER);
		mid.add(status);
		offerStatus[0] = new JCheckBox("Free");
		offerStatus[0].setHorizontalAlignment(JCheckBox.CENTER);
		offerStatus[1] = new JCheckBox("Booked");
		offerStatus[1].setHorizontalAlignment(JCheckBox.CENTER);
		offerStatus[2] = new JCheckBox("Rented");
		offerStatus[2].setHorizontalAlignment(JCheckBox.CENTER);
		for(JCheckBox rad: offerStatus) {
			mid.add(rad);
		}
		return mid;
	}
}
