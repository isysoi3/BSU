package model.medicine.internal;

import model.medicine.Medicine;

import java.util.Date;

/**
 * abstract class of internal medicine
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public abstract class InternalMedicine extends Medicine {

    /**
     * maximum daily dose that can be accepted
     */
    protected double maxDailyDoseInMg;

    /**
     * getter of daily dose
     *
     * @return daily dose in mg
     */
    public double getMaxDailyDoseInMg() {
        return maxDailyDoseInMg;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     *
     * @param name             name of medicine
     * @param price            price of medicine
     * @param manufactureDate  date when it was produced
     * @param expirationDate   date when it wil expire
     * @param maxDailyDoseInMg maximum daily dose that can be accepted
     * @throws IllegalArgumentException if maxDailyDoseInMg is bellow 0
     */
    protected InternalMedicine(String name, double price, Date manufactureDate, Date expirationDate, double maxDailyDoseInMg) {
        super(name, price, manufactureDate, expirationDate);
        if (maxDailyDoseInMg < 0)
            throw new IllegalArgumentException();
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
        return String.format("%sMax daily dose in mg: %.2f\n", stringFromSuper, maxDailyDoseInMg);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (int) maxDailyDoseInMg * 13;
    }

}
