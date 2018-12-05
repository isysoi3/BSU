package model.pharmacy;

import model.medicine.Medicine;

import java.util.ArrayList;
import java.util.List;

/**
 * this is pharmacy that store and sell medicines
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Pharmacy {

    /**
     * list of stored medicines
     */
    private List<Medicine> medicines;

    /**
     * getter of medicines
     *
     * @return medicine list
     */
    public List<Medicine> getMedicines() {
        return medicines;
    }

    /**
     * manager of pharmacy
     */
    private PharmacyManager manager;

    /**
     * getter of manager
     *
     * @return manager
     */
    public PharmacyManager getManager() {
        return manager;
    }

    /**
     * Constructor that create medicines with builder
     * @param manager pharmacy manager
     */
    public Pharmacy(PharmacyManager manager) {
        this.manager = manager;
        medicines = new ArrayList<>();
    }


    /**
     * add medicine to medicines list
     *
     * @param medicine medicine to add to list
     */
    public void addMedicine(Medicine medicine) {
        medicines.add(medicine);
    }

    /**
     * count the total price of medicines
     *
     * @return totalPrice
     */
    public double countTotalPrice() {
        return manager.countTotalPrice(medicines);
    }

    /**
     * sort medicines by price
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByPrice(boolean isReversed) {
        return manager.sortMedicinesByPrice(medicines, isReversed);
    }

    /**
     * sort medicines by name
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByName(boolean isReversed) {
        return manager.sortMedicinesByName(medicines, isReversed);
    }

    /**
     * sort medicines by expiration date
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByExpirationDate(boolean isReversed) {
        return manager.sortMedicinesByExpirationDate(medicines, isReversed);
    }

    /**
     * sort medicines by manufacture date
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByManufactureDate(boolean isReversed) {
        return manager.sortMedicinesByManufactureDate(medicines, isReversed);
    }

    /**
     * select items equal to price
     *
     * @param price some list
     * @return selected medicines list
     */
    public List<Medicine> selectMedicinesByPrice(double price) {
        return manager.selectMedicinesByPriceRange(medicines, price, price);
    }

    /**
     * select items between prices
     *
     * @param minPrice some list
     * @param maxPrice some list
     * @return selected medicines list
     */
    public List<Medicine> selectMedicinesByPriceRange(double minPrice, double maxPrice) {
        return manager.selectMedicinesByPriceRange(medicines, minPrice, maxPrice);
    }

    /**
     * select items by name
     *
     * @param name name of medicine
     * @return selected medicines list
     */
    public List<Medicine> selectMedicinesByName(String name) {
        return manager.selectMedicinesByName(medicines, name);
    }

}
