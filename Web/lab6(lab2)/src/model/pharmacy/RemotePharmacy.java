package model.pharmacy;

import model.medicine.Medicine;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

/**
 * interface that give RMI methods from pharmacy service to clients
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public interface RemotePharmacy extends Remote {

    /**
     * come to pharmacy
     *
     */
    void comeIn() throws RemoteException;

    /**
     * go out from pharmacy
     *
     */
    void goOut() throws RemoteException;

    /**
     * return medicines in pharmacy
     *
     * @return medicine list
     */
    List<Medicine> getMedicines() throws RemoteException;

    /**
     * return pharmacy maneger
     *
     * @return manager
     */
    PharmacyManager getManager() throws RemoteException;

    /**
     * buy medicine from pharmacy
     *
     * @param medicine medicine to buy
     * @return true if medicine bought abd false it didn`t
     */
    boolean buyMedicine(Medicine medicine) throws RemoteException;


    /**
     * count the total price of medicines
     *
     * @return totalPrice
     */
    double countTotalPrice() throws RemoteException;

    /**
     * sort medicines by price
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    List<Medicine> sortMedicinesByPrice(boolean isReversed) throws RemoteException;

    /**
     * sort medicines by name
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    List<Medicine> sortMedicinesByName(boolean isReversed) throws RemoteException;

    /**
     * sort medicines by expiration date
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    List<Medicine> sortMedicinesByExpirationDate(boolean isReversed) throws RemoteException;

    /**
     * sort medicines by manufacture date
     *
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    List<Medicine> sortMedicinesByManufactureDate(boolean isReversed) throws RemoteException;

    /**
     * select items equal to price
     *
     * @param price some list
     * @return selected medicines list
     */
    List<Medicine> selectMedicinesByPrice(double price) throws RemoteException;

    /**
     * select items between prices
     *
     * @param minPrice some list
     * @param maxPrice some list
     * @return selected medicines list
     */
    List<Medicine> selectMedicinesByPriceRange(double minPrice, double maxPrice) throws RemoteException;

    /**
     * select items by name
     *
     * @param name name of medicine
     * @return selected medicines list
     */
    List<Medicine> selectMedicinesByName(String name) throws RemoteException ;


}
