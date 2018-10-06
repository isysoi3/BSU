package model.text_unit.text.part;

import model.text_unit.text.TextUnitTypeEnum;
import model.text_unit.text.TextUnit;

public class Paragraph extends TextUnit {

    public static final String PARAGRAPH_NAME = "PARAGRAPH";
    public static final String DIVIDER = "\n";
    public static final String DIVIDER_PATTERN = DIVIDER;

    public Paragraph() {
        super(TextUnitTypeEnum.PARAGRAPH);
    }

    @Override
    public String toString() {
        return "\n";
    }

}
