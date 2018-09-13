package model;

import java.util.Date;

/**
 * a thick sweet liquid made by dissolving sugar in boiling water, often used for preserving fruit
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Syrup extends Medicine {

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
    public void someWork() {

    }
}
