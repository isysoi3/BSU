package model;

import model.medicine.Medicine;

import java.util.List;

/**
 * this is pharmacy when store and sell medicines
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Pharmacy {

    private List<Medicine> medicines;

    public List<Medicine> getMedicines() {
        return medicines;
    }

    public Pharmacy() {

    }

}
