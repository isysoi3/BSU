package model;

import model.medicine.Medicine;
import model.medicine.builder.Builder;
import model.medicine.internal.ColorEnum;

import java.util.Date;
import java.util.Random;

/**
 * director that help builder to build medicine items
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public class MedicineDirector {

    private Random random = new Random();

    /**
     * manufacture pill
     *
     * @return configured pill
     */
    public Medicine manufacturePill(Builder builder) {
        builder.setName("pill");
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setMaxDailyDoseInMg(12);
        builder.setDoseInMg(10);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture antibiotic
     *
     * @return configured antibiotic
     */
    public Medicine manufactureAntibiotic(Builder builder) {
        builder.setName("antibiotic");
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setMaxDailyDoseInMg(12);
        builder.setRecipeRequired(false);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture syrup
     *
     * @return configured syrup
     */
    public Medicine manufactureSyrup(Builder builder) {
        builder.setName("syrup");
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setMaxDailyDoseInMg(12);
        builder.setColor(ColorEnum.RED);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture gell
     *
     * @return configured gell
     */
    public Medicine manufactureGell(Builder builder) {
        builder.setName("gell");
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setFluidityPercent(12.4);
        builder.isCooling(true);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture ointment
     *
     * @return configured ointment
     */
    public Medicine manufactureOintment(Builder builder) {
        builder.setName("ointment");
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setFluidityPercent(50.4);
        builder.isWarming(false);
        return builder.buildMedicineItem();
    }
}
