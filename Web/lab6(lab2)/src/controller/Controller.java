package controller;

import controller.builder.MedicineBuilder;
import controller.director.MedicineDirector;
import model.pharmacy.Pharmacy;
import model.medicine.Medicine;
import model.medicine.internal.ColorEnum;

import java.util.List;

/**
 * Basic class demonstrates functions of classes
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Controller {

    /**
     * pharmacy
     */
    private Pharmacy pharmacy;

    /**
     * getter of pharmacy
     *
     * @return pharmacy
     */
    public Pharmacy getPharmacy() {
        return pharmacy;
    }


    /**
     * Constructor that create controller to work with pharmacy
     *
     * @param pharmacy pharmacy
     */
    public Controller(Pharmacy pharmacy) {
        this.pharmacy = pharmacy;

        MedicineDirector director = new MedicineDirector();
        MedicineBuilder builder = new MedicineBuilder();
        pharmacy.addMedicine(director.manufactureAntibiotic(builder, "Antibiotic4", 5.5, false));
        builder.reset();

        pharmacy.addMedicine(director.manufactureGell(builder, "gel1", 12.4, true));
        builder.reset();

        pharmacy.addMedicine(director.manufactureGell(builder, "gel2", 32.4, false));
        builder.reset();

        pharmacy.addMedicine(director.manufactureOintment(builder, "Ointment1", 50.5, true));
        builder.reset();

        pharmacy.addMedicine(director.manufactureAntibiotic(builder, "Antibiotic2", 50.5, true));
        builder.reset();

        pharmacy.addMedicine(director.manufacturePill(builder, "Pill43", 5.4, 2));
        builder.reset();

        pharmacy.addMedicine(director.manufactureSyrup(builder, "Syrup32", 42.5, ColorEnum.RED));
        builder.reset();

        pharmacy.addMedicine(director.manufacturePill(builder, "Pill753", 5.4, 2));
        builder.reset();

        pharmacy.addMedicine(director.manufactureGell(builder, "Gel5", 42.5, false));
        builder.reset();

        pharmacy.addMedicine(director.manufactureOintment(builder, "Ointment2", 2.4, false));
        builder.reset();

        pharmacy.addMedicine(director.manufacturePill(builder, "Pill23", 2.4, 1));
        builder.reset();

        pharmacy.addMedicine(director.manufactureAntibiotic(builder, "Antibiotic5", 54.5, false));
        builder.reset();
    }

    /**
     * Method to demonstrate work with  classes
     *
     * @return some work result to show it on view
     */
    public List<Medicine> getPharmacyMedicines() {
        return pharmacy.getMedicines();
    }

    /**
     * Method to demonstrate work of sorting method by name
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public List<Medicine> getPharmacyMedicinesSortedByName(boolean isRevesed) {
        return pharmacy.sortMedicinesByName(isRevesed);
    }

    /**
     * Method to demonstrate work of sorting method by price
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public List<Medicine> getPharmacyMedicinesSortedByPrice(boolean isRevesed) {
        return pharmacy.sortMedicinesByPrice(isRevesed);
    }

    /**
     * Method to demonstrate work of sorting method by manufacture date
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public List<Medicine> getPharmacyMedicinesSortedByManufactureDate(boolean isRevesed) {
        return pharmacy.sortMedicinesByManufactureDate(isRevesed);
    }

    /**
     * Method to demonstrate work of sorting method by expiration date
     *
     * @param isRevesed determinate order of sorted list
     * @return some work result to show it on view
     */
    public List<Medicine> getPharmacyMedicinesSortedByExpirationDate(boolean isRevesed) {
        return pharmacy.sortMedicinesByExpirationDate(isRevesed);
    }

    /**
     * Method to demonstrate work of selecting method by name
     *
     * @param name determinate order of sorted list
     * @return some work result to show it on view
     */
    public List<Medicine> getPharmacyMedicinesSelectedByName(String name) {
        return pharmacy.selectMedicinesByName(name);
    }

    /**
     * Method to demonstrate work of selecting method by range of price
     *
     * @param minPrice min price of range
     * @param maxPrice max price of range
     * @return some work result to show it on view
     */
    public List<Medicine> getPharmacyMedicinesSelectedByPriceRange(double minPrice, double maxPrice) {
        return pharmacy.selectMedicinesByPriceRange(minPrice, maxPrice);
    }

    /**
     * Method to demonstrate work of selecting method by price
     *
     * @param price price of medicine
     * @return some work result to show it on view
     */
    public List<Medicine> getPharmacyMedicinesSelectedByPrice(double price) {
        return pharmacy.selectMedicinesByPrice(price);
    }

}