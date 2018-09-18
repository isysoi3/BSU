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

    private static Pharmacy pharmacy = new Pharmacy();

    /**
     * Method to demonstrate work with  classes
     *
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicines() {
        return pharmacy.getMedicines();
    }

    /**
     * Method to demonstrate work of sorting method by name
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSortedByName(boolean isRevesed) {
        return pharmacy.sortMedicinesByName(isRevesed);
    }

    /**
     * Method to demonstrate work of sorting method by price
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSortedByPrice(boolean isRevesed) {
        return pharmacy.sortMedicinesByPrice(isRevesed);
    }

    /**
     * Method to demonstrate work of sorting method by manufacture date
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSortedByManufactureDate(boolean isRevesed) {
        return pharmacy.sortMedicinesByManufactureDate(isRevesed);
    }

    /**
     * Method to demonstrate work of sorting method by expiration date
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSortedByExpirationDate(boolean isRevesed) {
        return pharmacy.sortMedicinesByExpirationDate(isRevesed);
    }

}