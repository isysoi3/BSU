package view;

import controller.Controller;
import model.pharmacy.Pharmacy;
import model.pharmacy.PharmacyManager;
import model.medicine.Medicine;

import java.util.List;

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
        var controller = new Controller(new Pharmacy(new PharmacyManager()));
        printMedicineList("Just list of medicine in pharmacy", controller.getPharmacyMedicines());

        printMedicineList("Just list of medicine sorted by name", controller.getPharmacyMedicinesSortedByName(false));
        printMedicineList("Just list of medicine sorted by name reversed", controller.getPharmacyMedicinesSortedByName(true));

        printMedicineList("Just list of medicine sorted by price", controller.getPharmacyMedicinesSortedByPrice(false));
        printMedicineList("Just list of medicine sorted by price reversed", controller.getPharmacyMedicinesSortedByPrice(true));

        printMedicineList("Just list of medicine sorted by exp date", controller.getPharmacyMedicinesSortedByExpirationDate(false));
        printMedicineList("Just list of medicine sorted by exp date reversed", controller.getPharmacyMedicinesSortedByExpirationDate(true));

        printMedicineList("Just list of medicine sorted by man date", controller.getPharmacyMedicinesSortedByManufactureDate(false));
        printMedicineList("Just list of medicine sorted by man date reversed", controller.getPharmacyMedicinesSortedByManufactureDate(true));

        printMedicineList("Just list of medicine selected by name", controller.getPharmacyMedicinesSelectedByName("Antibiotic5"));
        printMedicineList("Just list of medicine selected by price range", controller.getPharmacyMedicinesSelectedByPriceRange(1.3, 1.5));
        printMedicineList("Just list of medicine selected by price", controller.getPharmacyMedicinesSelectedByPrice(1.3));
    }

    public static void printMedicineList(String textBefore, List<Medicine> list) {
        System.out.println("-----------" + textBefore + "---------");
        if (list.size() > 0) {
            for (Medicine medicine : list) {
                System.out.println(medicine);
            }
        } else {
            System.out.println("No items");
        }
        System.out.println();
    }

}
