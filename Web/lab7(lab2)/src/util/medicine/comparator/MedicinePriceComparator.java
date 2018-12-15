package util.medicine.comparator;

import model.medicine.Medicine;

import java.util.Comparator;

/**
 * Performances comparator class of medicine by price
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class MedicinePriceComparator implements Comparator<Medicine> {

    @Override
    public int compare(Medicine o1, Medicine o2) {
        return Double.compare(o1.getPrice(), o2.getPrice());
    }

}
