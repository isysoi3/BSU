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

    /**
     * Method to demonstrate work of selecting method by name
     *
     * @param name determinate order of sorted list
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSelectedByName(String name) {
        return pharmacy.selectMedicinesByName(name);
    }

    /**
     * Method to demonstrate work of selecting method by range of price
     *
     * @param minPrice min price of range
     * @param maxPrice max price of range
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSelectedByPriceRange(double minPrice, double maxPrice) {
        return pharmacy.selectMedicinesByPriceRange(minPrice, maxPrice);
    }

    /**
     * Method to demonstrate work of selecting method by price
     *
     * @param price price of medicine
     * @return some work result to show it on view
     */
    public static List<Medicine> getPharmacyMedicinesSelectedByPrice(double price) {
        return pharmacy.selectMedicinesByPrice(price);
    }

}