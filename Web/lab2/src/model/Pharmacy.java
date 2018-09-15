package model;

import model.medicine.Medicine;
import model.medicine.builder.MedicineBuilder;

import java.util.ArrayList;
import java.util.List;

/**
 * this is pharmacy that store and sell medicines
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

        medicines.add(director.manufactureAntibiotic(builder));
        builder.reset();

        medicines.add(director.manufactureGell(builder));
        builder.reset();

        medicines.add(director.manufactureGell(builder));
        builder.reset();

        medicines.add(director.manufactureOintment(builder));
        builder.reset();

        medicines.add(director.manufactureAntibiotic(builder));
        builder.reset();

        medicines.add(director.manufacturePill(builder));
        builder.reset();

        medicines.add(director.manufactureSyrup(builder));
        builder.reset();

        medicines.add(director.manufacturePill(builder));
        builder.reset();

        medicines.add(director.manufactureGell(builder));
        builder.reset();

        medicines.add(director.manufactureOintment(builder));
        builder.reset();

        medicines.add(director.manufacturePill(builder));
        builder.reset();

        medicines.add(director.manufactureAntibiotic(builder));
        builder.reset();

    }

    /**
     * count the total price of medicines
     * @return totalPrice
     */
    public double countTotalPrice() {
        double totalPrice = 0;
        for (Medicine medicine:
             medicines) {
            totalPrice += medicine.getPrice();
        }
        return totalPrice;
    }

}
