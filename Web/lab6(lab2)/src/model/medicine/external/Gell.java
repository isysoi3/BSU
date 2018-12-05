package model.medicine.external;

import java.util.Date;

/**
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Gell extends ExternalMedicine {

    /**
     * cooling effect of gell
     */
    private boolean isCooling;

    /**
     * getter of cooling effect
     *
     * @return is cooling
     */
    public boolean isСooling() {
        return isCooling;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     *
     * @param name            name of medicine
     * @param price           price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate  date when it wil expire
     * @param fluidityPercent percent of being fluid
     * @param isСooling       makeEffect of gell that cool
     */
    public Gell(String name, double price, Date manufactureDate, Date expirationDate, double fluidityPercent, boolean isСooling) {
        super(name, price, manufactureDate, expirationDate, fluidityPercent);
        this.isCooling = isСooling;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        ExternalMedicine externalMedicine = (ExternalMedicine) obj;
        Gell gell = (Gell) obj;

        return (gell.isCooling == this.isCooling)
                && externalMedicine.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sIs cooling: %b\n", stringFromSuper, isCooling);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isCooling ? 1 : -1) * 31;
    }

    @Override
    public String makeEffect() {
        var string = String.format("Gell is making effect, it will care external your external wound %s", (isCooling ? " and cool it" : ""));
        return string;
    }

}
