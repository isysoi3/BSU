package model.medicine.internal;

import java.util.Date;

/**
 * a thick sweet liquid made by dissolving sugar in boiling water, often used for preserving fruit
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Syrup extends InternalMedicine {

    /**
     * the color of liquid
     */
    private ColorEnum color;

    /**
     * getter of color
     *
     * @return color from ColorEnum
     */
    public ColorEnum getColor() {
        return color;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     *
     * @param name             name of medicine
     * @param price            price of medicine
     * @param manufactureDate  date when it was produced
     * @param expirationDate   date when it wil expire
     * @param maxDailyDoseInMg maximum daily dose that can be accepted
     * @param color            the color of liquid
     */
    public Syrup(String name, double price, Date manufactureDate, Date expirationDate, double maxDailyDoseInMg, ColorEnum color) {
        super(name, price, manufactureDate, expirationDate, maxDailyDoseInMg);
        this.color = color;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (this == obj) return true;
        if (getClass() != obj.getClass()) return false;

        Syrup syrup = (Syrup) obj;

        return (syrup.color == this.color)
                && super.equals(obj);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%sColor: %s\n", stringFromSuper, color.toString());
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + color.toString().hashCode();
    }

    @Override
    public String makeEffect() {
        var string = String.format("Syrup is making effect, it will care your illness");
        return string;
    }
}
