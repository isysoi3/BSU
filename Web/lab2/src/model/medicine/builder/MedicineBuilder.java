package model.medicine.builder;

import model.medicine.Medicine;
import model.medicine.external.Gell;
import model.medicine.external.Ointment;
import model.medicine.internal.Antibiotic;
import model.medicine.internal.ColorEnum;
import model.medicine.internal.Pill;
import model.medicine.internal.Syrup;

import java.util.Date;

public class MedicineBuilder implements Builder {

    private String name;
    private Double price;
    private Date manufactureDate;
    private Date expirationDate;
    private Double fluidityPercent;
    private Double maxDailyDoseInMg;
    private Boolean isCooling;
    private Boolean isWarming;
    private Integer doseInMg;
    private ColorEnum color;
    private Boolean isRecipeRequired;

    @Override
    public void setName(String name) {
        this.name = name;
    }

    @Override
    public void setPrice(double price) {
        this.price = price;
    }

    @Override
    public void setManufactureDate(Date date) {
        manufactureDate = date;
    }

    @Override
    public void setExpirationDate(Date date) {
        expirationDate = date;
    }

    @Override
    public void setFluidityPercent(double percent) {
        fluidityPercent = percent;
    }

    @Override
    public void setMaxDailyDoseInMg(double dose) {
        maxDailyDoseInMg = dose;
    }

    @Override
    public void isCooling(boolean isCooling) {
        this.isCooling = isCooling;
    }

    @Override
    public void isWarming(boolean isWarming) {
        this.isWarming = isWarming;
    }

    @Override
    public void setDoseInMg(int dose) {
        doseInMg = dose;
    }

    @Override
    public void setColor(ColorEnum color) {
        this.color = color;
    }

    @Override
    public void setRecipeRequired(boolean isRecipeRequired) {
        this.isRecipeRequired = isRecipeRequired;
    }

    @Override
    public void reset() {
        name = null;
        price = null;
        manufactureDate = null;
        expirationDate = null;
        fluidityPercent = null;
        maxDailyDoseInMg = null;
        isCooling = null;
        isWarming = null;
        doseInMg = null;
        color = null;
        isRecipeRequired = null;
    }

    public Medicine getResult() {
        if (name == null
                || price == null
                || manufactureDate == null
                || expirationDate == null) {
            throw new IllegalArgumentException();
        }
        if (fluidityPercent != null) {
            if (isCooling != null) {
                return new Gell(name,
                        price,
                        manufactureDate,
                        expirationDate,
                        fluidityPercent,
                        isCooling);
            } else if (isWarming != null) {
                return  new Ointment(name,
                        price,
                        manufactureDate,
                        expirationDate,
                        fluidityPercent,
                        isWarming);
            } else {
                throw new IllegalArgumentException();
            }
        } else if (maxDailyDoseInMg != null) {
            if (doseInMg != null) {
                return new Pill(name,
                        price,
                        manufactureDate,
                        expirationDate,
                        maxDailyDoseInMg,
                        doseInMg);
            } else if (color != null) {
                return  new Syrup(name,
                        price,
                        manufactureDate,
                        expirationDate,
                        maxDailyDoseInMg,
                        color);
            } else if (isRecipeRequired != null) {
                return  new Antibiotic(name,
                        price,
                        manufactureDate,
                        expirationDate,
                        maxDailyDoseInMg,
                        isRecipeRequired);
            } else {
                throw new IllegalArgumentException();
            }
        }
        throw new IllegalArgumentException();
    }

}


