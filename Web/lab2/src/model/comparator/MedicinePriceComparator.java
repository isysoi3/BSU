package model.comparator;

import model.medicine.Medicine;

import java.util.Comparator;

public class MedicinePriceComparator implements Comparator<Medicine> {

    @Override
    public int compare(Medicine o1, Medicine o2) {
        return Double.compare(o1.getPrice(), o2.getPrice());
    }

}
