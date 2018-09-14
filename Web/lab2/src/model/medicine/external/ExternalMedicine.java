package model.medicine.external;

import model.medicine.Medicine;

import java.util.Date;

public class ExternalMedicine extends Medicine {

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


    public ExternalMedicine(String name, double price, Date manufactureDate, Date expirationDate, double fluidityPercent) {
        super(name, price, manufactureDate, expirationDate);
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
