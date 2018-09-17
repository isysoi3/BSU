package view;

import controller.Controller;
import model.medicine.Medicine;

/**
 * Main class which run controller's demonstrate method
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Main {

    /**
     * The Main method
     *
     * @param args command line parameters
     */
    public static void main(String[] args) {
        var outputResult = Controller.getPharmacyMedicines();
        for (Medicine medicine : outputResult) {
            System.out.println(medicine);
        }
    }

}
