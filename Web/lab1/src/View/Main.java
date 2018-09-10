package View;

import Controller.Controller;

/**
 * Main class which run Controller's demonstrate method
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
