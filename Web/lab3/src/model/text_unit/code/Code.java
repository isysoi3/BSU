package model.text_unit.code;

import model.text_unit.text.TextUnit;
import model.text_unit.text.TextUnitTypeEnum;

public class Code extends TextUnit {

    public static final String DIVIDER = "<code>";
    public static final String DIVIDERS_PATTERN = DIVIDER;

    public Code( String value ){
        super( TextUnitTypeEnum.CODE );
    }

}
