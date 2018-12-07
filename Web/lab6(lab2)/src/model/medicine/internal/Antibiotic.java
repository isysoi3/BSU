package model.medicine.internal;

import java.util.Date;

/**
 * a medicine (such as penicillin or its derivatives) that inhibits the growth of or destroys microorganisms.
 *
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
     *
     * @return true if necessity, false in other way
     */
    public boolean isRecipeRequired() {
        return isRecipeRequired;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     *
     * @param name             name of medicine
     * @param price            price of medicine
     * @param manufactureDate  date when it was produced
     * @param expirationDate   date when it wil expire
     * @param maxDailyDoseInMg maximum daily dose that can be accepted
     * @param isRecipeRequired show if doctor should prescribe it to person
     */
    public Antibiotic(String name, double price, Date manufactureDate, Date expirationDate, double maxDailyDoseInMg, boolean isRecipeRequired) {
        super(name, price, manufactureDate, expirationDate, maxDailyDoseInMg);
        this.isRecipeRequired = isRecipeRequired;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (this == obj) return true;
        if (getClass() != obj.getClass()) return false;

        Antibiotic antibiotic = (Antibiotic) obj;

        return (antibiotic.isRecipeRequired == this.isRecipeRequired)
                && super.equals(obj);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sIs recipe required: %b\n", stringFromSuper, isRecipeRequired);
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + (isRecipeRequired ? 13 : 17) * 31;
    }

    @Override
    public String makeEffect() {
        var string = String.format("Antibiotic is making very fast effect, it will care your illness");
        return string;
    }

}
