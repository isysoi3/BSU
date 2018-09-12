package model;

import java.util.Date;

/**
 * abstract class which describes medicine
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public abstract class Medicine {

    /**
     * name of medicine
     */
    protected String name;

    /**
     * getter of name
     * @return name of medicine
     */
    public String getName() {
        return name;
    }

    /**
     * price of medicine
     */
    protected double price;

    /**
     * getter of price
     * @return price of medicine
     */
    public double getPrice() {
        return price;
    }

    /**
     * the date when medicine was produced
     */
    protected Date manufactureDate;

    /**
     * getter of production date
     * @return date of production
     */
    public Date getManufactureDate() {
        return manufactureDate;
    }

    /**
     * the date when medicine will expire
     */
    protected Date expirationDate;

    /**
     * getter of expiration date
     * @return date of expiration
     */
    public Date getExpirationDate() {
        return expirationDate;
    }

    /**
     * perform some work
     */
    public abstract void someWork();

}
