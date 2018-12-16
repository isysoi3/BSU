package controller;

import exception.ParserException;
import exception.XMLValidatorException;
import model.ParsingModeEnum;
import model.medicine.Medicine;
import model.pharmacy.Pharmacy;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import util.xml.XMLValidator;
import util.xml.parser.DOMParser;
import util.xml.parser.SAXParser;
import util.xml.parser.StAXParser;

import java.util.List;

/**
 * Basic class demonstrates functions of classes
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Controller {

    /**
     * logging via log4j
     */
    private static final Logger logger = LogManager.getLogger();

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
    }


    public List<Medicine> parseMedicinesList(String file, ParsingModeEnum mode) throws ParserException {
        switch (mode) {
            case DOM:
                return (new DOMParser()).parse(file);
            case SAX:
                return (new SAXParser()).parse(file);
            case StAX:
                return (new StAXParser()).parse(file);
            default:
                return null;
        }
    }

    /**
     * Validates XML file with given schema
     * @param file XML file
     * @param schema XSD file
     * @return true if validation succeed, otherwise false
     */
    public boolean validate(String file, String schema) throws XMLValidatorException {
        boolean result = XMLValidator.validate(file, schema);
        if (result) {
            logger.info("Validation succeed");
        } else {
            logger.info("Validation failed");
        }
        return result;
    }

    /**
     * Method to add new medicine
     */
    public void addMedicine(Medicine medicine) {
        pharmacy.addMedicine(medicine);
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