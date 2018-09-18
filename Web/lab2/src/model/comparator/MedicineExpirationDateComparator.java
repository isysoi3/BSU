package model.comparator;

import model.medicine.Medicine;

import java.util.Comparator;

public class MedicineExpirationDateComparator implements Comparator<Medicine> {

    @Override
    public int compare(Medicine o1, Medicine o2) {
        return o1.getExpirationDate().compareTo(o2.getExpirationDate());

    }

}
