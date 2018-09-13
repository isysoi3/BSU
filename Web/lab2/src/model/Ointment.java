package model;

import java.util.Date;

public class Ointment extends Medicine {

    private double fluidity;

    public double getFluidity() {
        return fluidity;
    }


    public Ointment(String name, double price, Date manufactureDate, Date expirationDate, double fluidity) {
        super(name, price, manufactureDate, expirationDate);
        this.fluidity = fluidity;
    }

    @Override
    public void someWork() {

    }
}
