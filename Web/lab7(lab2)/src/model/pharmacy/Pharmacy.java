package model.pharmacy;

import model.medicine.Medicine;

import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * this is pharmacy that store and sell medicines
 *
 * @author Ilya Sysoi
 * @version 2.0.0
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
     * buy medicine from pharmacy
     *
     * @param medicine medicine to buy
     * @return true if medicine bought abd false it didn`t
     */
    public boolean buyMedicine(Medicine medicine) {
        boolean result = medicines.remove(medicine);
        return result;
    }

    /**
     * count the total price of medicines
     *
     * @return totalPrice
     */
    public double countTotalPrice() {
        List<Medicine> tmpMedicines = getMedicines();
        return manager.countTotalPrice(tmpMedicines);
    }

    /**
     * sort medicines by price
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByPrice(boolean isReversed) {
        List<Medicine> tmpMedicines = getMedicines();
        return manager.sortMedicinesByPrice(tmpMedicines, isReversed);
    }

    /**
     * sort medicines by name
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByName(boolean isReversed) {
        List<Medicine> tmpMedicines = getMedicines();
        return manager.sortMedicinesByName(tmpMedicines, isReversed);
    }

    /**
     * sort medicines by expiration date
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByExpirationDate(boolean isReversed) {
        List<Medicine> tmpMedicines = getMedicines();
        return manager.sortMedicinesByExpirationDate(tmpMedicines, isReversed);
    }

    /**
     * sort medicines by manufacture date
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByManufactureDate(boolean isReversed) {
        List<Medicine> tmpMedicines = getMedicines();
        return manager.sortMedicinesByManufactureDate(tmpMedicines, isReversed);
    }

    /**
     * select items equal to price
     *
     * @param price some list
     * @return selected medicines list
     */
    public List<Medicine> selectMedicinesByPrice(double price) {
        List<Medicine> tmpMedicines = getMedicines();
        return manager.selectMedicinesByPriceRange(tmpMedicines, price, price);
    }

    /**
     * select items between prices
     *
     * @param minPrice some list
     * @param maxPrice some list
     * @return selected medicines list
     */
    public List<Medicine> selectMedicinesByPriceRange(double minPrice, double maxPrice) {
        List<Medicine> tmpMedicines = getMedicines();
        return manager.selectMedicinesByPriceRange(tmpMedicines, minPrice, maxPrice);
    }

    /**
     * select items by name
     *
     * @param name name of medicine
     * @return selected medicines list
     */
    public List<Medicine> selectMedicinesByName(String name) {
        List<Medicine> tmpMedicines = getMedicines();
        return manager.selectMedicinesByName(tmpMedicines, name);
    }

}
