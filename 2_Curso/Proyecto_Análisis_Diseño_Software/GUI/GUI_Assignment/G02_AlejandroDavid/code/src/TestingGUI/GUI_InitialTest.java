
package TestingGUI;

import java.io.IOException;
import Exceptions.UserException;
import View.*;
import padsof.Application;

/**
 * @author Alejandro Santorum and David Cabornero
 * This class is used to test the whole graphical user interface
 */
public class GUI_InitialTest {
	
	public static void main(String[] args) throws IOException, UserException, ClassNotFoundException {
		/* This flag is used to run an application with some data, or from zero */
		/* flag = 1 -> some data already loaded */
		/* flag = 0 -> application run from zero */
		int flag = 1;
		
		String filename = new String("application.txt"); /* This is the file where all the
		 													changes are going to be saved */
		Application app = new Application();
		
		if(flag == 1) { /* The application is run using some data already loaded */
			app.readData(filename);
			new WindowApp(app, filename);
		}
		else{ /* The application is run from zero */
			app.loadUsers("users.txt");
			new WindowApp(app, filename);
		}
		
		/**
		 *  IMPORTANT --> MANAGER KEYS:
		 *  		User ID: admin
		 *  		Password: admin
		 */
	}

}
