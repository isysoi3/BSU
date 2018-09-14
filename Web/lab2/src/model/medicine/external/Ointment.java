package model.medicine.external;

import model.medicine.Medicine;

import java.util.Date;

/**
 * a smooth oily preparation that is rubbed on the skin for medicinal purposes
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class Ointment extends ExternalMedicine {

    /**
     * Constructor, creates medicine with name, price and dates
     * @param name name of medicine
     * @param price price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate date when it wil expire
     * @param fluidityPercent percent of being fluidK
     * @throws IllegalArgumentException if price is bellow 0 or manufactureDate after expirationDate
     */
    public Ointment(String name, double price, Date manufactureDate, Date expirationDate, double fluidityPercent) {
        super(name, price, manufactureDate, expirationDate, fluidityPercent);
    }

    @Override
    public void effect() {

    }
}
