package model;

import java.util.Date;

public class Antibiotic extends Medicine {

    protected boolean isRecipeRequired;

    public boolean getRecipeRequired() {
        return isRecipeRequired;
    }

    public Antibiotic(String name, double price, Date manufactureDate, Date expirationDate, boolean isRecipeRequired) {
        super(name, price, manufactureDate, expirationDate);
        this.isRecipeRequired = isRecipeRequired;
    }

    @Override
    public void someWork() {

    }

}
