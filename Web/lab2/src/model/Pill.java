package model;

import java.util.Date;

public class Pill extends Medicine {

    private int doseInMg;

    public int getDoseInMg() {
        return doseInMg;
    }

    public Pill(String name, double price, Date manufactureDate, Date expirationDate, int doseInMg) {
        super(name, price, manufactureDate, expirationDate);
        this.doseInMg = doseInMg;
    }

    @Override
    public void someWork() {

    }
}
