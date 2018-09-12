package model;

import java.util.Date;

public abstract class Medicine {

    protected String name;

    public String getName() {
        return name;
    }

    protected double price;

    public double getPrice() {
        return price;
    }

    protected Date manufactureDate;

    public Date getManufactureDate() {
        return manufactureDate;
    }


    protected Date expirationDate;

    public Date getExpirationDate() {
        return expirationDate;
    }

    public  abstract void someWork();

}


class Test extends Medicine {


    protected ManufactureTypeEnum manufactureType;

    public ManufactureTypeEnum getManufactureType() {
        return manufactureType;
    }


    protected MedicineСonsistencyTypeEnum сonsistencyType;

    public MedicineСonsistencyTypeEnum getСonsistencyType() {
        return сonsistencyType;
    }

    protected Boolean isRecipeRequired;

    public Boolean getRecipeRequired() {
        return isRecipeRequired;
    }

    @Override
    public void someWork() {

    }
}

//TODO: write it
enum ManufactureTypeEnum {
    HOME,
    TMP
}

//TODO: write it
enum MedicineСonsistencyTypeEnum {
    liqued,
    TMP
}