package model;

import java.util.Date;

public abstract class Medicine {

    double price;

    Date manufactureDate;

    Date expirationDate;

    ManufactureTypeEnum manufactureType;

    MedicineСonsistencyTypeEnum сonsistencyType;

    Boolean isRecipeRequired;

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