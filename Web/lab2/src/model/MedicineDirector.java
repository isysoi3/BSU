package model;

import model.medicine.Medicine;
import model.medicine.builder.Builder;
import model.medicine.internal.ColorEnum;

import java.util.Date;
import java.util.Random;

public class MedicineDirector {

    public Medicine manufacturePill(Builder builder) {
        builder.setName("pill");
        builder.setPrice((new Random()).nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setMaxDailyDoseInMg(12);
        builder.setDoseInMg(10);
        return builder.getResult();
    }


    public Medicine manufactureAntibiotic(Builder builder) {
        builder.setName("antibiotic");
        builder.setPrice((new Random()).nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setMaxDailyDoseInMg(12);
        builder.setRecipeRequired(false);
        return builder.getResult();
    }


    public Medicine manufactureSyrup(Builder builder) {
        builder.setName("syrup");
        builder.setPrice((new Random()).nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setMaxDailyDoseInMg(12);
        builder.setColor(ColorEnum.RED);
        return builder.getResult();
    }


    public Medicine manufactureGell(Builder builder) {
        builder.setName("gell");
        builder.setPrice((new Random()).nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setFluidityPercent(12.4);
        builder.isCooling(true);
        return builder.getResult();
    }

    public Medicine manufactureOintment(Builder builder) {
        builder.setName("ointment");
        builder.setPrice((new Random()).nextDouble() % 10 + 1);
        builder.setManufactureDate(new Date());
        builder.setExpirationDate(new Date());
        builder.setFluidityPercent(50.4);
        builder.isWarming(false);
        return builder.getResult();
    }
}
