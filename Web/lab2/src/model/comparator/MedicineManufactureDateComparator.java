package model.comparator;

import model.medicine.Medicine;

import java.util.Comparator;

public class MedicineManufactureDateComparator implements Comparator<Medicine> {

    @Override
    public int compare(Medicine o1, Medicine o2) {
        return o1.getManufactureDate().compareTo(o2.getManufactureDate());
    }

}
