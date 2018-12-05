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
    private double doseInMg;

    /**
     * getter of dose in pill
     *
     * @return weight of active additives
     */
    public double getDoseInMg() {
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
     * @throws IllegalArgumentException if dose in mg is bellow 0
     */
    public Pill(String name, double price, Date manufactureDate, Date expirationDate, double maxDailyDoseInMg, double doseInMg) {
        super(name, price, manufactureDate, expirationDate, maxDailyDoseInMg);
        if (doseInMg < 0) {
            throw new IllegalArgumentException();
        }
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
        return String.format("%sDose in mg: %.2f\n", stringFromSuper, doseInMg);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (int) doseInMg * 13;
    }

    @Override
    public String makeEffect() {
        var string = String.format("Pill is making effect, it will care your illness");
        return string;
    }
}