package controller.builder;

import model.medicine.Medicine;
import model.medicine.external.Gell;
import model.medicine.external.Ointment;
import model.medicine.internal.Antibiotic;
import model.medicine.internal.ColorEnum;
import model.medicine.internal.Pill;
import model.medicine.internal.Syrup;

import java.util.Date;

/**
 * medicine builder
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class MedicineBuilder implements Builder {

    /**
     * name of medicine
     */
    private String name;

    /**
     * price of medicine
     */
    private Double price;

    /**
     * manufacture date of medicine
     */
    private Date manufactureDate;

    /**
     * expiration date of medicine
     */
    private Date expirationDate;

    /**
     * fluidity percent of medicine
     */
    private Double fluidityPercent;

    /**
     * max daily dose in mg of medicine
     */
    private Double maxDailyDoseInMg;

    /**
     * is cooling makeEffect
     */
    private Boolean isCooling;

    /**
     * is warming makeEffect
     */
    private Boolean isWarming;

    /**
     * dose in mg of medicine
     */
    private Integer doseInMg;

    /**
     * color of medicine
     */
    private ColorEnum color;

    /**
     * is recipe required
     */
    private Boolean isRecipeRequired;

    /**
     * set name
     */
    @Override
    public void setName(String name) {
        this.name = name;
    }

    /**
     * set price
     */
    @Override
    public void setPrice(double price) {
        this.price = price;
    }

    /**
     * set manufacture date
     */
    @Override
    public void setManufactureDate(Date date) {
        manufactureDate = date;
    }

    /**
     * set expiration date
     */
    @Override
    public void setExpirationDate(Date date) {
        expirationDate = date;
    }

    /**
     * set fluidity percent
     */
    @Override
    public void setFluidityPercent(double percent) {
        fluidityPercent = percent;
    }

    /**
     * set max daily dose in mg
     */
    @Override
    public void setMaxDailyDoseInMg(double dose) {
        maxDailyDoseInMg = dose;
    }

    /**
     * set is colling makeEffect
     */
    @Override
    public void isCooling(boolean isCooling) {
        this.isCooling = isCooling;
    }

    /**
     * set is warming makeEffect
     */
    @Override
    public void isWarming(boolean isWarming) {
        this.isWarming = isWarming;
    }

    /**
     * set dose in mg
     */
    @Override
    public void setDoseInMg(int dose) {
        doseInMg = dose;
    }

    /**
     * set color
     */
    @Override
    public void setColor(ColorEnum color) {
        this.color = color;
    }

    /**
     * set is recipe required to buy
     */
    @Override
    public void setRecipeRequired(boolean isRecipeRequired) {
        this.isRecipeRequired = isRecipeRequired;
    }

    /**
     * make all fields as null
     */
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

    /**
     * configure Medicine item
     *
     * @return medicine item with configured fields
     * @throws IllegalArgumentException if some fields doesn`t set
     */
    public Medicine buildMedicineItem() {
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
                return new Ointment(name,
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
                return new Syrup(name,
                        price,
                        manufactureDate,
                        expirationDate,
                        maxDailyDoseInMg,
                        color);
            } else if (isRecipeRequired != null) {
                return new Antibiotic(name,
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


