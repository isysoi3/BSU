package model.externalMedicine;

import model.Medicine;

import java.util.Date;

public class ExternalMedicine extends Medicine {

    public ExternalMedicine(String name, double price, Date manufactureDate, Date expirationDate) {
        super(name, price, manufactureDate, expirationDate);
    }

    @Override
    public void effect() {

    }

}
