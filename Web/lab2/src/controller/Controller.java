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

    /**
     * Method to demonstrate work of sorting method by name
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSortedByName(boolean isRevesed) {
        var pharmacy = new Pharmacy();
        var sortedMedicines = pharmacy.sortMedicinesByName(isRevesed);

        return sortedMedicines;
    }

    /**
     * Method to demonstrate work of sorting method by price
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSortedByPrice(boolean isRevesed) {
        var pharmacy = new Pharmacy();
        var sortedMedicines = pharmacy.sortMedicinesByPrice(isRevesed);

        return sortedMedicines;
    }

    /**
     * Method to demonstrate work of sorting method by manufacture date
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSortedByManufactureDate(boolean isRevesed) {
        var pharmacy = new Pharmacy();
        var sortedMedicines = pharmacy.sortMedicinesByManufactureDate(isRevesed);

        return sortedMedicines;
    }

    /**
     * Method to demonstrate work of sorting method by expiration date
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSortedByExpirationDate(boolean isRevesed) {
        var pharmacy = new Pharmacy();
        var sortedMedicines = pharmacy.sortMedicinesByExpirationDate(isRevesed);

        return sortedMedicines;
    }

}