package model.pharmacy;

import model.medicine.Medicine;
import model.medicine.comparator.MedicineExpirationDateComparator;
import model.medicine.comparator.MedicineManufactureDateComparator;
import model.medicine.comparator.MedicineNameComparator;
import model.medicine.comparator.MedicinePriceComparator;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
 * this is pharmacy  manager that control pharmacy
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class PharmacyManager {

    /**
     * count the total price of medicines
     *
     * @param medicines list of medicines
     * @return totalPrice
     */
    public double countTotalPrice(List<Medicine> medicines) {
        double totalPrice = 0;
        for (Medicine medicine :
                medicines) {
            totalPrice += medicine.getPrice();
        }
        return totalPrice;
    }

    /**
     * sort medicines by price
     *
     * @param medicines  list of medicines
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByPrice(List<Medicine> medicines, boolean isReversed) {
        Comparator<Medicine> priceComparator = new MedicinePriceComparator();
        if (isReversed) {
            priceComparator = priceComparator.reversed();
        }
        return sortListWithComparator(medicines, priceComparator);
    }

    /**
     * sort medicines by name
     *
     * @param medicines  list of medicines
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByName(List<Medicine> medicines, boolean isReversed) {
        Comparator<Medicine> nameComparator = new MedicineNameComparator();
        if (isReversed) {
            nameComparator = nameComparator.reversed();
        }
        return sortListWithComparator(medicines, nameComparator);
    }

    /**
     * sort medicines by expiration date
     *
     * @param medicines  list of medicines
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByExpirationDate(List<Medicine> medicines, boolean isReversed) {
        Comparator<Medicine> expirationDateComparator = new MedicineExpirationDateComparator();
        if (isReversed) {
            expirationDateComparator = expirationDateComparator.reversed();
        }
        return sortListWithComparator(medicines, expirationDateComparator);
    }

    /**
     * sort medicines by manufacture date
     *
     * @param medicines  list of medicines
     * @param isReversed is list should be reversed
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByManufactureDate(List<Medicine> medicines, boolean isReversed) {
        Comparator<Medicine> manufactureDateComparator = new MedicineManufactureDateComparator();
        if (isReversed) {
            manufactureDateComparator = manufactureDateComparator.reversed();
        }
        return sortListWithComparator(medicines, manufactureDateComparator);
    }

    /**
     * sort list by comparator
     *
     * @param list       some list
     * @param comparator condition to sort
     * @return sorted medicines list
     */
    private List<Medicine> sortListWithComparator(List<Medicine> list, Comparator<Medicine> comparator) {
        return list.stream()
                .sorted(comparator)
                .collect(Collectors.toList());
    }

    /**
     * select items equal to price
     *
     * @param medicines list of medicines
     * @param price     some list
     * @return selected medicines list
     */
    public List<Medicine> selectMedicinesByPrice(List<Medicine> medicines, double price) {
        return selectMedicinesByPriceRange(medicines, price, price);
    }

    /**
     * select items between prices
     *
     * @param medicines list of medicines
     * @param minPrice  some list
     * @param maxPrice  some list
     * @return selected medicines list
     */
    public List<Medicine> selectMedicinesByPriceRange(List<Medicine> medicines, double minPrice, double maxPrice) {
        return medicines.stream()
                .filter(medicine -> medicine.getPrice() >= minPrice && medicine.getPrice() <= maxPrice)
                .collect(Collectors.toList());
    }

    /**
     * select items by name
     *
     * @param medicines list of medicines
     * @param name      name of medicine
     * @return selected medicines list
     */
    public List<Medicine> selectMedicinesByName(List<Medicine> medicines, String name) {
        return medicines.stream()
                .filter(medicine -> medicine.getName().equals(name))
                .collect(Collectors.toList());
    }
}
