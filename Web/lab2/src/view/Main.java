package view;

import controller.Controller;
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
        printMedicineList("Just list of medicine in pharmacy", Controller.getPharmacyMedicines());

        printMedicineList("Just list of medicine sorted by name", Controller.getPharmacyMedicinesSortedByName(false));
        printMedicineList("Just list of medicine sorted by name reversed", Controller.getPharmacyMedicinesSortedByName(true));

        printMedicineList("Just list of medicine sorted by price", Controller.getPharmacyMedicinesSortedByPrice(false));
        printMedicineList("Just list of medicine sorted by price reversed", Controller.getPharmacyMedicinesSortedByPrice(true));

        printMedicineList("Just list of medicine sorted by exp date", Controller.getPharmacyMedicinesSortedByExpirationDate(false));
        printMedicineList("Just list of medicine sorted by exp date reversed", Controller.getPharmacyMedicinesSortedByExpirationDate(true));

        printMedicineList("Just list of medicine sorted by man date", Controller.getPharmacyMedicinesSortedByManufactureDate(false));
        printMedicineList("Just list of medicine sorted by man date reversed", Controller.getPharmacyMedicinesSortedByManufactureDate(true));

        printMedicineList("Just list of medicine selected by name", Controller.getPharmacyMedicinesSelectedByname("Antibiotic5"));
        printMedicineList("Just list of medicine selected by price", Controller.getPharmacyMedicinesSelecredByPriceRange(1.2, 1.5));
    }

    public static void printMedicineList(String textBefore, List<Medicine> list) {
        System.out.println("-----------" + textBefore + "---------");
        for (Medicine medicine : list) {
            System.out.println(medicine);
        }
        System.out.println();
    }

}
