package util.pharmacy.builder;

import model.medicine.Medicine;
import model.medicine.internal.ColorEnum;

import java.util.Date;

/**
 * Builder interface
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public interface Builder {

    void setName(String name);

    void setPrice(double price);

    void setManufactureDate(Date date);

    void setExpirationDate(Date date);

    void setFluidityPercent(double percent);

    void setMaxDailyDoseInMg(double dose);

    void isCooling(boolean isCooling);

    void isWarming(boolean isWarming);

    void setDoseInMg(int dose);

    void setColor(ColorEnum color);

    void setRecipeRequired(boolean isRecipeRequired);

    void reset();

    Medicine buildMedicineItem();
}
