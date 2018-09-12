package model;

import java.util.Date;

public class Antibiotic extends Medicine {

    protected boolean isRecipeRequired;

    public boolean getRecipeRequired() {
        return isRecipeRequired;
    }

    public Antibiotic(String name, double price, Date manufactureDate, Date expirationDate, boolean isRecipeRequired) {
        super(name, price, manufactureDate, expirationDate);
        isRecipeRequired = true;
    }

    @Override
    public void someWork() {

    }

}
