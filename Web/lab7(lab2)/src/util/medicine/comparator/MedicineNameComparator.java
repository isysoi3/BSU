package util.medicine.comparator;

import model.medicine.Medicine;

import java.util.Comparator;

/**
 * Performances comparator class of medicine by name
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class MedicineNameComparator implements Comparator<Medicine> {

    @Override
    public int compare(Medicine o1, Medicine o2) {
        return o1.getName().compareTo(o2.getName());
    }

}
