package model;

import model.comparator.MedicineExpirationDateComparator;
import model.comparator.MedicineManufactureDateComparator;
import model.comparator.MedicineNameComparator;
import model.comparator.MedicinePriceComparator;
import model.medicine.Medicine;
import controller.builder.MedicineBuilder;
import controller.director.MedicineDirector;
import model.medicine.internal.ColorEnum;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

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
     * Constructor that create medicines with builder
     */
    public Pharmacy() {
        MedicineDirector director = new MedicineDirector();
        MedicineBuilder builder = new MedicineBuilder();

        medicines = new ArrayList<>();

        medicines.add(director.manufactureAntibiotic(builder,"Antibiotic4", 5.5, false));
        builder.reset();

        medicines.add(director.manufactureGell(builder,"gel1", 12.4, true));
        builder.reset();

        medicines.add(director.manufactureGell(builder,"gel2", 32.4, false));
        builder.reset();

        medicines.add(director.manufactureOintment(builder, "Ointment1", 50.5, true));
        builder.reset();

        medicines.add(director.manufactureAntibiotic(builder,"Antibiotic2", 50.5, true));
        builder.reset();

        medicines.add(director.manufacturePill(builder, "Pill43", 5.4, 2));
        builder.reset();

        medicines.add(director.manufactureSyrup(builder,"Syrup32", 42.5, ColorEnum.RED));
        builder.reset();

        medicines.add(director.manufacturePill(builder,"Pill753", 5.4, 2));
        builder.reset();

        medicines.add(director.manufactureGell(builder,"Gel5", 42.5, false));
        builder.reset();

        medicines.add(director.manufactureOintment(builder,"Ointment2", 2.4, false));
        builder.reset();

        medicines.add(director.manufacturePill(builder,"Pill23", 2.4, 1));
        builder.reset();

        medicines.add(director.manufactureAntibiotic(builder,"Antibiotic5", 54.5, false));
        builder.reset();

    }

    /**
     * count the total price of medicines
     *
     * @return totalPrice
     */
    public double countTotalPrice() {
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
     * @param isReversed is list should be <
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByPrice(boolean isReversed) {
        Comparator<Medicine> priceComparator = new MedicinePriceComparator();
        if (isReversed) {
            priceComparator = priceComparator.reversed();
        }
        return sortListWithComparator(medicines, priceComparator);
    }

    /**
     * sort medicines by name
     *
     * @param isReversed is list should be <
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByName(boolean isReversed) {
        Comparator<Medicine> nameComparator = new MedicineNameComparator();
        if (isReversed) {
            nameComparator = nameComparator.reversed();
        }
        return sortListWithComparator(medicines, nameComparator);
    }

    /**
     * sort medicines by expiration date
     *
     * @param isReversed is list should be <
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByExpirationDate(boolean isReversed) {
        Comparator<Medicine> expirationDateComparator = new MedicineExpirationDateComparator();
        if (isReversed) {
            expirationDateComparator = expirationDateComparator.reversed();
        }
        return sortListWithComparator(medicines, expirationDateComparator);
    }

    /**
     * sort medicines by manufacture date
     *
     * @param isReversed is list should be <
     * @return sorted medicines list
     */
    public List<Medicine> sortMedicinesByManufactureDate(boolean isReversed) {
        Comparator<Medicine> manufactureDateComparator = new MedicineManufactureDateComparator();
        if (isReversed) {
            manufactureDateComparator = manufactureDateComparator.reversed();
        }
        return sortListWithComparator(medicines, manufactureDateComparator);
    }

    /**
     * sort list by comparator
     *
     * @param list some list
     * @param comparator condition to sort
     * @return sorted medicines list
     */
    private List<Medicine> sortListWithComparator(List<Medicine> list, Comparator<Medicine> comparator) {
        return list.stream()
                .sorted(comparator)
                .collect(Collectors.toList());
    }

}
