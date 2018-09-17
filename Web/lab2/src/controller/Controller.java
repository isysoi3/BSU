package controller;

import model.Pharmacy;
import model.medicine.Medicine;

import java.util.Arrays;

/**
 * Basic class demonstrates functions of classes
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Controller {

    /**
     * Method to demonstrate work with  classes
     *
     * @return some work result to show it on view
     */
    public static String demonstrateWork() {
        var pharmacy = new Pharmacy();
        var medicines = pharmacy.getMedicines();

        StringBuilder output = new StringBuilder();

        for (Medicine medicine : medicines) {
            output.append(medicine);
            output.append("\n");
        }

        return output.toString();
    }

}