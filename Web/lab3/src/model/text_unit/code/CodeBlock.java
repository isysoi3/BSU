package model.text_unit.code;

import model.text_unit.text.TextUnit;
import model.text_unit.text.TextUnitTypeEnum;

import java.util.ArrayList;

public class CodeBlock extends TextUnit {

    public static final String DIVIDER_START = "<code>";
    public static final String DIVIDER_END = "</code>";
    private ArrayList<CodeLine> code;


    public CodeBlock(String value ){
        super( TextUnitTypeEnum.CODE_BLOCK);
        code = new ArrayList<>();
    }

    @Override
    public String toString() {
        StringBuilder textToString = new StringBuilder(DIVIDER_START);
        for (CodeLine codeLine : code) {
            textToString.append(codeLine.toString() + "/n");
        }
        textToString.append(DIVIDER_END);
        return textToString.toString();
    }
}
