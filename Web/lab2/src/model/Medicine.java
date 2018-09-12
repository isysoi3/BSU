package model;

import java.util.Date;

public abstract class Medicine {

    protected String name;

    public String getName() {
        return name;
    }

    protected double price;

    public double getPrice() {
        return price;
    }

    protected Date manufactureDate;

    public Date getManufactureDate() {
        return manufactureDate;
    }


    protected Date expirationDate;

    public Date getExpirationDate() {
        return expirationDate;
    }

    public  abstract void someWork();

}
