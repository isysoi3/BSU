package model.medicine.internal;

import model.medicine.Medicine;

import java.util.Date;

public class InternalMedicine extends Medicine {

    public InternalMedicine(String name, double price, Date manufactureDate, Date expirationDate) {
        super(name, price, manufactureDate, expirationDate);
    }

    @Override
    public void effect() {

    }

}
