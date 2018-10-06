package model.text_unit.code;

import model.text_unit.text.TextUnit;
import model.text_unit.text.TextUnitTypeEnum;

import java.util.ArrayList;

public class CodeLine extends TextUnit {

    public static final String DIVIDER = "<code>";
    public static final String DIVIDER_START = "<code>";
    public static final String DIVIDER_END = "</code>";
    public static final String DIVIDERS_PATTERN = DIVIDER;
    private String codeLine;

    public CodeLine(String value ){
        super( TextUnitTypeEnum.CODE_LINE );
        codeLine = value;
    }

}
