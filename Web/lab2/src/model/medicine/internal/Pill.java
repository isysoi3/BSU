package model.medicine.internal;

import java.util.Date;

/**
 * a small round mass of solid medicine to be swallowed whole.
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Pill extends InternalMedicine {

    /**
     * the weight of active additives
     */
    private int doseInMg;

    /**
     * getter of dose in pill
     *
     * @return weight of active additives
     */
    public int getDoseInMg() {
        return doseInMg;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     *
     * @param name             name of medicine
     * @param price            price of medicine
     * @param manufactureDate  date when it was produced
     * @param expirationDate   date when it wil expire
     * @param maxDailyDoseInMg maximum daily dose that can be accepted
     * @param doseInMg         weight of active additives
     */
    public Pill(String name, double price, Date manufactureDate, Date expirationDate, double maxDailyDoseInMg, int doseInMg) {
        super(name, price, manufactureDate, expirationDate, maxDailyDoseInMg);
        this.doseInMg = doseInMg;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        InternalMedicine internalMedicine = (InternalMedicine) obj;
        Pill pill = (Pill) obj;

        return (pill.doseInMg == this.doseInMg)
                && internalMedicine.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sDose in mg: %d\n", stringFromSuper, doseInMg);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + doseInMg * 31;
    }

    @Override
    public void effect() {

    }
}