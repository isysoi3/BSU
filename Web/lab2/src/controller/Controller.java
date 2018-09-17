package controller;

import model.Pharmacy;
import model.medicine.Medicine;

import java.util.List;

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
    public static List<Medicine> getPharmacyMedicines() {
        var pharmacy = new Pharmacy();
        var medicines = pharmacy.getMedicines();

        return medicines;
    }

}