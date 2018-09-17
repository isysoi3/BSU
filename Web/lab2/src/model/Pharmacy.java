package model;

import model.medicine.Medicine;
import controller.builder.MedicineBuilder;
import controller.director.MedicineDirector;
import model.medicine.internal.ColorEnum;

import java.util.ArrayList;
import java.util.List;

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

}
