package view;

import controller.Controller;

/**
 * Main class which run controller's demonstrate method
 * @author Ilya Sysoi
 * @version 1.0.0
 */

public class Main {

    /**
     * The Main method
     * @param args command line parameters
     */
    public static void main(String[] args) {
        var outputResult = Controller.startWork();
        System.out.println(outputResult);
    }
}
