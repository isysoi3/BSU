package model.externalMedicine;

import model.Medicine;

import java.util.Date;

/**
 * a smooth oily preparation that is rubbed on the skin for medicinal purposes
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Ointment extends ExternalMedicine {

    /**
     * percent of being fluid of ointment
     */
    private double fluidityPercent;

    /**
     * getter of fluidity
     * @return fluidity of ointment
     */
    public double getFluidityPercent() {
        return fluidityPercent;
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
    public Ointment(String name, double price, Date manufactureDate, Date expirationDate, double fluidityPercent) {
        super(name, price, manufactureDate, expirationDate);
        this.fluidityPercent = fluidityPercent;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Medicine medicine = (Medicine) obj;
        Ointment ointment = (Ointment) obj;

        return (ointment.fluidityPercent == this.fluidityPercent)
                && medicine.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%s Fluidity percent: %f\n", stringFromSuper, fluidityPercent);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (int)fluidityPercent * 31;
    }

    @Override
    public void effect() {

    }
}
