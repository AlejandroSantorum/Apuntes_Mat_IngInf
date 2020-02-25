package Controllers;

import java.awt.CardLayout;
import java.awt.Container;
import java.awt.event.*;
import java.util.*;

import javax.swing.JCheckBox;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import Filters.*;
import View.*;
import padsof.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the controller that manages SearchPanel.
 * It implements ActionListener and ListSelectionListener
 */
public class SearchController implements ActionListener, ItemListener{
	private Application app;
	private Container window;
	private CardLayout card;
	private HashMap<String, JPanel> panels;
	private HashMap<String, ActionListener> controllers;
	private HashSet<Status> status = new HashSet<Status>();
	
	/**
	 * This constructor creates a new SearchController.
	 * It just stores all the information needed to control SearchPanel
	 * @param window Container of the application
	 * @param panels Map of String, JPanel. The string identifies the panel
	 * @param controllers Map of String, ActionListener. The string identifies de controller
	 * @param app The application (Model) run.
	 */
	public SearchController(Container window, HashMap<String, JPanel> panels, HashMap<String, ActionListener> controllers, Application app) {
		this.app = app;
		this.window = window;
		this.card = (CardLayout) window.getLayout();
		this.panels = panels;
		this.controllers = controllers;
	}
	
	@Override
	public void actionPerformed(ActionEvent arg) {
		if(arg.getActionCommand().equals("Go Back")) {
			card.show(window, "START PANEL");
			((SearchPanel)panels.get("SEARCH PANEL")).resetOptions();
			((SearchPanel)panels.get("SEARCH PANEL")).clean();
		}
		else if(arg.getActionCommand().equals("Short stay")) {
			((SearchPanel)panels.get("SEARCH PANEL")).prepareShortButtons(app.getLoggedUser());
		}
		else if(arg.getActionCommand().equals("Long stay")) {
			((SearchPanel)panels.get("SEARCH PANEL")).prepareLongButtons(app.getLoggedUser());
		}
		else if(arg.getActionCommand().equals("Both")) {
			((SearchPanel)panels.get("SEARCH PANEL")).prepareIniButtons(app.getLoggedUser());
		}
		else if(arg.getActionCommand().equals("Search")) {
			ArrayList<Filter> filters = new ArrayList<Filter>();
			String offerType = ((SearchPanel)panels.get("SEARCH PANEL")).getSelectedOfferTypeText();
			
			if(app.getLoggedUser() == null) {
				if(offerType.equals("Short stay")) {
					filters.add(new TypeStayFilter(OfferType.SHORT));
					String pc = ((SearchPanel)panels.get("SEARCH PANEL")).getPCText();
					if(!pc.equals("") && !pc.equals(" ")) {
						try {
							filters.add(new PostalCodeFilter(Integer.parseInt(pc)));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					String iniDay = ((SearchPanel)panels.get("SEARCH PANEL")).getIniDayText();
					String iniMonth = ((SearchPanel)panels.get("SEARCH PANEL")).getIniMonthText();
					String iniYear = ((SearchPanel)panels.get("SEARCH PANEL")).getIniYearText();
					String finDay = ((SearchPanel)panels.get("SEARCH PANEL")).getFinDayText();
					String finMonth = ((SearchPanel)panels.get("SEARCH PANEL")).getFinMonthText();
					String finYear = ((SearchPanel)panels.get("SEARCH PANEL")).getFinYearText();
					Boolean bool1 = !iniDay.equals("") && !iniDay.equals(" ");
					Boolean bool2 = !iniMonth.equals("") && !iniMonth.equals(" ");
					Boolean bool3 = !iniYear.equals("") && !iniYear.equals(" ");
					Boolean bool4 = !finDay.equals("") && !finDay.equals(" ");
					Boolean bool5 = !finMonth.equals("") && !finMonth.equals(" ");
					Boolean bool6 = !finYear.equals("") && !finYear.equals(" ");
					if(bool1 && bool2 && bool3 && bool4 && bool5 && bool6) {
						try {
							GregorianCalendar iniDate = new GregorianCalendar(Integer.parseInt(iniYear), Integer.parseInt(iniMonth), Integer.parseInt(iniDay));
							GregorianCalendar finDate = new GregorianCalendar(Integer.parseInt(finYear), Integer.parseInt(finMonth), Integer.parseInt(finDay));
							try{
								iniDate.setLenient(false);
								finDate.setLenient(false);
								iniDate.getTime();
								finDate.getTime();
							}catch(Exception ex) {
								JOptionPane.showMessageDialog(null, "Please, introduce correct dates",
										"ERROR", JOptionPane.ERROR_MESSAGE);
								return;
							}
							filters.add(new ShortTimeFilter(iniDate, finDate));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					ArrayList<Offer> filteredOffers = app.search(app.getOffersArray(), filters);
					((StartPanel)panels.get("START PANEL")).showOffers(filteredOffers, ((StartController)controllers.get("START CONTROLLER")));
					((StartPanel)panels.get("START PANEL")).prepareStartButtons(app.getLoggedUser().getUserType());
					card.show(window, "START PANEL");
					
				}
				
				else if(offerType.equals("Long stay")) {
					filters.add(new TypeStayFilter(OfferType.LONG));
					String pc = ((SearchPanel)panels.get("SEARCH PANEL")).getPCText();
					if(!pc.equals("") && !pc.equals(" ")) {
						try {
							filters.add(new PostalCodeFilter(Integer.parseInt(pc)));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					String iniDay = ((SearchPanel)panels.get("SEARCH PANEL")).getIniDayText();
					String iniMonth = ((SearchPanel)panels.get("SEARCH PANEL")).getIniMonthText();
					String iniYear = ((SearchPanel)panels.get("SEARCH PANEL")).getIniYearText();
					String nDays = ((SearchPanel)panels.get("SEARCH PANEL")).getNDaysText();
					String nMonths = ((SearchPanel)panels.get("SEARCH PANEL")).getNMonthsText();
					String nYears = ((SearchPanel)panels.get("SEARCH PANEL")).getNYearsText();
					Boolean bool1 = !iniDay.equals("") && !iniDay.equals(" ");
					Boolean bool2 = !iniMonth.equals("") && !iniMonth.equals(" ");
					Boolean bool3 = !iniYear.equals("") && !iniYear.equals(" ");
					Boolean bool4 = !nDays.equals("") && !nDays.equals(" ");
					Boolean bool5 = !nMonths.equals("") && !nMonths.equals(" ");
					Boolean bool6 = !nYears.equals("") && !nYears.equals(" ");
					if((bool1 && bool2 && bool3) && (bool4 || bool5 || bool6)) {
						try {
							GregorianCalendar iniDate = new GregorianCalendar(Integer.parseInt(iniYear), Integer.parseInt(iniMonth), Integer.parseInt(iniDay));
							try{
								iniDate.setLenient(false);
								iniDate.getTime();
							}catch(Exception ex) {
								JOptionPane.showMessageDialog(null, "Please, introduce correct dates",
										"ERROR", JOptionPane.ERROR_MESSAGE);
								return;
							}
							Integer nDaysAux;
							Integer nMonthsAux;
							Integer nYearsAux;
							if(nDays.equals("") || nDays.equals(" ")) nDaysAux = 0;
							else nDaysAux = Integer.parseInt(nDays);
							if(nMonths.equals("") || nMonths.equals(" ")) nMonthsAux = 0;
							else nMonthsAux = Integer.parseInt(nMonths);
							if(nYears.equals("") || nYears.equals(" ")) nYearsAux = 0;
							else nYearsAux = Integer.parseInt(nYears);
							filters.add(new LongTimeFilter(iniDate, nDaysAux, nMonthsAux, nYearsAux));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					ArrayList<Offer> filteredOffers = app.search(app.getOffersArray(), filters);
					((StartPanel)panels.get("START PANEL")).showOffers(filteredOffers, ((StartController)controllers.get("START CONTROLLER")));
					((StartPanel)panels.get("START PANEL")).prepareStartButtons(app.getLoggedUser().getUserType());
					card.show(window, "START PANEL");
					
				}
				
				else if(offerType.equals("Both")) {
					String pc = ((SearchPanel)panels.get("SEARCH PANEL")).getPCText();
					if(!pc.equals("") && !pc.equals(" ")) {
						try {
							filters.add(new PostalCodeFilter(Integer.parseInt(pc)));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					ArrayList<Offer> filteredOffers = app.search(app.getOffersArray(), filters);
					((StartPanel)panels.get("START PANEL")).showOffers(filteredOffers, ((StartController)controllers.get("START CONTROLLER")));
					if(app.getLoggedUser() != null) {
						((StartPanel)panels.get("START PANEL")).prepareStartButtons(app.getLoggedUser().getUserType());
					}
					else {
						((StartPanel)panels.get("START PANEL")).prepareStartButtons(null);
					}
					card.show(window, "START PANEL");
					
				}
			}
			else {
				if(offerType.equals("Short stay")) {
					filters.add(new TypeStayFilter(OfferType.SHORT));
					String pc = ((SearchPanel)panels.get("SEARCH PANEL")).getPCText();
					if(!pc.equals("") && !pc.equals(" ")) {
						try {
							filters.add(new PostalCodeFilter(Integer.parseInt(pc)));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					String iniDay = ((SearchPanel)panels.get("SEARCH PANEL")).getIniDayText();
					String iniMonth = ((SearchPanel)panels.get("SEARCH PANEL")).getIniMonthText();
					String iniYear = ((SearchPanel)panels.get("SEARCH PANEL")).getIniYearText();
					String finDay = ((SearchPanel)panels.get("SEARCH PANEL")).getFinDayText();
					String finMonth = ((SearchPanel)panels.get("SEARCH PANEL")).getFinMonthText();
					String finYear = ((SearchPanel)panels.get("SEARCH PANEL")).getFinYearText();
					Boolean bool1 = !iniDay.equals("") && !iniDay.equals(" ");
					Boolean bool2 = !iniMonth.equals("") && !iniMonth.equals(" ");
					Boolean bool3 = !iniYear.equals("") && !iniYear.equals(" ");
					Boolean bool4 = !finDay.equals("") && !finDay.equals(" ");
					Boolean bool5 = !finMonth.equals("") && !finMonth.equals(" ");
					Boolean bool6 = !finYear.equals("") && !finYear.equals(" ");
					if(bool1 && bool2 && bool3 && bool4 && bool5 && bool6) {
						try {
							GregorianCalendar iniDate = new GregorianCalendar(Integer.parseInt(iniYear), Integer.parseInt(iniMonth), Integer.parseInt(iniDay));
							GregorianCalendar finDate = new GregorianCalendar(Integer.parseInt(finYear), Integer.parseInt(finMonth), Integer.parseInt(finDay));
							try{
								iniDate.setLenient(false);
								finDate.setLenient(false);
								iniDate.getTime();
								finDate.getTime();
							}catch(Exception ex) {
								JOptionPane.showMessageDialog(null, "Please, introduce correct dates",
										"ERROR", JOptionPane.ERROR_MESSAGE);
								return;
							}
							filters.add(new ShortTimeFilter(iniDate, finDate));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}catch(IllegalArgumentException ex) {
							System.out.println("foahiudhsa");
							return;
						}
					}
					String rate = ((SearchPanel)panels.get("SEARCH PANEL")).getSelectedRatingText();
					try {
						filters.add(new RatingFilter(Integer.parseInt(rate)));
					}catch(NumberFormatException ex) {
						JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
								"ERROR", JOptionPane.ERROR_MESSAGE);
						return;
					}
					String minPrice = ((SearchPanel)panels.get("SEARCH PANEL")).getMinPriceText();
					String maxPrice = ((SearchPanel)panels.get("SEARCH PANEL")).getMaxPriceText();
					if(!minPrice.equals(" ") && !minPrice.equals("") && !maxPrice.equals(" ") && !maxPrice.equals("")) {
						try {
							filters.add(new PriceFilter(Integer.parseInt(minPrice), Integer.parseInt(maxPrice)));
						}catch(Exception ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					if(status.size()==0) {
						Set<Status> aux = new HashSet<Status>();
						aux.add(Status.FREE);
						aux.add(Status.RENTED);
						aux.add(Status.BOOKED);
						aux.add(Status.OUT);
						aux.add(Status.WAITING);
						aux.add(Status.DENIED);
						filters.add(new StatusFilter(aux));
					}else {
						filters.add(new StatusFilter(status));
					}
					ArrayList<Offer> filteredOffers = app.search(app.getOffersArray(), filters);
					((StartPanel)panels.get("START PANEL")).showOffers(filteredOffers, ((StartController)controllers.get("START CONTROLLER")));
					((StartPanel)panels.get("START PANEL")).prepareStartButtons(app.getLoggedUser().getUserType());
					card.show(window, "START PANEL");
					
				}
				else if(offerType.equals("Long stay")) {
					filters.add(new TypeStayFilter(OfferType.LONG));
					String pc = ((SearchPanel)panels.get("SEARCH PANEL")).getPCText();
					if(!pc.equals("") && !pc.equals(" ")) {
						try {
							filters.add(new PostalCodeFilter(Integer.parseInt(pc)));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					String iniDay = ((SearchPanel)panels.get("SEARCH PANEL")).getIniDayText();
					String iniMonth = ((SearchPanel)panels.get("SEARCH PANEL")).getIniMonthText();
					String iniYear = ((SearchPanel)panels.get("SEARCH PANEL")).getIniYearText();
					String nDays = ((SearchPanel)panels.get("SEARCH PANEL")).getNDaysText();
					String nMonths = ((SearchPanel)panels.get("SEARCH PANEL")).getNMonthsText();
					String nYears = ((SearchPanel)panels.get("SEARCH PANEL")).getNYearsText();
					Boolean bool1 = !iniDay.equals("") && !iniDay.equals(" ");
					Boolean bool2 = !iniMonth.equals("") && !iniMonth.equals(" ");
					Boolean bool3 = !iniYear.equals("") && !iniYear.equals(" ");
					Boolean bool4 = !nDays.equals("") && !nDays.equals(" ");
					Boolean bool5 = !nMonths.equals("") && !nMonths.equals(" ");
					Boolean bool6 = !nYears.equals("") && !nYears.equals(" ");
					if((bool1 && bool2 && bool3) && (bool4 || bool5 || bool6)) {
						try {
							GregorianCalendar iniDate = new GregorianCalendar(Integer.parseInt(iniYear), Integer.parseInt(iniMonth), Integer.parseInt(iniDay));
							try{
								iniDate.setLenient(false);
								iniDate.getTime();
							}catch(Exception ex) {
								JOptionPane.showMessageDialog(null, "Please, introduce correct dates",
										"ERROR", JOptionPane.ERROR_MESSAGE);
								return;
							}
							Integer nDaysAux;
							Integer nMonthsAux;
							Integer nYearsAux;
							if(nDays.equals("") || nDays.equals(" ")) nDaysAux = 0;
							else nDaysAux = Integer.parseInt(nDays);
							if(nMonths.equals("") || nMonths.equals(" ")) nMonthsAux = 0;
							else nMonthsAux = Integer.parseInt(nMonths);
							if(nYears.equals("") || nYears.equals(" ")) nYearsAux = 0;
							else nYearsAux = Integer.parseInt(nYears);
							filters.add(new LongTimeFilter(iniDate, nDaysAux, nMonthsAux, nYearsAux));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					String rate = ((SearchPanel)panels.get("SEARCH PANEL")).getSelectedRatingText();
					try {
						filters.add(new RatingFilter(Integer.parseInt(rate)));
					}catch(NumberFormatException ex) {
						JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
								"ERROR", JOptionPane.ERROR_MESSAGE);
						return;
					}
					String minPrice = ((SearchPanel)panels.get("SEARCH PANEL")).getMinPriceText();
					String maxPrice = ((SearchPanel)panels.get("SEARCH PANEL")).getMaxPriceText();
					if(!minPrice.equals(" ") && !minPrice.equals("") && !maxPrice.equals(" ") && !maxPrice.equals("")) {
						try {
							filters.add(new PriceFilter(Integer.parseInt(minPrice), Integer.parseInt(maxPrice)));
						}catch(Exception ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					if(status.size()==0) {
						Set<Status> aux = new HashSet<Status>();
						aux.add(Status.FREE);
						aux.add(Status.RENTED);
						aux.add(Status.BOOKED);
						aux.add(Status.OUT);
						aux.add(Status.WAITING);
						aux.add(Status.DENIED);
						filters.add(new StatusFilter(aux));
					}else {
						filters.add(new StatusFilter(status));
					}
					ArrayList<Offer> filteredOffers = app.search(app.getOffersArray(), filters);
					((StartPanel)panels.get("START PANEL")).showOffers(filteredOffers, ((StartController)controllers.get("START CONTROLLER")));
					((StartPanel)panels.get("START PANEL")).prepareStartButtons(app.getLoggedUser().getUserType());
					card.show(window, "START PANEL");
					
				}
				else if(offerType.equals("Both")) {
					String pc = ((SearchPanel)panels.get("SEARCH PANEL")).getPCText();
					if(!pc.equals("") && !pc.equals(" ")) {
						try {
							filters.add(new PostalCodeFilter(Integer.parseInt(pc)));
						}catch(NumberFormatException ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					String rate = ((SearchPanel)panels.get("SEARCH PANEL")).getSelectedRatingText();
					try {
						filters.add(new RatingFilter(Integer.parseInt(rate)));
					}catch(NumberFormatException ex) {
						JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
								"ERROR", JOptionPane.ERROR_MESSAGE);
						return;
					}
					String minPrice = ((SearchPanel)panels.get("SEARCH PANEL")).getMinPriceText();
					String maxPrice = ((SearchPanel)panels.get("SEARCH PANEL")).getMaxPriceText();
					if(!minPrice.equals(" ") && !minPrice.equals("") && !maxPrice.equals(" ") && !maxPrice.equals("")) {
						try {
							filters.add(new PriceFilter(Integer.parseInt(minPrice), Integer.parseInt(maxPrice)));
						}catch(Exception ex) {
							JOptionPane.showMessageDialog(null, "Please, introduce correct number values",
									"ERROR", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
					if(status.size()==0) {
						Set<Status> aux = new HashSet<Status>();
						aux.add(Status.FREE);
						aux.add(Status.RENTED);
						aux.add(Status.BOOKED);
						aux.add(Status.OUT);
						aux.add(Status.WAITING);
						aux.add(Status.DENIED);
						filters.add(new StatusFilter(aux));
					}else {
						filters.add(new StatusFilter(status));
					}
					ArrayList<Offer> filteredOffers = app.search(app.getOffersArray(), filters);
					((StartPanel)panels.get("START PANEL")).showOffers(filteredOffers, ((StartController)controllers.get("START CONTROLLER")));
					((StartPanel)panels.get("START PANEL")).prepareStartButtons(app.getLoggedUser().getUserType());
					card.show(window, "START PANEL");
					
				}
			}
		}
	}
	

	@Override
	public void itemStateChanged(ItemEvent arg) {
		JCheckBox source = (JCheckBox) arg.getItem();
		String str = source.getText();
		
		if(str.equals("Free") && arg.getStateChange()==ItemEvent.SELECTED) {
			status.add(Status.FREE);
		}
		else if(str.equals("Rented") && arg.getStateChange()==ItemEvent.SELECTED) {
			status.add(Status.RENTED);
		}
		else if(str.equals("Booked") && arg.getStateChange()==ItemEvent.SELECTED) {
			status.add(Status.BOOKED);
		}
		else if(str.equals("Free") && arg.getStateChange()==ItemEvent.DESELECTED) {
			status.remove(Status.FREE);
		}
		else if(str.equals("Rented") && arg.getStateChange()==ItemEvent.DESELECTED) {
			status.remove(Status.RENTED);
		}
		else if(str.equals("Booked") && arg.getStateChange()==ItemEvent.DESELECTED) {
			status.remove(Status.BOOKED);
		}
	}
}
