package model.medicine.internal;

import model.medicine.Medicine;

import java.util.Date;

/**
 * a thick sweet liquid made by dissolving sugar in boiling water, often used for preserving fruit
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
     * @return color from ColorEnum
     */
    public ColorEnum getColor() {
        return color;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     * @param name name of medicine
     * @param price price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate date when it wil expire
     * @param color the color of liquid
     * @throws IllegalArgumentException if price is bellow 0 or manufactureDate after expirationDate
     */
    public Syrup(String name, double price, Date manufactureDate, Date expirationDate, ColorEnum color) {
        super(name, price, manufactureDate, expirationDate);
        this.color = color;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Medicine medicine = (Medicine) obj;
        Syrup syrup = (Syrup) obj;

        return (syrup.color == this.color)
                && medicine.equals(this);
    }

    @Override
    public String toString() {
        String stringFromSuper = super.toString();
        return String.format("%s Color: %s\n", stringFromSuper, color.toString());
    }

    @Override
    public int hashCode() {
        int hashCodeFromSuper = super.hashCode();
        return hashCodeFromSuper + color.toString().hashCode();
    }

    @Override
    public void effect() {

    }
}
