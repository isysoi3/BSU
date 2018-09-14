package model.medicine.external;

import model.medicine.Medicine;

import java.util.Date;

/**
 * a smooth oily preparation that is rubbed on the skin for medicinal purposes
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Ointment extends ExternalMedicine {

    private boolean isWarming;

    public boolean isWarming() {
        return isWarming;
    }


    /**
     * Constructor, creates medicine with name, price and dates
     * @param name name of medicine
     * @param price price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate date when it wil expire
     * @param fluidityPercent percent of being fluidK
     * @throws IllegalArgumentException if price is bellow 0 or manufactureDate after expirationDate
     */
    public Ointment(String name, double price, Date manufactureDate, Date expirationDate, double fluidityPercent, boolean isWarming) {
        super(name, price, manufactureDate, expirationDate, fluidityPercent);
        this.isWarming = isWarming;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        ExternalMedicine externalMedicine = (ExternalMedicine) obj;
        Ointment ointment = (Ointment) obj;

        return (ointment.isWarming == this.isWarming)
                && externalMedicine.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%s Tmp: %b\n", stringFromSuper, isWarming);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isWarming ? 2 : -2 ) * 13;
    }

    @Override
    public void effect() {

    }

}
