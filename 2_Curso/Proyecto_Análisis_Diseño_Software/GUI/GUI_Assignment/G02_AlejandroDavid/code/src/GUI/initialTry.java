package GUI;

import java.io.*;
import padsof.*;
import java.util.*;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

import Exceptions.*;
import padsof.Application;

public class initialTry {
	String password, user;
	int status;
	public void tryout() throws IOException, UserException{
		JFrame window = new JFrame("My first tryout");
		
		Container container = window.getContentPane();
		container.setLayout(new FlowLayout());
		
		final JPanel window1 = new JPanel();
		JLabel labelName = new JLabel("Username: ");
		final JTextField username = new JTextField(10);
		JLabel labelPass = new JLabel("Password: ");
		final JPasswordField pass = new JPasswordField(10);
		JButton okButton = new JButton("Login");
		
		
		window1.add(labelName);
		window1.add(username);
		window1.add(labelPass);
		window1.add(pass);
		window1.add(okButton);
		window1.setVisible(true);
		
		final JPanel window2 = new JPanel();
		JLabel labelName2 = new JLabel("No se que estoy haciendo");
		window2.add(labelName2);
		window2.setVisible(false);
		
		
		okButton.addActionListener(
				new ActionListener() {
					public void actionPerformed(ActionEvent e){
						user = username.getText();
						password = String.copyValueOf(pass.getPassword());
						Application app = new Application();
						try {
							app.loadUsers("users.txt");
						} catch (IOException e1) {
							e1.printStackTrace();
						} catch (UserException e1) {
							e1.printStackTrace();
						}
						status = login(app,user,password);
						if(status ==-1) {
							JOptionPane.showMessageDialog(null, "Sorry, Invalid user or password", "Invalid data", JOptionPane.WARNING_MESSAGE);
						}
						else if(status == 1) {
							//System.out.println("User blocked(haber pagao)");
							JOptionPane.showMessageDialog(null, "Sorry, You cannot loging. Your are blocked", "Blocked", JOptionPane.ERROR_MESSAGE);
						}
						else {
							//System.out.println("Te metería en algún sitio si tuviera otra pantalla");
							window1.setVisible(false);
							window2.setVisible(true);
							
						}
					}
				}
		);
		
		container.add(window1);
		container.add(window2);
		
		/*
		container.add(labelName);
		container.add(userName);
		container.add(labelPass);
		container.add(pass);
		container.add(okButton);
		*/
		
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setSize(500, 500);
		window.setVisible(true);
	}
	
	public int login(Application app, String user, String pass){
		ArrayList<RegisteredUser> users;
		
		users = app.getUsersArray();
		for(RegisteredUser usr: users) {
			if(usr.getNick().equals(user)) {
				if(usr.getPassword().equals(pass)) {
					if(usr.isBlocked() == false) {
						return 0;
					}
					return 1;
				}
			}
		}
		return -1;
	}
	
	


}
