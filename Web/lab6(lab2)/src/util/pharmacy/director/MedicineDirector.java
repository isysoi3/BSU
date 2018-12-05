package util.pharmacy.director;

import util.pharmacy.builder.Builder;
import model.medicine.Medicine;
import model.medicine.internal.ColorEnum;

import java.time.LocalDate;
import java.time.ZoneId;
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
     * @param builder     to build some medicine
     * @param name        name of medicine
     * @param maxDoseInMg max dose in mg to daily use
     * @param doseInMg    dose in one pill
     * @return configured pill
     */
    public Medicine manufacturePill(Builder builder, String name, double maxDoseInMg, int doseInMg) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(Date.from(
                LocalDate.now().plusDays(5).atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
        builder.setMaxDailyDoseInMg(maxDoseInMg);
        builder.setDoseInMg(doseInMg);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture antibiotic
     *
     * @param builder          to build some medicine
     * @param name             name of medicine
     * @param maxDoseInMg      max dose in mg to daily use
     * @param isRecipeRequired is recipe requeid to buy
     * @return configured antibiotic
     */
    public Medicine manufactureAntibiotic(Builder builder, String name, double maxDoseInMg, boolean isRecipeRequired) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(Date.from(
                LocalDate.now().plusDays(8).atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
        builder.setMaxDailyDoseInMg(maxDoseInMg);
        builder.setRecipeRequired(isRecipeRequired);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture syrup
     *
     * @param builder     to build some medicine
     * @param name        name of medicine
     * @param maxDoseInMg max dose in mg to daily use
     * @param color       color of syrup
     * @return configured syrup
     */
    public Medicine manufactureSyrup(Builder builder, String name, double maxDoseInMg, ColorEnum color) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(Date.from(
                LocalDate.now().plusDays(6).atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
        builder.setMaxDailyDoseInMg(maxDoseInMg);
        builder.setColor(color);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture gell
     *
     * @param builder         to build some medicine
     * @param name            name of medicine
     * @param fluidityPercent fluidity percent of medicine
     * @param isCooling       is cooling effect present
     * @return configured gell
     */
    public Medicine manufactureGell(Builder builder, String name, double fluidityPercent, boolean isCooling) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(Date.from(
                LocalDate.now().plusDays(11).atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
        builder.setFluidityPercent(fluidityPercent);
        builder.isCooling(isCooling);
        return builder.buildMedicineItem();
    }

    /**
     * manufacture ointment
     *
     * @param builder         to build some medicine
     * @param name            name of medicine
     * @param fluidityPercent fluidity percent of medicine
     * @param isWarming       is warming effect present
     * @return configured ointment
     */
    public Medicine manufactureOintment(Builder builder, String name, double fluidityPercent, boolean isWarming) {
        builder.setName(name);
        builder.setPrice(random.nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(Date.from(
                LocalDate.now().plusDays(9).atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
        builder.setFluidityPercent(fluidityPercent);
        builder.isWarming(isWarming);
        return builder.buildMedicineItem();
    }
}
