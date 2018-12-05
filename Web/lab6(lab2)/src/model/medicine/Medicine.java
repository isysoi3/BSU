package model.medicine;

import java.io.Serializable;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * abstract class which describes medicine
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public abstract class Medicine implements Serializable {

    /**
     * name of medicine
     */
    protected String name;

    /**
     * getter of name
     *
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
     *
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
     *
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
     *
     * @return date of expiration
     */
    public Date getExpirationDate() {
        return expirationDate;
    }


    /**
     * Constructor, creates medicine with name, price and dates
     *
     * @param name            name of medicine
     * @param price           price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate  date when it wil expire
     * @throws IllegalArgumentException if price is bellow 0 or manufactureDate after expirationDate
     */
    protected Medicine(String name, double price, Date manufactureDate, Date expirationDate) {
        if (price <= 0 || manufactureDate.after(expirationDate)) {
            throw new IllegalArgumentException();
        }
        this.name = name;
        this.price = price;
        this.expirationDate = expirationDate;
        this.manufactureDate = manufactureDate;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) return false;
        if (this == obj) return true;
        if (getClass() != obj.getClass()) return false;

        Medicine medicine = (Medicine) obj;

        return price == medicine.price
                && name.equals(medicine.name)
                && expirationDate.equals(medicine.expirationDate)
                && manufactureDate.equals(medicine.manufactureDate);
    }

    @Override
    public String toString() {
        Format formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

        return String.format("Name: %s\nPrice: %.2f\nManufacture date: %s\nExpiration date: %s\n",
                name, price, formatter.format(manufactureDate), formatter.format(expirationDate));
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result += 31 * (result + expirationDate.hashCode() + manufactureDate.hashCode() + price);
        return result;
    }

    /**
     * perform some work
     *
     * @return some string of medicine effect
     */
    public abstract String makeEffect();


}
