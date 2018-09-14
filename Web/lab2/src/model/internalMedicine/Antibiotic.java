package model.internalMedicine;

import model.Medicine;

import java.util.Date;

/**
 * a medicine (such as penicillin or its derivatives) that inhibits the growth of or destroys microorganisms.
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Antibiotic extends InternalMedicine {

    /**
     * the field that show is recipe from doctor to buy it required
     */
    protected boolean isRecipeRequired;

    /**
     * getter of recipe necessity
     * @return true if necessity, false in other way
     */
    public boolean getRecipeRequired() {
        return isRecipeRequired;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     * @param name name of medicine
     * @param price price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate date when it wil expire
     * @param isRecipeRequired show if doctor should prescribe it to person
     * @throws IllegalArgumentException if price is bellow 0 or manufactureDate after expirationDate
     */
    public Antibiotic(String name, double price, Date manufactureDate, Date expirationDate, boolean isRecipeRequired) {
        super(name, price, manufactureDate, expirationDate);
        this.isRecipeRequired = isRecipeRequired;
    }

    @Override
    public void effect() {

    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Medicine medicine = (Medicine) obj;
        Antibiotic antibiotic = (Antibiotic) obj;

        return (antibiotic.isRecipeRequired == this.isRecipeRequired)
                && medicine.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%s Is recipe required: %b\n", stringFromSuper, isRecipeRequired);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isRecipeRequired ? 13 : 17) * 31;
    }

}
