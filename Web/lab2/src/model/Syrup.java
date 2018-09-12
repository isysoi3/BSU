package model;

import java.util.Date;

public class Syrup extends Medicine {

    private ColorEnum color;

    public ColorEnum getColor() {
        return color;
    }

    public Syrup(String name, double price, Date manufactureDate, Date expirationDate, ColorEnum color) {
        super(name, price, manufactureDate, expirationDate);
        this.color = color;
    }

    @Override
    public void someWork() {

    }
}
