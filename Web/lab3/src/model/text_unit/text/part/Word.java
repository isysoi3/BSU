package model.text_unit.text.part;

import model.text_unit.text.TextUnit;
import model.text_unit.text.TextUnitTypeEnum;

public class Word extends TextUnit {

    public static final String WORD_NAME = "WORD";
    public static final String DIVIDER = ",:;'\"";
    public static final String DELIM_FOR_COMBINING = " ";
    public static final String PATTERN = "[^ " + Paragraph.DIVIDER + Sentence.DIVIDER + DIVIDER +  "]+";
    private String text;

    public Word(String text) {
        super(TextUnitTypeEnum.WORD);
        this.text = text;
    }

    @Override
    public String toString() {
        return text;
    }

}
