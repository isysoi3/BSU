package model.medicine.internal;

import model.medicine.Medicine;

import java.util.Date;

public class InternalMedicine extends Medicine {

    private double maxDailyDoseInMg;

    public double getMaxDailyDoseInMg() {
        return maxDailyDoseInMg;
    }

    public InternalMedicine(String name, double price, Date manufactureDate, Date expirationDate, double maxDailyDoseInMg) {
        super(name, price, manufactureDate, expirationDate);
        this.maxDailyDoseInMg = maxDailyDoseInMg;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;


        Medicine medicine = (Medicine) obj;
        InternalMedicine internalMedicine = (InternalMedicine) obj;

        return (internalMedicine.maxDailyDoseInMg == this.maxDailyDoseInMg)
                && medicine.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%s Max daily dose in mg: %f\n", stringFromSuper, maxDailyDoseInMg);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (int)maxDailyDoseInMg * 13;
    }

    @Override
    public void effect() {

    }

}
