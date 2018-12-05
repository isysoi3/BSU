package model.medicine.external;

import java.util.Date;

/**
 * a smooth oily preparation that is rubbed on the skin for medicinal purposes
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Ointment extends ExternalMedicine {

    /**
     * is warming effect of ointment
     */
    private boolean isWarming;


    /**
     * getter of warming effect
     *
     * @return is warming
     */
    public boolean isWarming() {
        return isWarming;
    }


    /**
     * Constructor, creates medicine with name, price and dates
     *
     * @param name            name of medicine
     * @param price           price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate  date when it wil expire
     * @param fluidityPercent percent of being fluidK
     * @param isWarming       makeEffect of ointment that warm
     */
    public Ointment(String name, double price, Date manufactureDate, Date expirationDate, double fluidityPercent, boolean isWarming) {
        super(name, price, manufactureDate, expirationDate, fluidityPercent);
        this.isWarming = isWarming;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (this == obj) return true;
        if (getClass() != obj.getClass()) return false;

        Ointment ointment = (Ointment) obj;

        return (ointment.isWarming == this.isWarming)
                && super.equals(obj);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sIs warming: %b\n", stringFromSuper, isWarming);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isWarming ? 2 : -2) * 13;
    }

    @Override
    public String makeEffect() {
        var string = String.format("Ointment is making effect, it will care your external wound %s", (isWarming ? " and warm it" : ""));
        return string;
    }

}
