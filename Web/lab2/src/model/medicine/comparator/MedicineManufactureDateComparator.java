package model.medicine.comparator;

import model.medicine.Medicine;

import java.util.Comparator;

/**
 * Performances comparator class of medicine by manufacture date
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class MedicineManufactureDateComparator implements Comparator<Medicine> {

    @Override
    public int compare(Medicine o1, Medicine o2) {
        return o1.getManufactureDate().compareTo(o2.getManufactureDate());
    }

}
