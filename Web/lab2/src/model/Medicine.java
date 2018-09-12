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
     * Constructor, creates medicine with name, price and dates
     * @param name name of medicine
     * @param price price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate date when it wil expire
     * @throws IllegalArgumentException if price is bellow 0 or manufactureDate after expirationDate
     */
    public Medicine(String name, double price, Date manufactureDate, Date expirationDate) {
        if (price <= 0 || manufactureDate.after(expirationDate)) {
            throw new IllegalArgumentException();
        }
        this.name = name;
        this.price = price;
        this.expirationDate = expirationDate;
        this.manufactureDate = manufactureDate;
    }

    /**
     * perform some work
     */
    public abstract void someWork();

}
