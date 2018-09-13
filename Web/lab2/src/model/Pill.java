package model;

import java.util.Date;

/**
 * a small round mass of solid medicine to be swallowed whole.
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Pill extends Medicine {

    /**
     * the weight of active additives
     */
    private int doseInMg;

    /**
     * getter of dose in pill
     * @return weight of active additives
     */
    public int getDoseInMg() {
        return doseInMg;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     * @param name name of medicine
     * @param price price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate date when it wil expire
     * @param doseInMg weight of active additives
     * @throws IllegalArgumentException if price is bellow 0 or manufactureDate after expirationDate
     */
    public Pill(String name, double price, Date manufactureDate, Date expirationDate, int doseInMg) {
        super(name, price, manufactureDate, expirationDate);
        this.doseInMg = doseInMg;
    }

    @Override
    public void someWork() {

    }
}
