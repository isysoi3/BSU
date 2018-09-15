package model.medicine.external;

import model.medicine.Medicine;

import java.util.Date;

/**
 * abstract class of external medicine
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public abstract class ExternalMedicine extends Medicine {

    /**
     * percent of being fluid of ointment
     */
    protected double fluidityPercent;

    /**
     * getter of fluidity
     *
     * @return fluidity
     */
    public double getFluidityPercent() {
        return fluidityPercent;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     *
     * @param name            name of medicine
     * @param price           price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate  date when it wil expire
     * @param fluidityPercent percent of being fluidK
     * @throws IllegalArgumentException if fluidityPercent is bellow 0 or more than 100
     */
    protected ExternalMedicine(String name, double price, Date manufactureDate, Date expirationDate, double fluidityPercent) {
        super(name, price, manufactureDate, expirationDate);
        if (fluidityPercent < 0 && fluidityPercent > 100) {
            throw new IllegalArgumentException();
        }
        this.fluidityPercent = fluidityPercent;
    }


    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Medicine medicine = (Medicine) obj;
        ExternalMedicine externalMedicine = (ExternalMedicine) obj;

        return (externalMedicine.fluidityPercent == this.fluidityPercent)
                && medicine.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sFluidity percent: %.2f\n", stringFromSuper, fluidityPercent);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (int) fluidityPercent * 31;
    }

}
