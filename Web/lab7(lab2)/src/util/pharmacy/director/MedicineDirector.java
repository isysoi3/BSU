package util.pharmacy.director;

import model.medicine.Medicine;
import model.medicine.internal.ColorEnum;
import util.pharmacy.builder.Builder;

import java.util.Date;

/**
 * director that help builder to build medicine items
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class MedicineDirector {

    /**
     * manufacture pill
     *
     * @param builder     to build some medicine
     * @param name        name of medicine
     * @param price the price of medicine
     * @param manufactureDate date of manufacture
     * @param expirationDate date of expiration
     * @param maxDoseInMg max dose in mg to daily use
     * @param doseInMg    dose in one pill
     * @return configured pill
     */
    public Medicine manufacturePill(Builder builder,
                                    String name,
                                    double price,
                                    Date manufactureDate,
                                    Date expirationDate,
                                    double maxDoseInMg,
                                    int doseInMg) {
        builder.setName(name);
        builder.setPrice(price);
        builder.setManufactureDate(manufactureDate);
        builder.setExpirationDate(expirationDate);
        builder.setMaxDailyDoseInMg(maxDoseInMg);
        builder.setDoseInMg(doseInMg);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture antibiotic
     *
     * @param builder          to build some medicine
     * @param name             name of medicine
     * @param price the price of medicine
     * @param manufactureDate date of manufacture
     * @param expirationDate date of expiration
     * @param maxDoseInMg      max dose in mg to daily use
     * @param isRecipeRequired is recipe requeid to buy
     * @return configured antibiotic
     */
    public Medicine manufactureAntibiotic(Builder builder,
                                          String name,
                                          double price,
                                          Date manufactureDate,
                                          Date expirationDate,
                                          double maxDoseInMg,
                                          boolean isRecipeRequired) {
        builder.setName(name);
        builder.setPrice(price);
        builder.setManufactureDate(manufactureDate);
        builder.setExpirationDate(expirationDate);
        builder.setMaxDailyDoseInMg(maxDoseInMg);
        builder.setRecipeRequired(isRecipeRequired);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture syrup
     *
     * @param builder     to build some medicine
     * @param name        name of medicine
     * @param price the price of medicine
     * @param manufactureDate date of manufacture
     * @param expirationDate date of expiration
     * @param maxDoseInMg max dose in mg to daily use
     * @param color       color of syrup
     * @return configured syrup
     */
    public Medicine manufactureSyrup(Builder builder,
                                     String name,
                                     double price,
                                     Date manufactureDate,
                                     Date expirationDate,
                                     double maxDoseInMg,
                                     ColorEnum color) {
        builder.setName(name);
        builder.setPrice(price);
        builder.setManufactureDate(manufactureDate);
        builder.setExpirationDate(expirationDate);
        builder.setMaxDailyDoseInMg(maxDoseInMg);
        builder.setColor(color);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture gell
     *
     * @param builder         to build some medicine
     * @param name            name of medicine
     * @param price the price of medicine
     * @param manufactureDate date of manufacture
     * @param expirationDate date of expiration
     * @param fluidityPercent fluidity percent of medicine
     * @param isCooling       is cooling effect present
     * @return configured gell
     */
    public Medicine manufactureGell(Builder builder,
                                    String name,
                                    double price,
                                    Date manufactureDate,
                                    Date expirationDate,
                                    double fluidityPercent,
                                    boolean isCooling) {
        builder.setName(name);
        builder.setPrice(price);
        builder.setManufactureDate(manufactureDate);
        builder.setExpirationDate(expirationDate);
        builder.setFluidityPercent(fluidityPercent);
        builder.isCooling(isCooling);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture ointment
     *
     * @param builder         to build some medicine
     * @param name            name of medicine
     * @param price the price of medicine
     * @param manufactureDate date of manufacture
     * @param expirationDate date of expiration
     * @param fluidityPercent fluidity percent of medicine
     * @param isWarming       is warming effect present
     * @return configured ointment
     */
    public Medicine manufactureOintment(Builder builder,
                                        String name,
                                        double price,
                                        Date manufactureDate,
                                        Date expirationDate,
                                        double fluidityPercent,
                                        boolean isWarming) {
        builder.setName(name);
        builder.setPrice(price);
        builder.setManufactureDate(manufactureDate);
        builder.setExpirationDate(expirationDate);
        builder.setFluidityPercent(fluidityPercent);
        builder.isWarming(isWarming);
        return builder.buildMedicineItem();
    }
}
