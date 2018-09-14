package model.medicine.internal;

import model.medicine.Medicine;

import java.util.Date;

/**
 * a small round mass of solid medicine to be swallowed whole.
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
     * @return weight of active additives
     */
    public int getDoseInMg() {
        return doseInMg;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     * @param name name of medicine
     * @param price price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate date when it wil expire
     * @param doseInMg weight of active additives
     * @throws IllegalArgumentException if price is bellow 0 or manufactureDate after expirationDate
     */
    public Pill(String name, double price, Date manufactureDate, Date expirationDate, int doseInMg) {
        super(name, price, manufactureDate, expirationDate);
        this.doseInMg = doseInMg;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Medicine medicine = (Medicine) obj;
        Pill pill = (Pill) obj;

        return (pill.doseInMg == this.doseInMg)
                && medicine.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%s Dose in mg: %d\n", stringFromSuper, doseInMg);
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