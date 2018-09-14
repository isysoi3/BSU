package model.medicine.external;

import java.util.Date;

public class Gell extends ExternalMedicine {

    private boolean isСooling;

    public boolean isСooling() {
        return isСooling;
    }

    /**
     * Constructor, creates medicine with name, price and dates
     * @param name name of medicine
     * @param price price of medicine
     * @param manufactureDate date when it was produced
     * @param expirationDate date when it wil expire
     * @param fluidityPercent percent of being fluidK
     * @throws IllegalArgumentException if price is bellow 0 or manufactureDate after expirationDate
     */
    public Gell(String name, double price, Date manufactureDate, Date expirationDate, double fluidityPercent, boolean isСooling) {
        super(name, price, manufactureDate, expirationDate, fluidityPercent);
        this.isСooling = isСooling;
    }

    @Override
    public void effect() {

    }

}
