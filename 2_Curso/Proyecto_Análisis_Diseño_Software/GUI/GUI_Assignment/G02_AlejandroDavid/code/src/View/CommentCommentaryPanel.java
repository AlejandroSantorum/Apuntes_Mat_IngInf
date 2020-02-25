package View;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import javax.swing.*;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class implements the panel where the user can comment commentaries
 */
public class CommentCommentaryPanel extends JPanel{
	/* Buttons */
	private JButton goBackButton;
	private JButton textButton;
	private JButton rateButton;
	/* Text Fields */
	private JTextField textField;
	/* Labels */
	private JLabel rate;
	private JLabel text;
	/* JRadioButtons */
	private JRadioButton ratings[] = new JRadioButton[6];
	
	/**
	 * This constructor creates a new CommentCommentaryPanel.
	 * It help helped by 3 privated methods that just creates different smaller panels
	 */
	public CommentCommentaryPanel() {
		JPanel top = buildTopPanel();
		JPanel mid = buildMidPanel();
		JPanel down = buildDownPanel();
		
		this.setLayout(new BorderLayout());
		
		this.add(BorderLayout.NORTH, top);
		this.add(BorderLayout.CENTER, mid);
		this.add(BorderLayout.SOUTH, down);
	}
	
	/**
	 * Sets the controller to the buttons of this panel
	 * @param al  ActionListener
	 */
	public void setController(ActionListener al) {
		goBackButton.addActionListener(al);
		textButton.addActionListener(al);
		rateButton.addActionListener(al);
		for(JRadioButton rad: ratings) {
			rad.addActionListener(al);
		}
	}
	
	public String getCommentText() {
		return this.textField.getText();
	}
	
	public String getSelectedRateText() {
		for(JRadioButton rad: ratings) {
			if(rad.isSelected()) {
				return rad.getText();
			}
		}
		return null;
	}
	
	/**
	 * It cleans the JTextFields
	 */
	public void clean() {
		this.textField.setText("");
	}
	
	private JPanel buildTopPanel() {
		JPanel top = new JPanel();
		this.goBackButton = new JButton("Go Back");
		this.textButton = new JButton("Comment textually");
		this.rateButton = new JButton("Rate the commentary");
		top.add(goBackButton);
		top.add(textButton);
		top.add(rateButton);
		
		return top;
	}
	
	private JPanel buildMidPanel() {
		JPanel mid = new JPanel();
		mid.setLayout(new GridLayout(1, 0));
		text = new JLabel("Comment the commentary");
		text.setHorizontalAlignment(JLabel.CENTER);
		textField = new JTextField(100);
		textField.setHorizontalAlignment(JTextField.CENTER);
		mid.add(text);
		mid.add(textField);
		return mid;
	}
	
	private JPanel buildDownPanel() {
		JPanel down = new JPanel();
		down.setLayout(new GridLayout(1, 0));
		
		rate = new JLabel("Rate the commentary");
		rate.setHorizontalAlignment(JLabel.CENTER);
		down.add(rate);
		
		for(int i=0; i<6; i++) {
			ratings[i] = new JRadioButton(Integer.toString(i));
			ratings[i].setHorizontalAlignment(JRadioButton.CENTER);
		}
		ratings[3].setSelected(true); 
		
		ButtonGroup group = new ButtonGroup();
		for(JRadioButton rad: ratings) {
			group.add(rad);
			down.add(rad);
		}
		return down;
	}

}
