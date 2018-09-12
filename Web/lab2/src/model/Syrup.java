package model;

import java.util.Date;

public class Syrup extends Medicine {

    private ColorEnum color;

    public ColorEnum getColor() {
        return color;
    }

    enum ColorEnum {
        RED {
            public String toString() {
                return "red";
            }
        },
        GREEN {
            public String toString() {
                return "green";
            }
        },
        YELLOW {
            public String toString() {
                return "yellow";
            }
        }
    }

    public Syrup(String name, double price, Date manufactureDate, Date expirationDate, ColorEnum color) {
        super(name, price, manufactureDate, expirationDate);
        this.color = color;
    }

    @Override
    public void someWork() {

    }
}
